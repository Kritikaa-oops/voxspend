#include "BackendManager.h"

#include <QCryptographicHash>
#include <QDir>
#include <QLoggingCategory>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QUuid>
#include <QVariantMap>
#include <regex>

using namespace std;

vector<User> g_users = {};
User g_currentUser = {};
string g_lastAuthError = "";
vector<Expense> g_expenses = {};
int g_nextId = 1;
string g_lastExpenseError = "";

namespace {
const char* kConnectionName = "voxspend_auth";

QString authDatabasePath()
{
    const QString folder = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(folder);
    return folder + "/voxspend200.sqlite";
}

void setAuthError(const QString& message)
{
    g_lastAuthError = message.toStdString();
    qWarning().noquote() << "Authentication failed:" << message;
}
}

bool isValidEmail(const string& email)
{
    const regex pattern(R"(^[\w.+-]+@[\w.-]+\.[A-Za-z]{2,}$)");
    return regex_match(email, pattern);
}

BackendManager::BackendManager(QObject* parent) : QObject(parent)
{
    m_databaseReady = initializeDatabase();
}

bool BackendManager::initializeDatabase()
{
    QSqlDatabase database = QSqlDatabase::contains(kConnectionName)
        ? QSqlDatabase::database(kConnectionName)
        : QSqlDatabase::addDatabase("QSQLITE", kConnectionName);
    database.setDatabaseName(authDatabasePath());
    if (!database.open()) {
        m_databaseError = database.lastError().text();
        qCritical().noquote() << "Authentication database could not open:" << m_databaseError;
        return false;
    }

    QSqlQuery query(database);
    if (!query.exec("CREATE TABLE IF NOT EXISTS users ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "name TEXT NOT NULL, "
                    "email TEXT NOT NULL UNIQUE COLLATE NOCASE, "
                    "password_salt TEXT NOT NULL, "
                    "password_hash TEXT NOT NULL, "
                    "created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP)")) {
        m_databaseError = query.lastError().text();
        qCritical().noquote() << "Authentication database setup failed:" << m_databaseError;
        return false;
    }
    if (!query.exec("CREATE TABLE IF NOT EXISTS expenses ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "user_id INTEGER NOT NULL, "
                    "title TEXT NOT NULL, "
                    "amount REAL NOT NULL CHECK(amount > 0), "
                    "category TEXT NOT NULL, "
                    "expense_date TEXT NOT NULL, "
                    "note TEXT, "
                    "created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP, "
                    "FOREIGN KEY(user_id) REFERENCES users(id) ON DELETE CASCADE)")) {
        m_databaseError = query.lastError().text();
        qCritical().noquote() << "Expense database setup failed:" << m_databaseError;
        return false;
    }
    qInfo().noquote() << "Authentication database ready:" << database.databaseName();
    return true;
}

QString BackendManager::passwordHash(const QString& password, const QString& salt) const
{
    return QString::fromLatin1(QCryptographicHash::hash(
        (salt + ":" + password).toUtf8(), QCryptographicHash::Sha256).toHex());
}

bool BackendManager::signup(const QString& nameInput, const QString& emailInput, const QString& password, const QString& confirmPassword)
{
    clearAuthError();
    const QString name = nameInput.trimmed();
    const QString email = emailInput.trimmed().toLower();
    if (!m_databaseReady) { setAuthError("Account storage is unavailable. " + m_databaseError); return false; }
    if (name.isEmpty() || email.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) { setAuthError("Complete every field to create your account."); return false; }
    if (name.length() < 2 || name.length() > 60) { setAuthError("Name must be between 2 and 60 characters."); return false; }
    if (!isValidEmail(email.toStdString())) { setAuthError("Enter a valid email address."); return false; }
    if (password.length() < 8) { setAuthError("Password must contain at least 8 characters."); return false; }
    if (password != confirmPassword) { setAuthError("Passwords do not match."); return false; }

    const QString salt = QUuid::createUuid().toString(QUuid::WithoutBraces);
    QSqlQuery query(QSqlDatabase::database(kConnectionName));
    query.prepare("INSERT INTO users (name, email, password_salt, password_hash) VALUES (?, ?, ?, ?)");
    query.addBindValue(name); query.addBindValue(email); query.addBindValue(salt); query.addBindValue(passwordHash(password, salt));
    if (!query.exec()) {
        if (query.lastError().nativeErrorCode() == "19") setAuthError("An account already exists for this email.");
        else setAuthError("Could not create your account. Please try again.");
        qWarning().noquote() << "Signup database error:" << query.lastError().text();
        return false;
    }
    g_currentUser.name = name.toStdString();
    g_currentUser.email = email.toStdString();
    g_currentUser.password.clear();
    m_currentUserId = query.lastInsertId().toInt();
    ++m_dataRevision;
    emit dataChanged();
    qInfo().noquote() << "Account created for" << email;
    return true;
}

bool BackendManager::login(const QString& emailInput, const QString& password)
{
    clearAuthError();
    const QString email = emailInput.trimmed().toLower();
    if (!m_databaseReady) { setAuthError("Account storage is unavailable. " + m_databaseError); return false; }
    if (email.isEmpty() || password.isEmpty()) { setAuthError("Enter your email and password."); return false; }
    if (!isValidEmail(email.toStdString())) { setAuthError("Enter a valid email address."); return false; }

    QSqlQuery query(QSqlDatabase::database(kConnectionName));
    query.prepare("SELECT id, name, email, password_salt, password_hash FROM users WHERE email = ?");
    query.addBindValue(email);
    if (!query.exec()) { setAuthError("Could not sign in. Please try again."); qWarning() << query.lastError(); return false; }
    if (!query.next() || passwordHash(password, query.value(3).toString()) != query.value(4).toString()) {
        setAuthError("Email or password is incorrect.");
        return false;
    }
    m_currentUserId = query.value(0).toInt();
    g_currentUser.name = query.value(1).toString().toStdString();
    g_currentUser.email = query.value(2).toString().toStdString();
    g_currentUser.password.clear();
    ++m_dataRevision;
    emit dataChanged();
    qInfo().noquote() << "Sign in succeeded for" << email;
    return true;
}

QString BackendManager::getLastAuthError() const { return QString::fromStdString(g_lastAuthError); }
void BackendManager::clearAuthError() { g_lastAuthError.clear(); }
bool BackendManager::isDatabaseReady() const { return m_databaseReady; }
QString BackendManager::currentUserName() const { return QString::fromStdString(g_currentUser.name); }
QString BackendManager::currentUserEmail() const { return QString::fromStdString(g_currentUser.email); }
void BackendManager::logout() { m_currentUserId = -1; g_currentUser = {}; ++m_dataRevision; emit dataChanged(); qInfo() << "User signed out"; }

bool BackendManager::updateProfile(const QString& nameInput, const QString& emailInput)
{
    clearAuthError();
    const QString name = nameInput.trimmed();
    const QString email = emailInput.trimmed().toLower();
    if (m_currentUserId < 0) { setAuthError("Sign in before updating your profile."); return false; }
    if (name.length() < 2 || name.length() > 60) { setAuthError("Name must be between 2 and 60 characters."); return false; }
    if (!isValidEmail(email.toStdString())) { setAuthError("Enter a valid email address."); return false; }
    QSqlQuery query(QSqlDatabase::database(kConnectionName));
    query.prepare("UPDATE users SET name = ?, email = ? WHERE id = ?"); query.addBindValue(name); query.addBindValue(email); query.addBindValue(m_currentUserId);
    if (!query.exec()) { setAuthError(query.lastError().nativeErrorCode() == "19" ? "An account already exists for this email." : "Could not update your profile."); qWarning() << "Profile update failed:" << query.lastError(); return false; }
    g_currentUser.name = name.toStdString(); g_currentUser.email = email.toStdString();
    ++m_dataRevision;
    emit dataChanged();
    qInfo().noquote() << "Profile updated for user" << m_currentUserId;
    return true;
}

bool BackendManager::addExpense(const QString& title, double amount, const QString& category, const QString& date, const QString& note)
{
    g_lastExpenseError.clear();
    if (m_currentUserId < 0) { g_lastExpenseError = "Sign in before adding an expense."; return false; }
    if (title.trimmed().isEmpty()) { g_lastExpenseError = "Expense title is required."; return false; }
    if (amount <= 0) { g_lastExpenseError = "Expense amount must be greater than zero."; return false; }
    if (category.trimmed().isEmpty()) { g_lastExpenseError = "Select an expense category."; return false; }
    QSqlQuery query(QSqlDatabase::database(kConnectionName));
    query.prepare("INSERT INTO expenses (user_id, title, amount, category, expense_date, note) VALUES (?, ?, ?, ?, ?, ?)");
    query.addBindValue(m_currentUserId); query.addBindValue(title.trimmed()); query.addBindValue(amount); query.addBindValue(category.trimmed()); query.addBindValue(date); query.addBindValue(note.trimmed());
    if (!query.exec()) { g_lastExpenseError = "Could not save the expense. Please try again."; qWarning() << "Expense insert failed:" << query.lastError(); return false; }
    ++m_dataRevision;
    emit dataChanged();
    qInfo().noquote() << "Expense saved for user" << m_currentUserId << "category" << category;
    return true;
}

QString BackendManager::getLastExpenseError() { return QString::fromStdString(g_lastExpenseError); }
void BackendManager::clearExpenseError() { g_lastExpenseError.clear(); }

QVariantList BackendManager::getExpenses() const
{
    QVariantList expenses;
    if (m_currentUserId < 0) return expenses;
    QSqlQuery query(QSqlDatabase::database(kConnectionName));
    query.prepare("SELECT id, title, amount, category, expense_date, COALESCE(note, '') FROM expenses WHERE user_id = ? ORDER BY expense_date DESC, id DESC");
    query.addBindValue(m_currentUserId);
    if (!query.exec()) { qWarning() << "Expense read failed:" << query.lastError(); return expenses; }
    while (query.next()) {
        QVariantMap row;
        row["id"] = query.value(0); row["title"] = query.value(1); row["amount"] = query.value(2); row["category"] = query.value(3); row["date"] = query.value(4); row["note"] = query.value(5);
        expenses.append(row);
    }
    return expenses;
}

QVariantList BackendManager::getCategoryTotals() const
{
    QVariantList categories;
    if (m_currentUserId < 0) return categories;
    QSqlQuery query(QSqlDatabase::database(kConnectionName));
    query.prepare("SELECT category, ROUND(SUM(amount), 2) FROM expenses WHERE user_id = ? GROUP BY category ORDER BY SUM(amount) DESC");
    query.addBindValue(m_currentUserId);
    if (!query.exec()) { qWarning() << "Category read failed:" << query.lastError(); return categories; }
    while (query.next()) { QVariantMap row; row["category"] = query.value(0); row["amount"] = query.value(1); categories.append(row); }
    return categories;
}

double BackendManager::getMonthlyTotal() const
{
    if (m_currentUserId < 0) return 0;
    QSqlQuery query(QSqlDatabase::database(kConnectionName));
    query.prepare("SELECT COALESCE(SUM(amount), 0) FROM expenses WHERE user_id = ? AND substr(expense_date, 1, 7) = strftime('%Y-%m', 'now', 'localtime')");
    query.addBindValue(m_currentUserId);
    return query.exec() && query.next() ? query.value(0).toDouble() : 0;
}

int BackendManager::getExpenseCount() const
{
    if (m_currentUserId < 0) return 0;
    QSqlQuery query(QSqlDatabase::database(kConnectionName)); query.prepare("SELECT COUNT(*) FROM expenses WHERE user_id = ?"); query.addBindValue(m_currentUserId);
    return query.exec() && query.next() ? query.value(0).toInt() : 0;
}

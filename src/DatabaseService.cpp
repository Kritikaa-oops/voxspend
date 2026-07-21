#include "DatabaseService.h"

#include <QCryptographicHash>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QUuid>
#include <QVariantMap>
#include <QLoggingCategory>
#include <regex>

namespace {

bool isValidEmail(const std::string& email)
{
    static const std::regex pattern(R"(^[\w.+-]+@[\w.-]+\.[A-Za-z]{2,}$)");
    return std::regex_match(email, pattern);
}

} // namespace

SQLiteDataStore::SQLiteDataStore() = default;

QString SQLiteDataStore::databasePath() const
{
    const QString folder = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(folder);
    return folder + "/voxspend200.sqlite";
}

QString SQLiteDataStore::passwordHash(const QString& password, const QString& salt) const
{
    return QString::fromLatin1(QCryptographicHash::hash(
        (salt + ":" + password).toUtf8(), QCryptographicHash::Sha256).toHex());
}

bool SQLiteDataStore::initializeDatabase(QString& errorMessage)
{
    QSqlDatabase database = QSqlDatabase::contains(kConnectionName)
        ? QSqlDatabase::database(kConnectionName)
        : QSqlDatabase::addDatabase("QSQLITE", kConnectionName);
    database.setDatabaseName(databasePath());
    if (!database.open()) {
        errorMessage = database.lastError().text();
        qCritical().noquote() << "Authentication database could not open:" << errorMessage;
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
        errorMessage = query.lastError().text();
        qCritical().noquote() << "Authentication database setup failed:" << errorMessage;
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
        errorMessage = query.lastError().text();
        qCritical().noquote() << "Expense database setup failed:" << errorMessage;
        return false;
    }
    qInfo().noquote() << "Authentication database ready:" << database.databaseName();
    return true;
}

bool SQLiteDataStore::createUser(const QString& name, const QString& email, const QString& password, int& userId, QString& errorMessage)
{
    if (name.trimmed().isEmpty() || email.trimmed().isEmpty() || password.isEmpty()) {
        errorMessage = "Complete every field to create your account.";
        return false;
    }
    if (name.length() < 2 || name.length() > 60) {
        errorMessage = "Name must be between 2 and 60 characters.";
        return false;
    }
    if (!isValidEmail(email.toStdString())) {
        errorMessage = "Enter a valid email address.";
        return false;
    }
    if (password.length() < 8) {
        errorMessage = "Password must contain at least 8 characters.";
        return false;
    }

    const QString salt = QUuid::createUuid().toString(QUuid::WithoutBraces);
    QSqlQuery query(QSqlDatabase::database(kConnectionName));
    query.prepare("INSERT INTO users (name, email, password_salt, password_hash) VALUES (?, ?, ?, ?)");
    query.addBindValue(name.trimmed());
    query.addBindValue(email.trimmed().toLower());
    query.addBindValue(salt);
    query.addBindValue(passwordHash(password, salt));
    if (!query.exec()) {
        errorMessage = query.lastError().nativeErrorCode() == "19"
            ? "An account already exists for this email."
            : "Could not create your account. Please try again.";
        qWarning().noquote() << "Signup database error:" << query.lastError().text();
        return false;
    }
    userId = query.lastInsertId().toInt();
    return true;
}

bool SQLiteDataStore::authenticateUser(const QString& email, const QString& password, int& userId, QString& name, QString& storedEmail, QString& errorMessage)
{
    if (email.isEmpty() || password.isEmpty()) {
        errorMessage = "Enter your email and password.";
        return false;
    }
    if (!isValidEmail(email.toStdString())) {
        errorMessage = "Enter a valid email address.";
        return false;
    }

    QSqlQuery query(QSqlDatabase::database(kConnectionName));
    query.prepare("SELECT id, name, email, password_salt, password_hash FROM users WHERE email = ?");
    query.addBindValue(email.trimmed().toLower());
    if (!query.exec()) {
        errorMessage = "Could not sign in. Please try again.";
        qWarning() << query.lastError();
        return false;
    }
    if (!query.next() || passwordHash(password, query.value(3).toString()) != query.value(4).toString()) {
        errorMessage = "Email or password is incorrect.";
        return false;
    }
    userId = query.value(0).toInt();
    name = query.value(1).toString();
    storedEmail = query.value(2).toString();
    return true;
}

bool SQLiteDataStore::updateUserProfile(int userId, const QString& name, const QString& email, QString& errorMessage)
{
    if (name.length() < 2 || name.length() > 60) {
        errorMessage = "Name must be between 2 and 60 characters.";
        return false;
    }
    if (!isValidEmail(email.toStdString())) {
        errorMessage = "Enter a valid email address.";
        return false;
    }

    QSqlQuery query(QSqlDatabase::database(kConnectionName));
    query.prepare("UPDATE users SET name = ?, email = ? WHERE id = ?");
    query.addBindValue(name.trimmed());
    query.addBindValue(email.trimmed().toLower());
    query.addBindValue(userId);
    if (!query.exec()) {
        errorMessage = query.lastError().nativeErrorCode() == "19"
            ? "An account already exists for this email."
            : "Could not update your profile.";
        qWarning() << "Profile update failed:" << query.lastError();
        return false;
    }
    return true;
}

bool SQLiteDataStore::addExpenseEntry(int userId, const QString& title, double amount, const QString& category, const QString& date, const QString& note, QString& errorMessage)
{
    if (title.trimmed().isEmpty()) {
        errorMessage = "Expense title is required.";
        return false;
    }
    if (amount <= 0) {
        errorMessage = "Expense amount must be greater than zero.";
        return false;
    }
    if (category.trimmed().isEmpty()) {
        errorMessage = "Select an expense category.";
        return false;
    }

    QSqlQuery query(QSqlDatabase::database(kConnectionName));
    query.prepare("INSERT INTO expenses (user_id, title, amount, category, expense_date, note) VALUES (?, ?, ?, ?, ?, ?)");
    query.addBindValue(userId);
    query.addBindValue(title.trimmed());
    query.addBindValue(amount);
    query.addBindValue(category.trimmed());
    query.addBindValue(date);
    query.addBindValue(note.trimmed());
    if (!query.exec()) {
        errorMessage = "Could not save the expense. Please try again.";
        qWarning() << "Expense insert failed:" << query.lastError();
        return false;
    }
    return true;
}

QVariantList SQLiteDataStore::loadExpenses(int userId) const
{
    QVariantList expenses;
    QSqlQuery query(QSqlDatabase::database(kConnectionName));
    query.prepare("SELECT id, title, amount, category, expense_date, COALESCE(note, '') FROM expenses WHERE user_id = ? ORDER BY expense_date DESC, id DESC");
    query.addBindValue(userId);
    if (!query.exec()) {
        qWarning() << "Expense read failed:" << query.lastError();
        return expenses;
    }
    while (query.next()) {
        QVariantMap row;
        row["id"] = query.value(0);
        row["title"] = query.value(1);
        row["amount"] = query.value(2);
        row["category"] = query.value(3);
        row["date"] = query.value(4);
        row["note"] = query.value(5);
        expenses.append(row);
    }
    return expenses;
}

QVariantList SQLiteDataStore::loadCategoryTotals(int userId) const
{
    QVariantList categories;
    QSqlQuery query(QSqlDatabase::database(kConnectionName));
    query.prepare("SELECT category, ROUND(SUM(amount), 2) FROM expenses WHERE user_id = ? GROUP BY category ORDER BY SUM(amount) DESC");
    query.addBindValue(userId);
    if (!query.exec()) {
        qWarning() << "Category read failed:" << query.lastError();
        return categories;
    }
    while (query.next()) {
        QVariantMap row;
        row["category"] = query.value(0);
        row["amount"] = query.value(1);
        categories.append(row);
    }
    return categories;
}

double SQLiteDataStore::loadMonthlyTotal(int userId) const
{
    QSqlQuery query(QSqlDatabase::database(kConnectionName));
    query.prepare("SELECT COALESCE(SUM(amount), 0) FROM expenses WHERE user_id = ? AND substr(expense_date, 1, 7) = strftime('%Y-%m', 'now', 'localtime')");
    query.addBindValue(userId);
    return query.exec() && query.next() ? query.value(0).toDouble() : 0;
}

int SQLiteDataStore::loadExpenseCount(int userId) const
{
    QSqlQuery query(QSqlDatabase::database(kConnectionName));
    query.prepare("SELECT COUNT(*) FROM expenses WHERE user_id = ?");
    query.addBindValue(userId);
    return query.exec() && query.next() ? query.value(0).toInt() : 0;
}

bool SQLiteDataStore::clearExpenses(int userId, QString& errorMessage)
{
    QSqlQuery query(QSqlDatabase::database(kConnectionName));
    query.prepare("DELETE FROM expenses WHERE user_id = ?");
    query.addBindValue(userId);
    if (!query.exec()) {
        errorMessage = query.lastError().text();
        qWarning() << "Expense reset failed:" << query.lastError();
        return false;
    }
    return true;
}

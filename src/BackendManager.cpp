#include "BackendManager.h"
#include "DatabaseService.h"

#include <QLoggingCategory>
#include <QVariantMap>

using namespace std;

// ==========================================
// GLOBAL SESSION & STATE MANAGEMENT
// ==========================================
vector<User> g_users = {};
User g_currentUser = {};
string g_lastAuthError = "";
vector<Expense> g_expenses = {};
int g_nextId = 1;
string g_lastExpenseError = "";

namespace {

// Helper function to centralize authentication error logging
void setAuthError(const QString& message)
{
    g_lastAuthError = message.toStdString();
    qWarning().noquote() << "Authentication failed:" << message;
}

} // namespace

// ==========================================
// CONSTRUCTOR & DATABASE INITIALIZATION
// ==========================================
BackendManager::BackendManager(QObject* parent) : QObject(parent)
{
    // OOP Concept: Composition - Instantiating SQLite storage engine
    m_dataStore = new SQLiteDataStore();
    m_databaseReady = initializeDatabase();
}

bool BackendManager::initializeDatabase()
{
    QString errorMessage;
    m_databaseReady = m_dataStore->initializeDatabase(errorMessage);
    if (!m_databaseReady) {
        m_databaseError = errorMessage;
        qCritical().noquote() << "Authentication database could not open:" << m_databaseError;
    }
    return m_databaseReady;
}

// ==========================================
// USER AUTHENTICATION MODULE (SIGNUP / LOGIN)
// ==========================================

// Handles new user creation and persists records in SQLite
bool BackendManager::signup(const QString& nameInput, const QString& emailInput, const QString& password, const QString& confirmPassword)
{
    clearAuthError();
    const QString name = nameInput.trimmed();
    const QString email = emailInput.trimmed().toLower();
    
    // Input & Database availability validation
    if (!m_databaseReady) { setAuthError("Account storage is unavailable. " + m_databaseError); return false; }
    if (password != confirmPassword) { setAuthError("Passwords do not match."); return false; }

    QString errorMessage;
    int userId = -1;
    if (!m_dataStore->createUser(name, email, password, userId, errorMessage)) {
        setAuthError(errorMessage);
        return false;
    }

    // Update active user session state
    g_currentUser.name = name.toStdString();
    g_currentUser.email = email.toStdString();
    g_currentUser.password.clear(); // Clear sensitive plain-text password from memory
    m_currentUserId = userId;
    
    // Notify QML frontend of data changes
    ++m_dataRevision;
    emit dataChanged();
    qInfo().noquote() << "Account created for" << email;
    return true;
}

// Authenticates user credentials against the database
bool BackendManager::login(const QString& emailInput, const QString& password)
{
    clearAuthError();
    const QString email = emailInput.trimmed().toLower();
    if (!m_databaseReady) { setAuthError("Account storage is unavailable. " + m_databaseError); return false; }

    QString errorMessage;
    QString userName;
    QString storedEmail;
    int userId = -1;
    
    if (!m_dataStore->authenticateUser(email, password, userId, userName, storedEmail, errorMessage)) {
        setAuthError(errorMessage);
        return false;
    }
    
    // Set active session variables upon successful authentication
    m_currentUserId = userId;
    g_currentUser.name = userName.toStdString();
    g_currentUser.email = storedEmail.toStdString();
    g_currentUser.password.clear();
    
    // Trigger UI refresh signal
    ++m_dataRevision;
    emit dataChanged();
    qInfo().noquote() << "Sign in succeeded for" << email;
    return true;
}

// ==========================================
// SESSION & ERROR ACCESSORS (QML BRIDGES)
// ==========================================
QString BackendManager::getLastAuthError() const { return QString::fromStdString(g_lastAuthError); }
void BackendManager::clearAuthError() { g_lastAuthError.clear(); }
bool BackendManager::isDatabaseReady() const { return m_databaseReady; }
QString BackendManager::currentUserName() const { return QString::fromStdString(g_currentUser.name); }
QString BackendManager::currentUserEmail() const { return QString::fromStdString(g_currentUser.email); }

// Clears active user session data on logout
void BackendManager::logout() { 
    m_currentUserId = -1; 
    g_currentUser = {}; 
    ++m_dataRevision; 
    emit dataChanged(); 
    qInfo() << "User signed out"; 
}

// ==========================================
// USER PROFILE MANAGEMENT
// ==========================================
bool BackendManager::updateProfile(const QString& nameInput, const QString& emailInput)
{
    clearAuthError();
    const QString name = nameInput.trimmed();
    const QString email = emailInput.trimmed().toLower();
    if (m_currentUserId < 0) { setAuthError("Sign in before updating your profile."); return false; }

    QString errorMessage;
    if (!m_dataStore->updateUserProfile(m_currentUserId, name, email, errorMessage)) {
        setAuthError(errorMessage);
        return false;
    }
    g_currentUser.name = name.toStdString(); 
    g_currentUser.email = email.toStdString();
    ++m_dataRevision;
    emit dataChanged();
    qInfo().noquote() << "Profile updated for user" << m_currentUserId;
    return true;
}

// ==========================================
// EXPENSE MANAGEMENT MODULE
// ==========================================

// Creates and stores a new expense record linked to m_currentUserId
bool BackendManager::addExpense(const QString& title, double amount, const QString& category, const QString& date, const QString& note)
{
    g_lastExpenseError.clear();
    if (m_currentUserId < 0) { g_lastExpenseError = "Sign in before adding an expense."; return false; }

    QString errorMessage;
    if (!m_dataStore->addExpenseEntry(m_currentUserId, title, amount, category, date, note, errorMessage)) {
        g_lastExpenseError = errorMessage.toStdString();
        return false;
    }
    
    // Increments revision counter to update analytical UI components
    ++m_dataRevision;
    emit dataChanged();
    qInfo().noquote() << "Expense saved for user" << m_currentUserId << "category" << category;
    return true;
}

QString BackendManager::getLastExpenseError() { return QString::fromStdString(g_lastExpenseError); }
void BackendManager::clearExpenseError() { g_lastExpenseError.clear(); }

// Accessors returning structured QVariantList data to QML UI components
QVariantList BackendManager::getExpenses() const
{
    if (m_currentUserId < 0) return {};
    return m_dataStore->loadExpenses(m_currentUserId);
}

QVariantList BackendManager::getCategoryTotals() const
{
    if (m_currentUserId < 0) return {};
    return m_dataStore->loadCategoryTotals(m_currentUserId);
}

double BackendManager::getMonthlyTotal() const
{
    if (m_currentUserId < 0) return 0;
    return m_dataStore->loadMonthlyTotal(m_currentUserId);
}

int BackendManager::getExpenseCount() const
{
    if (m_currentUserId < 0) return 0;
    return m_dataStore->loadExpenseCount(m_currentUserId);
}

// Resets all expense records belonging to the currently logged-in user
void BackendManager::resetExpenses()
{
    if (m_currentUserId < 0) return;
    QString errorMessage;
    if (!m_dataStore->clearExpenses(m_currentUserId, errorMessage)) {
        qWarning() << "Expense reset failed:" << errorMessage;
        return;
    }
    ++m_dataRevision;
    emit dataChanged();
    qInfo().noquote() << "Expenses reset for user" << m_currentUserId;
}
#ifndef BACKEND_MANAGER_H
#define BACKEND_MANAGER_H

#include <QObject>
#include <QString>
#include <vector>
#include <string>
#include <QVariantList>

class QSqlDatabase;

// Include your expense struct definition
#include "expense.h"

class BackendManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(int dataRevision READ dataRevision NOTIFY dataChanged)
public:
    explicit BackendManager(QObject *parent = nullptr);

    // Authentication Modules
    Q_INVOKABLE bool login(const QString& email, const QString& password);
    Q_INVOKABLE bool signup(const QString& name, const QString& email, const QString& password, const QString& confirmPassword);
    Q_INVOKABLE QString getLastAuthError() const;
    Q_INVOKABLE void clearAuthError();
    Q_INVOKABLE bool isDatabaseReady() const;
    Q_INVOKABLE QString currentUserName() const;
    Q_INVOKABLE QString currentUserEmail() const;
    Q_INVOKABLE void logout();
    Q_INVOKABLE bool updateProfile(const QString& name, const QString& email);

    // Expense Tracking Modules
    Q_INVOKABLE bool addExpense(const QString& title, double amount, const QString& category, const QString& date, const QString& note);
    Q_INVOKABLE QString getLastExpenseError();
    Q_INVOKABLE void clearExpenseError();
    Q_INVOKABLE QVariantList getExpenses() const;
    Q_INVOKABLE QVariantList getCategoryTotals() const;
    Q_INVOKABLE double getMonthlyTotal() const;
    Q_INVOKABLE int getExpenseCount() const;
    Q_INVOKABLE void resetExpenses();
    int dataRevision() const { return m_dataRevision; }

signals:
    void dataChanged();

private:
    bool initializeDatabase();
    QString passwordHash(const QString& password, const QString& salt) const;
    QString m_databaseError;
    bool m_databaseReady = false;
    int m_currentUserId = -1;
    int m_dataRevision = 0;
};

// GLOBAL DATA DECLARATIONS (Shared across files)
extern std::vector<User> g_users;
extern User g_currentUser;
extern std::string g_lastAuthError;

extern std::vector<Expense> g_expenses;
extern int g_nextId;
extern std::string g_lastExpenseError;

// FIXED: Expose the email validator function to other .cpp files
bool isValidEmail(const std::string& email);

#endif // BACKEND_MANAGER_H

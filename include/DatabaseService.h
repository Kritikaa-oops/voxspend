#ifndef DATABASESERVICE_H
#define DATABASESERVICE_H

#include <QString>
#include <QVariantList>

class IDataStore {
public:
    virtual ~IDataStore() = default;

    virtual bool initializeDatabase(QString& errorMessage) = 0;
    virtual bool createUser(const QString& name, const QString& email, const QString& password, int& userId, QString& errorMessage) = 0;
    virtual bool authenticateUser(const QString& email, const QString& password, int& userId, QString& name, QString& storedEmail, QString& errorMessage) = 0;
    virtual bool updateUserProfile(int userId, const QString& name, const QString& email, QString& errorMessage) = 0;
    virtual bool addExpenseEntry(int userId, const QString& title, double amount, const QString& category, const QString& date, const QString& note, QString& errorMessage) = 0;
    virtual QVariantList loadExpenses(int userId) const = 0;
    virtual QVariantList loadCategoryTotals(int userId) const = 0;
    virtual double loadMonthlyTotal(int userId) const = 0;
    virtual int loadExpenseCount(int userId) const = 0;
    virtual bool clearExpenses(int userId, QString& errorMessage) = 0;
};

class SQLiteDataStore : public IDataStore {
public:
    explicit SQLiteDataStore();

    bool initializeDatabase(QString& errorMessage) override;
    bool createUser(const QString& name, const QString& email, const QString& password, int& userId, QString& errorMessage) override;
    bool authenticateUser(const QString& email, const QString& password, int& userId, QString& name, QString& storedEmail, QString& errorMessage) override;
    bool updateUserProfile(int userId, const QString& name, const QString& email, QString& errorMessage) override;
    bool addExpenseEntry(int userId, const QString& title, double amount, const QString& category, const QString& date, const QString& note, QString& errorMessage) override;
    QVariantList loadExpenses(int userId) const override;
    QVariantList loadCategoryTotals(int userId) const override;
    double loadMonthlyTotal(int userId) const override;
    int loadExpenseCount(int userId) const override;
    bool clearExpenses(int userId, QString& errorMessage) override;

private:
    QString databasePath() const;
    QString passwordHash(const QString& password, const QString& salt) const;

    static constexpr const char* kConnectionName = "voxspend_auth";
};

#endif

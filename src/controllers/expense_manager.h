#ifndef EXPENSE_MANAGER_H
#define EXPENSE_MANAGER_H

#include <QObject>
#include <QVariantList>

#include "database/json_storage.h"

class ExpenseManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList expenses READ expenses NOTIFY dataChanged)
    Q_PROPERTY(double totalSpent READ totalSpent NOTIFY dataChanged)
    Q_PROPERTY(double monthlyLimit READ monthlyLimit WRITE setMonthlyLimit NOTIFY budgetChanged)
    Q_PROPERTY(QString currency READ currency NOTIFY budgetChanged)

public:
    explicit ExpenseManager(QObject *parent = nullptr);

    QVariantList expenses() const;
    double totalSpent() const;
    double monthlyLimit() const;
    QString currency() const;

    Q_INVOKABLE bool addExpense(double amount, const QString &category, const QString &description, const QString &date);
    Q_INVOKABLE bool removeExpense(const QString &id);
    Q_INVOKABLE void setMonthlyLimit(double limit);

signals:
    void dataChanged();
    void budgetChanged();
    void errorOccurred(const QString &message);

private:
    void persist();

    JsonStorage m_storage;
    LedgerData m_ledger;
};

#endif

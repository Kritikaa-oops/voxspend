#include "controllers/expense_manager.h"

#include <QDate>
#include <QUuid>
#include <QVariantMap>

ExpenseManager::ExpenseManager(QObject *parent)
    : QObject(parent),
      m_storage(),
      m_ledger(m_storage.load())
{
}

QVariantList ExpenseManager::expenses() const
{
    QVariantList items;
    for (const ExpenseItem &expense : m_ledger.expenses) {
        QVariantMap item;
        item.insert("id", expense.id());
        item.insert("amount", expense.amount());
        item.insert("category", expense.category());
        item.insert("date", expense.date().toString(Qt::ISODate));
        item.insert("description", expense.description());
        items.append(item);
    }
    return items;
}

double ExpenseManager::totalSpent() const
{
    double total = 0.0;
    for (const ExpenseItem &expense : m_ledger.expenses) {
        total += expense.amount();
    }
    return total;
}

double ExpenseManager::monthlyLimit() const
{
    return m_ledger.monthlyLimit;
}

QString ExpenseManager::currency() const
{
    return m_ledger.currency;
}

bool ExpenseManager::addExpense(double amount, const QString &category, const QString &description, const QString &date)
{
    if (amount <= 0.0) {
        emit errorOccurred("Amount must be greater than zero.");
        return false;
    }

    if (category.trimmed().isEmpty()) {
        emit errorOccurred("Category is required.");
        return false;
    }

    const QDate parsedDate = date.isEmpty()
        ? QDate::currentDate()
        : QDate::fromString(date, Qt::ISODate);

    if (!parsedDate.isValid()) {
        emit errorOccurred("Date must use YYYY-MM-DD format.");
        return false;
    }

    m_ledger.expenses.prepend(ExpenseItem(
        QUuid::createUuid().toString(QUuid::WithoutBraces),
        amount,
        category.trimmed(),
        parsedDate,
        description.trimmed()));

    persist();
    emit dataChanged();
    return true;
}

bool ExpenseManager::removeExpense(const QString &id)
{
    for (qsizetype index = 0; index < m_ledger.expenses.size(); ++index) {
        if (m_ledger.expenses.at(index).id() == id) {
            m_ledger.expenses.removeAt(index);
            persist();
            emit dataChanged();
            return true;
        }
    }

    emit errorOccurred("Expense was not found.");
    return false;
}

void ExpenseManager::setMonthlyLimit(double limit)
{
    if (limit <= 0.0 || qFuzzyCompare(m_ledger.monthlyLimit, limit)) {
        return;
    }

    m_ledger.monthlyLimit = limit;
    persist();
    emit budgetChanged();
    emit dataChanged();
}

void ExpenseManager::persist()
{
    if (!m_storage.save(m_ledger)) {
        emit errorOccurred("Could not save the local ledger.");
    }
}

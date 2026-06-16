#include "models/expense_item.h"

#include <utility>

ExpenseItem::ExpenseItem(QString id, double amount, QString category, QDate date, QString description)
    : m_id(std::move(id)),
      m_amount(amount),
      m_category(std::move(category)),
      m_date(date),
      m_description(std::move(description))
{
}

QString ExpenseItem::id() const
{
    return m_id;
}

double ExpenseItem::amount() const
{
    return m_amount;
}

QString ExpenseItem::category() const
{
    return m_category;
}

QDate ExpenseItem::date() const
{
    return m_date;
}

QString ExpenseItem::description() const
{
    return m_description;
}

QJsonObject ExpenseItem::toJson() const
{
    return {
        {"id", m_id},
        {"amount", m_amount},
        {"category", m_category},
        {"date", m_date.toString(Qt::ISODate)},
        {"description", m_description},
    };
}

ExpenseItem ExpenseItem::fromJson(const QJsonObject &object)
{
    return ExpenseItem(
        object.value("id").toString(),
        object.value("amount").toDouble(),
        object.value("category").toString(),
        QDate::fromString(object.value("date").toString(), Qt::ISODate),
        object.value("description").toString());
}

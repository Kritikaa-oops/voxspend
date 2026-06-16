#ifndef EXPENSE_ITEM_H
#define EXPENSE_ITEM_H

#include <QDate>
#include <QJsonObject>
#include <QString>

class ExpenseItem
{
public:
    ExpenseItem() = default;
    ExpenseItem(QString id, double amount, QString category, QDate date, QString description);

    QString id() const;
    double amount() const;
    QString category() const;
    QDate date() const;
    QString description() const;

    QJsonObject toJson() const;
    static ExpenseItem fromJson(const QJsonObject &object);

private:
    QString m_id;
    double m_amount = 0.0;
    QString m_category;
    QDate m_date;
    QString m_description;
};

#endif

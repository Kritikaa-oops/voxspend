#ifndef JSON_STORAGE_H
#define JSON_STORAGE_H

#include <QList>
#include <QString>

#include "models/expense_item.h"

struct LedgerData
{
    double monthlyLimit = 15000.0;
    QString currency = "NPR";
    QList<ExpenseItem> expenses;
};

class JsonStorage
{
public:
    explicit JsonStorage(QString filePath = QString());

    LedgerData load() const;
    bool save(const LedgerData &ledger) const;
    QString filePath() const;

private:
    QString m_filePath;
};

#endif

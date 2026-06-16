#include "database/json_storage.h"

#include <QDate>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

#include <utility>

namespace {
QString defaultLedgerPath()
{
    const QString dataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dataDir);
    return dataDir + QDir::separator() + "data.json";
}
}

JsonStorage::JsonStorage(QString filePath)
    : m_filePath(filePath.isEmpty() ? defaultLedgerPath() : std::move(filePath))
{
}

LedgerData JsonStorage::load() const
{
    LedgerData ledger;
    QFile file(m_filePath);

    if (!file.exists() || !file.open(QIODevice::ReadOnly)) {
        return ledger;
    }

    const QJsonDocument document = QJsonDocument::fromJson(file.readAll());
    if (!document.isObject()) {
        return ledger;
    }

    const QJsonObject root = document.object();
    const QJsonObject budget = root.value("budget_settings").toObject();
    ledger.monthlyLimit = budget.value("monthly_limit").toDouble(ledger.monthlyLimit);
    ledger.currency = budget.value("currency").toString(ledger.currency);

    const QJsonArray expenses = root.value("expenses").toArray();
    for (const QJsonValue &value : expenses) {
        if (value.isObject()) {
            ledger.expenses.append(ExpenseItem::fromJson(value.toObject()));
        }
    }

    return ledger;
}

bool JsonStorage::save(const LedgerData &ledger) const
{
    QJsonArray expenses;
    for (const ExpenseItem &expense : ledger.expenses) {
        expenses.append(expense.toJson());
    }

    QJsonObject budget{
        {"monthly_limit", ledger.monthlyLimit},
        {"currency", ledger.currency},
        {"last_updated", QDate::currentDate().toString(Qt::ISODate)},
    };

    QJsonObject root{
        {"budget_settings", budget},
        {"expenses", expenses},
    };

    QFile file(m_filePath);
    QDir().mkpath(QFileInfo(m_filePath).absolutePath());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return false;
    }

    file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    return true;
}

QString JsonStorage::filePath() const
{
    return m_filePath;
}

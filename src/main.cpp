#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "controllers/expense_manager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setOrganizationName("VoxSpend");
    app.setApplicationName("VoxSpend");

    ExpenseManager expenseManager;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("expenseManager", &expenseManager);

    const QUrl url(QStringLiteral("qrc:/ui/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}

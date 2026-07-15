#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "BackendManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    BackendManager backend;

    // Registers the BackendManager class so it can be used inside your QML UI files
    qmlRegisterType<BackendManager>("com.voxspend.backend", 1, 0, "BackendManager");
    engine.rootContext()->setContextProperty("backend", &backend);
    engine.rootContext()->setContextProperty("backendManager", &backend);

    const QUrl url(QStringLiteral("qrc:/qt/qml/com/voxspend/backend/Main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app, []() { QCoreApplication::exit(-1); },
                     Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}

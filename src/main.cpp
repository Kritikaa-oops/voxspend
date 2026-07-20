#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQuickControls2/QQuickStyle>
#include "BackendManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Fusion");

    QQmlApplicationEngine engine;
    BackendManager backend;

    // Registers the BackendManager class so it can be used inside your QML UI files
    qmlRegisterType<BackendManager>("com.voxspend200.backend", 1, 0, "BackendManager");
    engine.rootContext()->setContextProperty("backend", &backend);
    engine.rootContext()->setContextProperty("backendManager", &backend);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app, []() { QCoreApplication::exit(-1); },
                     Qt::QueuedConnection);

    engine.loadFromModule("com.voxspend200.backend", "Main");

    return app.exec();
}

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "udp.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<Udp>("mark.udp",1,0,"Udp");
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/testMP/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

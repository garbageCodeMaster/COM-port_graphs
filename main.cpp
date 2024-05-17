#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QtQml>
#include <QIcon>
#include <QQmlContext>
#include "serialportreader.h"
#include <QDebug>
#include <QStringLiteral>
#include <comemulator.h>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qDebug() << "Starting application";

    QQmlApplicationEngine engine;

    qDebug() << "Registering SerialPortReader";
    qmlRegisterType<SerialPortReader>("SerialPortReader", 1, 0, "SerialPortReader");

    // Создаем объект SerialPortReader и добавляем его в QML контекст
    SerialPortReader serialPortReader;
    engine.rootContext()->setContextProperty(QLatin1String("serialPortReader"), &serialPortReader);
    const QUrl url(QStringLiteral("qrc:/COM-port_graphs/Main.qml"));

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);


    engine.load(url);
    qDebug() << "Loading QML file";

    COMemulator emulator;

    qDebug() << "Entering main event loop";
    return app.exec();
}

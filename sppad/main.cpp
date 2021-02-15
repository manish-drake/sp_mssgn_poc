#include <QGuiApplication>
#include <QQmlApplicationEngine>
//#include <query.h>
#include <QQmlContext>
#include <test.h>
#include "listener.h"
#include <thread>
#include "delegate.h"
#include <iostream>
#include "ftpclient.h"
#include <fstream>
#include "messages.h"

using namespace std;
using namespace Messaging;

int main(int argc, char *argv[])

{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QQmlContext* ctx = engine.rootContext();
    // query qr;
    Messaging::Messages::Register("tcp://localhost:8286");
    test tr;
    ctx->setContextProperty("_tr", &tr);


    //   ctx->setContextProperty("_qr", &qr);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    return app.exec();
}

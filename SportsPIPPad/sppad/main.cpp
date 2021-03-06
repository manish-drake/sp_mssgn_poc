#include <QGuiApplication>
#include <QQmlApplicationEngine>
//#include <query.h>
#include <QQmlContext>
#include <viewmodel.h>
#include "listener.h"
#include <thread>
#include "delegate.h"
#include <iostream>
#include "ftpclient.h"
#include <fstream>
#include "messages.h"
#include "../common/network.h"

using namespace std;
using namespace Messaging;

#include "loggerf.h"
#include "loggerc.h"


void initLog()
{
    const char *logOut = getenv("LOG_OUT");
    if(logOut)
    {
        if (strcmp(logOut, "0") == 0)
        {
            Logger::Instance()->Add(new LoggerF);
        }
        else
        {
            Logger::Instance()->Add(new LoggerC);
        }
    }
    else
    {
        Logger::Instance()->Add(new LoggerC("____________________SPORTSPIP COACH____________________"));
        //#ifndef Q_OS_IOS
        Logger::Instance()->Add(new LoggerF("____________________SPORTSPIP COACH____________________"));
        //#endif
    }
}
int main(int argc, char *argv[])

{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    initLog();

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QQmlContext* ctx = engine.rootContext();
    // query qr;

    viewmodel _vm;
    ctx->setContextProperty("vm", &_vm);

    network _net;
    ctx->setContextProperty("net", &_net);
    QObject::connect(&_net, &network::ipSelected, &_vm, &viewmodel::ipSelected);



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

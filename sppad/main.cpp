#include <QGuiApplication>
#include <QQmlApplicationEngine>
//#include <query.h>
#include <QQmlContext>
#include <viewmodel.h>
#include "listener.h"
#include <thread>
#include "delegate.h"
#include <iostream>
#include <fstream>
#include "messages.h"
#include "../common/network.h"
#include <QStandardPaths>
#include <QDir>
#include "../common/threadpool.h"

using namespace std;
using namespace Messaging;

#include "loggerf.h"
#include "loggerc.h"


void initLog(std::string path = "")
{
    const char *logOut = getenv("LOG_OUT");
    if(logOut)
    {
        if (strcmp(logOut, "0") == 0)
        {
            Logger::Instance()->Add(new LoggerF("____________________SPORTSPIP SOURCE____________________", path));
        }
        else
        {
            Logger::Instance()->Add(new LoggerC);
        }
    }
    else
    {
        Logger::Instance()->Add(new LoggerC("____________________SPORTSPIP SOURCE____________________"));
        //#ifndef Q_OS_IOS
        Logger::Instance()->Add(new LoggerF("____________________SPORTSPIP SOURCE____________________", path));
        //#endif
    }
}

int main(int argc, char *argv[])

{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    /***********Initializing Log Location************/
    QString localPath = QStandardPaths::writableLocation( QStandardPaths::AppDataLocation );

    QString appLogFolder = localPath.append("/SportsPIP/Logs");

    QDir dAppMediaFolder(appLogFolder);
    if (!dAppMediaFolder.exists())
    {
        dAppMediaFolder.mkpath(".");
    }
    /************************************************/
    initLog(appLogFolder.toStdString());

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

    auto result = app.exec();
    ThreadPool::Factory()->Join();
    return result;
}

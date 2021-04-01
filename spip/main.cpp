#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "viewmodel.h"
#include "messages.h"
#include "loggerf.h"
#include "loggerc.h"
#include "../common/network.h"
#include <QStandardPaths>
#include <QDir>
#include "../common/threadpool.h"
#include "../common/logmanager.h"


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
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

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

    QQmlApplicationEngine engine;
    auto ctx = engine.rootContext();

    viewmodel _vm;
    ctx->setContextProperty("vm", &_vm);

    LogManager _log;
    ctx->setContextProperty("log", &_log);

    QObject::connect(&_vm, &viewmodel::ftpServerNotified, &_log, &LogManager::ftpServerNotified);

    network _net;
    ctx->setContextProperty("net", &_net);
    QObject::connect(&_net, &network::ipSelected, &_vm, &viewmodel::ipSelected);


    _vm.start();

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

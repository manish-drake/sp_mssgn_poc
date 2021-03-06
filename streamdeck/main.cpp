#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "viewmodel.h"
#include "messages.h"
#include "loggerf.h"
#include "loggerc.h"
#include "../common/network.h"
#include "../common/threadpool.h"


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
        Logger::Instance()->Add(new LoggerC("____________________STREAM-DECK EMU____________________"));
        //#ifndef Q_OS_IOS
        Logger::Instance()->Add(new LoggerF("____________________STREAM-DECK EMU____________________"));
        //#endif
    }
}
int main(int argc, char *argv[])
{
    initLog();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    auto ctx = engine.rootContext();
    viewmodel _vm;
    ctx->setContextProperty("vm", &_vm);

    network _net;
    ctx->setContextProperty("net", &_net);
    QObject::connect(&_net, &network::ipSelected, &_vm, &viewmodel::ipSelected);

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

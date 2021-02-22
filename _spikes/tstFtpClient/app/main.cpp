#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "viewmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    auto ctx = engine.rootContext();
    viewmodel _vm;
    ctx->setContextProperty("vm", &_vm);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

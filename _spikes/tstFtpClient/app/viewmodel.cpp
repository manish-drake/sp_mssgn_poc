#include "viewmodel.h"
#include "ftpclient.h"
#include <thread>
#include <iostream>
#include <QStandardPaths>
#include <QDir>


viewmodel::viewmodel(QObject *parent) : QObject(parent), client{nullptr}
{

}

void viewmodel::run()
{
//    std::thread t([this](QObject* parent){


//    }, this);
//    t.detach();

    client = new FTPClient("192.168.1.2");
//    client->Send("/home/manish/Presentation.odp");
    QString localPath = QStandardPaths::writableLocation( QStandardPaths::MoviesLocation );
    QString appMediaFolder = localPath.append("/SportsPIP/Videos");
    QDir dAppMediaFolder(appMediaFolder);
    if (!dAppMediaFolder.exists()) {
        dAppMediaFolder.mkpath(".");
    }
    auto fileName = appMediaFolder.append("/video1.mp4");
    client->Send(fileName);
}

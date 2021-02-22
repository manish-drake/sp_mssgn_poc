#include "viewmodel.h"
#include "ftpclient.h"
#include <thread>
#include <iostream>


viewmodel::viewmodel(QObject *parent) : QObject(parent), client{nullptr}
{

}

void viewmodel::run()
{
//    std::thread t([this](QObject* parent){


//    }, this);
//    t.detach();

    client = new FTPClient("192.168.1.166");
    client->Send("/home/manish/Presentation.odp");

}

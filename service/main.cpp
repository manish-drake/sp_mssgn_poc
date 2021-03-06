#include <iostream>
#include "messenger.h"
#include "listener.h"
#include <thread>
#include "delegate.h"
#include "worker.h"
#include "messages.h"
#include "logger.h"
#include "loggerf.h"
#include "loggerc.h"
#include "multisender.h"



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
        Logger::Instance()->Add(new LoggerC("____________________SPORTSPIP SERVICE____________________"));
        //#ifndef Q_OS_IOS
        Logger::Instance()->Add(new LoggerF("____________________SPORTSPIP SERVICE____________________"));
        //#endif
    }
}


using namespace std;
using namespace Messaging;
#define UNUSED(x) (void)(x)
int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);
    initLog();
    
    MultiSender broadcaster;
    broadcaster.Start("192.168.10.10");
    
    Worker worker;

    Delegate broker(&worker);


    Listener listener(8285);
    listener.Listen([&](const std::string &msg) {

        std::cout << "Received: " << msg << std::endl;

        broker.OnReceived(msg);
    });
    
    // cin.ignore();
    return 0;
}

#include <iostream>
#include "messenger.h"
#include "listener.h"
#include <thread>
#include <memory>
#include "delegate.h"
#include "worker.h"
#include "messages.h"
#include "logger.h"
#include "loggerf.h"
#include "loggerc.h"
#include "multisender.h"
#include "broadcast.h"
#include "getlocalip.h"

void initLog()
{
    const char *logOut = getenv("LOG_OUT");
    if (logOut)
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
#define PORT 8285
int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);
    initLog();
    std::vector<std::string> localIps;
    std::unique_ptr<GetLocalIP> glip(new GetLocalIP);
    glip->Run(localIps);
    glip.release();

    if (localIps.size() <= 0)
    {
        LOGWARN("Unabe to find any IP address! Many features will not work without that information");
    }
    else
    {
        const std::string &selectedIP = localIps[0];
        LOGINFOZ("Selecting %s for all further communication.", selectedIP.c_str());

        Broadcast::Instance()->Create("0", "0", "00", const_cast<char*>(selectedIP.c_str()));
        MultiSender broadcaster;
        broadcaster.Start(Broadcast::Instance()->data());

        char ep[24] = {};
        sprintf(ep, "%s:%d", selectedIP.c_str(), PORT);
        Messaging::Messages::Register(ep);
    }

    Worker worker;

    Delegate broker(&worker);

    Listener listener(PORT);
    listener.Listen([&](const std::string &msg) {
        std::cout << "Received: " << msg << std::endl;

        broker.OnReceived(msg);
    });

    // cin.ignore();
    return 0;
}

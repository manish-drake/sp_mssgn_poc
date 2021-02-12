#include <iostream>
#include "messenger.h"
#include "filemonitor.h"
#include "listener.h"
#include <thread>
#include "delegate.h"

using namespace std;
using namespace Messaging;
#define UNUSED(x) (void)(x)
int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    Delegate worker;

    FileMonitor monitor([&worker](const std::string &newVideo) {
        worker.Notify(newVideo);
    });

    std::thread tmonitor([&monitor]() {
        while (1)
        {
            monitor.Watch();
        }
    });

    Listener prime([&worker](const std::string &msg) {
        std::cout << "Received: " << msg << std::endl;
        worker.Received(msg);
    });

    std::thread tprime([&prime]() {
        while (1)
        {
            prime.Listen();
        }
    });

    tprime.join();
    tmonitor.join();
    cin.ignore();
    return 0;
}

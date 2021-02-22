#include <iostream>
#include "messenger.h"
#include "listener.h"
#include <thread>
#include "delegate.h"
#include "worker.h"
#include "messages.h"

using namespace std;
using namespace Messaging;
#define UNUSED(x) (void)(x)
int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    
    
    Worker worker;

    Delegate broker(&worker);


    Listener listener(8285);
    listener.Listen([&](const std::string &msg) {

        std::cout << "Received: " << msg << std::endl;

        broker.OnReceived(msg);
    });
    
    // tmonitor.join();
    cin.ignore();
    return 0;
}

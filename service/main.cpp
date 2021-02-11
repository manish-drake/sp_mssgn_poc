#include <iostream>
#include "messenger.h"
#include "filemonitor.h"
#include "listener.h"
#include <thread>
#include "delegate.h"

using namespace std;
#define UNUSED(x) (void)(x)
int main(int argc, char* argv[]){
    UNUSED(argc);
    UNUSED(argv);

    Delegate worker;

    Listener prime([&worker](const std::string &msg){
        std::cout << "Received: " << msg << std::endl;
        worker.Received(msg);
    });

    std::thread t([&prime](){
        while(1)
        {
            prime.Listen();
        }
    });

    t.join();
    cin.ignore();
    return 0;
}

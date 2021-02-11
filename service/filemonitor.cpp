#include "filemonitor.h"
#include "inotifycpp.h"
#include <thread>
FileMonitor::FileMonitor()
{
    inotifycpp ino([](std::string msg) {
        printf(msg.c_str());
    });

    std::thread t([&ino]() {
        while (true)
        {
            ino.Start();
        }
    });

    t.join();
}

FileMonitor::~FileMonitor()
{
}

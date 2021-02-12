#include "filemonitor.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <thread>
FileMonitor::FileMonitor(std::function<void(std::string)> cb):m_cb{cb}
{
    fd = inotify_init();
    if (fd < 0)
    {
        perror("Failed at inotify_init");
    }
    wd = inotify_add_watch(fd, "/home/manish/sportspip/videos",
                           IN_MODIFY |
                               IN_DELETE |
                               IN_CREATE);
}

int FileMonitor::Watch()
{
    char buffer[BUF_LEN] = {};
    int length, i = 0;
    length = read(fd, buffer, BUF_LEN);

    if (length < 0)
    {
        perror("Failed at read");
        return -2;
    }

    while (i < length)
    {
        struct inotify_event *event = (struct inotify_event *)&buffer[i];
        if (event->len)
        {
            if (event->mask & IN_CREATE)
            {
                if (event->mask & IN_ISDIR)
                {
                }
                else
                {
                    printf("New video arrived: %s", event->name);
                    m_cb("Msg from inside");
                }
            }
            else if (event->mask & IN_DELETE)
            {
                if (event->mask & IN_ISDIR)
                {
                }
                else
                {
                    printf("Vide file deleted: %s", event->name);
                }
            }
            else if (event->mask & IN_MODIFY)
            {
                if (event->mask & IN_ISDIR)
                {
                }
                else
                {
                    printf("Video file modified: %s", event->name);
                }
            }
        }
        i += EVENT_SIZE + event->len;
    }
    return 0;
}

FileMonitor::~FileMonitor()
{
    (void)inotify_rm_watch(fd, wd);
    (void)close(fd);
}
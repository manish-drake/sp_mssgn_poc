#ifndef INOTIFYCPP_H
#define INOTIFYCPP_H
#include <string>
#include <functional>

using std::string;
#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN (1024 * (EVENT_SIZE + 16))

class FileMonitor
{
private:
    int fd, wd;
    std::function<void(std::string)>& m_cb;
public:
    FileMonitor(std::function<void(std::string)> cb);

    int Watch();

    ~FileMonitor();
};
#endif //INOTIFYCPP_H

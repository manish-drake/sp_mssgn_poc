#ifndef DELEGATE_H
#define DELEGATE_H
#include <string>
#include "messenger.h"
#include <map>
#include <vector>
#include <cstring>
#ifndef SRVC_MK
#include "ftpclient.h"
#endif

using std::string;
enum MSG_EVENTS_ENUM {
    NEW_VIDEO_AVAILABLE = 0,
};
namespace Messaging
{
class Delegate
{
private:
    Messenger m_messenger;
#ifndef SRVC_MK
    FTPClient m_ftp;
#endif
    std::map<MSG_EVENTS_ENUM, std::vector<std::string>> m_subscriptions;
private:
    void subscribe(const std::string &argEP, const std::string &argEvent);
    void fetchVideo(const std::string &fileName);
    void notify(const std::string &argNewVideo);
    void startRecording(const std::string &argFrom);
    void stopRecording(const std::string &argFrom);
public:
    void OnReceived(const std::string &argMsg);
    Delegate();


    ~Delegate();
};
} // namespace Messaging
#endif //DELEGATE_H

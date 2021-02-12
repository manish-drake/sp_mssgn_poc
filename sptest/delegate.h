#ifndef DELEGATE_H
#define DELEGATE_H
#include <string>
#include "messenger.h"
#include <map>
#include <vector>
#include <cstring>

using std::string;
enum MSG_EVENTS_ENUM{
  NEW_VIDEO_AVAILABLE = 0,
};
namespace Messaging
{
  class Delegate
  {
  private:
    Messenger m_messenger;
    std::map<MSG_EVENTS_ENUM, std::vector<std::string>> m_subscriptions;
  private:
    void subscribe(const char* argEP, const char* argEvent)
    {
      auto event = std::stoi(argEvent);
      m_subscriptions[static_cast<MSG_EVENTS_ENUM>(event)].push_back(argEP);
    }
  public:
    Delegate();

    void Received(const std::string &argMsg);
    void Notify(const std::string &argNewVideo);
    void StartRecording(const std::string &argFrom);
    void StopRecording(const std::string &argFrom);

    ~Delegate();
  };
} // namespace Messaging
#endif //DELEGATE_H

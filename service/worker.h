#ifndef WORKER_H
#define WORKER_H
#include <string>
#include "idelegator.h"
#include <map>
#include <vector>
#include "messenger.h"
#include "messages.h"

using std::string;

class Worker:public IDelegator
{
  private:
    void OnAcknowledgement(const char* from, const char* args) override;
    void OnException(const char* from, const char* args) override;
    void OnSubscription(const char* from, const char* args) override;
    void OnVideoFTPComplete(const char* from, const char* args) override;
    void OnUnknownMessage(const char* from, const char* args) override;
    void OnHandshake(const char* from, const char* args) override;
    void OnRequestSources(const char* from, const char* args) override;
    
    std::map<Messaging::MSG_ROLES_ENUM, std::vector<std::string>> m_subscribers;
    Messaging::Messenger m_messenger;
  public:
    Worker();
    ~Worker();
};
#endif //WORKER_H
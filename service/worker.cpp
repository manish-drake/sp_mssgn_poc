#include "worker.h"
#include "messages.h"
#include "messaging_exceptions.h"
#include <cstring>
#include "logger.h"
#include <algorithm>
#include "messages.h"

const char *MsgRoleStr(Messaging::MSG_ROLES_ENUM role)
{
    static char *roles[] = {"Source", "Consumer", "Controller"};
    return roles[role];
}

void Worker::OnAcknowledgement(const char *from, const char *args)
{
    LOGINFOZ("%s -ack-> %s", from, args);
}

void Worker::OnException(const char *from, const char *args)
{
    LOGERRZ("%s -err-> %s", from, args);
    throw Messaging::UnknownMessageException();
}

void Worker::OnSubscription(const char *from, const char *args)
{
    LOGINFOZ("Adding %s for event: %d", from, args);
    auto event = std::stoi(args);
}

void Worker::OnVideoFTPComplete(const char *from, const char *args)
{
    LOGINFO("Sending notifcation to all subscribers...");
    for (auto &src : m_subscribers[Messaging::MSG_ROLES_ENUM::CONSUMER])
        m_messenger.Send(src, Messaging::Messages::Factory()->MSG_NWVA(args));

    for (auto &src : m_subscribers[Messaging::MSG_ROLES_ENUM::CONTROLLER])
        m_messenger.Send(src, Messaging::Messages::Factory()->MSG_SRID(from));
}

void Worker::OnUnknownMessage(const char *from, const char *args)
{
    LOGWARNZ("%s -ukn-> %s", from, args);
}

void Worker::OnHandshake(const char *from, const char *args)
{
    auto roleVal = atoi(args);
    auto role = static_cast<Messaging::MSG_ROLES_ENUM>(roleVal);
    auto &list = m_subscribers[role];
    auto subscriber = std::string(from);
    auto it = std::find(list.begin(), list.end(), subscriber);
    if (it == list.end())
    {
        list.push_back(subscriber);
        LOGINFOZ("%s added to the [%s] role", from, MsgRoleStr(role));
    }
    else
        LOGWARNZ("%s already subscrbed to [%s] role.", from, MsgRoleStr(role));
}

void Worker::OnRequestSources(const char *from, const char *args)
{
    std::string csvSources;
    auto &list = m_subscribers[Messaging::MSG_ROLES_ENUM::SOURCE];
    for (auto &src : list)
    {
        csvSources += src + ",";
    }
    m_messenger.Send(from, Messaging::Messages::Factory()->MSG_RPSR(csvSources));
}

Worker::Worker()
{
}

Worker::~Worker()
{
}

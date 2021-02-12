#include "delegate.h"
#include "messages.h"
#include "messaging_exceptions.h"

Messaging::Delegate::Delegate()
{
}

void Messaging::Delegate::Received(const std::string &argMsg)
{
    Messaging::Message msg = Messaging::Messages::Factory()->Parse(argMsg.c_str());
    switch (msg.task)
    {
    case 200://acknowledgement received for last sent message
        break;
    case 400:
        //Last message you sent was unknown
        throw Messaging::UnknownMessageException();
    case 201:
        m_messenger.Send(msg.from, Messaging::Messages::Factory()->MSG_RCVD());
        break;
    case 202:
        m_messenger.Send(msg.from, Messaging::Messages::Factory()->MSG_RCVD());
        subscribe(msg.from, msg.args);
        break;
    default:
        m_messenger.Send(msg.from, Messaging::Messages::Factory()->MSG_UNKN());
        break;
    }
}

void Messaging::Delegate::Notify(const std::string &argNewVideo)
{
    for(auto &subscriber: m_subscriptions[MSG_EVENTS_ENUM::NEW_VIDEO_AVAILABLE])
    {
        m_messenger.Send(subscriber.c_str(), Messaging::Messages::Factory()->MSG_NWVA(argNewVideo.c_str()));
    }
}

Messaging::Delegate::~Delegate()
{
}
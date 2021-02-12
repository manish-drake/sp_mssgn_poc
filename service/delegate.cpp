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
    case 200: //acknowledgement received for last sent message
        break;
    case 400: //last message you sent was unknown
        throw Messaging::UnknownMessageException();
    case 201:
        m_messenger.Send(msg.from, Messaging::Messages::Factory()->MSG_RCVD());
        break;
    case 202: //request for subscription
        m_messenger.Send(msg.from, Messaging::Messages::Factory()->MSG_RCVD());
        subscribe(msg.from, msg.args);
        break;
    case 203: //request for starting the recording
        m_messenger.Send(msg.from, Messaging::Messages::Factory()->MSG_RCVD());
        StartRecording(msg.from);
        break;
    case 204: //request for stopping the recording
        m_messenger.Send(msg.from, Messaging::Messages::Factory()->MSG_RCVD());
        StopRecording(msg.from);
        break;
    default:  //unknown message
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

void Messaging::Delegate::StartRecording(const std::string &argFrom)
{
    
}

void Messaging::Delegate::StopRecording(const std::string &argFrom)
{
    
}

Messaging::Delegate::~Delegate()
{
}
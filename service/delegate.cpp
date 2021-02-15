#include "delegate.h"
#include "messages.h"
#include "messaging_exceptions.h"
#include <iostream>

void Messaging::Delegate::subscribe(const std::string &argEP, const std::string &argEvent)
{
    auto event = std::stoi(argEvent);
    m_subscriptions[static_cast<MSG_EVENTS_ENUM>(event)].push_back(argEP);
}
void Messaging::Delegate::OnReceived(const std::string &argMsg)
{
    Messaging::Message msg = Messaging::Messages::Factory()->Parse(argMsg.c_str());
    switch (msg.task)
    {
    case 200: //acknowledgement received for last sent message
        break;
    case 400: //last message you sent was unknown
        throw Messaging::UnknownMessageException();
    case 201://notification that the new video is available on server
        m_messenger.Send(msg.from, Messaging::Messages::Factory()->MSG_RCVD());
        fetchVideo(msg.args);
        break;
    case 202: //request for subscription
        m_messenger.Send(msg.from, Messaging::Messages::Factory()->MSG_RCVD());
        subscribe(msg.from, msg.args);
        break;
    case 203: //request for starting the recording
        m_messenger.Send(msg.from, Messaging::Messages::Factory()->MSG_RCVD());
        startRecording(msg.from);
        break;
    case 204: //request for stopping the recording
        m_messenger.Send(msg.from, Messaging::Messages::Factory()->MSG_RCVD());
        stopRecording(msg.from);
        break;
    case 205: //notification that the video has been FTPed
        m_messenger.Send(msg.from, Messaging::Messages::Factory()->MSG_RCVD());
        notify(msg.args);
        break;
    default:  //unknown message
        m_messenger.Send(msg.from, Messaging::Messages::Factory()->MSG_UNKN());
        break;
    }
}

void Messaging::Delegate::notify(const std::string &argNewVideo)
{
    m_messenger.Send("tcp://localhost:8286", Messaging::Messages::Factory()->MSG_NWVA(argNewVideo.c_str()));
    return;

    for(auto &subscriber: m_subscriptions[MSG_EVENTS_ENUM::NEW_VIDEO_AVAILABLE])
    {
        m_messenger.Send(subscriber.c_str(), Messaging::Messages::Factory()->MSG_NWVA(argNewVideo.c_str()));
    }
}

void Messaging::Delegate::startRecording(const std::string &argFrom)
{

}

void Messaging::Delegate::stopRecording(const std::string &argFrom)
{
#ifndef SRVC_MK
    static int num = 0;
    QString filename = "sample.mp4";

    m_ftp.Send(filename, [this](const std::string& file) {
        m_messenger.Send("tcp://localhost:8285", Messages::Factory()->MSG_VFTP(file));
    });
#endif
}
void Messaging::Delegate::fetchVideo(const std::string& fileName)
{
#ifndef SRVC_MK
    m_ftp.Receive(fileName, [](const bool& completedOkay)
    {
        std::cout << "Video fetch status: " << completedOkay << std::endl;
    });
#endif
}


Messaging::Delegate::Delegate()
{
}


Messaging::Delegate::~Delegate()
{
}

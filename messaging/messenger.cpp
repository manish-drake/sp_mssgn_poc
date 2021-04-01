#include "messenger.h"
#include <zmq.hpp>
#include "logger.h"
#include <exception>

Messaging::Messenger::Messenger()
{
}

void Messaging::Messenger::Send(std::string to, const std::string &argMsg)
{
    LOGINFOZ("%s: %s", to.c_str(), argMsg.c_str());

    zmq::context_t ctx(1);
    zmq::socket_t sock(ctx, ZMQ_DEALER);
    size_t sz = argMsg.size();
    zmq::message_t msg(sz);
    memcpy(msg.data(), argMsg.c_str(), sz);
    sock.connect(to.c_str());
    sock.send(msg);
    sock.close();
    ctx.close();
}

Messaging::Messenger::~Messenger()
{
}

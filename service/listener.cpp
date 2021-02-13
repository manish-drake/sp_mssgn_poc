#include "listener.h"
Listener::Listener(std::function<void(const std::string&)> cb):m_cb{cb}
{
    m_ctx = new zmq::context_t(1);
    m_sock = new zmq::socket_t(*m_ctx, ZMQ_REP);
    m_sock->bind("tcp://*:8283");
}

void Listener::Listen()
{
    zmq::message_t msg;
    m_sock->recv(&msg);
    m_cb(std::string((char*)msg.data()));
}


Listener::~Listener()
{
    m_sock->close();
    m_ctx->close();
    delete m_sock;
    delete m_ctx;
}

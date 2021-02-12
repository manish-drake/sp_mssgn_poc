#include "listener.h"
void Listener::init()
{
    m_ctx = new zmq::context_t(1);
    m_sock = new zmq::socket_t(*m_ctx, ZMQ_REP);
    m_sock->bind("tcp://*:8284");
    m_init = true;
}

Listener::Listener()
{
}

void Listener::Connect(std::function<void (const std::string &)> cb)
{
    m_cb = cb;
}

void Listener::Listen()
{
    if(!m_init) init();

    zmq::message_t msg;
    m_sock->recv(&msg);
    m_cb(std::string((char*)msg.data()));
}

void Listener::Close()
{
    m_sock->close();
    m_ctx->close();
    delete m_sock;
    delete m_ctx;
}


Listener::~Listener()
{

}

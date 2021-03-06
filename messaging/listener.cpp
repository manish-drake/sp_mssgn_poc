#include "listener.h"
#include "thread"
#include "logger.h"

//Listener::Listener(std::function<void(const std::string&)> cb):m_cb{cb}

void Messaging::Listener::init(zmq::context_t **argCtx, zmq::socket_t **argSock)
{
    char endpoint[255] = {};
    sprintf(endpoint, "tcp://*:%d", m_port);
    m_endpoint = endpoint;

    LOGINFOZ("Starting listener at: %s", m_endpoint.c_str());

    *argCtx = new zmq::context_t(1);
    *argSock = new zmq::socket_t(**argCtx, ZMQ_ROUTER);
    (*argSock)->bind(m_endpoint.c_str());
    m_isInitialized = true;
}

Messaging::Listener::Listener(int port):
    m_ctx{nullptr},
    m_sock{nullptr},
    m_close{0},
    m_isInitialized{false},
    m_port{port},
    m_pth{nullptr}
{
    
}

void Messaging::Listener::Listen(std::function<void(const std::string&)> cb)
{
     m_pth.reset(new std::thread([this](std::function<void(const std::string&)> cb){

        if(!m_isInitialized) this->init(&this->m_ctx, &this->m_sock);

        while (!m_close) {
            zmq::message_t msg;
            m_sock->recv(&msg);
            m_sock->recv(&msg);
            auto received = (char*)msg.data();
            LOGINFOZ("Received: %s", received);
            cb(received);
        }
    }, cb));

}

void Messaging::Listener::Close()
{
    m_sock->close();
    m_ctx->close();
    delete m_sock;
    delete m_ctx;
}


Messaging::Listener::~Listener()
{
    if ((m_pth) && (m_pth->joinable()))
    {
        m_pth->join();
    }
    this->Close();
}

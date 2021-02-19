#ifndef LISTENER_H
#define LISTENER_H
#include <string>
#include <functional>
#include <zmq.hpp>

using std::string;
namespace Messaging
{
  class Listener
  {
  private:
    zmq::context_t *m_ctx;
    zmq::socket_t *m_sock;
    bool m_close, m_isInitialized;
    std::string m_endpoint;
    int m_port;

  private:
    void init(zmq::context_t **argCtx, zmq::socket_t **argSock);

  public:
    Listener(int port);
    void Listen(std::function<void(const std::string &)> cb);
    void Close();
    ~Listener();
  };
} // namespace Messaging
#endif //LISTENER_H

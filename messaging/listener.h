#ifndef LISTENER_H
#define LISTENER_H
#include <string>
#include <functional>
#include <zmq.hpp>
#include <thread>
#include <memory>

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
    std::unique_ptr<std::thread> m_pth;

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

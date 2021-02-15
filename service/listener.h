#ifndef LISTENER_H
#define LISTENER_H
#include <string>
#include <functional>
#include <zmq.hpp>

using std::string;
class Listener
{
private:
  zmq::context_t *m_ctx;
  zmq::socket_t *m_sock;
  bool m_close, m_isInitialized;
  std::string m_endpoint;
private:
  void init(zmq::context_t **argCtx, zmq::socket_t **argSock);
public:
  Listener(const std::string &argEndpoint);
  void Listen(std::function<void(const std::string&)> cb);
  void Close();
  ~Listener();
};
#endif //LISTENER_H

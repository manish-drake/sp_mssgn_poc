#ifndef LISTENER_H
#define LISTENER_H
#include <string>
#include <functional>
#include <zmq.hpp>

using std::string;
class Listener
{
private:
  std::function<void(const std::string &)> m_cb;
  zmq::context_t *m_ctx;
  zmq::socket_t *m_sock;

public:
  Listener(std::function<void(const std::string &)> cb);
  void Listen();
  ~Listener();
};
#endif //LISTENER_H
#ifndef MESSENGER_H
#define MESSENGER_H
#include <string>
using std::string;
namespace Messaging
{
  class Messenger
  {
  private:
  public:
    Messenger();
    void Send(std::string to, const std::string &msg);
    ~Messenger();
  };
} // namespace Messaging
#endif //MESSENGER_H

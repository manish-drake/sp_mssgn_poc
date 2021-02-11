#ifndef MESSENGER_H
#define MESSENGER_H
#include <string>
using std::string;
struct Node{

};
class Messenger
{
  private:
  public:
    Messenger();
    void Send(std::string &msg, Node& node);
    ~Messenger();
};
#endif //MESSENGER_H
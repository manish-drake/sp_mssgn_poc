#ifndef DELEGATE_H
#define DELEGATE_H
#include <string>
using std::string;
class Delegate
{
  private:
  public:
    Delegate();

    void Received(const std::string &msg);

    ~Delegate();
};
#endif //DELEGATE_H
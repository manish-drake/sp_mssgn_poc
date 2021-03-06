#ifndef MULTISENDER_H
#define MULTISENDER_H
#include <string>

class MultiSender
{
public:
    MultiSender();

    void Start(const std::string& broadcast);
    ~MultiSender();
};

#endif // MULTISENDER_H

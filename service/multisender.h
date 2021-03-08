#ifndef MULTISENDER_H
#define MULTISENDER_H
#include <string>
#include <thread>
#include <memory>

class MultiSender
{
    std::unique_ptr<std::thread> m_pth;    
public:
    MultiSender();

    void Start(const std::string& broadcast);
    ~MultiSender();
};

#endif // MULTISENDER_H

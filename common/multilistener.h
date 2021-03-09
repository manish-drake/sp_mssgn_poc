#ifndef MULTILISTENER_H
#define MULTILISTENER_H
#include <iostream>
#include <functional>
class MultiListener
{
public:
    MultiListener();

    void Start(std::function<void(const std::string &, const std::string &, const std::string &)> cb);
    ~MultiListener();
};

#endif // MULTILISTENER_H

#ifndef MULTILISTENER_H
#define MULTILISTENER_H
#include <iostream>
#include <functional>

class MultiListener
{
public:
    MultiListener();

    void Start(std::function<void(std::string&)> cb);
    ~MultiListener();
};

#endif // MULTILISTENER_H

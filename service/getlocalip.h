#ifndef GETLOCALIP_H
#define GETLOCALIP_H

#include <iostream>
#include <winsock.h>
#include <vector>

class GetLocalIP
{
    WSAData wsaData;

public:
    GetLocalIP();
    bool Run(std::vector<std::string> &localIps);
    ~GetLocalIP();
};

#endif //GETLOCALIP_H
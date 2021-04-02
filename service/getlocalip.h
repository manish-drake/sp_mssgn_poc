#ifndef GETLOCALIP_H
#define GETLOCALIP_H

#include <iostream>
#include <vector>
#if _WIN32
#include <winsock.h>
#endif

class GetLocalIP
{

#if _WIN32
    WSAData wsaData;
#endif

public:
    GetLocalIP();
    bool Run(std::vector<std::string> &localIps);
    ~GetLocalIP();
};

#endif //GETLOCALIP_H
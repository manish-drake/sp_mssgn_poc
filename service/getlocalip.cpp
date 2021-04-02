#include "getlocalip.h"
#include "logger.h"
#if _WIN32
#else
#include <stdio.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#endif
using namespace std;
GetLocalIP::GetLocalIP()
{
    LOGINFO("Getting local IP addresses..");
}

bool GetLocalIP::Run(std::vector<std::string> &localIps)
{
#if _WIN32
    if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
        LOGERR("Failed to start the winsock service. Quitting.");
        return false;
    }
    char ac[80];
    if (gethostname(ac, sizeof(ac)) == SOCKET_ERROR) {
        LOGERRZ("Error %d when getting local host name.", WSAGetLastError());
        return false;
    }
    LOGINFOZ("Host name is %s.", ac);

    struct hostent *phe = gethostbyname(ac);
    if (phe == 0) {
        LOGERR("Bad host lookup! Quitting");
        return false;
    }

    for (int i = 0; phe->h_addr_list[i] != 0; ++i) {
        struct in_addr addr;
        memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
        std::string ip(inet_ntoa(addr));
        localIps.push_back(ip);
        LOGINFOZ("IP Address %s", ip.c_str());
    }
#else
    struct ifaddrs * ifAddrStruct = nullptr;
    struct ifaddrs * ifa = nullptr;
    void * tmpAddrPtr = nullptr;

    auto result = getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != nullptr; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) { // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
            localIps.push_back(addressBuffer);
            
        } else if (ifa->ifa_addr->sa_family == AF_INET6) { // check it is IP6
            // is a valid IP6 Address
            tmpAddrPtr=&((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
            char addressBuffer[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
            printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
        }
    }
    if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
#endif
    return true;
}

GetLocalIP::~GetLocalIP()
{
#if _WIN32
    WSACleanup();
#endif
}
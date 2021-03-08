#include "getlocalip.h"
#include "logger.h"
using namespace std;
GetLocalIP::GetLocalIP()
{
    LOGINFO("Getting local IP addresses..");
}

bool GetLocalIP::Run(std::vector<std::string> &localIps)
{
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
}

GetLocalIP::~GetLocalIP()
{
    WSACleanup();
}
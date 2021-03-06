#ifdef _WIN32
#include <Winsock2.h> // before Windows.h, else Winsock 1 conflict
#include <Ws2tcpip.h> // needed for ip_mreq definition for multicast
#include <Windows.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> // for sleep()
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "multisender.h"
#include "logger.h"

MultiSender::MultiSender() : m_pth{nullptr}
{
    LOGINFO("Starting multicast service..");
}

void MultiSender::Start(const std::string &broadcast)
{
    m_pth.reset(new std::thread([](const std::string &broadcastRef) -> int {
        char *group = "239.255.255.250"; // e.g. 239.255.255.250 for SSDP
        int port = 7755;                 

        const int delay_secs = 2;
        const char *message = broadcastRef.c_str();
        
        LOGINFOZ("New thread broadcasting %s on %s:%d at a delay of %d secs", message, group, port, delay_secs);

#ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(0x0101, &wsaData))
        {
            perror("WSAStartup");
            return 1;
        }
#endif

        int fd = socket(AF_INET, SOCK_DGRAM, 0);
        if (fd < 0)
        {
            perror("socket");
            return 1;
        }

        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(group);
        addr.sin_port = htons(port);

        while (1)
        {
            char ch = 0;
            int nbytes = sendto(
                fd,
                message,
                strlen(message),
                0,
                (struct sockaddr *)&addr,
                sizeof(addr));
            if (nbytes < 0)
            {
                perror("sendto");
                return 1;
            }

#ifdef _WIN32
            Sleep(delay_secs * 1000); 
#else
            sleep(delay_secs); 
#endif
        }

#ifdef _WIN32
        WSACleanup();
#endif

        return 0;
    },
                                broadcast));
}

MultiSender::~MultiSender()
{
    if ((m_pth) && (m_pth->joinable()))
    {
        LOGINFO("Joining in with main..");
        m_pth->join();
    }
}

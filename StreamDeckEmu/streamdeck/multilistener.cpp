#include "multilistener.h"
#ifdef _WIN32
#include <Winsock2.h> // before Windows.h, else Winsock 1 conflict
#include <Ws2tcpip.h> // needed for ip_mreq definition for multicast
#include <Windows.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>

#define MSGBUFSIZE 256

MultiListener::MultiListener()
{
}

void MultiListener::Start(std::function<void (std::string &)> cb)
{
    std::thread t([](std::function<void(std::string&)> cbref)->int{

        char* group = "239.255.255.250"; // e.g. 239.255.255.250 for SSDP
        int port = 7755;


#ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(0x0101, &wsaData)) {
            perror("WSAStartup");
            return 1;
        }
#endif

        int fd = socket(AF_INET, SOCK_DGRAM, 0);
        if (fd < 0) {
            perror("socket");
            return 1;
        }

        u_int yes = 1;
        if (
                setsockopt(
                    fd, SOL_SOCKET, SO_REUSEADDR, (char*) &yes, sizeof(yes)
                    ) < 0
                ){
            perror("Reusing ADDR failed");
            return 1;
        }

        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port = htons(port);

        if (bind(fd, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
            perror("bind");
            return 1;
        }

        struct ip_mreq mreq;
        mreq.imr_multiaddr.s_addr = inet_addr(group);
        mreq.imr_interface.s_addr = htonl(INADDR_ANY);
        if (
                setsockopt(
                    fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*) &mreq, sizeof(mreq)
                    ) < 0
                ){
            perror("setsockopt");
            return 1;
        }

        while (1) {
            char msgbuf[MSGBUFSIZE];
            int addrlen = sizeof(addr);
            int nbytes = recvfrom(
                        fd,
                        msgbuf,
                        MSGBUFSIZE,
                        0,
                        (struct sockaddr *) &addr,
                        &addrlen
                        );
            if (nbytes < 0) {
                perror("recvfrom");
                return 1;
            }
            msgbuf[nbytes] = '\0';
            std::string msg{msgbuf};
            cbref(msg);
        }

#ifdef _WIN32
        WSACleanup();
#endif
    }, cb);
    t.detach();
}

MultiListener::~MultiListener()
{

}

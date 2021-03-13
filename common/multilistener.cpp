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
#include <map>
#include "logger.h"

#define MSGBUFSIZE 256

MultiListener::MultiListener()
{
}

void MultiListener::Start(std::function<void (const std::string &, const std::string &, const std::string &)> cb)
{
    std::thread t([](std::function<void(const std::string &, const std::string &, const std::string &)> cbref)->int{

        std::map<std::string,std::string> castsTimestamp;

        char* group = "239.255.255.250"; // e.g. 239.255.255.250 for SSDP
        int port = 7755;
        LOGINFOZ("Listening for broadcasts on %s:%d", group, port);

#ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(0x0101, &wsaData)) {
            LOGERR("WSAStartup, quitting..");
            return 1;
        }
#endif

        int fd = socket(AF_INET, SOCK_DGRAM, 0);
        if (fd < 0) {
            LOGERR("Socket, quitting..");
            return 1;
        }

        u_int yes = 1;
        if (
                setsockopt(
                    fd, SOL_SOCKET, SO_REUSEADDR, (char*) &yes, sizeof(yes)
                    ) < 0
                ){
            LOGERR("Reusing ADDR failed, quitting..");
            return 1;
        }

        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port = htons(port);

        if (::bind(fd, (struct sockaddr*) &addr, sizeof(addr)) < 0)
        {
            LOGERR("Binding, quitting..");
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
            LOGERR("Setsockopt, quiting..");
            return 1;
        }

        while (1) {
            char msgbuf[MSGBUFSIZE];
#ifdef Q_OS_IOS
            unsigned int addrlen = sizeof(addr);
#else
            int addrlen = sizeof(addr);
#endif
            long nbytes = recvfrom(
                        fd,
                        msgbuf,
                        MSGBUFSIZE,
                        0,
                        (struct sockaddr *) &addr,
                        static_cast<socklen_t*>(&addrlen)
                        );
            if (nbytes < 0) {
                LOGERR("Recvfrom, quitting..");
                return 1;
            }
            msgbuf[nbytes] = '\0';

            std::string msg{msgbuf};
            auto idAndTp = msg.substr(0, 2);
            auto ts = msg.substr(2, 2);
            if(castsTimestamp[idAndTp] != ts)
            {
                castsTimestamp[idAndTp] = ts;
                auto payload = msg.substr(4, msg.size() - 4);
                auto id = msg.substr(0, 1);
                auto tp = msg.substr(1, 1);

                cbref(id, tp, payload);
            }

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

#ifndef LIB_SOCKET_H
#define LIB_SOCKET_H

#if _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h> //hostent
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#endif
#include <iostream>
#include <cerrno>
#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <ctime>

//multi platform socket descriptor
#if _WIN32
typedef SOCKET socketfd_t;
#else
typedef int socketfd_t;
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////
//utils
/////////////////////////////////////////////////////////////////////////////////////////////////////

std::string str_extract(const std::string &str_in);
std::string prt_time();
int set_daemon(const char *str_dir);
void wait(int nbr_secs);

/////////////////////////////////////////////////////////////////////////////////////////////////////
//socket_t
/////////////////////////////////////////////////////////////////////////////////////////////////////

class socket_t
{
public:
  socket_t();
  socket_t(socketfd_t sockfd, sockaddr_in sock_addr);
  void close();
  int write_all(const void *buf, int size_buf);
  int read_all(void *buf, int size_buf);
  int hostname_to_ip(const char *host_name, char *ip);

public:
  socketfd_t m_sockfd;       //socket descriptor
  sockaddr_in m_sockaddr_in; //client address (used to store return value of server accept())
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
//tcp_server_t
/////////////////////////////////////////////////////////////////////////////////////////////////////

class tcp_server_t : public socket_t
{
public:
  tcp_server_t(const unsigned short server_port);
  socket_t accept();
  ~tcp_server_t();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
//tcp_client_t
/////////////////////////////////////////////////////////////////////////////////////////////////////

class tcp_client_t : public socket_t
{
#define NS_INADDRSZ 4
#define NS_IN6ADDRSZ 16
#define NS_INT16SZ 2
  int inet_pton4(const char *src, char *dst)
  {
    uint8_t tmp[NS_INADDRSZ], *tp;

    int saw_digit = 0;
    int octets = 0;
    *(tp = tmp) = 0;

    int ch;
    while ((ch = *src++) != '\0')
    {
      if (ch >= '0' && ch <= '9')
      {
        uint32_t n = *tp * 10 + (ch - '0');

        if (saw_digit && *tp == 0)
          return 0;

        if (n > 255)
          return 0;

        *tp = n;
        if (!saw_digit)
        {
          if (++octets > 4)
            return 0;
          saw_digit = 1;
        }
      }
      else if (ch == '.' && saw_digit)
      {
        if (octets == 4)
          return 0;
        *++tp = 0;
        saw_digit = 0;
      }
      else
        return 0;
    }
    if (octets < 4)
      return 0;

    memcpy(dst, tmp, NS_INADDRSZ);

    return 1;
  }
  int inet_pton6(const char *src, char *dst)
  {
    static const char xdigits[] = "0123456789abcdef";
    uint8_t tmp[NS_IN6ADDRSZ];

    uint8_t *tp = (uint8_t *)memset(tmp, '\0', NS_IN6ADDRSZ);
    uint8_t *endp = tp + NS_IN6ADDRSZ;
    uint8_t *colonp = NULL;

    /* Leading :: requires some special handling. */
    if (*src == ':')
    {
      if (*++src != ':')
        return 0;
    }

    const char *curtok = src;
    int saw_xdigit = 0;
    uint32_t val = 0;
    int ch;
    while ((ch = tolower(*src++)) != '\0')
    {
      const char *pch = strchr(xdigits, ch);
      if (pch != NULL)
      {
        val <<= 4;
        val |= (pch - xdigits);
        if (val > 0xffff)
          return 0;
        saw_xdigit = 1;
        continue;
      }
      if (ch == ':')
      {
        curtok = src;
        if (!saw_xdigit)
        {
          if (colonp)
            return 0;
          colonp = tp;
          continue;
        }
        else if (*src == '\0')
        {
          return 0;
        }
        if (tp + NS_INT16SZ > endp)
          return 0;
        *tp++ = (uint8_t)(val >> 8) & 0xff;
        *tp++ = (uint8_t)val & 0xff;
        saw_xdigit = 0;
        val = 0;
        continue;
      }
      if (ch == '.' && ((tp + NS_INADDRSZ) <= endp) &&
          inet_pton4(curtok, (char *)tp) > 0)
      {
        tp += NS_INADDRSZ;
        saw_xdigit = 0;
        break; /* '\0' was seen by inet_pton4(). */
      }
      return 0;
    }
    if (saw_xdigit)
    {
      if (tp + NS_INT16SZ > endp)
        return 0;
      *tp++ = (uint8_t)(val >> 8) & 0xff;
      *tp++ = (uint8_t)val & 0xff;
    }
    if (colonp != NULL)
    {
      /*
         * Since some memmove()'s erroneously fail to handle
         * overlapping regions, we'll do the shift by hand.
         */
      const int n = tp - colonp;

      if (tp == endp)
        return 0;

      for (int i = 1; i <= n; i++)
      {
        endp[-i] = colonp[n - i];
        colonp[n - i] = 0;
      }
      tp = endp;
    }
    if (tp != endp)
      return 0;

    memcpy(dst, tmp, NS_IN6ADDRSZ);

    return 1;
  }
  int inet_pton(int af, const char *src, void *dst)
  {
    switch (af)
    {
    case AF_INET:
      return inet_pton4(src, (char*)dst);
    case AF_INET6:
      return inet_pton6(src, (char*)dst);
    default:
      return -1;
    }
  }

public:
  tcp_client_t();
  ~tcp_client_t();
  int connect();

  tcp_client_t(const char *host_name, const unsigned short server_port);
  int connect(const char *host_name, const unsigned short server_port);

protected:
  std::string m_server_ip;
  unsigned short m_server_port;
};

#endif
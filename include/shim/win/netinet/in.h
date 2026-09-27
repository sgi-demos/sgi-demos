#ifndef NETINET_IN_SHIM_H_
#define NETINET_IN_SHIM_H_

#if defined(_WIN32)

#ifdef __cplusplus
extern "C" {
#endif

// POSIX <netinet/in.h> for Windows: the IPv4 addresses and multicast options
// flight 3.4's dogfight code uses (see sys/socket.h here)
#include <stdint.h>
#include <sys/socket.h>

typedef uint32_t in_addr_t;
typedef uint16_t in_port_t;

struct in_addr {
    in_addr_t s_addr;
};

struct sockaddr_in {
    short sin_family;
    in_port_t sin_port;
    struct in_addr sin_addr;
    char sin_zero[8];
};

struct ip_mreq {
    struct in_addr imr_multiaddr;
    struct in_addr imr_interface;
};

#define INADDR_ANY          ((in_addr_t)0x00000000)
#define INADDR_BROADCAST    ((in_addr_t)0xffffffff)
#define INADDR_NONE         ((in_addr_t)0xffffffff)

#define IPPROTO_IP          0
#define IP_MULTICAST_IF     9
#define IP_MULTICAST_TTL    10
#define IP_MULTICAST_LOOP   11
#define IP_ADD_MEMBERSHIP   12

// <arpa/inet.h>'s, here because the IRIX code calls them with no
// declaration. inet_ntoa is declared without a prototype: flight's radar
// passes it a long plane id (the same 4 bytes as a struct in_addr on
// Windows), which a prototype would refuse, and without any declaration its
// char * result would be truncated to int.
in_addr_t inet_addr(const char *cp);
char *inet_ntoa();

#ifdef __cplusplus
}
#endif

#endif // _WIN32

#endif // NETINET_IN_SHIM_H_

#ifndef SYS_SOCKET_SHIM_H_
#define SYS_SOCKET_SHIM_H_

#if defined(_WIN32)

#ifdef __cplusplus
extern "C" {
#endif

// POSIX <sys/socket.h> for Windows, as much as flight 3.4's dogfight code
// (udpbrdcst.c) uses. Network play is not ported, so the functions are stubs
// that fail with ENOSYS (libs/libgl/win_posix.c): the demo runs single-player,
// as it does elsewhere when the "sgi-dogfight" udp service is not defined.
#include <stddef.h>
#include <sys/types.h>

typedef char *caddr_t;      // IRIX <sys/types.h>
typedef int socklen_t;

struct sockaddr {
    unsigned short sa_family;
    char sa_data[14];
};

#define AF_INET         2
#define SOCK_DGRAM      2
#define SOL_SOCKET      0xffff
#define SO_BROADCAST    0x0020

int socket(int domain, int type, int protocol);
int bind(int fd, const struct sockaddr *addr, socklen_t len);
int setsockopt(int fd, int level, int name, const void *value, socklen_t len);
int sendto(int fd, const void *buf, size_t len, int flags, const struct sockaddr *to, socklen_t tolen);
int recvfrom(int fd, void *buf, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen);

#ifdef __cplusplus
}
#endif

#endif // _WIN32

#endif // SYS_SOCKET_SHIM_H_

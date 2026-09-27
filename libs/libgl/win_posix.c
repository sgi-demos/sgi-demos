// POSIX functions the demos use that Windows lacks, declared by the headers
// in include/shim/win: the drand48 family (ep-1994), the BSD memory
// functions (flight 3.4), and stubs for the sockets of flight 3.4's
// dogfight code, whose network play is not ported.

#if defined(_WIN32) && !defined(__EMSCRIPTEN__)

// netinet/in.h declares inet_ntoa without a prototype on purpose (see there)
#pragma clang diagnostic ignored "-Wdeprecated-non-prototype"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netdb.h>

// drand48/srand48: the POSIX 48-bit linear congruential generator,
// X' = (aX + c) mod 2^48, so a seeded run draws the same sequence as on
// macOS, Linux, and the web. The initial X is glibc's.
#define RAND48_A    0x5DEECE66DULL
#define RAND48_C    0xBULL
#define RAND48_MASK ((1ULL << 48) - 1)

static unsigned long long rand48_x = 0x1234ABCD330EULL;

void srand48(long seedval)
{
    // high 32 bits from the seed, low 16 bits 0x330E
    rand48_x = ((unsigned long long)(unsigned long)seedval << 16) | 0x330E;
}

double drand48(void)
{
    rand48_x = (RAND48_A * rand48_x + RAND48_C) & RAND48_MASK;
    return (double)rand48_x / (double)(1ULL << 48);
}

// bcopy/bzero/bcmp: BSD <strings.h>, as their <string.h> equivalents
void bcopy(const void *src, void *dst, size_t n)
{
    memmove(dst, src, n);
}

void bzero(void *s, size_t n)
{
    memset(s, 0, n);
}

int bcmp(const void *s1, const void *s2, size_t n)
{
    return memcmp(s1, s2, n);
}

// Socket stubs: every call fails as if the system had no network
int socket(int domain, int type, int protocol)
{
    errno = ENOSYS;
    return -1;
}

int bind(int fd, const struct sockaddr *addr, socklen_t len)
{
    errno = ENOSYS;
    return -1;
}

int setsockopt(int fd, int level, int name, const void *value, socklen_t len)
{
    errno = ENOSYS;
    return -1;
}

int sendto(int fd, const void *buf, size_t len, int flags, const struct sockaddr *to, socklen_t tolen)
{
    errno = ENOSYS;
    return -1;
}

int recvfrom(int fd, void *buf, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen)
{
    errno = ENOSYS;
    return -1;
}

int ioctl(int fd, unsigned long request, ...)
{
    errno = ENOSYS;
    return -1;
}

in_addr_t inet_addr(const char *cp)
{
    return INADDR_NONE;
}

// the one real one: dotted-quad text for an address (flight's radar prints
// plane ids with it)
char *inet_ntoa(struct in_addr in)
{
    static char buf[16];
    const unsigned char *b = (const unsigned char *)&in.s_addr;
    snprintf(buf, sizeof(buf), "%u.%u.%u.%u", b[0], b[1], b[2], b[3]);
    return buf;
}

struct hostent *gethostbyname(const char *name)
{
    return NULL;
}

struct servent *getservbyname(const char *name, const char *proto)
{
    return NULL;
}

int gethostname(char *name, size_t len)
{
    errno = ENOSYS;
    return -1;
}

#endif // _WIN32 && !__EMSCRIPTEN__

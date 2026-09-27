#ifndef NETDB_SHIM_H_
#define NETDB_SHIM_H_

#if defined(_WIN32)

#ifdef __cplusplus
extern "C" {
#endif

// POSIX <netdb.h> for Windows: host and service lookup for flight 3.4's
// dogfight code (see sys/socket.h here). The stubs find nothing.
#include <stddef.h>

struct hostent {
    char *h_name;
    char **h_aliases;
    short h_addrtype;
    short h_length;
    char **h_addr_list;
};
#define h_addr h_addr_list[0]

struct servent {
    char *s_name;
    char **s_aliases;
    int s_port;
    char *s_proto;
};

struct hostent *gethostbyname(const char *name);
struct servent *getservbyname(const char *name, const char *proto);

// <unistd.h>'s, here because the IRIX code calls it with no declaration
int gethostname(char *name, size_t len);

#ifdef __cplusplus
}
#endif

#endif // _WIN32

#endif // NETDB_SHIM_H_

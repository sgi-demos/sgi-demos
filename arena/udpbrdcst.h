#ifdef UDPBRDCSTDEF
#else
#define UDPBRDCSTDEF

#if NETWORKING

#include <sys/types.h>
#ifdef CLOVER
#include <bsd/sys/socket.h>
#include <bsd/netinet/in.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#endif
#include <netdb.h>
// #include <sys/termio.h>
// #define FIONBIO		0x5421
#include <errno.h>

#define	IGNOREOWNMSG 1	/* Flag for recvbroadcast() to ignore messages */
			/* which are received on originating host */
#define ACCEPTOWNMSG 0	/* Flag for recvbroadcast() to accept messages */
			/* which are received on originating host */

extern int getbroadcast (/* char *service, struct sockaddr_in *addr */);

extern int sendbroadcast(/* int socketfiledes, char *message, 
			    int messagelength, struct sockaddr_in *addr */);

extern int recvbroadcast(/* int socketfiledes, char *messagebuf,
			    int messagebuflen, int ignoreownflag */);

#endif // NETWORKING

#endif /* UDPBRDCSTDEF */

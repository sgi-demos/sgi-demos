/**************************************************************************
 *									  *
 *  Copyright (C)  1988 Silicon Graphics, Inc.	  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/

#ifdef _4D
#include <sys/time.h>
#else
#include <bsd/sys/time.h>
#endif
#include "udpbrdcst.h"


static struct sockaddr_in  hostaddr;

/*
 * Get a broadcast socket for the given service.  Return in "addr" the
 * address to use in a "sendto" so that a message can be broadcast.
 * The socket returned can be used to send a broadcast message, as well
 * as receive a broadcast message.  Some interfaces will receive what
 * they send, so be prepared to drop messages from yourself.
 */
int
getbroadcast(service, addr)
    char *service;
    struct sockaddr_in *addr;
{
    struct servent *sp;
    int fd;
    int on = 1;
    int arg;

    sp = getservbyname(service, "udp");
    if (sp == 0) {
    	printf("Can't find broadcast udp service \"%s\"\n", service);
    	return(-2);
    }
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
	perror("socket");
    	return (-1);
    }
    if (setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &on, sizeof (on)) < 0) {
	perror("setsockopt");
    	close(fd);
    	return (-1);
    }
    bzero(addr, sizeof(addr));
    addr->sin_family = AF_INET;
    addr->sin_port = sp->s_port;
    if (bind(fd, addr, sizeof(*addr)) < 0) {
	perror("bind");
    	close(fd);
    	return (-1);
    }
    
    addr->sin_addr.s_addr = INADDR_BROADCAST;

    if (ioctl(fd, FIONBIO, &on) < 0) {	/* Turn on non-blocking I/O */
	perror("ioctl");
	close(fd);
	return (-1);
    }
    
    gethostaddr(&hostaddr);

    return (fd);
}


/*
** Get host internet address
*/

int
gethostaddr(addr)
    struct sockaddr_in *addr;
{
    char hostname[100];
    struct hostent *hp;

    if (gethostname(hostname, sizeof(hostname)) < 0)
    	return (-1);
    hp = gethostbyname(hostname);
    if (!hp)
    	return (-1);
    addr->sin_family = AF_INET;
    addr->sin_port = 0;
    bcopy(hp->h_addr, &addr->sin_addr, sizeof(addr->sin_addr));
    return (0);
}


/*
** sendbroadcast
*/
	
int
sendbroadcast (broadcastsocket, message, messagelength, addr)
    int			broadcastsocket;
    char *		message;
    int			messagelength;
    struct sockaddr_in *addr;
{
    return(sendto(broadcastsocket, message, messagelength, 0, addr, sizeof(*addr)));
}


/*
**  recvbroadcast
*/
int
recvbroadcast (broadcastsocket, message, messagelength, ignoreown)
    int		broadcastsocket;
    char *	message;
    int		messagelength;
    int		ignoreown;
{
    struct sockaddr_in  fromaddr;
    int			fromaddrlength = sizeof(fromaddr);
    int			charcount;
    
    do {
        charcount=recvfrom(broadcastsocket, message, messagelength, 0,
				&fromaddr, &fromaddrlength);
        if (charcount < 0) {
	    if (errno == EWOULDBLOCK) {
		return (0);
	    }
	    else {
	        perror("recvbroadcast");
	        exit(-1);
	    }
        }

	if (charcount == 0) {
	    break;
	}

    } while (ignoreown && (fromaddr.sin_addr.s_addr == hostaddr.sin_addr.s_addr));

    return(charcount);
}

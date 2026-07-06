/*
 * Copyright 1984-1991, 1992, 1993, 1994, Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * Permission to use, copy, modify, and distribute this software for
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission.
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor
 * clauses in the FAR or the DOD or NASA FAR Supplement.
 * Unpublished-- rights reserved under the copyright laws of the
 * United States.  Contractor/manufacturer is Silicon Graphics,
 * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
 */

/*
 *  udpbrdcst.c $Revision: 1.1 $
 */

#include <stdio.h>
#include <sys/time.h>
#include "udpbrdcst.h"

#define DOG_MCAST_ADDR	"224.0.1.2"	/* official address */
#define DEFAULT_TTL	8		/* packet time-to-live */
#define MAX_TTL		32		/* can't go beyond the "site" */
char multicast = 1;		/* if 1 use multicast instead of broadcast */
char mcast_ttl = DEFAULT_TTL;	/* must be type "char" */
char *mcast_ifaddr = NULL;	/* interface address to send to/recv from */

static struct sockaddr_in  hostaddr;


/*
 * Get a broadcast or multicast socket for the given service.  
 * Return in "addr" the address to use in a "sendto" so that a message 
 * can be sent.  The socket returned can be used to send a message, as well
 * as receive a message.  Some interfaces will receive what
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

    /* Get our port number */
    sp = getservbyname(service, "udp");
    if (sp == 0)
    {
	printf("Can't find udp service \"%s\"\n", service);
	return(-2);
    }

    /* Open the socket */
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0)
    {
	perror("socket");
	return(-1);
    }

    bzero(addr, sizeof(*addr));
    addr->sin_addr.s_addr = INADDR_ANY;
    addr->sin_family = AF_INET;
    addr->sin_port = sp->s_port;
    if (bind(fd, addr, sizeof(*addr)) < 0)
    {
	perror("bind");
	close(fd);
	return(-1);
    }

    if (multicast)
    {
	struct ip_mreq mreq;
	struct in_addr ifaddr;
	char mcloop = 0;		/* must be type "char" */

	/* Disable loopback of mcast packets */
	if (setsockopt(fd, IPPROTO_IP, IP_MULTICAST_LOOP, &mcloop, 
		sizeof(mcloop)) < 0){
	    perror("setsockopt mcast loop");
	    close(fd);
	    return(-1);
	}

	if (mcast_ttl < 0 || mcast_ttl > MAX_TTL)
	{
	    mcast_ttl = DEFAULT_TTL;
	}
	if (setsockopt(fd, IPPROTO_IP, IP_MULTICAST_TTL, &mcast_ttl, 
		       sizeof(mcast_ttl)) < 0)
	{
	    perror("setsockopt mcast ttl");
	    close(fd);
	    return(-1);
	}

	/* Change the default interface (only useful on gateways) */
	if (mcast_ifaddr != NULL)
	{
	    struct hostent *hp;

	    ifaddr.s_addr = inet_addr(mcast_ifaddr);
	    if (ifaddr.s_addr == (unsigned)-1)
	    {
		hp = gethostbyname(mcast_ifaddr);
		if (hp)
		{
		    bcopy(hp->h_addr, (caddr_t)&ifaddr, hp->h_length);
		}
		else
		{
		    fprintf(stderr, "Can't find IP address for '%s'\n",
			    mcast_ifaddr);
		    close(fd);
		    return(-1);
		}
	    }
	    if (setsockopt(fd, IPPROTO_IP, IP_MULTICAST_IF, &ifaddr, 
			   sizeof(ifaddr)) < 0)
	    {
		perror("Can't send mcasts on the specified interface");
		close(fd);
		return(-1);
	    }
	    mreq.imr_interface = ifaddr;
	}
	else
	{
	    mreq.imr_interface.s_addr = INADDR_ANY;
	}

	mreq.imr_multiaddr.s_addr = addr->sin_addr.s_addr = 
		inet_addr(DOG_MCAST_ADDR);
	if (setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, 
		       sizeof(mreq)) < 0)
	{
	    perror("Can't add mcast address"); 
	    fprintf(stderr,
		    "Can't use multicast mode, reverting to broadcast mode.\n");
	    multicast = 0;	/* fall through */
	}
    } 

    if (!multicast)
    {
	addr->sin_addr.s_addr = INADDR_BROADCAST;
	if (setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &on, sizeof (on)) < 0)
	{
	    perror("setsockopt");
	    close(fd);
	    return(-1);
	}
    }

    if (ioctl(fd, FIONBIO, &on) < 0)	/* Turn on non-blocking I/O */
    {
	perror("ioctl");
	close(fd);
	return(-1);
    }
    
    (void) gethostaddr(&hostaddr);

    return(fd);
}


/*
 * Get host internet address
 */

int
gethostaddr(addr)
    struct sockaddr_in *addr;
{
    char hostname[100];
    struct hostent *hp;

    if (gethostname(hostname, sizeof(hostname)) < 0)
	return(-1);
    hp = gethostbyname(hostname);
    if (!hp)
	return(-1);
    addr->sin_family = AF_INET;
    addr->sin_port = 0;
    bcopy(hp->h_addr, &addr->sin_addr, sizeof(addr->sin_addr));
    return(0);
}


/*
 * sendbroadcast
 */
	
int
sendbroadcast(broadcastsocket, message, messagelength, addr)
    int			broadcastsocket;
    char *		message;
    int			messagelength;
    struct sockaddr_in *addr;
{
    return(sendto(broadcastsocket, message, messagelength, 0, addr,
		  sizeof(*addr)));
}


/*
 *  recvbroadcast
 */
int
recvbroadcast(broadcastsocket, message, messagelength, ignoreown)
    int broadcastsocket;
    char *message;
    int messagelength;
    int ignoreown;
{
    struct sockaddr_in fromaddr;
    int fromaddrlength = sizeof(fromaddr);
    int charcount;
    
    do
    {
	charcount=recvfrom(broadcastsocket, message, messagelength, 0,
				&fromaddr, &fromaddrlength);
	if (charcount < 0)
	{
	    if (errno == EWOULDBLOCK)
		return(0);
	    else
	    {
		perror("recvbroadcast");
		exit(-1);
	    }
	}

	if (charcount == 0)
	    break;

    } while (ignoreown &&
	     (fromaddr.sin_addr.s_addr == hostaddr.sin_addr.s_addr));

    return(charcount);
}

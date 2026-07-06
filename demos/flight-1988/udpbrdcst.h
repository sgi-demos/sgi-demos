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

#ifdef UDPBRDCSTDEF
#else
#define UDPBRDCSTDEF

#include <sys/types.h>
#ifdef _4D
#include <bsd/sys/socket.h>
#include <bsd/netinet/in.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#endif
#include <bsd/netdb.h>
#include <sys/termio.h>
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

#endif /* UDPBRDCSTDEF */

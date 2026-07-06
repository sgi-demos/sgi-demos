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

#include "flight.h"
#include <stdio.h>
#define PID_ID(p) (*(long *) &((p) -> header.zmsg[12]))
#define REC_SIZE(p) (sizeof(*p)-sizeof(struct zmsg)+sizeof(PID_ID(p)))

char *infile,*outfile;
static FILE *inf, *outf;
static int numrecs;		/* number of plane records in inf */
int enet;
int number_messages, MSG_SIZE;
static char myname[NAME_LENGTH+1];
static struct plane pbuf,	/* an extra plane structure	*/
		    mbuf,	/* used only to outout messages	*/
		    *pin;	/* pointer to input buffer	*/
Plane planes[MAX_PLANES];
Plane messages[2*MAX_PLANES];

/****************************************************************/
/*		communication routines				*/
/****************************************************************/

/* init ethernet interface, discard my packets, no debug	*/
InitComm (game)
    char *game;
{
    char buf[80];
    register char *name;
    register int i;
    register Plane pp;
    extern char *getenv();

    pin = &pbuf;
    MSG_SIZE = ((int)&mbuf.mtype)-(int)&mbuf.azimuth;
    number_messages = 0;
    for (i = 0; i < MAX_PLANES; i++) {
	pp = (Plane) malloc (sizeof (struct plane));
	pp -> alive = -1;
	planes [i] = pp;
	pp = (Plane) malloc (sizeof (struct plane));
	pp -> alive = -1;
	messages [i] = pp;
	pp = (Plane) malloc (sizeof (struct plane));
	pp -> alive = -1;
	messages [i+MAX_PLANES] = pp;
    }
    pp = planes[0];
    if (infile || outfile) {
	numrecs = 0;
	if (infile) {
	    inf = fopen (infile,"r");
	    if (inf == NULL) {
		fprintf (stderr,"input file '%s' not found\n",infile);
		exit (3);
	    }
	    fread (&numrecs,sizeof(numrecs),1,inf);
	}
	if (outfile) {
	    outf = fopen (outfile,"w");
	    if (outf == NULL) {
		fprintf (stderr,"could not open output file '%s'\n",outfile);
		exit (3);
	    }
	    numrecs++;
	    fwrite (&numrecs,sizeof(numrecs),1,outf);
	    numrecs--;
	}
	PLANE_ID(pp) = getpid ();
	PID_ID(pp) = PLANE_ID(pp);
	enet = -1;
    }
    else {
	enet = zinit (pp,"dogfight",TRUE,FALSE);
	if (enet < 0) {
	    gexit ();
	    fprintf (stderr,"Ethernet init failed\n");
	    exit (enet);
	}
    }

    pp -> myname[0] = '\0';
    name = getenv("DOGID");
    if (name && *name)
    then strncpy (pp -> myname, name, NAME_LENGTH);
    else if (game) while (!pp -> myname[0]) 
	 get_text ("Enter your name: ",&pp -> myname[0], NAME_LENGTH);
    pp -> version = 5;
    pp -> cmd = DATA_PACKET;
    pp -> won = 0;
    pp -> lost = 0;

    mbuf = *pp;			/* init msg packet	*/
    mbuf.cmd = MSG_PACKET;
    mbuf.status = MSTART;
    if (game) {
	sprintf (buf,"joining the dogfight as a %s",game);
	broadcast (buf);
    }
}

ExitComm ()
{
    broadcast ("signing off");
    replacecolors();
    greset ();
    color (BLACK);
    clear ();
    if (inf != NULL) fclose (inf);
    if (outf != NULL) fclose (outf);
}

/* return a pointer to a new message pointer	*/
Plane *new_msg()
{
    register Plane *m;

    m = &messages[number_messages];	/* return pointer to last msg	*/
    number_messages++;			/* bump count		*/
    ringbell ();			/* and ring bell	*/
    return (m);
}

/* find the plane whose enet id matches pfind, return it if found */
Plane lookup_plane (id)
    register long id;
{
    register Plane p, *pp;

    FOR_EACH_PLANE (p,pp) {
	if (id == PLANE_ID(p)) then return (p);
    }
    return (NULL);
}

/* find the plane whose enet id matches pfind, create one if needed */
Plane *find_plane (pfind)
    Plane pfind;
{
    register long id;
    register Plane p, *pp;

    id = PLANE_ID (pfind);
    FOR_EACH_PLANE (p,pp) {
	if (id == PLANE_ID(p)) then return (pp-1);
    }
    addplane (pfind);		/* call user routine	*/
    return (pp-1);		/* return pointer	*/
}

/* decrement each planes alive counter and check if its dead	*/
check_alive (dec)
    register int dec;
{
    register int n;
    register Plane p, *pp, temp;

    FOR_EACH_PLANE (p,pp) {		/* for each alive plane		*/
	p -> alive -= dec;		/* decrement alive counter	*/
	if (p -> alive <= 0) {		/* if its dead			*/
	    n = delplane (p);		/* call user routine		*/
	    temp = *--pp;		/* swap last with dead plane	*/
	    *pp++ = planes[n];
	    planes[n] = temp;
	}
    }
    FOR_EACH_MSG (p,pp) {		/* for each alive message	*/
	p -> alive -= dec;		/* decrement alive counter	*/
	if (p -> alive <= 0) {		/* if its dead			*/
	    number_messages--;
	    temp = *--pp;		/* swap last with dead message	*/
	    *pp++ = messages[number_messages];
	    messages[number_messages] = temp;
	}
    }
}

kill_obsolete ()
{
    kill_me("You are running an obsolete version, try copying a new version");
}

kill_me (msg)
    char *msg;
{
    gexit ();
    fprintf (stderr,msg);	fprintf (stderr,"\n");
    exit (1);
}

/* get other planes data into global data structures	*/
/* returns whether this plane got blown up or not	*/
Plane get_indata (count)
    int count;
{
    register Plane p, *pp, retval;

#ifdef DEBUG
if (debug & (1<<9)) printf ("---------- get_indata -------------\n");
#endif

    retval = NULL;
    check_alive (count);
    /* read all packets that are there	*/
    while (enet >= 0 ? zrecv (enet, pin, sizeof (*pin),0) : readfile(pin))
    switch (pin -> cmd) {
	case DATA_PACKET:
	    if (pin -> mstatus && pin -> mkill == PLANE_ID (&mbuf))
	    then retval = pin;		/* see if he killed me	*/
	    pp = find_plane (pin);	/* find the plane	*/
#ifdef DEBUG
if (debug & (1<<9)) {
    printf("%16s (%4d,%4d) mst:%3d %2d  mpos:%6d %6d %6d\n",
		pin -> myname,
		pin -> type, pin -> status,
		pin -> mstatus, pin -> mtype,
		(int)pin -> mx, (int)pin -> my, (int)pin -> mz);
}
#endif
	    p = *pp;			/* and swap data	*/
	    *pp = pin;
	    pin = p;
	    break;
	case MSG_PACKET:
	case SUPERKILL_PACKET:	
	    if (pin -> version < mbuf.version) {
		mbuf.cmd = KILL_PACKET;	/* send out a kill cmd	*/
		send_outdata (&mbuf);
		mbuf.cmd = MSG_PACKET;	/* restore it to msg	*/
	    }
	    if (*(long *)&pin -> won == NULL_PLANE_ID ||
		*(long *)&pin -> won == PLANE_ID(&mbuf))
	    {			/* if broadcast or sent to me	*/
		if (pin -> cmd == SUPERKILL_PACKET)
		then kill_me ("You were logged off by a wizard");
		pp = new_msg ();	/* grab a new message	*/
		p = *pp;		/* and swap data	*/
		*pp = pin;
		pin = p;
	    }
	    break;
	case KILL_PACKET:	
	    if (pin -> version > mbuf.version) then kill_obsolete ();
	    break;
	default:			/* unknown packet type	*/
	    kill_obsolete ();		/* say bye bye		*/
    }
    return (retval);
}

readfile (p)
    register Plane p;
{
    static int count;

    if (inf == NULL) return (0);
    if (count==numrecs) return (count = 0);
    if (fread (&PID_ID(p),REC_SIZE(p),1,inf) == 0) {
	register Plane pmsg;
    
	fseek(inf,4,0);			/* reposition on byte 4	*/
	pmsg = *new_msg ();		/* grab a new msg	*/
	pmsg -> alive = TPS * 4;
	strncpy (pmsg -> myname,"disk reader",NAME_LENGTH);
	*(long *)&pmsg -> won = NULL_PLANE_ID;
	strncpy (&pmsg -> azimuth,"end of file - starting over",MSG_SIZE);

	if (fread (&PID_ID(p),REC_SIZE(p),1,inf) == 0)
	fprintf (stderr, "comm: fread returned 0\n");
    }
    PLANE_ID(p) = PID_ID(p);
    if (p -> cmd == DATA_PACKET) then count++;
    if (outf) then fwrite (&PID_ID(p),REC_SIZE(p),1,outf);
    return (1);
}

/* send out my plane's data	*/
send_outdata (p)
    register Plane p;
{
    static unsigned short last_status = MSTART;

    if (enet >= 0) {
	if (last_status > 0) zsend (enet,p,sizeof (*p));
    }
    else if (outf) then fwrite (&PID_ID(p),REC_SIZE(p),1,outf);

    last_status = p -> status + p -> mstatus;
}

broadcast (msg)
    char *msg;
{
    register Plane p;

    send_message (msg,NULL_PLANE_ID);
    p = *new_msg ();			/* grab a new msg	*/
    *p = mbuf;				/* copy data to it	*/
}

send_message (msg,to)
    char *msg;
    long to;
{
    register Plane psend;

    psend = &mbuf;
    psend -> alive = TPS * 4;
    *(long *)&psend -> won = to;
    strncpy (&psend -> azimuth,msg,MSG_SIZE);
    if (!strcmp(msg,"SUPERKILL")) {
	psend -> cmd = SUPERKILL_PACKET;
	send_outdata (psend);
	psend -> cmd = MSG_PACKET;
    }
    else send_outdata (psend);
}

#define llx 200
#define urx (llx+600)
#define lly 500
#define ury (lly+40)

get_text (prompt, user_buf, maxlen)
    char *prompt, *user_buf;
    int maxlen;
{
    short type,val;
    char strbuf[132];
    register char c, *str, *end;

    viewport (llx,urx,lly,ury);
    ortho2 (llx-.5,urx+.5,lly-.5,ury+.5);
    writemask (0xffff);
    end = strbuf + maxlen +1;
    cursoff ();

ctrlu:
    str = strbuf;
    *str++ = '_';
    *str = '\0';

    while (1) {
	color (black);
	clear ();
	color (white);
	recti (llx,lly,urx,ury);
	cmov2i (llx+12,lly+10);
	charstr (prompt);
	charstr (strbuf);
	swapbuffers ();

	type = qread (&val);
	if (type == KEYBD) {
	    c = val;
	    if (c == '\r') then goto all_done;
	    else if (c == '') then goto ctrlu;
	    else if (c == '' || c == '') {
		if (str-1 != strbuf) {	/* if not at start	*/
		    str -= 2;		/* then backup 2 chars	*/
		    *str++ = '_';	/* reinsert cursor, null*/
		    *str = '\0';
		}
	    }
	    else if (c >= ' ') {	/* if its a valid char	*/
		if (str < end) {	/* check to see if there's room	*/
		    *--str = c;
		    *++str = '_';	/* reinsert cursor, null*/
		    *++str = '\0';
		}
		else ;
	    }
	}
	else;				/* not a keyboard */
    }

all_done:
    *--str = '\0';			/* remove cursor	*/
    strcpy (user_buf,strbuf);
    curson ();
}

#define DY 10;
draw_messages ()
{
    register int y;
    register Plane p,*pp;

    color (orange);
    y = 80;
    FOR_EACH_MSG (p,pp) {
	cmov2i (-195,y);
	if (*(long *)&p -> won == NULL_PLANE_ID)
	then charstr ("Broadcast message from ");
	else charstr ("Message from ");
	charstr (p -> myname);
	charstr (": ");
	charstr (&p -> azimuth);
	y -= DY;
    }
}


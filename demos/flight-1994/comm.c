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
 *  flight/comm.c $Revision: 1.1 $
 */

#include "flight.h"
#include <stdio.h>
#include "udpbrdcst.h"


#define PID_ID(p) ((p)->planeid)
#define REC_SIZE(p) sizeof(*p)

int enet;
struct sockaddr_in dogaddr;
struct sockaddr_in hostaddr;

int number_messages, MSG_SIZE;
static char myname[NAME_LENGTH+1];
static struct plane pbuf,	/* an extra plane structure	*/
		    mbuf,	/* used only to outout messages	*/
		    *pin;	/* pointer to input buffer	*/
Plane planes[MAX_PLANES];
Plane plane_futures[MAX_PLANES];
Plane messages[2*MAX_PLANES];
Plane_hist plane_hists[MAX_PLANES];

/*
 *  airshow input/output file control
 */
char *infile, *outfile;
FILE *inf, *outf;
static int numrecs;		/* number of plane records in inf */
int read_pause = FALSE;
int read_reset = FALSE;
int read_backwards = FALSE;
float read_speed = 1.0;




/****************************************************************/
/*		communication routines				*/
/****************************************************************/

/* init ethernet interface, discard my packets, no debug	*/
InitComm(game)
    char *game;
{
    char buf[80];
    register char *name;
    register int i;
    register Plane pp;
    register Plane_hist pph;
    extern char *getenv();

    pin = &pbuf;
    MSG_SIZE = ((int)&mbuf.mtype)-(int)&mbuf.azimuth;
    number_messages = 0;
    for (i = 0; i < MAX_PLANES; i++)
    {
	pp = (Plane)malloc(sizeof(struct plane));
	pp->alive = -1;
	planes[i] = pp;
	pp = (Plane)malloc(sizeof(struct plane));
	pp->alive = -1;
	messages[i] = pp;
	pp = (Plane)malloc(sizeof(struct plane));
	pp->alive = -1;
	messages[i+MAX_PLANES] = pp;
	pph = (Plane_hist)malloc(sizeof(struct plane_hist));
	pph->malive = 0;
	plane_hists[i] = pph;
	if (infile)
	{
	    pp = (Plane)malloc(sizeof(struct plane));
	    pp->alive = -1;
	    plane_futures[i] = pp;
	}
    }
    pp = planes[0];
    if (infile || outfile)
    {
	numrecs = 0;
	if (infile)
	{
	    inf = fopen(infile, "r");
	    if (inf == NULL)
	    {
		fprintf(stderr, "input file '%s' not found\n", infile);
		exit(3);
	    }
	    fread(&numrecs, sizeof(numrecs), 1, inf);
	}
	if (outfile)
	{
	    outf = fopen(outfile, "w");
	    if (outf == NULL)
	    {
		fprintf(stderr, "could not open output file '%s'\n", outfile);
		exit(3);
	    }
	    numrecs++;
	    fwrite(&numrecs, sizeof(numrecs), 1, outf);
	    numrecs--;
	}
	PLANE_ID(pp) = getpid();
	PID_ID(pp) = PLANE_ID(pp);
	enet = -1;
    }
    else
    {
	enet = getbroadcast("sgi-dogfight", &dogaddr);
	gethostaddr(&hostaddr);
	PLANE_ID(pp) = hostaddr.sin_addr.s_addr;
	PID_ID(pp) = PLANE_ID(pp);
	if (enet < 0)
	{
	    /*
	     *  exit graphics
	     */
	    restore_map();
	    drawmode(PUPDRAW);
	    color(0);
	    clear();
	    drawmode(UNDERDRAW);
	    color(0);
	    clear();
	    gexit();

	    if (enet == -2)
		udp_warning();
	    else
		fprintf(stderr, "Ethernet init failed\n");

	    exit(enet);
	}
    }

    pp->myname[0] = '\0';
    name = getenv("DOGID");
    if (name && *name)
	strncpy(pp->myname, name, NAME_LENGTH);
    else if (game)
	while (!pp->myname[0])
	    get_text("Enter your name: ", &pp->myname[0], NAME_LENGTH);
    pp->version = 5;
    pp->cmd = DATA_PACKET;
    pp->won = 0;
    pp->lost = 0;

    mbuf = *pp;			/* init msg packet	*/
    mbuf.cmd = MSG_PACKET;
    mbuf.status = MSTART;
    if (game)
    {
	sprintf(buf, "joining the dogfight as a %s", game);
	broadcast(buf);
    }
}

ExitComm()
{
    broadcast("signing off");

    if (inf != NULL)
	fclose(inf);
    if (outf != NULL)
	fclose(outf);
}

/* return a pointer to a new message pointer	*/
Plane *new_msg()
{
    register Plane *m;

    m = &messages[number_messages];	/* return pointer to last msg	*/
    number_messages++;			/* bump count		*/
    ringbell();				/* and ring bell	*/
    return(m);
}

/* find the plane whose enet id matches pfind, return it if found */
Plane lookup_plane(id)
    register long id;
{
    register Plane p, *pp;

    FOR_EACH_PLANE (p, pp)
    {
	if (id == PLANE_ID(p))
	    return(p);
    }
    return(NULL);
}

/* find the plane whose enet id matches pfind, create one if needed */
Plane *find_plane(pfind)
    Plane pfind;
{
    register long id;
    register Plane p, *pp;

    id = PLANE_ID(pfind);
    FOR_EACH_PLANE (p, pp)
    {
	if (id == PLANE_ID(p))
	    return(pp-1);
    }

    /*
     *  This is a new plane
     */
    addplane(pfind);		/* call user routine	*/
    bcopy(pfind, p, sizeof(*p));
    return(pp-1);		/* return pointer	*/
}

/*
 *  decrement each planes alive counter and check if its dead
 */
check_alive(dec)
    register int dec;
{
    register int n;
    register Plane p, *pp, *ppf, temp;
    register Plane_hist ph, *pph, htemp;

    FOR_EACH_PLANE_AND_HIST (p, pp, ph, pph)	/* for each alive plane	*/
    {
	p->alive -= dec;		/* decrement alive counter	*/
	if (p->alive <= 0)		/* if its dead			*/
	{
	    n = delplane(p);		/* call user routine		*/

	    /*
	     *  swap last with dead plane
	     */
	    temp = *--pp;
	    *pp++ = planes[n];
	    planes[n] = temp;
	    htemp = *--pph;
	    *pph++ = plane_hists[n];
	    plane_hists[n] = htemp;
	    if (inf)
	    {
		ppf = pp - planes + plane_futures;
		temp = *--ppf;
		*ppf++ = plane_futures[n];
		plane_futures[n] = temp;
	    }
	}
    }
    FOR_EACH_MSG (p, pp)		/* for each alive message	*/
    {
	p->alive -= dec;		/* decrement alive counter	*/
	if (p->alive <= 0)		/* if its dead			*/
	{
	    number_messages--;
	    temp = *--pp;		/* swap last with dead message	*/
	    *pp++ = messages[number_messages];
	    messages[number_messages] = temp;
	}
    }
}


kill_obsolete()
{
    kill_me("You are running an obsolete version, try copying a new version");
}


kill_me(msg)
    char *msg;
{
    gexit();
    fprintf(stderr, msg);	fprintf(stderr, "\n");
    exit(1);
}



/*
 *  get other planes data into global data structures
 *  returns whether this plane got blown up or not
 */
Plane get_indata(count)
    int count;
{
    register Plane p, *pp, retval;
    Plane pf, *ppf, ptmp;
    float current_time;
    static float future_time = 0.0;
    float last_m[MAX_PLANES][4];
    int i;

    retval = NULL;

    if (read_pause)
	return(retval);

    /*
     *  throw out stale airplanes
     */
    check_alive(count);

    if (inf)
    {
	if (read_reset)
	    future_time = 0.0;

	current_time = (1.0 / tps) * read_speed;

	FOR_EACH_PLANE_I (i, p)
	    if (last_m[i][3] = p->mstatus)
	    {
		last_m[i][0] = p->mx;
		last_m[i][1] = p->my;
		last_m[i][2] = p->mz;
	    }
    }

    /*
     *  read all packets that are there
     */
    while (1)
    {
	if (inf && future_time > 0.0)
	{
	    if (current_time >= future_time)
	    {
		current_time -= future_time;
		future_time = 0.0;

		FOR_EACH_PLANE_AND_FUTURE (p, pp, pf, ppf)
		{
		    ptmp = *--pp;
		    *pp++ = *--ppf;
		    *ppf++ = ptmp;
		}
	    }
	    else
	    {
		FOR_EACH_PLANE_AND_FUTURE (p, pp, pf, ppf)
		    partial_plane_move(p, pf, current_time / future_time);

		future_time -= current_time;
		current_time = 0.0;
	    }

	    if (current_time == 0.0)
	    {
		FOR_EACH_PLANE_I (i, p)
		{
		    if (last_m[i][3])
		    {
			p->last_mx = last_m[i][0];
			p->last_my = last_m[i][1];
			p->last_mz = last_m[i][2];
		    }
		    if (outf)
			fwrite(&PID_ID(p), REC_SIZE(p), 1, outf);
		}
		return(retval);
	    }
	}

	while ((enet >= 0)? recvbroadcast(enet, pin, sizeof(*pin), IGNOREOWNMSG)
			    :
			    read_infile(pin, current_time))
	    switch (pin->cmd)
	    {
		case DATA_PACKET:
		    convert_planetype(pin);

		    /*
		     *  see if he killed me
		     */
		    if (pin->mstatus && pin->mkill == PLANE_ID(&mbuf))
			retval = pin;		/* he killed me	*/

		    /*
		     *  find the plane
		     */
		    pp = find_plane(pin);

		    /*
		     *  and swap the data
		     */
		    if (inf)
		    {
			future_time = 1.0 / pin->tps;
			pin->tps = tps;

			ppf = pp - planes + plane_futures;
			p = *ppf;
			*ppf = pin;
			pin = p;
		    }
		    else
		    {
			p = *pp;
			*pp = pin;
			pin = p;
		    }
		    break;
		case MSG_PACKET:
		case SUPERKILL_PACKET:
		    if (pin->version < mbuf.version)
		    {
			mbuf.cmd = KILL_PACKET;	/* send out a kill cmd	*/
			send_outdata(&mbuf);
			mbuf.cmd = MSG_PACKET;	/* restore it to msg	*/
		    }
		    if (*(long *)&pin->won == NULL_PLANE_ID ||
			*(long *)&pin->won == PLANE_ID(&mbuf))
		    {				/* if broadcast or sent to me */
			if (pin->cmd == SUPERKILL_PACKET)
			    kill_me("You were logged off by a wizard");
			pp = new_msg();		/* grab a new message	*/
			p = *pp;		/* and swap data	*/
			*pp = pin;
			pin = p;
		    }
		    break;
		case KILL_PACKET:
		    if (pin->version > mbuf.version)
			kill_obsolete();
		    break;
		default:			/* unknown packet type	*/
		    kill_obsolete();		/* say bye bye		*/
	    }

	if (!inf)
	    return(retval);
    }
}

int read_infile(Plane p, float current_time)
{
    static int count;

    if (inf == NULL)
	return(0);

    if (read_reset)
    {
	fseek(inf, 4, SEEK_SET);		/* reposition on byte 4	*/
	read_reset = FALSE;
    }

    if (count == numrecs)
	return(count = 0);

    if (read_backwards)
    {
	if (fseek(inf, -2 * sizeof(*p), SEEK_CUR) || ftell(inf) <= 0)
	    fseek(inf, -sizeof(*p), SEEK_END);
    }

    if (fread(&PID_ID(p), REC_SIZE(p), 1, inf) == 0)
    {
	register Plane pmsg;

	fseek(inf, 4, SEEK_SET);		/* reposition on byte 4	*/
	pmsg = *new_msg();			/* grab a new msg	*/
	pmsg->alive = TPS * 4;
	strncpy(pmsg->myname, "disk reader", NAME_LENGTH);
	*(long *)&pmsg->won = NULL_PLANE_ID;
	strncpy(&pmsg->azimuth, "end of file - starting over", MSG_SIZE);

	if (fread(&PID_ID(p), REC_SIZE(p), 1, inf) == 0)
	    fprintf(stderr, "comm: fread returned 0\n");
    }

    PLANE_ID(p) = PID_ID(p);
    if (p->cmd == DATA_PACKET)
	count++;
    if (outf && p->cmd != DATA_PACKET)
	fwrite(&PID_ID(p), REC_SIZE(p), 1, outf);
    return(1);
}


rewind_if(d)
{
    register Plane p;

    if (inf)
    {
	fseek(inf, REC_SIZE(p)*d, SEEK_CUR);
	if (ftell(inf) <= 3)
	    fseek(inf, 4, SEEK_SET);		/* reposition on byte 4	*/
    }
}

/* send out my plane's data	*/
send_outdata(p)
    register Plane p;
{
    static unsigned short last_status;

    last_status = MSTART;

    p->tps = tps;

    if (enet >= 0)
    {
	if (last_status > 0)
	    sendbroadcast(enet, p, sizeof(*p), &dogaddr);
    }
    else if (outf)
	fwrite(&PID_ID(p), REC_SIZE(p), 1, outf);

    last_status = p->status + p->mstatus;
}

broadcast(msg)
    char *msg;
{
    register Plane p;

    if (dogfight)
    {
	send_message(msg, NULL_PLANE_ID);
	p = *new_msg();			/* grab a new msg	*/
	*p = mbuf;			/* copy data to it	*/
    }
}

send_message(msg, to)
    char *msg;
    long to;
{
    register Plane psend;

    psend = &mbuf;
    psend->alive = TPS * 4;
    *(long *)&psend->won = to;
    strncpy(&psend->azimuth, msg, MSG_SIZE);

    if (!strcmp(msg, "SUPERKILL"))
    {
	psend->cmd = SUPERKILL_PACKET;
	send_outdata(psend);
	psend->cmd = MSG_PACKET;
    }
    else
	send_outdata(psend);
}


#define llx 200
#define urx (llx+600)
#define lly 500
#define ury (lly+40)

get_text(prompt, user_buf, maxlen)
    char *prompt, *user_buf;
    int maxlen;
{
    short type, val;
    char strbuf[132];
    register char c, *str, *end;

    viewport(llx, urx, lly, ury);
    ortho2(llx-.5, urx+.5, lly-.5, ury+.5);
    end = strbuf + maxlen +1;
    cursoff();

ctrlu:
    str = strbuf;
    *str++ = '_';
    *str = '\0';

    while (1)
    {
	COLOR(C_BLACK);
	clear();
	COLOR(C_WHITE);
	recti(llx, lly, urx, ury);
	cmov2i(llx+12, lly+10);
	charstr(prompt);
	charstr(strbuf);
	swapbuffers();

	type = qread(&val);
	if (type == KEYBD)
	{
	    c = val;
	    if (c == '\r')
		goto all_done;
	    else if (c == '')
		goto ctrlu;
	    else if (c == '' || c == '')
	    {
		if (str-1 != strbuf)	/* if not at start	*/
		{
		    str -= 2;		/* then backup 2 chars	*/
		    *str++ = '_';	/* reinsert cursor, null*/
		    *str = '\0';
		}
	    }
	    else if (c >= ' ')		/* if its a valid char	*/
	    {
		if (str < end)		/* check to see if there's room	*/
		{
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
    strcpy(user_buf, strbuf);
    curson();
    COLOR(C_BLACK);
    clear();
    swapbuffers();
    clear();
}



draw_messages()
{
    register Plane p, *pp;
    register int y, dy;

    COLOR(C_ORANGE);
    if (hud)
    {
	y = ymaxscreen - 44;
	dy = 24;
    }
    else if (shadow)
    {
	y = 180;
	dy = 10;
    }
    else
    {
	y = 80;
	dy = 10;
    }

    FOR_EACH_MSG (p, pp)
    {
	if (hud)
	    cmov2i(50, y);
	else
	    cmov2i(-195, y);
	if (*(long *)&p->won == NULL_PLANE_ID)
	    charstr("Broadcast message from ");
	else
	    charstr("Message from ");
	charstr(p->myname);
	charstr(": ");
	charstr((char *)(&p->azimuth));
	y -= dy;
    }
}


udp_warning()
{
    printf("\n");
    printf("To run dog over the network you must have the following line\n");
    printf("in your /etc/services file.\n");
    printf("\n");
    printf("sgi-dogfight	5130/udp		# dogfight demo\n");
    printf("\n");
    printf("WARNING some machines can not handle large numbers of udp\n");
    printf("broadcast packets.  If you have machines from other vendors\n");
    printf("on your network, running dog on your network may bring them\n");
    printf("to a halt.  VAXes are known to have this problem.\n");
}


/*
 *  old plane types
 *  currently used on 3XXX and non GT 4Ds
 */
#define OLD_C150 1000
#define OLD_B747 1010
#define OLD_F15  1020
#define OLD_F16  1030
#define OLD_F18  1040
#define OLD_P38  1050
#define OLD_F16W 1060
#define OLD_P38W 1070


/*
 *  convert plane types from old form to new
 */
convert_planetype(p)
    struct plane *p;
{
    if (p->type >= OLD_C150 && p->type <= OLD_P38W)
	switch(p->type)
	{
	    case OLD_C150:
		p->type = C150;
		break;
	    case OLD_B747:
		p->type = B747;
		break;
	    case OLD_F15:
		p->type = F15;
		break;
	    case OLD_F16:
	    case OLD_F16W:
		p->type = F16;
		break;
	    case OLD_F18:
		p->type = F18;
		break;
	    case OLD_P38:
	    case OLD_P38W:
		p->type = P38;
		break;
	    default:
		printf("Unknown plane type\n");
	}
}


#define NORMALIZE(A, B);	\
{				\
    i = B - A;			\
    if (i >= 1800)		\
	A += 3600;		\
    else if (i <= -1800)	\
	B += 3600;		\
}

void partial_plane_move(Plane p0, Plane p1, float percent)
{
    int i;

    p0->x += (p1->x - p0->x) * percent;
    p0->y += (p1->y - p0->y) * percent;
    p0->z += (p1->z - p0->z) * percent;

    NORMALIZE(p0->azimuth, p1->azimuth);
    p0->azimuth += (p1->azimuth - p0->azimuth) * percent;
    NORMALIZE(p0->elevation, p1->elevation);
    p0->elevation += (p1->elevation - p0->elevation) * percent;
    NORMALIZE(p0->twist, p1->twist);
    p0->twist += (p1->twist - p0->twist) * percent;

    if (p0->mstatus)
    {
	p0->mx += (p1->mx - p0->mx) * percent;
	p0->my += (p1->my - p0->my) * percent;
	p0->mz += (p1->mz - p0->mz) * percent;
    }
}

/*
 * Copyright 1990, 1991, 1992, 1993, 1994, Silicon Graphics, Inc.
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
 *  radar.c $Revision: 1.1 $
 */

#include "flight.h"
#include "udpbrdcst.h"
#include <stdio.h>

#define MAX_RADAR_MODE 1

static char *buffers[MAX_PLANES+6];
int do_send;
int vcx, vcy;
float stw, vsx, usx, usy, ucx, ucy;

int plane_colors[8] = {C_ORANGE, C_HBLUE, C_RED, C_WHITE,
		       C_BLUE, C_PURPLE_0, C_YELLOW, C_GREEN};

radar_hist_t radar_history[MAX_PLANES];
int draging = FALSE;

int radar_mode;
long old_mousex, old_mousey;


void radar_start()
{
    char **msg;
    int i;

    for (i = 0; i < MAX_PLANES; i++)
	radar_history[i].id = NULL_PLANE_ID;

    debug = 0;
    radar_mode = 1;
    dogfight = 1;
    ucx = 0.0;
    ucy = 5000.0;
    usx = 70000.0;
    reset_winodow_size();
    rebuild_ortho();

    for (msg = buffers;
	 msg < buffers+MAX_PLANES+6;
	 *msg++ = (char *)malloc(132));
}


void radar_loop()
{
    while (1)
    {
	/*
	 *  read all input commands
	 */
	radar_read_queue();

	if (do_send)
	{
	    char buf[132], prompt[80];
	    float fmx, fmy;
	    register Plane p;
	    extern int MSG_SIZE;

	    fmx = (getvaluator(MOUSEX)-vcx) * stw + ucx;
	    fmy = (getvaluator(MOUSEY)-vcy) * stw + ucy;
	    if (do_send == MOUSE2)
	    {
		get_text("Enter message to broadcast: ", buf, MSG_SIZE);
		if (*buf)
		    broadcast(buf);
	    }
	    else if (p = radar_find_closest_plane(fmx, -fmy))
	    {
		sprintf(prompt, "Enter message to send to %s: ", p->myname);
		get_text(prompt, buf, MSG_SIZE);
		if (*buf)
		    send_message(buf, PLANE_ID(p));
	    }
	    do_send = FALSE;
	}

	/*
	 *  start up the screen clear
	 */
	switch (radar_mode)
	{
	    case 0:
		reshapeviewport();
		COLOR(C_BLUE);
		clear();
		break;
	    case 1:
		reshapeviewport();
		COLOR(C_BLACK);
		clear();
		break;
	}

	/*
	 *  read all packets that are there
	 */
	get_indata(1);			/* read new data */
	gather_radar_history();		/* copy data into radar_hist */

	/*
	 *  draw the screen
	 */
	switch (radar_mode)
	{
	    case 0:
		radar_text();
		break;
	    case 1:
		if (draging)
		{
		    mousex = getvaluator(MOUSEX);
		    mousey = getvaluator(MOUSEY);
		    do_pan(stw * (old_mousex - mousex),
			   stw * (old_mousey - mousey));
		    old_mousex = mousex;
		    old_mousey = mousey;
		}
		radar_picture();
		break;
	}

	/*
	 *  display any network messages
	 */
	ortho2(-200.0, 200.0, -300.0, 100.0);
	draw_messages();

	swapbuffers();
    }
}


void radar_read_queue()
{
    short type, val;

    /*
     *  read all input commands
     */
    while (qtest())
    {
	switch (type = qread(&val))
	{
	    case REDRAW:
		reset_winodow_size();
		rebuild_ortho();
		break;
	    case INPUTCHANGE:
		if (!val)
		    draging = FALSE;
		break;
	    case KEYBD:
		switch (val)
		{
		    case 27:		/* ESC */
			end_of_program();
			break;
		    case 'x':
		    case 'z':
			if (radar_mode == 1)
			{
			    if (val == 'x')
				usx *= .9;
			    else
				usx /= .9;
			    rebuild_ortho();
			}
			break;
		    case 'h':
			show_help = !show_help;
			break;
		    case ' ':
			radar_mode++;
			if (radar_mode > MAX_RADAR_MODE)
			    radar_mode = 0;
			break;
#ifdef DEBUG
		    default:
			if (val >= '0' && val <= '9')
			    debug ^= 1 << (val-'0');
			break;
#endif
		}
		break;
	    case MOUSE1:
		draging = val;
		if (val && radar_mode == 1)
		{
		    old_mousex = getvaluator(MOUSEX);
		    old_mousey = getvaluator(MOUSEY);
		}
		break;
	    case MOUSE2:
	    case MOUSE3:
		if (val && radar_mode == 1)
		    do_send = type;
		break;
	    case LEFTARROWKEY:
		if (val && radar_mode == 1)
		    do_pan(-10000.0, 0.0);
		break;
	    case RIGHTARROWKEY:
		if (val && radar_mode == 1)
		    do_pan(10000.0, 0.0);
		break;
	    case UPARROWKEY:
		if (val && radar_mode == 1)
		    do_pan(0.0, 10000.0);
		break;
	    case DOWNARROWKEY:
		if (val && radar_mode == 1)
		    do_pan(0.0, -10000.0);
		break;
	}
    }
}


void reset_winodow_size()
{
    long xorig, yorig, xsize, ysize;

    getsize(&xsize, &ysize);
    getorigin(&xorig, &yorig);
    vsx = xsize/2-1;
    vcx = xsize/2 + xorig;
    vcy = ysize/2 + yorig;
}


void rebuild_ortho()
{
    usy = usx * (YMAXSCREEN+1.0)/(XMAXSCREEN+1.0);
    stw = usx/vsx;
}


void do_pan(float dx, float dy)
{
    ucx += dx;
    ucy += dy;
    rebuild_ortho();
}


void reset_radar_hist(radar_hist_t *rh)
{
    register int i;

    rh->velocity = 0;
    rh->vx = 0.0;
    rh->vy = 0.0;
    rh->vz = 0.0;
    for (i=0; i<RADAR_HISTORY; i++)
	rh->status[i] = 0;
}


/*
 *  find and return the closest plane to me
 */
Plane radar_find_closest_plane(float x, float z)
{
    register float d, dbest, temp;
    register Plane p, *pp, pbest;

    pbest = NULL;
    dbest = 1e30;

    FOR_EACH_PLANE (p, pp)		/* for each plane	*/
    {
	d = x - p->x;			/* compute distance	*/
	temp = z - p->z;
	d = d*d + temp*temp;
	if (d < dbest)			/* and compare with best */
	{
	    dbest = d;
	    pbest = p;
	}
    }
    return(pbest);
}


radar_hist_t *findit(Plane p)
{
    register long i, id;

    id = PLANE_ID(p);
    for (i=0; i < MAX_PLANES; i++)
	if (id == radar_history[i].id)
	    return(&radar_history[i]);

    printf("Oops: fatal error, findit &d, %s failed\n", id, p->myname);
    end_of_program();
}


void radar_text()
{
    register char **msg;
    register Plane p, *pp;

    msg = buffers;
    sprintf(*msg++, "  IP address        Name         (type,al)  Ver Status Won Lost       Position              Angles       MS MT");
    sprintf(*msg++, "---------------- --------------- ---------- --- ------ --- ---- ----------------------  --------------  --- --");

    FOR_EACH_PLANE (p, pp)
    {
	sprintf(*msg++,
		"%-16s %-15s (%4d,%3d)  %2d %6d %3d %4d %6d %6d %6d    %4d %4d %4d  %3d %2d",
		inet_ntoa(p->planeid),
		p->myname,
		p->type, p->alive, p->version,
		p->status, p->won, p->lost,
		(int)p->x, (int)p->y, (int)p->z,
		p->azimuth, p->elevation, p->twist,
		p->mstatus, p->mtype);
    }
    sprintf(*msg, "");
    COLOR(C_BLUE);
    clear();
    display_message_no_wait(buffers, 1);
}


void gather_radar_history()
{
    char *plane_name;
    register int tick, dt;
    register Plane p, *pp;
    register radar_hist_t *rh;
    float fps_knots;			/* fps to knots conversion factor */
    float temp;

    FOR_EACH_PLANE (p, pp)
    {
	if (p->tps > 0.0)
	    fps_knots = p->tps * 3600.0/6082.0;
	else
	    fps_knots = 20 * 3600.0/6082.0;

	rh = findit(p);
	tick = rh->n;

	if (p->status == 0)
	    reset_radar_hist(rh);
	else if ((dt=rh->status[tick]) != p->status)
	{
	    dt = p->status - dt;	/* compute delta time	*/
	    if (dt <= 0)		/* compute velocities	*/
	    {
		rh->vx = 0.0;
		rh->vy = 0.0;
		rh->vz = 0.0;
	    }
	    else
	    {
		temp = 1.0/dt;
		rh->vx = (p->x - rh->x[tick]) * temp;
		rh->vy = (p->y - rh->y[tick]) * temp;
		rh->vz = (p->z - rh->z[tick]) * temp;
	    }
	    rh->velocity = fps_knots * sqrt(rh->vx * rh->vx +
					    rh->vy * rh->vy +
					    rh->vz * rh->vz);

	    /*
	     *  copy current data into data array
	     */
	    tick++;
	    if (tick >= RADAR_HISTORY)
		tick = 0;
	    rh->n = tick;
	    rh->status[tick] = p->status;
	    rh->x[tick] = p->x;
	    rh->y[tick] = p->y;
	    rh->z[tick] = p->z;
	}

	switch (p->type)
	{
	    case C150:
		plane_name = C150_NAME;
		break;
	    case B747:
		plane_name = B747_NAME;
		break;
	    case F15:
		plane_name = F15_NAME;
		break;
	    case F16:
		plane_name = F16_NAME;
		break;
	    case F18:
		plane_name = F18_NAME;
		break;
	    case P38:
		plane_name = P38_NAME;
		break;
	    case F14:
		plane_name = F14_NAME;
		break;
	    case B727:
		plane_name = B727_NAME;
		break;
	}

	sprintf(rh->buf, "%s:%d%c%03d",
		plane_name,
		rh->velocity,
		(rh->vy >= 0.0) ? '+' : '-',
		(int)(.01 * p->y));
    }
}


void radar_picture()
{
    int plane_color;
    register int i;
    float y, dy;			/* height of text in user space */
    register Plane p, *pp;
    register radar_hist_t *rh;

    ortho2(ucx-usx, ucx+usx, ucy-usy, ucy+usy);
    pushmatrix();

    plane_color = 0;
    dy = 1.4 * getheight() * stw;	/* char height in user space */
    draw_radar_world();

    scale(1.0, -1.0, 1.0);

    /*
     *  draw planes
     */
    FOR_EACH_PLANE (p, pp)
    {
	rh = findit(p);
	COLOR(plane_colors[plane_color++]);
	plane_color &= 0x7;

	/*
	 *  draw history dots
	 */
	for (i = 0; i < RADAR_HISTORY; i+= int_tps)
	    if (rh->status[i])
		pnt2(rh->x[i], rh->z[i]);

	y = p->z;
	pushmatrix();
	translate(p->x, y, 0.0);
	rotate(-p->azimuth, 'z');
	draw_triangle();
	popmatrix();

	/*
	 *  draw velocity vector
	 */
	pnt2(p->x, y);
	draw2(p->x + RADAR_HISTORY/2*rh->vx, y + RADAR_HISTORY/2*rh->vz);

	cmov2(p->x, y += 1.4*dy);
	charstr(p->myname);

	cmov2(p->x, y += dy);
	charstr(rh->buf);

	/*
	 *  display missile if its active
	 */
	if (p->mstatus > 0)
	{
	    if (p->mtype == TYPE_CANNON)
		COLOR(C_YELLOW);
	    else if (p->mtype == TYPE_SIDEWINDER)
		COLOR(C_RED);
	    else
		COLOR(C_ORANGE);
	    pushmatrix();
	    translate(p->mx, p->mz, 0.0);
	    draw_projectile();
	    popmatrix();
	}
    }

    popmatrix();

    if (show_help)
	overlay_radar_help();
}


void draw_radar_world()
{
    static long airport[12*4][2] =
		{{ -700, 3100}, { -700, 3300}, { -100, 4000}, { -100, 3800},
		 { -700, 4700}, { -700, 4900}, { -100, 4200}, { -100, 4000},
		 { -700, 8400}, { -100, 8400}, { -100, 8500}, { -700, 8500},
		 { -700, 5900}, { -100, 5900}, { -100, 6000}, { -700, 6000},
		 {-1200, 4700}, { -800, 4700}, { -800, 4900}, {-1200, 4900},
		 {-1200, 3100}, { -800, 3100}, { -800, 3300}, {-1200, 3300},
		 {-1200, 2000}, {  700, 2000}, {  700, 2100}, {-1200, 2100},
		 { -700,    0}, { -100,    0}, { -100,  100}, { -700,  100},
		 {-2000, 2000}, {-1200, 2000}, {-1200, 4900}, {-2000, 4900},
		 {  700, 1600}, { 1000, 1600}, { 1000, 2500}, {  700, 2500},
		 { -800,    0}, { -700,    0}, { -700, 8500}, { -800, 8500},
		 { -100,    0}, {  100,    0}, {  100, 8500}, { -100, 8500}};
    register int i;

    /*
     *  grid
     */
    COLOR(C_DIRT);
    for (i = -55000; i <= 55000; i += 10000)
    {
	move2i(i, -50000);
	draw2i(i, 50000);
    }
    for (i = -50000; i <= 50000; i += 10000)
    {
	move2i(-55000, i);
	draw2i(55000, i);
    }

    /*
     *  airport
     */
    COLOR(C_GREY_8);
    for (i = 0; i < (12*4); i+=4)
    {
	bgnpolygon();
	v2i(airport[i]);
	v2i(airport[i+1]);
	v2i(airport[i+2]);
	v2i(airport[i+3]);
	endpolygon();

	bgnclosedline();
	v2i(airport[i]);
	v2i(airport[i+1]);
	v2i(airport[i+2]);
	v2i(airport[i+3]);
	endclosedline();
    }
}


void draw_projectile()
{
    static long projectile[6][2] = {{-100,    0}, { -50,  100}, {  50,  100},
				    { 100,    0}, {  50, -100}, { -50, -100}};

    bgnpolygon();
    v2i(projectile[0]);
    v2i(projectile[1]);
    v2i(projectile[2]);
    v2i(projectile[3]);
    endpolygon();

    bgnpolygon();
    v2i(projectile[0]);
    v2i(projectile[3]);
    v2i(projectile[4]);
    v2i(projectile[5]);
    endpolygon();
}


void draw_triangle()
{
    static long triangle[3][2] = {{0, 0}, {-200, 800}, {200, 800}};

    bgnclosedline();
    v2i(triangle[0]);
    v2i(triangle[1]);
    v2i(triangle[2]);
    endclosedline();
}

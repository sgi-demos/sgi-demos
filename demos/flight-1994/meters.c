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
 *  flight/meters.c $Revision: 1.1 $
 */

#include "flight.h"

extern short wm_allplanes;

static float xscale, yscale;

static int bar_max_x;
static int bar_max_y;
static float bar_ticks[9][4][2];
static float bar_nums[4][2];

static float gy_triangle[3][2];
static float horizon_mark[3][2];
static float heading_mark[3][2];


static int meter_x1, meter_x2, meter_y1, meter_y2;
static int thrust_x1;
static int heading_cx;
static int speed_x1;
static int climb_x1;
static int fuel_x1;

#define X_ADJUST(x) (int)(xscale * (x) + 0.1)
#define Y_ADJUST(y) (int)(yscale * (y) + 0.1)

#define GENBAR(x, y)				\
{						\
    move2s(-x, -y);	draw2s(x, -y);		\
    move2s(-x, y);	draw2s(x, y);		\
}


void reset_meters()
{
    clear_report_card();
    if (!hud && !new_inst && !shadow)
    {
	clear_text_display();
	draw_clear_meters();
	draw_horizon_meter();
    }
}



void redraw_screen()
{
    /*
     *  draw static stuff
     */
    viewport(0, xmaxwindow, 0, ymaxwindow);
    ortho2(-0.5, xmaxwindow+0.5, -0.5, ymaxwindow+0.5);
    COLOR(C_BLACK);
    clear();			/* clear the normal planes */
    if (!in_cmode)
	zclear();		/* clear the z planes */

    if (bits_under)
    {
	drawmode(UNDERDRAW);	/* clear the underlay planes */
	color(0);
	clear();
    }

    drawmode(over_drawmode);	/* clear the pup planes */
    color(0);
    clear();

    if (hud || shadow || radar)
    {
	drawmode(NORMALDRAW);
	return;
    }

    /*
     *  windshield
     */
    if (!in_cmode)
    {
	color(P_ORANGE);
	move2s(xmiddle, ymiddle-1);		     /* center of windshield */
	draw2s(xmiddle, ymiddle-16);
	rects(0, ymiddle-1, xmaxwindow, ymaxwindow); /* outline windshield */

	drawmode(NORMALDRAW);
    }
    else
    {
	drawmode(NORMALDRAW);

	frontbuffer(TRUE);
	color(ci_table[C_ORANGE]);
	move2s(xmiddle, ymiddle-1);		     /* center of windshield */
	draw2s(xmiddle, ymiddle-16);
	rects(0, ymiddle-1, xmaxwindow, ymaxwindow); /* outline windshield */
	frontbuffer(FALSE);
    }

    if (new_inst)
	draw_instruments();
    else
	init_meters();
}


void init_meters()
{
    init_meter_sizes((int)(62*xscale), (int)(266*yscale));

    viewport(inst_x1, inst_x2, inst_y1, inst_y2);
    ortho2(inst_x1-0.5, inst_x2+0.5, inst_y1-0.5, inst_y2+0.5);

    drawmode(over_drawmode);
    color(P_ORANGE);

    /*
     *  label meters
     */
    cmov2s(thrust_x1, meter_y1-20);		charstr("Thrust");
    cmov2s(speed_x1, meter_y1-20);		charstr("Speed");
    cmov2s(speed_x1, meter_y1-36);		charstr("knots");
    cmov2s(climb_x1, meter_y1-20);		charstr("Climb");
    cmov2s(climb_x1, meter_y1-36);		charstr(" fpm");
    cmov2s(climb_x1+70, meter_y1-20);		charstr("G-force");
    cmov2s(xmiddle-30, meter_y1-20);		charstr("Horizon");
    cmov2s(heading_cx-30, meter_y1-20);	charstr("Heading");
    cmov2s(fuel_x1+8, meter_y1-20);		charstr("Fuel");


    /*
     *  set up bar meters
     */
    pushmatrix();
    translate((float)thrust_x1, (float)meter_y1, 0.0);
    draw_meter_static();
    translate((float)(speed_x1-thrust_x1), 0.0, 0.0);
    draw_meter_static();
    translate((float)(climb_x1-speed_x1), 0.0, 0.0);
    draw_meter_static();
    translate((float)(fuel_x1-climb_x1), 0.0, 0.0);
    draw_meter_static();
    popmatrix();

    /*
     *  set up gforce meters
     */
    drawmode(over_drawmode);
    color(P_ORANGE);
    pushmatrix();
    translate(412.0*xscale, 0.0, 0.0);
    scale(xscale, yscale, 0.0);
    draw_gforce_static();
    popmatrix();

    /*
     *  set up heading/radar meter
     */
    polf2(3, heading_mark);
    pushmatrix();
    translate((float)heading_cx, 266.0*yscale, 0.0);
    scale(1.35*yscale, 1.35*yscale, 1.35*yscale);
    if (bits_under)
    {
	drawmode(UNDERDRAW);
	color(U_BROWN);
	circfs(0, 0, 102);
    }
    drawmode(over_drawmode);
    color(P_ORANGE);			/* draw plane		*/
    if (!dogfight)
    {
	move2s(0, 0);
	draw2s(2, -10);
	draw2s(12, -18);
	draw2s(12, -20);
	draw2s(2, -14);
	draw2s(2, -20);
	draw2s(5, -23);
	draw2s(-5, -23);
	draw2s(-2, -20);
	draw2s(-2, -14);
	draw2s(-12, -20);
	draw2s(-12, -18);
	draw2s(-2, -10);
	draw2s(0, 0);
    }
    else
	rectfs(-1, -1, 1, 1);
    popmatrix();

    /*
     *  set up horizon meter
     */
    polf2(3, horizon_mark);

    viewport(X_ADJUST(515), X_ADJUST(765),
	     meter_y1, meter_y2);

    ortho2(-90.0, 90.0, -90.0, 90.0);
    if (bits_under)
    {
	drawmode(UNDERDRAW);
	color(U_BROWN);
	clear();
	color(0);
	draw_blanking();
    }
    drawmode(over_drawmode);
    color(P_ORANGE);
    rectfs(-66, -2, -30, 0);		/* W	*/
    rectfs(66, -2, 30, 0);
    linewidth(2);
    move2s(33, -6);
    draw2s(20, -20);
    draw2s(0, 0);
    draw2s(-20, -20);
    draw2s(-33, -6);
    linewidth(1);
    move2s(-60, -90);	draw2s(-60, -83);	/* yaw lines	*/
    move2s(-30, -90);	draw2s(-30, -86);
    move2s(0, -90);	draw2s(0, -83);
    move2s(30, -90);	draw2s(30, -86);
    move2s(60, -90);	draw2s(60, -83);

    drawmode(NORMALDRAW);
}



/*
 *  clear the text display area
 */
void clear_text_display()
{
    viewport(X_ADJUST(124), X_ADJUST(1125), Y_ADJUST(413), Y_ADJUST(460));
    ortho2(99.0, 900.0, 300.0, 345.0);
    COLOR(C_BLACK);
    clear();
    COLOR(C_WHITE);
}

/*
 *  clear ALL the meters
 */
void draw_clear_meters()
{
    viewport(meter_x1-2, meter_x2+2, meter_y1-2, meter_y2+2);
    COLOR(C_BLACK);
    clear();
}



void draw_slow_meters()
{
    register int i;
    float r, sin, cos;
    char buf[32];

    COLOR(C_WHITE);
    pushmatrix();
    translate(457.0*xscale, -133.0/8.0/GRAVITY * lift * yscale, 0.0);
    draw_gforce();
    popmatrix();

    COLOR(C_WHITE);
    sprintf(buf, "%d", airspeed);
    cmov2s(speed_x1+8, meter_y1+5);
    charstr(buf);
    sprintf(buf, "%d", (climbspeed << 6) - (climbspeed << 2));
    cmov2s(climb_x1+3, meter_y1+5);		/* (x*64) - (x*4) */
    charstr(buf);

    /*
     *  HEADING meter
     */
    pushmatrix();
    translate((float)heading_cx, 266.0*yscale, 0.0);
    scale(1.35*yscale, 1.35*yscale, 1.35*yscale);
    if (!bits_under)
    {
	COLOR(C_INST_BROWN);
	circfs(0, 0, 102);
    }
    rotate(-azimuth, 'z');
    COLOR(C_WHITE);
    for (i = 0; i < 3600; i += 100)
    {
	gl_sincos(i, &sin, &cos);
	move2(100.0 * sin, 100.0 * cos);
	if (i == 300 || i == 600 || i == 1200 || i == 1500 ||
	    i == 2100 || i == 2400 || i == 3000 || i == 3300)
	    r = 75.0;	/* long line	*/
	else
	    r = 90.0;	/* short line	*/
	draw2(r * sin, r * cos);
    }
    move2s(-7, 60);	/* N	*/
    draw2s(-7, 80);
    draw2s(7, 60);
    draw2s(7, 80);
    move2s(60, -7);	/* E	*/
    draw2s(60, 7);
    draw2s(80, 7);
    draw2s(80, -7);
    move2s(70, 7);
    draw2s(70, -3);
    move2s(-80, -9);	/* W	*/
    draw2s(-60, -4);
    draw2s(-70, 0);
    draw2s(-60, 4);
    draw2s(-80, 9);
    move2s(-7, -78);	/* S	*/
    draw2s(-5, -80);
    draw2s(7, -80);
    draw2s(7, -70);
    draw2s(-7, -70);
    draw2s(-7, -60);
    draw2s(5, -60);
    draw2s(7, -62);
    scale(0.004, -0.004, 0.004);	/* scale down (y=-z)	*/
    draw_radar_objects();
    COLOR(C_WHITE);
    popmatrix();
}



void draw_horizon_meter()
{
    static Scoord yaw_indicator[][2] = {{0, -85}, {-4, -81}, {4, -81}};

    /*
     *  set up horizon meter
     */
    viewport(X_ADJUST(515), X_ADJUST(765), meter_y1, meter_y2);
    if (!bits_under)
    {
	COLOR(C_INST_BROWN);
	clear();
    }

    ortho2(-90.0, 90.0, -90.0, 90.0);
    pushmatrix();
    COLOR(C_BLUE);
    rotate(-twist, 'z');
    translate(0.0, -0.1 * elevation, 0.0);
    rectfs(-150, 0, 150, 500);

    COLOR(C_WHITE);
    move2s(-30, 0);	draw2s(30, 0);
    GENBAR(30, 80);
    GENBAR(10, 60);
    GENBAR(15, 40);
    GENBAR(10, 20);

    popmatrix();				/* return to ortho	*/
    COLOR(C_BLACK);
    draw_blanking();

    COLOR(C_RED);
    pushmatrix();			/* save matrix for wing_stall	*/
    translate(rudder * 75.0, 0.0, 0.0); /* map 0.8 => 60	*/
    polf2s(3, yaw_indicator);
    popmatrix();
}

void draw_wing_stall()
{
    COLOR(C_WHITE);
    cmov2s(-32, 4);
    charstr("WING-STALL");
}

void draw_g_limit()
{
    COLOR(C_WHITE);
    cmov2s(-24, 4);
    charstr("G-LIMIT");
}

void draw_auto_pilot()
{
    COLOR(C_WHITE);
    cmov2s(-40, 20);
    charstr("AUTO-PILOT");
}

void draw_crash_meters()
{
    viewport(meter_x1, meter_x2, meter_y1, meter_y2);
    COLOR(C_WHITE);
    setpattern(CRASH_PATTERN);
    clear();
    setpattern(0);
}



/************************************************************
/*	Trash procedures
/************************************************************/
void draw_blanking()
{
    static Scoord blanking1[][2] = { {91, 91}, {70, 91}, {91, 70} };
    static Scoord blanking2[][2] = { {-91, 91}, {-91, 70}, {-70, 91} };
    static Scoord blanking3[][2] = { {-91, -91}, {-70, -91}, {-91, -70} };
    static Scoord blanking4[][2] = { {91, -91}, {91, -70}, {70, -91} };

    polf2s(3, blanking1);
    polf2s(3, blanking2);
    polf2s(3, blanking3);
    polf2s(3, blanking4);
}


void draw_meter(int val)
{
    short i;

    if (val >= 0)
    {
	if (val > 100) val = 100;
	i = bar_max_y * (val / 100.0);

	if (i < bar_max_y && !bits_under)
	{
	    COLOR(C_INST_BROWN);
	    rectfs(0, i, bar_max_x, bar_max_y);
	}

	COLOR(C_BLUE);
	rectfs(0, 0, bar_max_x, i);
    }
    else
    {
	if (val < -100) val = -100;
	i = bar_max_y * (-val / 100.0);

	if (i < bar_max_y && !bits_under)
	{
	    COLOR(C_INST_BROWN);
	    rectfs(0, i, bar_max_x, bar_max_y);
	}

	COLOR(C_RED);
	rectfs(0, 0, bar_max_x, i);
    }


}


void draw_meter_bar(int val, int bar)
{
    short i;

    draw_meter(val);

    if (bar != val)
    {
	if (bar >= 0)
	{
	    COLOR(C_GREEN);
	    if (bar > 100) bar = 100;
	    i = bar_max_y * (bar / 100.0);
	}
	else
	{
	    COLOR(C_YELLOW);
	    if (bar < -100) bar = -100;
	    i = bar_max_y * (-bar / 100.0);
	}

	rectfs(0, i-2, bar_max_x, i);
    }
}



/*
 *  draw the radar display
 */
void draw_radar_objects()
{
    Plane pp, ptemp, *ptemp2;

    pp = planes[0];

    translate(-pp->x, -pp->z, 0.0);

    /*
     *  other planes
     */
    if (dogfight)
    {
	FOR_EACH_PLANE (ptemp, ptemp2)
	    if (ptemp != pp)
	    {
		if (ptemp->y <= pp->y)
		    COLOR(C_GREEN);
		else
		    COLOR(C_RED);
		if (hud)
		{
		    cmov2(ptemp->x, ptemp->z); charstr("^");
		}
		else
		    rectf(ptemp->x - 200.0, ptemp->z - 200.0,
			  ptemp->x + 200.0, ptemp->z + 200.0);
	    }
    }

    /*
     *  missiles
     */
    COLOR(C_RED);
    FOR_EACH_PLANE (ptemp, ptemp2)
	if (ptemp->mstatus && ptemp->mtype != TYPE_CANNON)
	    pnt2(ptemp->mx, ptemp->mz);

    /*
     *  the runway
     */
    COLOR(C_BLUE);
    move2(0.0, 0.0);
    draw2(0.0, -8500.0);
}



static char *numbers[] = {
	 "0",  "1",  "2",  "3",  "4",  "5",  "6",  "7",  "8",  "9",
	"10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
	"20", "21", "22", "23", "24", "25", "26", "27", "28", "29",
	"30", "31", "32", "33", "34", "35", "36", "37", "38", "39",
	"40", "41", "42", "43", "44", "45", "46", "47", "48", "49",
	"50", "51", "52", "53", "54", "55", "56", "57", "58", "59",
	"60", "61", "62", "63", "64", "65", "66", "67", "68", "69",
	"70", "71", "72", "73", "74", "75", "76", "77", "78", "79",
	"80", "81", "82", "83", "84", "85", "86", "87", "88", "89",
	"90", "91", "92", "93", "94", "95", "96", "97", "98", "99", "100"
};

static float rhaws[][2] = {     /* 20 point unit circle */
	 0.000000,  1.000000,
	 0.309017,  0.951057,
	 0.587785,  0.809017,
	 0.809017,  0.587785,
	 0.951057,  0.309017,
	 1.000000,  0.000000,
	 0.951057, -0.309017,
	 0.809017, -0.587785,
	 0.587785, -0.809017,
	 0.309017, -0.951057,
	 0.000000, -1.000000,
	-0.309017, -0.951057,
	-0.587785, -0.809017,
	-0.809017, -0.587785,
	-0.951057, -0.309017,
	-1.000000,  0.000000,
	-0.951057,  0.309017,
	-0.809017,  0.587785,
	-0.587785,  0.809017,
	-0.309017,  0.951057};

char alt_text[16];		/* global altitude text */
char mach_text[8];		/* global mach number text */
char g_text[8];			/* global g-force text */


draw_hud(p, tick, vx, vy, vz, vv, mach, gf,
	 wheels, flaps, spoilers, autop, fuel, thrust, throttle)
    register Plane p;
    int tick;
    float vx, vy, vz;
    int vv;
    float mach, gf;
    int wheels, flaps, spoilers, autop, fuel, thrust, throttle;
{
    register char buf[32];
    register int a, i, x, y;
    float k, r, sin, cos, temp;

    static float yaw_x_trans = 0.0, yaw_y_trans = 0.0;
    static int heading_rotate = 0;

    extern char alt_text[], mach_text[], g_text[];
    extern rockets, sidewinders;

#ifdef DEBUG
    if (debug & (1<<9))
    {
	ortho2(-0.5, xmaxwindow+0.5, -0.5, ymaxwindow+0.5);
	draw_report();			/* display messages	*/
	COLOR(C_ORANGE);
	goto skipit;
    }
#endif /* DEBUG */

    /* this should be moved to overlap graphics if possible	*/
    if ((tick & 3) == 2)		/* do every fourth frame */
    {
	sprintf(mach_text, "%.2f", mach);	/* update text	*/
	sprintf(g_text, "%.1f", gf);

	y = p->y;
	if (y >= 1000)
	    sprintf(alt_text, "%3d,%03d", y/1000, y%1000);
	else
	    sprintf(alt_text,"    %3d", y);
	temp = (vv < 0)? -vv : vv;
	if (temp > 300) alt_text[4] = '0';
	if (temp > 30) alt_text[5] = '0';
	alt_text[6] = '0';
    }

    COLOR(C_ORANGE);

    /*
     *  assume viewport is whole screen
    ortho2(-0.5, xmaxwindow+0.5, -0.5, ymaxwindow+0.5);
     */

    cmov2s(HUD_MARGIN-30, 30); charstr(plane_type);	/* plane's text */
    sprintf(buf, "%.1f", Lmax);
    cmov2s(HUD_MARGIN-30, 50); charstr(buf);		/* max G force */

    x = xmiddle;
    y = 75;					/* marker for heading	*/
    move2s(x, y);	draw2s(x, y+15);

    y = (ymaxwindow+1)/2;
    move2s(x+4, y);	draw2s(x+16, y);	/* nose cross hairs	*/
    move2s(x-4, y);	draw2s(x-16, y);
    move2s(x, y+4);	draw2s(x, y+16);
    move2s(x, y-4);	draw2s(x, y-16);

    x = HUD_MARGIN;				/* mach and g text	*/
    cmov2s(x, 290); charstr(g_text);
    cmov2s(x, 75); charstr(mach_text);

    y = (ymaxwindow+1)/4;
    x = HUD_MARGIN;				/* marker for airspeed	*/
    move2s(x, y);	draw2s(x+16, y);
    cmov2s(x+4, y+4); charstr("C");

    x = xmaxwindow-HUD_MARGIN;			/* marker for altitude	*/
    move2s(x, y);	draw2s(x-16, y);	/* and vv (climbspeed)	*/
    x -= 32;	y += 30*3;
    for (i=0; i<6; i++)
    {
	move2s(x, y); draw2s(x+8, y);		/* long tick	*/
	move2s(x, y-15); draw2s(x+4, y-15);	/* short tick	*/
	y -= 30;
    }
    y -= 24;
    cmov2s(x-14, y); charstr("R");		/* radar altimiter	*/
    rects(x, y-2, x+60, y+14);
    cmov2s(x-5, y); charstr(alt_text);

    pushmatrix();
    translate(0.0, vv * (60.0*30.0/1000.0) ,0.0);
    y = (ymaxwindow+1)/4;
    move2s(x, y); draw2s(x-14, y+6);		/* draw triangle	*/
    draw2s(x-14, y-6); draw2s(x, y);
    popmatrix();

    pushmatrix();
    if (vz != 0.0)
    {
	k = -57.3*(ymaxwindow+1)/36.0;	/* window is 36 degrees */
	yaw_x_trans = k*vx/vz;
	yaw_y_trans = k*vy/vz;
    }
    translate(yaw_x_trans, yaw_x_trans, 0.0);
    x = xmiddle;
    y = (ymaxwindow+1)/2;
    move2s(x+16, y);	draw2s(x+6, y);		/* draw FPM		*/
    draw2s(x+4, y+4);	draw2s(x, y+6);
    draw2s(x, y+16);
    move2s(x-16, y);	draw2s(x-6, y);
    move2s(x, y+6);	draw2s(x-4, y+4);
    draw2s(x-6, y);	draw2s(x-4, y-4);
    draw2s(x, y-6);	draw2s(x+4, y-4);
    draw2s(x+6, y);
    popmatrix();

    pushviewport();
    pushmatrix();
    viewport(8, HUD_MARGIN-50, 8, HUD_MARGIN-50); /* RHAWS scope	*/
    ortho2(-100.5, 100.5, -100.0, 100.5);
    COLOR(C_GREEN);
    pnt2s(0, 0);
    for (i = 0; i < 3600; i += 150)	/* static ticks	*/
    {
	gl_sincos(i, &sin, &cos);
	move2(100.0 * sin, 100.0 * cos);
	if (i % 900 == 0) r = 20.0;
	else if (i % 450 == 0) r = 75.0;
	else r = 88.0;
	draw2(r * sin, r * cos);
    }
    move2s(20, 0);
    if (tick < int_tps/2)			/* RHAWS ticker		*/
	draw2s(20, 8);
    else
	draw2s(20, -8);
    pushmatrix();
    scale(25.0, 25.0, 1.0);
    poly2(20, rhaws);
    scale(2.0, 2.0, 1.0);
    poly2(20, rhaws);
    scale(2.0, 2.0, 1.0);
    poly2(20, rhaws);
    popmatrix();
    if (tick & 1)				/* do every other tick	*/
	heading_rotate = -p->azimuth;
    rotate(heading_rotate, 'z');
    scale(0.004, -0.004, 0.004);	/* scale down (y=-z)	*/
    draw_radar_objects();
    COLOR(C_WHITE);	/* NOTE: threat patches are in land2.c */
    cmov2i(6000, 14000);	charstr("4");
    cmov2i(-20000, 15000);	charstr("8");
    cmov2i(3000, 34000);	charstr("A");
    popmatrix();
    popviewport();

    pushviewport();
    draw_report();			/* display messages	*/
    popviewport();

    ortho2(-0.5, xmaxwindow+0.5, -0.5, ymaxwindow+0.5);

    COLOR(C_ORANGE);

    a = -TPS * 3600.0/6082.0 * vz;	/* airspeed meter	*/
    y = (ymaxwindow+1)/4 - (a%10) - 70;
    x = HUD_MARGIN-8;			/* right edge		*/
    a = a/10 - 7;			/* starting number	*/
    for (i=0; i<16; i++)
    {
	if (a >= 0)
	{
	    if (a % 5)
	    {
		move2s(x, y);	draw2s(x-4, y);
	    }
	    else
	    {
		move2s(x, y);	draw2s(x-8, y);
		cmov2s(x-8-30, y-4);
		if (a<10) charstr("  "), charstr(numbers[a]);
		else if (a<100) charstr(" "), charstr(numbers[a]);
		else
		{
		    sprintf(buf, "%3d", a);
		    charstr(buf);
		}
	    }
	}
	a++;
	y += 10;
    }

    a = 0.1 * p->y;			/* altitude in 10's	*/
    x = xmaxwindow-HUD_MARGIN+4;
    y = (ymaxwindow+1)/4 - (a%10) - 70;
    a = a/10 - 7;			/* starting number	*/
    for (i=0; i < 16; i++)
    {
	if (a >= 0)
	{
	    if (a % 5)
	    {
		move2s(x, y);	draw2s(x+4, y);
	    }
	    else
	    {
		move2s(x, y);	draw2s(x+8, y);
		cmov2s(x+10, y-4);
		if (a < 10)
		{
		    charstr("   ");
		    charstr(numbers[a]);
		}
		else
		{
		    int j=a/10;

		    if (j<10)
			charstr(" ");
		    else if (j >= 100)
			charstr(numbers[j/100]);
		    charstr(numbers[j%100]);
		    charstr(",");
		    charstr(numbers[a%10]);
		}
	    }
	}
	a++;
	y += 10;
    }

    a = 3600-p -> azimuth;		/* heading in tenth's	*/
    x = xmiddle - (a%50) - 100;
    y = 75-4;
    a = a/50 - 2;			/* heading in 5's	*/
    for (i=0; i<6; i++)
    {
	if (a < 0) a += 360/5;	/* wrap around		*/
	if (a >= 360/5) a -= 360/5;
	if (a & 1)
	{
	    move2s(x, y);	draw2s(x, y-4);
	}
	else
	{
	    move2s(x, y);	draw2s(x, y-8);
	    cmov2s(x-8, y-9-12);
	    if (a<20) charstr("0");
	    charstr(numbers[a>>1]);
	}
	a++;
	x += 50;
    }

    pushmatrix();
    pushviewport();
    viewport(xmiddle-200, xmiddle+200, 75, (ymaxwindow+1)*3/4);
    ortho2(-200.5, 200.5, 74.5-(ymaxwindow+1)/2, (ymaxwindow+1)/4+0.5);
    rotate(-p->twist, 'z');	/* rotate about nose marker	*/
    a = p -> elevation;		/* elevation in tenths		*/
    i = a%50;
    y = i * -(ymaxwindow+1)/36/10 - 1 * (ymaxwindow+1)*5/36;
    a = (a-i)/10 - 1*5;			/* starting number	*/

    for (i=0; i<4; i++)
    {
	if (a >= -90 && a <= 90)
	{
	    if (a > 0)
	    {
		move2s(25, y); draw2s(75, y); draw2s(75, y-12);
		cmov2s(77, y-12); charstr(numbers[a]);
		move2s(-25, y); draw2s(-75, y); draw2s(-75, y-12);
		cmov2s(-77-20, y-12); charstr(numbers[a]);
	    }
	    else if (a < 0)
	    {
		setlinestyle(1);
		move2s(25, y); draw2s(75, y); draw2s(75, y+12);
		cmov2s(77, y); charstr(numbers[-a]);
		move2s(-25, y); draw2s(-75, y); draw2s(-75, y+12);
		cmov2s(-77-20, y); charstr(numbers[-a]);
		setlinestyle(0);
	    }
	    else			/* 0 marker	*/
	    {
		move2s(25, y);	draw2s(75, y);
		move2s(-25, y);	draw2s(-75, y);
	    }
	}
	a += 5;
	y += 5*(ymaxwindow+1)/36;
    }
    popmatrix ();
    popviewport();

    ortho2(-0.5, xmaxwindow+0.5, -0.5, ymaxwindow+0.5);

    x = xmaxwindow-HUD_MARGIN-32-14-20;
    if (wheels)
    {
	cmov2s(x, 50);	charstr("L");
    }
    if (flaps)
    {
	cmov2s(x, 30);
	charstr("Flap:"); charstr(numbers[flaps]);
    }
    if (spoilers)
    {
	cmov2s(x+80, 30);
	charstr("Spoilr:"); charstr(numbers[spoilers]);
    }
    if (autop)
    {
	cmov2s(x-60, 10);	charstr("Auto");
    }
    cmov2s(x, 10);
    charstr("Fuel:");
    if ((fuel == 0) || (fuel > 10))
	charstr(numbers[fuel]);
    else if (fuel < 0)
	charstr("E");
    else
	/*
	 *  make fuel flash in the 1-10 % range
	 */
	if(tick & 2)
	    charstr(numbers[fuel]);
	else
	    charstr("    ");

    cmov2s(x+80, 10);
    charstr("Thrust:");
    if (thrust>=0)
	charstr(numbers[thrust]);
    else
    {
	charstr("-");
	charstr(numbers[-thrust]);
    }

    cmov2s(x+190, 10);
    charstr("Throttle:");
    if (throttle>=0)
	charstr(numbers[throttle]);
    else
    {
	charstr("-");
	charstr(numbers[-throttle]);
    }

    x = HUD_MARGIN+40;
    if (rockets)
    {
	strcpy(buf, "RRRRRRRRRR");	buf[rockets] = '\0';
	cmov2s(x, 30);	charstr(buf);
    }
    if (sidewinders)
    {
	strcpy(buf, "SSSSSSSSSS");	buf[sidewinders] = '\0';
	cmov2s(x, 10);	charstr(buf);
    }
skipit:
    if (p -> status <= MEXPLODE)	/* if exploding or crashed	*/
    {
	COLOR(C_WHITE);
	setpattern(CRASH_PATTERN);	/* clear in crash pattern	*/
	rectfi(0, ymaxwindow/2, xmaxwindow, ymaxwindow);
	setpattern(0);			/* reset pattern and color	*/
    }
}



/*
 *  report buffer routines
 */

#define MAX_REPORT_LINE 20

int report_lines = 0;
struct {
    float x, y;
    char line[80];
} report_buf[MAX_REPORT_LINE];


void clear_report_area()
{
    viewport(report_x1, report_x2, report_y1, report_y2);
    COLOR(C_BLACK);
    clear();
}


void clear_report()
{
    report_lines = 0;
}


void add_report_line(float x, float y, char *line)
{
    if (report_lines < MAX_REPORT_LINE-1)
    {
	report_buf[report_lines].x = x;
	report_buf[report_lines].y = y;
	strncpy(report_buf[report_lines].line, line, 80);
	report_lines++;
    }
}


void draw_report()
{
    int i;

    viewport(report_x1, report_x2, report_y1, report_y2);
    ortho2(report_x1-0.5, report_x2+0.5, 0.0, 1.0);
    COLOR(C_WHITE);

    for (i=0; i < report_lines; i++)
    {
	cmov2(report_buf[i].x, report_buf[i].y);
	charstr(report_buf[i].line);
    }
}

/*---------------------------------------------------------------------------*/


void draw_gforce_static()
{
    rects(25, 129, 43, 137);
    move2s(25, 167);	draw2s(33, 167);
    rects(25, 196, 33, 204);
    move2s(25, 233);	draw2s(33, 233);
    rects(25, 263, 43, 271);
    move2s(25, 300);	draw2s(33, 300);
    rects(25, 329, 33, 337);
    move2s(25, 367);	draw2s(33, 367);
    rects(25, 396, 43, 404);
    cmov2s(0, 128);	charstr("8");
    cmov2s(0, 161);	charstr("6");
    cmov2s(0, 195);	charstr("4");
    cmov2s(0, 228);	charstr("2");
    cmov2s(0, 261);	charstr("0");
    cmov2s(0, 295);	charstr("2");
    cmov2s(0, 328);	charstr("4");
    cmov2s(0, 361);	charstr("6");
    cmov2s(0, 395);	charstr("8");
}


void draw_gforce()
{
    polf2(3, gy_triangle);
}



void init_meter_sizes()
{
    float delta, ch, cw;
    int i;

    xscale = (xmaxwindow+1) / 1280.0;
    yscale = (ymaxwindow+1) / 1024.0;

    meter_x1 = X_ADJUST(METER_VLLX);
    meter_x2 = X_ADJUST(METER_VURX);
    meter_y1 = Y_ADJUST(METER_VLLY);
    meter_y2 = Y_ADJUST(METER_VURY);
    thrust_x1 = X_ADJUST(THRUST_LLX);
    heading_cx = X_ADJUST(HEADING_CX);
    speed_x1 = X_ADJUST(SPEED_LLX);
    climb_x1 = X_ADJUST(CLIMB_LLX);
    fuel_x1 = X_ADJUST(FUEL_LLX);


    bar_max_x = 62 * xscale;
    bar_max_y = 266 * yscale;

    delta = bar_max_y / 10.0;

    for (i = 0; i < 9; i++)
    {
	bar_ticks[i][0][X] = 0.0;
	bar_ticks[i][0][Y] = (i+1) * delta;
	bar_ticks[i][1][X] = 0.3 * bar_max_x;
	bar_ticks[i][1][Y] = (i+1) * delta;
	bar_ticks[i][2][X] = bar_max_x - 0.3 * bar_max_x;
	bar_ticks[i][2][Y] = (i+1) * delta;
	bar_ticks[i][3][X] = bar_max_x;
	bar_ticks[i][3][Y] = (i+1) * delta;
    }

    ch = 4.0;
    cw = 3.5;
    for (i = 0; i < 4; i++)
    {
	bar_nums[i][X] = bar_max_x / 2.0 - cw;
	bar_nums[i][Y] = (i*2+2) * delta - ch;
    }

    gy_triangle[0][X] = 0;
    gy_triangle[0][Y] = 267 * yscale;
    gy_triangle[1][X] = 8 * xscale;
    gy_triangle[1][Y] = 275 * yscale;
    gy_triangle[2][X] = 8 * xscale;
    gy_triangle[2][Y] = 259 * yscale;

    horizon_mark[0][X] = xmiddle + 1;
    horizon_mark[0][Y] = 403 * yscale;
    horizon_mark[1][X] = xmiddle + 9;
    horizon_mark[1][Y] = 415 * yscale;
    horizon_mark[2][X] = xmiddle - 7;
    horizon_mark[2][Y] = 415 * yscale;

    heading_mark[0][X] = heading_cx + 1;
    heading_mark[0][Y] = 403 * yscale;
    heading_mark[1][X] = heading_cx + 9;
    heading_mark[1][Y] = 415 * yscale;
    heading_mark[2][X] = heading_cx - 7;
    heading_mark[2][Y] = 415 * yscale;
}

void draw_meter_static()
{
    register int i;

    drawmode(over_drawmode);
    color(P_ORANGE);
    recti(0, 0, bar_max_x, bar_max_y);
    for(i=0; i < 9; i++)
    {
	bgnline();
	v2f(bar_ticks[i][0]);
	v2f(bar_ticks[i][1]);
	endline();
	bgnline();
	v2f(bar_ticks[i][2]);
	v2f(bar_ticks[i][3]);
	endline();
    }
    cmov2s(bar_nums[0][X], bar_nums[0][Y]);
    charstr("2");
    cmov2s(bar_nums[1][X], bar_nums[1][Y]);
    charstr("4");
    cmov2s(bar_nums[2][X], bar_nums[2][Y]);
    charstr("6");
    cmov2s(bar_nums[3][X], bar_nums[3][Y]);
    charstr("8");

    if (bits_under)
    {
	drawmode(UNDERDRAW);
	color(U_BROWN);
	rectfi(0, 0, bar_max_x, bar_max_y);
    }
}


void old_meters()
{
    Plane pp = planes[0], ptemp;
    int itemp;
    char charbuf[256];

    viewport(inst_x1, inst_x2, inst_y1, inst_y2);
    ortho2(inst_x1-0.5, inst_x2+0.5, inst_y1-0.5, inst_y2+0.5);

    pushmatrix();

    translate((float)thrust_x1, (float)meter_y1, 0.0);
    draw_meter_bar(thrust, throttle);			/* thrust meter */

    translate((float)(speed_x1-thrust_x1), 0.0, 0.0);
    draw_meter(airspeed/10);				/* speed meter */

    translate((float)(climb_x1-speed_x1), 0.0, 0.0);
    draw_meter((climbspeed>>1)+(climbspeed>>3));	/* 1/2 + 1/8 */

    translate((float)(fuel_x1-climb_x1), 0.0, 0.0);
    draw_meter(fuel >> 7);				/* fuel meter */

    popmatrix();

    draw_slow_meters();			/* display the text	*/

    draw_horizon_meter();		/* resets writemask	*/
    if (g_limit)
	draw_g_limit();
    else if (wing_stall)
	draw_wing_stall();
    if (autopilot_on)
	draw_auto_pilot();
    if (pp->status <= MEXPLODE)
	draw_crash_meters();

    /*
     *	display TEXT readouts
     */
    clear_text_display();
    if (flaps)
    {
	if (airspeed > 400-flaps)
	    strcpy(charbuf, "Flaps torn off");
	else
	    sprintf(charbuf, "Flaps: %2d degrees", flaps);
	cmov2s(100, 310);
	charstr(charbuf);
    }
    if (spoilers > 0)
    {
	cmov2s(280, 310);
	sprintf(charbuf, "Spoilers: %d degrees", spoilers);
	charstr(charbuf);
    }

    cmov2s(100, 330);
    if (wheels)
    {
	if (airspeed > 400)	/* if airspeed > 400 knots	*/
	    charstr("LANDING GEAR TORN OFF");
	else
	    charstr("LANDING GEAR DOWN");
    }

    if (pp->mstatus)
    {
	cmov2s(310, 330);
	if (pp->mkill != NULL_PLANE_ID)
	{
	    ptemp = lookup_plane(pp->mkill);
	    if (ptemp)
	    {
		sprintf(charbuf, "DESTROYED->%s", ptemp->myname);
		charstr(charbuf);
	    }
	}
	else if (pp->mtype == TYPE_CANNON)
	    charstr("20mm Cannon Fired");
	else if (pp->mtype == TYPE_ROCKET)
	    charstr("Rocket Launched");
	else
	{
	    ptemp = lookup_plane(missile_target);
	    if (ptemp == NULL)
		charstr("Sidewinder Launched");
	    else
	    {
		sprintf(charbuf,"Sidewinder->%s", ptemp->myname);
		charstr(charbuf);
	    }
	}
    }
    /*
     *  check for a locked on target
     */
    else if (missile_target != NULL_PLANE_ID)
    {
	cmov2s(310, 330);
	ptemp = lookup_plane(missile_target);
	if (ptemp != NULL)
	{
	    sprintf(charbuf, "Locked on->%s", ptemp->myname);
	    charstr(charbuf);
	}
    }
    cmov2s(492, 310);
    charstr(status_text);

    sprintf(charbuf, "Altitude: %d  Won:%d  Lost:%d",
	    (int)(pp->y - plane_height), pp->won, pp->lost);
    cmov2s(612, 330);
    charstr(charbuf);
}

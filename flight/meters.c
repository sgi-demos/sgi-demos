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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flight.h"

/*
 *  because flight was originally written for a screen with resolution
 *  of 1024 in X and 768 in Y we must use an adjust ment factor
 */
#define X_ADJUST (XMAXSCREEN / 1024.0)
#define Y_ADJUST (YMAXSCREEN / 768.0)

extern short wm_allplanes;

/* make objects for drawing meters	*/
void
make_meters ()
{
    int i;

    static Pattern16 crash_pattern = {
	0x0007,0x000e,0x001c,0x0038,
	0x0070,0x00e0,0x01c0,0x0380,
	0x0700,0x0e00,0x1c00,0x3800,
	0x7000,0xe000,0xc001,0x8003,
    };

    defpattern (1,PATTERN_16,crash_pattern);
    if (hud) return;		/* don't need any more meters	*/

    makeobj (METER_OVERLAY);
	color (brown);
	rectfs (0,0,50,200);
	color (orange);
	recti (0,0,50,200);
	for (i=20; i < 200; i+=20) {
	    move2s (0,i);	draw2s (15,i);
	    move2s (35,i);	draw2s (50,i);
	}
	cmov2s (20,34);		charstr ("2");
	cmov2s (20,74);		charstr ("4");
	cmov2s (20,114);	charstr ("6");
	cmov2s (20,154);	charstr ("8");
    closeobj ();

    make_clear_meters ();
    make_slow_meters ();
    make_horizon_meter ();
}

#define OLD_XMIDDLE 512
void
redraw_screen ()
{
    static Scoord triangle [3][2] = {
	{OLD_XMIDDLE+1,302},
	{OLD_XMIDDLE+9,310},
	{OLD_XMIDDLE-7,310}
    };
    static Scoord triangle1 [3][2] = {
	{HEADING_CX+1,302},
	{HEADING_CX+9,310},
	{HEADING_CX-7,310}
    };

    if (hud) return;
    /* draw static stuff	*/
    cursoff ();
    frontbuffer (TRUE);

    viewport (0,XMAXSCREEN,0,YMAXSCREEN);
    ortho2 (-0.5, XMAXSCREEN+0.5, -0.5, YMAXSCREEN+0.5);
    color (black);				/* clear the screen	*/
    clear ();

    color (orange);				/* label meters		*/
    move2s (XMIDDLE,YMIDDLE);			/* center of windshield	*/
    draw2s (XMIDDLE,YMIDDLE-16);
    rects (0,YMIDDLE-1,XMAXSCREEN,YMAXSCREEN);	/* outline windshield	*/

    ortho2 (-0.5,1023+.5,-0.5,767+.5);

    cmov2s (THRUST_LLX,METER_LLY-20);		charstr ("Thrust");
    cmov2s (SPEED_LLX,METER_LLY-20);		charstr ("Speed");
    cmov2s (SPEED_LLX,METER_LLY-36);		charstr ("knots");
    cmov2s (CLIMB_LLX,METER_LLY-20);		charstr ("Climb");
    cmov2s (CLIMB_LLX,METER_LLY-36);		charstr (" fpm");
    cmov2s (CLIMB_LLX+70,METER_LLY-20);		charstr ("G-force");
    cmov2s (OLD_XMIDDLE-30,METER_LLY-20);		charstr ("Horizon");
    cmov2s (HEADING_CX-30,METER_LLY-20);	charstr ("Heading");
    cmov2s (FUEL_LLX+8,METER_LLY-20);		charstr ("Fuel");

    polf2s (3,triangle);			/* meter center marks	*/
    polf2s (3,triangle1);

    pushmatrix ();				/* set up meters	*/
    translate ((float)THRUST_LLX,(float)METER_LLY,0.0);
    callobj (METER_OVERLAY);
    translate ((float)(SPEED_LLX-THRUST_LLX),0.0,0.0);
    callobj (METER_OVERLAY);
    translate ((float)(CLIMB_LLX-SPEED_LLX),0.0,0.0);
    callobj (METER_OVERLAY);
    translate ((float)(FUEL_LLX-CLIMB_LLX),0.0,0.0);
    callobj (METER_OVERLAY);
    popmatrix ();

    color (orange);				/* set up gforce meters	*/
    rects (350,97,364,103);				/* Y	*/
    move2s (350,125);	draw2s (356,125);
    rects (350,147,356,153);
    move2s (350,175);	draw2s (356,175);
    rects (350,197,364,203);
    move2s (350,225);	draw2s (356,225);
    rects (350,247,356,253);
    move2s (350,275);	draw2s (356,275);
    rects (350,297,364,303);
    cmov2s (330,96);	charstr ("8");
    cmov2s (330,121);	charstr ("6");
    cmov2s (330,146);	charstr ("4");
    cmov2s (330,171);	charstr ("2");
    cmov2s (330,196);	charstr ("0");
    cmov2s (330,221);	charstr ("2");
    cmov2s (330,246);	charstr ("4");
    cmov2s (330,271);	charstr ("6");
    cmov2s (330,296);	charstr ("8");

    translate ((float)HEADING_CX,200.0,0.0);/* set up heading meter	*/
    color (brown);
    circfs (0,0,102);
    color (orange);			/* draw plane		*/
    if (!dogfight) {
	move2s (0,0);
	draw2s (2,-10);
	draw2s (12,-18);
	draw2s (12,-20);
	draw2s (2,-14);
	draw2s (2,-20);
	draw2s (5,-23);
	draw2s (-5,-23);
	draw2s (-2,-20);
	draw2s (-2,-14);
	draw2s (-12,-20);
	draw2s (-12,-18);
	draw2s (-2,-10);
	draw2s (0,0);
    }
    else rectfs (-1,-1,1,1);

    /*
     *  set up horizon meter
     */
#ifdef NTSC
    viewport (260,380,METER_VLLY,METER_VURY);
#else
    /*viewport (412,612,METER_VLLY,METER_VURY);XXX*/
    viewport ((int)(412 * X_ADJUST + 0.1),
	      (int)(612 * X_ADJUST + 0.1),
	      (int)(METER_VLLY * Y_ADJUST + 0.1),
	      (int)(METER_VURY * Y_ADJUST + 0.1));
#endif

    ortho2 (-90.0,90.0,-90.0,90.0);
    color (brown);
    clear ();
    draw_blanking ();
    color (orange);
    rectfs (-66,-2,-30,0);		/* W	*/
    rectfs (66,-2,30,0);
    linewidth (2);
    move2s (33,-6);
    draw2s (20,-20);
    draw2s (0,0);
    draw2s (-20,-20);
    draw2s (-33,-6);
    linewidth (1);
    move2s (-60,-90);	draw2s(-60,-83);	/* yaw lines	*/
    move2s (-30,-90);	draw2s(-30,-86);
    move2s (0,-90);	draw2s(0,-83);
    move2s (30,-90);	draw2s(30,-86);
    move2s (60,-90);	draw2s(60,-83);
    frontbuffer (FALSE);
    curson ();
}

make_clear_meters ()
{
    makeobj (CLEAR_TEXT_DISPLAY);
#ifdef NTSC
	viewport (79,560,196,217);
#else
	/*viewport (99,900,310,345);*/
	viewport ((int)(99 * X_ADJUST + 0.1),
		  (int)(900 * X_ADJUST + 0.1),
		  (int)(310 * Y_ADJUST + 0.1),
		  (int)(345 * Y_ADJUST + 0.1));
#endif
	ortho2 (99.0,900.0,300.0,345.0);
	color (black);
	clear ();
	color (white);
    closeobj ();

    makeobj (CLEAR_METERS);	/* clear ALL the meters	*/
	/*viewport (METER_VLLX,FUEL_VLLX,METER_VLLY,METER_VURY);XXX*/
	viewport ((int)(METER_VLLX * X_ADJUST + 0.1),
		  (int)(FUEL_VLLX * X_ADJUST + 0.1),
		  (int)(METER_VLLY * Y_ADJUST + 0.1),
		  (int)(METER_VURY * Y_ADJUST + 0.1));
	ortho2 (50-0.5,FUEL_LLX+0.5,100-0.5,300+0.5);
	writemask (wm_allplanes-3);
	color (black);
	clear ();
    closeobj ();

    makeobj (CLEAR_FUEL_METER);
	/*viewport (FUEL_VLLX,METER_VURX,METER_VLLY,METER_VURY);*/
	viewport ((int)(FUEL_VLLX * X_ADJUST + 0.1),
		  (int)(METER_VURX * X_ADJUST + 0.1),
		  (int)(METER_VLLY * Y_ADJUST + 0.1),
		  (int)(METER_VURY * Y_ADJUST + 0.1));
	ortho2 (FUEL_LLX-0.5,FUEL_LLX+50.5,100-0.5,300+0.5);
	color (black);
	clear ();
    closeobj ();

    makeobj (CLEAR_REPORT_CARD);
	viewport (0,XMAXSCREEN,0,METER_VLLY - 40);
	ortho2 (-0.5,1023+.5,-0.5,METER_LLY - 39.5);
	color (black);
	clear ();
    closeobj ();
}

make_slow_meters ()
{
    int i;
    float r,sin,cos;

    static Scoord gy_triangle [][2] = {
	{0,200},
	{8,208},
	{8,192},
    };

    makeobj (SLOW_METERS);
	color (white);
    maketag (TEXT_EDIT);
	cmov2s (0,0);
	charstr ("");
	cmov2s (0,0);
	charstr ("");

#ifndef NOGMETER
	pushmatrix ();
    maketag (GY_EDIT);
	translate (0.0,0.0,0.0);
	polf2s (3,gy_triangle);
	popmatrix ();
#endif

	/* HEADING meter	*/
	translate ((float)HEADING_CX,200.0,0.0);
    maketag (HEADING_ROTATE_EDIT);
	rotate (0,'z');
	color (white);
	for (i = 0; i < 3600; i += 100) {
	    gl_sincos(i,&sin,&cos);
	    move2 (100.0 * sin,100.0 * cos);
	    if (i == 300 || i == 600 || i == 1200 || i == 1500 ||
		i == 2100 || i == 2400 || i == 3000 || i == 3300)
	    then r = 75.0;	/* long line	*/
	    else r = 90.0;	/* short line	*/
	    draw2 (r * sin, r * cos);
	}
	move2s (-7,60);		/* N	*/
	draw2s (-7,80);
	draw2s (7,60);
	draw2s (7,80);
	move2s (60,-7);		/* E	*/
	draw2s (60,7);
	draw2s (80,7);
	draw2s (80,-7);
	move2s (70,7);
	draw2s (70,-3);
	move2s (-80,-9);	/* W	*/
	draw2s (-60,-4);
	draw2s (-70,0);
	draw2s (-60,4);
	draw2s (-80,9);
	move2s (-7,-78);	/* S	*/
	draw2s (-5,-80);
	draw2s (7,-80);
	draw2s (7,-70);
	draw2s (-7,-70);
	draw2s (-7,-60);
	draw2s (5,-60);
	draw2s (7,-62);
	scale (.004,-.004,.004);	/* scale down (y=-z)	*/
	callobj (RADAR);
	color (blue);
	move2 (0.0,0.0);		/* the runway	*/
	draw2 (0.0,-8500.0);
    closeobj ();
}

genbar (x,y)
    int x,y;
{
    move2s (-x,-y);	draw2s (x,-y);
    move2s (-x,y);	draw2s (x,y);
}

make_horizon_meter ()
{
    static Scoord yaw_indicator[][2] = {{0,-85},{-4,-81},{4,-81}};

    makeobj (HORIZON_METER);

    /*
     *  set up horizon meter
     */
#ifdef NTSC
    viewport (260,380,METER_VLLY,METER_VURY);
#else
    /*viewport (412,612,METER_VLLY,METER_VURY);XXX*/
    viewport ((int)(412 * X_ADJUST + 0.1),
	      (int)(612 * X_ADJUST + 0.1),
	      (int)(METER_VLLY * Y_ADJUST + 0.1),
	      (int)(METER_VURY * Y_ADJUST + 0.1));
#endif

	ortho2 (-90.0,90.0,-90.0,90.0);
	pushmatrix ();
	color (blue);
    maketag (HORIZON_EDIT);
	rotate (0,'z');
	translate (0.0,0.0,0.0);
	rectfs (-150,0,150,500);

	color (white);
	move2s (-30,0);	draw2s (30,0);
	genbar (30,80);
	genbar (10,60);
	genbar (15,40);
	genbar (10,20);

	popmatrix ();				/* return to ortho	*/
	draw_blanking ();
	color (red);
	pushmatrix ();			/* save matrix for wing_stall	*/
    maketag(YAW_EDIT);
	translate (0.0,0.0,0.0);
	polf2s (3,yaw_indicator);
	writemask (wm_allplanes);
	popmatrix ();
    closeobj ();

    makeobj (WING_STALL);
	writemask (white);
	color (white);
	cmov2s (-32,4);
	charstr ("WING-STALL");
	writemask (wm_allplanes);
    closeobj ();

    makeobj (G_LIMIT);
	writemask (white);
	color (white);
	cmov2s (-24,4);
	charstr ("G-LIMIT");
	writemask (wm_allplanes);
    closeobj ();

    makeobj (AUTO_PILOT);
	writemask (white);
	color (white);
	cmov2s (-40,20);
	charstr ("AUTO-PILOT");
	writemask (wm_allplanes);
    closeobj ();

    makeobj (CRASH_METERS);
	/*viewport (METER_VLLX,METER_VURX,METER_VLLY,METER_VURY);XXX*/
	viewport ((int)(METER_VLLX * X_ADJUST + 0.1),
		  (int)(METER_VURX * X_ADJUST + 0.1),
		  (int)(METER_VLLY * Y_ADJUST + 0.1),
		  (int)(METER_VURY * Y_ADJUST + 0.1));
	writemask (white);
	color (white);
	setpattern (1);
	clear ();
	setpattern (0);
	writemask (wm_allplanes);
    closeobj ();
}

display_help ()
{
#define HEADER(vnum)\
"                      SGI Flight Simulator Version vnum"
    static char *helpmsg[] = {
HEADER_VERSION,
" ",
"The mouse  controls the white square on the screen which represents the control",
"stick of the plane.  Moving  the  mouse  to  the right causes the plane to roll",
"to the right.  Note that the plane continues to roll until you return the stick",
"to the  center (the bottom center of the windshield).  To takeoff,  use maximum",
"thrust and  pull  back on the stick once you are going fast enough.  The  mouse",
"buttons control the rudder.  Each press of the left mouse button increases left",
"rudder, likewise for the right button.  The  middle  button  returns the rudder",
"to the middle position.  The  rudder  position is indicated by the red triangle",
"at the bottom of the horizon meter.  Try to land with less than 600 fpm descent",
"and 10 degrees roll.  The better the landing, the more  fuel  and  weapons  you",
"receive.  Press any character to continue.  Good luck!",
" ",
"                       Keyboard commands",
"                       -------- --------",
"  t   - track/lock on a target      x/z - zoom in/out (tower view)",
"  n   - toggle day/night time       a/s - decrease/increase thrust",
"  d   - toggle tower/plane view     f/F - increase/decrease flaps",
"  l   - toggle landing gear         c/C - increase/decrease spoilers",
"  v   - autopilot                   r/R - detonate/restart game (also 'u')",
"  e   - fire a cannon round         q/w - fire a rocket/sidewinder",
"  ESC - quit                        h   - display help and pause",
"  ^R  - redraw screen               ^Z  - suspend (iconize) game",
""
    };
    display_message_no_wait (helpmsg);
}

int pick_plane ()
{
    static char *plane_menu[] = {
"                  Choose a plane from the following list",
"                    by typing the number of the plane",
" ",
"                      Weight(lbs)     Max        Wing     Loading   Takeoff",
"  #     Type        body      fuel   Thrust   area  span  max  min   speed",
"  -   ----------   -------  -------  -------  ----  ----  ---  ---  -------",
"  1   Cessna 150     1,000      400      250   157    28  +5g  -3g     55",
"  2   Boeing 747   500,000  100,000  200,000  5500   220  +4g  -2g    148",
"  3   F-15          28,000   14,000   46,000   608    42  +8g  -5g    112",
"  4   F-16          18,000    8,000   23,000   390    32 +10g  -7g    122",
"  5   F-18          24,000   12,000   32,000   510    38  +9g  -6g    116",
"  6   P-38          13,500    1,600    4,000   327    52  +6g  -3.5g   75",
"  ",
"  ",
"The left and right arrow keys rotate  your head 90 degrees left and right when viewing",
"from the plane, check the upper left of the screen for status.  Only one weapon can be",
"in play at a time.  To prematurely detonate a rocket or sidewinder, use restart ('r').",
"Cannon shots last one second.  Sidewinders  track planes (except the C-150) within the",
"target window that are higher than 150 feet.  The track command identifies the closest",
"target and locks on to it for one second.  Sidewinders are guaranteed to track  locked",
"targets.  Flaps increase lift and angle of attack but decrease the  stall  angle.  The",
"spoilers  substantially  increase drag and decrease lift.  To land, first slow down to",
"just over the stall speed.  Then use full flaps and don't forget your landing gear!",
""
};
    int i;
    i = display_message (plane_menu);
    if (i > 0) then return (i - '0');
    i = -i;
    if (i == LEFTMOUSE) then return 2;
    if (i == PAD1) then return (1);
    else if (i == PAD2) then return (2);
    else if (i == PAD3) then return (3);
    else if (i == PAD4) then return (4);
    else if (i == PAD5) then return (5);
}

/************************************************************
 *	Trash procedures
 ************************************************************/
draw_blanking ()
{
    static Scoord blanking1[][2] = { {90,90}, {70,90}, {90,70} };
    static Scoord blanking2[][2] = { {-90,90}, {-90,70}, {-70,90} };
    static Scoord blanking3[][2] = { {-90,-90}, {-70,-90}, {-90,-70} };
    static Scoord blanking4[][2] = { {90,-90}, {90,-70}, {70,-90} };

    color (black);				/* remove borders	*/
    polf2s (3,blanking1);
    polf2s (3,blanking2);
    polf2s (3,blanking3);
    polf2s (3,blanking4);
}

draw_meter (llx, val)
    int llx,  val;
{
    if (val >= 0) {
	color (blue);
	if (val > 100) then val = 100;
	rectfs (llx,METER_LLY,llx+50,METER_LLY+(val<<1));
    }
    else {
	color (red);
	if (val < -100) then val = -100;
	rectfs (llx,METER_LLY,llx+50,METER_LLY-(val<<1));
    }
}

change_rudder (rudder)
    float rudder;
{
    if (hud) {
    }
    else {
	editobj (HORIZON_METER);
	    objreplace (YAW_EDIT);
	    translate (rudder * 75.0, 0.0,0.0); /* map .8 => 60	*/
	closeobj ();
    }
}

static char *numbers[] = {
	"0","1","2","3","4","5","6","7","8","9",
	"10","11","12","13","14","15","16","17","18","19",
	"20","21","22","23","24","25","26","27","28","29",
	"30","31","32","33","34","35","36","37","38","39",
	"40","41","42","43","44","45","46","47","48","49",
	"50","51","52","53","54","55","56","57","58","59",
	"60","61","62","63","64","65","66","67","68","69",
	"70","71","72","73","74","75","76","77","78","79",
	"80","81","82","83","84","85","86","87","88","89",
	"90","91","92","93","94","95","96","97","98","99","100" 
};


void
draw_hud (p,tick,vx,vy,vz,vv,mach,gf,wheels,flaps,spoilers,autop,fuel,thrust)
    Plane p;
    int tick;
    float vx,vy,vz;
    int vv;
    float mach,gf;
    int wheels,flaps,spoilers,autop,fuel,thrust;
{
    char buf[32];
    int a,i,x,y;
    float k;

    extern char alt_text[], mach_text[], g_text[];
    extern rockets, sidewinders;

    if (!hud) {
	callobj (CROSS_HAIRS);
	return;
    }
#ifdef DEBUG
    if (debug & (1<<9)) {
	ortho2 (-0.5,XMAXSCREEN+0.5, -0.5, YMAXSCREEN+.5);
	callobj (CLEAR_TEXT_DISPLAY);		/* display messages	*/
	color (orange);
	goto skipit;
    }
#endif // DEBUG

    editobj (CROSS_HAIRS);
	objreplace (VV_EDIT);			/* vv marker		*/
	translate (0.0, vv * (60.0*30.0/1000.0) ,0.0);

	if (vz != 0.0) {
	    objreplace (YAW_EDIT);		/* FPM marker		*/
	    k = -57.3*(YMAXSCREEN+1)/36.0;	/* screen is 36 degrees */
	    translate (k*vx/vz,k*vy/vz,0.0);
	}

	if (tick & 1) {			/* do every other tick	*/
	    objreplace (HEADING_ROTATE_EDIT);	/* RHAWS scope rotate	*/
	    rotate (-p->azimuth,'z');
	}
	if (tick == TPS/2) {			/* RHAWS ticker		*/
	    objreplace (RHAWS_EDIT);
	    draw2s(20,-8);
	}
	if (tick == TPS) {
	    objreplace (RHAWS_EDIT);
	    draw2s(20,8);
	}
    closeobj ();

    /* this should be moved to overlap graphics if possible	*/
    if ((tick & 3) == 2) {		/* do every fourth frame */
	sprintf (mach_text,"%.2f",mach);	/* update text	*/
	sprintf (g_text,"%.1f",gf);

	y = p->y;
	if (y >= 1000)
	then sprintf (alt_text,"%2d,%03d",y/1000,y%1000);
	else sprintf (alt_text,"   %3d",y);
	if (vv < 0) then vv = -vv;
	if (vv > 300) then alt_text[3] = '0';
	if (vv > 30) then alt_text[4] = '0';
	alt_text[5] = '0';
    }

    callobj (CROSS_HAIRS);
    a = -TPS * 3600.0/6082.0 * vz;	/* airspeed meter	*/
    y = (YMAXSCREEN+1)/4 - (a%10) - 70;
    x = HUD_MARGIN-8;			/* right edge		*/
    a = a/10 - 7;			/* starting number	*/
    for (i=0; i<16; i++) {
	if (a >= 0) {
	    if (a % 5) {
		move2s(x,y);	draw2s(x-4,y);
	    }
	    else {
		move2s(x,y);	draw2s(x-8,y);
		cmov2s(x-8-30,y-4);
		if (a<10) then charstr("  "),charstr(numbers[a]);
		else if (a<100) then charstr(" "),charstr(numbers[a]);
		else {
		    sprintf(buf,"%3d",a);
		    charstr(buf);
		}
	    }
	}
	a++;
	y += 10;
    }

    a = 0.1 * p -> y;			/* altitude in 10's	*/
    x = XMAXSCREEN-HUD_MARGIN+4;
    y = (YMAXSCREEN+1)/4 - (a%10) - 70;
    a = a/10 - 7;			/* starting number	*/
    for (i=0; i<16; i++) {
	if (a >= 0) {
	    if (a % 5) {
		move2s(x,y);	draw2s(x+4,y);
	    }
	    else {
		move2s(x,y);	draw2s(x+8,y);
		cmov2s(x+10,y-4);
		if (a < 10) {
		    charstr("   ");
		    charstr(numbers[a]);
		}
		else {
		    int j=a/10;
		    
		    if (j<10) then charstr(" ");
		    charstr(numbers[j]);
		    charstr(",");
		    charstr(numbers[a%10]);
		}
	    }
	}
	a++;
	y += 10;
    }

    a = 3600-p -> azimuth;		/* heading in tenth's	*/
    x = XMIDDLE - (a%50) - 100;
    y = 75-4;
    a = a/50 - 2;			/* heading in 5's	*/
    for (i=0; i<6; i++) {
	if (a < 0) then a += 360/5;	/* wrap around		*/
	if (a >= 360/5) then a -= 360/5;
	if (a & 1) {
	    move2s(x,y);	draw2s(x,y-4);
	}
	else {
	    move2s(x,y);	draw2s(x,y-8);
	    cmov2s(x-8,y-9-12);
	    if (a<20) then charstr("0");
	    charstr(numbers[a>>1]);
	}
	a++;
	x += 50;
    }

    pushmatrix ();
    pushviewport ();
    viewport(XMIDDLE-200,XMIDDLE+200,75,(YMAXSCREEN+1)*3/4);
    ortho2 (-200.5,200.5,74.5-(YMAXSCREEN+1)/2,(YMAXSCREEN+1)/4+.5);
    rotate (-p->twist,'z');	/* rotate about nose marker	*/
    a = p -> elevation;		/* elevation in tenths		*/
    i = a%50;
    y = i * -(YMAXSCREEN+1)/36/10 - 1 * (YMAXSCREEN+1)*5/36;
    a = (a-i)/10 - 1*5;			/* starting number	*/

    for (i=0; i<4; i++) {
	if (a >= -90 && a <= 90) {
	    if (a > 0) {
		move2s(25,y); draw2s(75,y); draw2s(75,y-12);
		cmov2s(77,y-12); charstr(numbers[a]);
		move2s(-25,y); draw2s(-75,y); draw2s(-75,y-12);
		cmov2s(-77-20,y-12); charstr(numbers[a]);
	    }
	    else if (a < 0) {
		setlinestyle (1);
		move2s(25,y); draw2s(75,y); draw2s(75,y+12);
		cmov2s(77,y); charstr(numbers[-a]);
		move2s(-25,y); draw2s(-75,y); draw2s(-75,y+12);
		cmov2s(-77-20,y); charstr(numbers[-a]);
		setlinestyle (0);
	    }
	    else {			/* 0 marker	*/
		move2s(25,y);	draw2s(75,y);
		move2s(-25,y);	draw2s(-75,y);
	    }
	}
	a += 5;
	y += 5*(YMAXSCREEN+1)/36;
    }
    popmatrix ();
    popviewport ();

    x = XMAXSCREEN-HUD_MARGIN-32-14;
    if (wheels) {
	cmov2s (x,50);	charstr ("L");
    }
    if (flaps) {
	cmov2s (x,30); 
	charstr ("Flap:"); charstr (numbers[flaps]);
    }
    if (spoilers) {
	cmov2s (x+80,30);
	charstr ("Spoilr:"); charstr (numbers[spoilers]);
    }
    if (autop) {
	cmov2s (x-60,10);	charstr ("Auto");
    }
    cmov2s(x,10);
    charstr("Fuel:");
    if ((fuel == 0) || (fuel >10)) charstr(numbers[fuel]);
    else if (fuel < 0) charstr("E"); 
    /* make fuel flash in the 1-10 % range */
    else if(tick & 2) charstr(numbers[fuel]); else charstr("    ");

    cmov2s(x+80,10);
    charstr("Thrust:");
    if (thrust>=0) charstr(numbers[thrust]); 
    else {
	charstr("-");
	charstr(numbers[-thrust]);
    }
     
    x = HUD_MARGIN+40;
    if (rockets) {
	strcpy(buf,"RRRRRRRRRR");	buf[rockets] = '\0';
	cmov2s (x,30);	charstr(buf);
    }
    if (sidewinders) {
	strcpy(buf,"SSSSSSSSSS");	buf[sidewinders] = '\0';
	cmov2s (x,10);	charstr(buf);
    }
skipit:
    if (p -> status <= MEXPLODE) {	/* if exploding or crashed	*/
	color (white);
	setpattern (1);			/* clear in crash pattern	*/
	rectfi(0,YMAXSCREEN/2,XMAXSCREEN,YMAXSCREEN);
	setpattern (0);			/* reset pattern and color	*/
	color (orange);
    }
    cmov2s (50,YMAXSCREEN-20);		/* position character origin	*/
}

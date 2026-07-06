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

/* contains init and help stuff		*/
#include "flight.h"

static Cursor bcursor = {
	0xffff,0xffff,0xffff,0xe007,
	0xe007,0xe007,0xe007,0xe007,
	0xe007,0xe007,0xe007,0xe007,
	0xe007,0xffff,0xffff,0xffff,
};
short bitplanes, wm_allplanes;
short building_shade[4][5];

/************************************************************
/*	Help procedure
/************************************************************/

/* wait for a key to be hit and return it	*/
int wait_for_input ()
{
    short type,val;

    type = qread (&val);		/* wait for character	*/
    if (type == KEYBD) return (val);	/* if keyboard, return	*/
    if (type == REDRAW)
    then redraw_screen();
    else while (val) qread (&val);	/* read button release	*/
    return (-type);			/* return negated type	*/
}

/* display a message and wait for input before returning	*/
int display_message (msg)
    register char **msg;
{
    display_message_no_wait (msg);
    return (wait_for_input());
}

/* display a message but dont wait for input	*/
display_message_no_wait (msg)
    register char **msg;
{
    register int y;

    callobj (SETUP_WORLD);
    if (hud)
	ortho2 (-200.0, 200.0, -150.0, 150.0);
    else
	ortho2 (-200.0, 200.0, -100.0, 100.0);
    color (blue);
    clear ();

    y = 90;
    color (white);
    while (**msg) {			/* display help in white	*/
#ifdef _4D
	cmov2i(-100,y);
#else
	cmov2i(-140,y);
#endif
	charstr (*msg++);
	y -= 8;
    }
    swapbuffers ();
}

init_shade (i,shade)
    register int i,shade;
{
    building_shade[i][0] = shade++;
    building_shade[i][1] = shade++;
    building_shade[i][2] = shade++;
    building_shade[i][3] = shade++;
    building_shade[i][4] = shade++;
}

/************************************************************
/*	Init the IRIS
/************************************************************/
init_graphics (name)
    char *name;
{
    static Pattern16 shadow_pattern = {
	0x5555,0xaaaa,0x5555,0xaaaa, 0x5555,0xaaaa,0x5555,0xaaaa,
	0x5555,0xaaaa,0x5555,0xaaaa, 0x5555,0xaaaa,0x5555,0xaaaa,
    };

	static firsttime = 1;	/* can be called again after suspended */

	if(firsttime) {
		/* use prefposition, winopen, etc. so runs in background; so that
			if user does ^Z to iconify, they have their prompt */
		prefposition(0, XMAXSCREEN, 0, YMAXSCREEN);
		noborder();
		winopen(name);
		icontitle(name);
		qdevice(KEYBD);
		qdevice(WINQUIT);	/* restore everything on a winquit; can
			only happen if iconisized since no border */
	}

#ifdef XXX
    if (ismex()){
	keepaspect(XMAXSCREEN+1,YMAXSCREEN+1);
	getport(name);
	wintitle(name);
    }
    else
	gbegin ();				/* init iris		*/
#endif

    savecolors();
    doublebuffer ();
    gconfig ();
#ifdef _4D
    shademodel(FLAT);
#else
    winattach();
#endif
    bitplanes = getplanes();

    wm_allplanes = (1 << bitplanes) - 1;
    writemask (wm_allplanes);
    color (0); clear (); swapbuffers (); clear ();

    defcursor (1,bcursor);		/* set up block cursor	*/
    curorigin (1,8,8);
    setcursor (1,white,wm_allplanes);
    deflinestyle (1,0x3333);
    defpattern (3,PATTERN_16,shadow_pattern);
	if(firsttime)
		set_sun(-1.0,1.0,2.0);		/* default sun position	*/

    mapcolor (black,0,0,0);		/* 0	*/
    mapcolor (brown,96,80,64);		/* 1	*/
    mapcolor (orange,255,192,0);	/* 2	*/
    mapcolor (blue,80,160,240);		/* 4	*/
    mapcolor (blue+orange,255,192,0);
    mapcolor (blue+brown,0,0,255);

    mapcolor (red,255,0,0);		/* 8	*/
    mapcolor (red+brown,255,0,0);
    mapcolor (red+orange,255,192,0);
    mapcolor (white,220,220,220);
    mapcolor (white+brown,220,220,220);
    mapcolor (white+orange,220,220,220);

    if (bitplanes >= 6) {
	mapcolor (blue,0,0,255);
	mapcolor (green0,0,255,0);		/* radar green	*/
	mapcolor (green0+brown,0,255,0);
	mapcolor (green0+orange,255,192,0);	/* (orange)	*/

	init_shade (blime,lime0);
	init_shade (borange,orange0);
	init_shade (btan,tan0);

	building_shade[bgrey][0] = grey0;
	building_shade[bgrey][1] = grey3;
	building_shade[bgrey][2] = grey4;
	building_shade[bgrey][3] = grey7;
	building_shade[bgrey][4] = grey8;
    }
    else {
	building_shade[bgrey][0] = white;
	building_shade[bgrey][1] = grey2;
	building_shade[bgrey][2] = grey5;
	building_shade[bgrey][3] = grey8;
	building_shade[bgrey][4] = brown;
    }

	if(firsttime) {
		qdevice (REDRAW);
		qdevice (MOUSE1);
		qdevice (MOUSE2);
		qdevice (MOUSE3);
		qdevice (LEFTARROWKEY);
		qdevice (RIGHTARROWKEY);
		qdevice (UPARROWKEY);
		qdevice (DOWNARROWKEY);
		qdevice (PAD0);
		qdevice (PAD1);
		qdevice (PAD2);
		qdevice (PAD3);
		qdevice (PAD4);
		qdevice (PAD5);
		qdevice (PAD6);
		qdevice (PAD7);
		qdevice (PAD8);
		qdevice (PAD9);
		qdevice (KEYBD);
		setvaluator (MOUSEX, XMIDDLE, 0,XMAXSCREEN);
		setvaluator (MOUSEY, YMIDDLE, 0,YMAXSCREEN);
		make_buildings (); 
		makeobjs ();
		map_daynight (TRUE);	/* maps grey2,5,8 and green always	*/
	}
	firsttime = 0;
}

map_daynight (daytime)
    int daytime;
{
    register Colorindex i;
    register RGBvalue r,g,b;

    mapcolor (grey2,192,192,192);
    mapcolor (grey5,140,140,140);
    mapcolor (grey8,96,96,96);
    mapcolor (green,80,144,80);
    if (bitplanes < 6) then return;

    if (daytime) {
	mapcolor (skyblue,80,160,240);
	mapcolor (dirt,0x70,0x60,0x30);
	mapcolor (grey0,224,224,224);
	mapcolor (grey1,208,208,208);
	mapcolor (grey3,176,176,176);
	mapcolor (grey4,160,160,160);
	mapcolor (grey6,128,128,128);
	mapcolor (grey7,112,112,112);
	mapcolor (grey9,80,80,80);
	mapcolor (grey10,64,64,64);
	mapcolor (grey11,48,48,48);
	mapcolor (grey12,32,32,32);

	for (i=purple0,r=208,g=0,b=208; i < purple0+5; i++,r-=32,b-=32)
	    mapcolor (i,r,g,b);
	for (i=lime0, r=176,g=208,b=160; i < lime0+5; i++,r-=32,g-=32,b-=32)
	    mapcolor (i,r,g,b);
	for (i=orange0, r=200,g=70,b=0; i < orange0+5; i++,r-=32,g-=13)
	    mapcolor (i,r,g,b);
	for (i=tan0, r=176,g=144,b=112;i < tan0+5;i++,r-=20,g-=20,b-=20)
	    mapcolor (i,r,g,b);
	for (i=silver0, r=160,g=176,b=188;i <= silver9;i++,r-=10,g-=10,b-=10)
	    mapcolor (i,r,g,b);
    }
    else {
	mapcolor (green,80>>2,144>>2,80>>2);
	mapcolor (skyblue,80>>2,160>>2,240>>2);
	mapcolor (dirt,0x70>>2,0x60>>2,0x30>>2);
	mapcolor (grey0,224>>2,224>>2,224>>2);
	mapcolor (grey1,208>>2,208>>2,208>>2);
	mapcolor (grey2,192>>2,192>>2,192>>2);
	mapcolor (grey3,176>>2,176>>2,176>>2);
	mapcolor (grey4,160>>2,160>>2,160>>2);
	mapcolor (grey5,140>>2,140>>2,140>>2);
	mapcolor (grey6,128>>2,128>>2,128>>2);
	mapcolor (grey7,112>>2,112>>2,112>>2);
	mapcolor (grey8,96>>2,96>>2,96>>2);
	mapcolor (grey9,80>>2,80>>2,80>>2);
	mapcolor (grey10,64>>2,64>>2,64>>2);
	mapcolor (grey11,48>>2,48>>2,48>>2);
	mapcolor (grey12,32>>2,32>>2,32>>2);

	for (i=purple0,r=208>>2,g=0,b=208>>2; i < purple0+5; i++,r-=8,b-=8)
	    mapcolor (i,r,g,b);
for (i=lime0, r=176>>2,g=208>>2,b=160>>2; i < lime0+5; i++,r-=8,g-=8,b-=8)
	    mapcolor (i,r,g,b);
	for (i=orange0, r=200>>2,g=70>>2,b=0; i < orange0+5; i++,r-=8,g-=3)
	    mapcolor (i,r,g,b);
	for (i=tan0,r=176>>2,g=144>>2,b=112>>2;i<tan0+5;i++,r-=5,g-=5,b-=5)
	    mapcolor (i,r,g,b);
for (i=silver0, r=160>>2,g=176>>2,b=188>>2;i <= silver9;i++,r-=2,g-=2,b-=2)
	    mapcolor (i,r,g,b);
    }
}

/************************************************************
/*	Object definitions
/************************************************************/
makeobjs ()
{
    int i;
    Matrix identity;

    gl_IdentifyMatrix (identity);
    makeobj (PUSH_IDENTITY);
	pushmatrix ();
	loadmatrix (identity);
    closeobj ();

    make_world ();
    make_cross_hairs ();
    make_explosion ();
}

char alt_text[8];		/* global altitude text	*/
char mach_text[8];		/* global mach number text	*/
char g_text[8];			/* global g-force text	*/

static float rhaws[][2] = {	/* 20 point unit circle	*/
	0,1,
	0.309017,0.951057,
	0.587785,0.809017,
	0.809017,0.587785,
	0.951057,0.309017,
	1,0,
	0.951057,-0.309017,
	0.809017,-0.587785,
	0.587785,-0.809017,
	0.309017,-0.951057,
	0,-1,
	-0.309017,-0.951057,
	-0.587785,-0.809017,
	-0.809017,-0.587785,
	-0.951057,-0.309017,
	-1,0,
	-0.951057,0.309017,
	-0.809017,0.587785,
	-0.587785,0.809017,
	-0.309017,0.951057,
};

make_cross_hairs ()
{
    register char buf[32];
    register int i,x,y;
    float r,sin,cos;

    makeobj (CROSS_HAIRS);
	color (orange);
    if (hud) {		/* assume viewport is whole screen	*/
	ortho2 (-0.5,XMAXSCREEN+0.5, -0.5, YMAXSCREEN+.5);
	callobj (METER_OVERLAY);		/* plane's text		*/
	x = XMIDDLE;
	y = 75;					/* marker for heading	*/
	move2s(x,y);	draw2s(x,y+15);

	y = (YMAXSCREEN+1)/2;
	move2s(x+4,y);	draw2s(x+16,y);		/* nose cross hairs	*/
	move2s(x-4,y);	draw2s(x-16,y);
	move2s(x,y+4);	draw2s(x,y+16);
	move2s(x,y-4);	draw2s(x,y-16);
    
	x = HUD_MARGIN;				/* mach and g text	*/
	cmov2s (x,290); charstr (g_text);
	cmov2s (x,75); charstr (mach_text);
	/*XXX
	cmov2s (x,290); loccharstr (g_text);
	cmov2s (x,75); loccharstr (mach_text);
	*/

	y = (YMAXSCREEN+1)/4;
	x = HUD_MARGIN;				/* marker for airspeed	*/
	move2s(x,y);	draw2s(x+16,y);
	cmov2s(x+4,y+4); charstr("C");

	x = XMAXSCREEN-HUD_MARGIN;		/* marker for altitude	*/
	move2s(x,y);	draw2s(x-16,y);		/* and vv (climbspeed)	*/
	x -= 32;	y += 30*3;
	for (i=0; i<6; i++) {
	    move2s(x,y); draw2s(x+8,y);		/* long tick	*/
	    move2s(x,y-15); draw2s(x+4,y-15);	/* short tick	*/
	    y -= 30;
	}
	y -= 24;
	cmov2s(x-14,y); charstr("R");		/* radar altimiter	*/
	rects(x,y-2,x+60,y+14);
	cmov2s (x+2,y); charstr (alt_text);
	/*XXX
	cmov2s (x+2,y); loccharstr (alt_text);
	*/

	pushmatrix ();
    maketag (VV_EDIT);
	translate (0.0,0.0,0.0);		/* set y = fpm*30/1000	*/
	y = (YMAXSCREEN+1)/4;
	move2s(x,y); draw2s(x-14,y+6);		/* draw triangle	*/
	draw2s(x-14,y-6); draw2s(x,y);
	popmatrix ();

	pushmatrix ();
    maketag (YAW_EDIT);
	translate (0.0,0.0,0.0);
	x = XMIDDLE;
	y = (YMAXSCREEN+1)/2;
	move2s(x+16,y); draw2s(x+6,y);		/* draw FPM		*/
	draw2s(x+4,y+4); draw2s(x,y+6);
	draw2s(x,y+16);
	move2s(x-16,y);	draw2s(x-6,y);
	move2s(x,y+6); draw2s(x-4,y+4);
	draw2s(x-6,y); draw2s(x-4,y-4);
	draw2s(x,y-6); draw2s(x+4,y-4);
	draw2s(x+6,y);
	popmatrix ();

	pushviewport();
	pushmatrix();
	viewport(8,HUD_MARGIN-50,8,HUD_MARGIN-50); /* RHAWS scope	*/
	ortho2 (-100.5,100.5,-100.0,100.5);
	color(green0);
	pnt2s(0,0);
	for (i = 0; i < 3600; i += 150) {	/* static ticks	*/
	    gl_sincos(i,&sin,&cos);
	    move2 (100.0 * sin,100.0 * cos);
	    if (i % 900 == 0) then r = 20.0;
	    else if (i % 450 == 0) then r = 75.0;
	    else r = 88.0;
	    draw2 (r * sin, r * cos);
	}
	move2s(20,0);
    maketag(RHAWS_EDIT);
	draw2s(20,0);
	pushmatrix ();
	scale (25.0,25.0,1.0);
	poly2 (20,rhaws);
	scale (2.0,2.0,1.0);
	poly2 (20,rhaws);
	scale (2.0,2.0,1.0);
	poly2 (20,rhaws);
	popmatrix ();
    maketag (HEADING_ROTATE_EDIT);
	rotate (0,'z');
	scale (.004,-.004,.004);	/* scale down (y=-z)	*/
	callobj (RADAR);
	color (blue);
	move2 (0.0,0.0);		/* the runway	*/
	draw2 (0.0,-8500.0);
	color (white);		/* NOTE: threat patches are in land2.c */
	cmov2i (6000,14000);	charstr("4");
	cmov2i (-20000,15000);	charstr("8");
	cmov2i (3000,34000);	charstr("A");
	popmatrix ();
	popviewport ();

	color (orange);
	callobj (CLEAR_TEXT_DISPLAY);		/* display messages	*/
	color (orange);
    }
    else {
	ortho2 (-200.0,200.0,-100.0,100.0);
	move2s (0,-3);
	draw2s (0,3);
	move2s (-2,0);
	draw2s (2,0);
	cmov2s (-195,92);		/* position character origin	*/
    }
    closeobj ();
}

#define RADIUS 300
make_explosion ()
{
    Object i;
    int n,temp;
    register int x,y,z,radius;

    makeobj (EXPLOSION);
    closeobj ();

    for (i=1; i < MEXPLODE; i++) {
	if (i<=10*TPS/8) then n = i * 8; else n = 90;
	radius = (MEXPLODE+1-i) * RADIUS/TPS/2;

	makeobj (i+EXPLOSION);
	    color (red);
	    for (; n>0; n--) {
		temp = random(3);
		if (temp>2) color (orange);
	    r1:
		x = random(radius);
		y = random(radius);
		z = random(radius);
		if (x*x + y*y + z*z > RADIUS*RADIUS) then goto r1;
		moves (x,y,z);
		x = radius >> 3;
		if (n & 7) then draws (random(x),random(x),random(x));
	    r2:
		x = random(radius);
		y = random(radius);
		z = random(radius);
		if (x*x + y*y + z*z > RADIUS*RADIUS) then goto r2;
		draws (x,y,z);
		if (temp>2) color (red);
	    }
	closeobj ();
    }
}

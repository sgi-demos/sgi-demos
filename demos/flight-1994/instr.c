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
 *  flight/instr.c $Revision: 1.1 $
 *
 *  Instruments package for flight
 */

#include "flight.h"
#include <device.h>
#include <math.h>
#include <stdio.h>
#include "light.h"


#define INST_AR ((inst_x2+1 - inst_x1) / (float)(inst_y2+1 - inst_y1))

#define MARKINGS	2

#define P_MARKINGS	3

#define ICOLOR(col)	if (in_cmode) color(ci_table[col]); else cpack(col)

int maxspeed = 700;
int plate_ci_mode = PUPDRAW;  /* what mode to draw plates in */

object_t *plate1;
object_t *plate2;
object_t *plate3;
object_t *plate4;
object_t *plate5;
object_t *wlight;


typedef struct inst_list {
    int (*draw_func)();
    int (*update_func)();
    void *data;
    struct inst_list *next;
} inst_list_t;



static struct instrument_data
{
    unsigned char antialias;		/* If true, antialias the needles */
    int charwide;			/* Width of a single character	  */
    int chartall;			/* Height of a char, no descender */
    int threewide;			/* Width of three numbers	  */
    int twowide;			/* Width of two numbers		  */
    int fourwide;			/* Width of four numbers	  */
    int fivewide;			/* Width of five numbers	  */
    int sixwide;			/* Width of six numbers		  */
    int eightwide;			/* Width of eight numbers	  */
    int daytime;			/* True if daytime, else night	  */
    inst_list_t *inst_list;		/* List of instruments		  */
    int current;			/* 1 or 0: buffer being drawn	  */
    unsigned long jamblack;		/* Colors			  */
    unsigned long text;
    unsigned long textborder;
    unsigned long textbackground;
    unsigned long yellow;
    unsigned long darkneedle;
    unsigned long lightneedle;
    unsigned long redlamp;
    unsigned long greenlamp;
    unsigned long backlittext;
    int force_update;
} instrument_data;


/*
 *  Add an instrument to the instrument list.
 */
void append_inst_list(int (*draw_func)(), int (*update_func)(), void *data)
{
    inst_list_t *p;

    p = (inst_list_t *)malloc(sizeof(inst_list_t));
    p->draw_func = draw_func;
    p->update_func = update_func;
    p->data = data;
    p->next = instrument_data.inst_list;
    instrument_data.inst_list = p;
}


/*
 *  Erase the instrument list.
 */
void kill_inst_list()
{
    inst_list_t *p, *q;

    q = p = instrument_data.inst_list;
    while (p)
    {
	p = p->next;
	free(q);
	q = p;
    }
    instrument_data.inst_list = NULL;
}


/*
 *  Draw a four-sided polygon
 */
void drawneedlebox(float (*verts)[3])
{
    bgnpolygon();
    v3f(verts[0]);
    v3f(verts[1]);
    v3f(verts[2]);
    v3f(verts[3]);
    endpolygon();
}


/*
 *  Draw a needle.  First, draw the shadow, then the needle, then an
 *  antialiased outline.
 */
void drawneedle(float ang, unsigned long col, float (*verts)[3])
{
    ICOLOR(instrument_data.jamblack);
    setpattern(SHADOW_PATTERN);
    pushmatrix();
    translate(0.2, -0.2, 0.0);
    rot(ang, 'z');
    bgnpolygon();
    v3f(verts[0]);
    v3f(verts[1]);
    v3f(verts[3]);
    v3f(verts[4]);
    endpolygon();
    bgnpolygon();
    v3f(verts[1]);
    v3f(verts[2]);
    v3f(verts[3]);
    endpolygon();
    setpattern(0);
    popmatrix();
    pushmatrix();
    ICOLOR(col);
    rot(ang, 'z');
    bgnpolygon();
    v3f(verts[0]);
    v3f(verts[1]);
    v3f(verts[3]);
    v3f(verts[4]);
    endpolygon();
    bgnpolygon();
    v3f(verts[1]);
    v3f(verts[2]);
    v3f(verts[3]);
    endpolygon();
    if (instrument_data.antialias)
    {
	if (!in_cmode)
	{
	    blendfunction(BF_SA, BF_MSA);
	    linesmooth(SML_ON);
	}
	bgnline();
	v3f(verts[0]);
	v3f(verts[1]);
	v3f(verts[2]);
	v3f(verts[3]);
	v3f(verts[4]);
	endline();
	if (!in_cmode)
	{
	    linesmooth(SML_OFF);
	    blendfunction(BF_ONE, BF_ZERO);
	}
    }
    popmatrix();
}


/*
 * Initialize the instruments - set up some common data
 */
void init_instruments()
{
    static int firsttime = TRUE;

    if (in_cmode)
    {
	char gv_here[16];

	gversion(gv_here);  /* damn I hate how I'm doing this */
	/* getgdesc(GD_CIFRACT) my ass.  All bitplanes, hah! */
	if (strncmp(gv_here,"GL4DPI",6)==0)
	{
	    plate_ci_mode = NORMALDRAW;
	}
	else
	    plate_ci_mode = PUPDRAW;
    }

    instrument_data.charwide = strwidth("0")/2 - 1;
    instrument_data.chartall = (getheight() - getdescender())/2 - 1;
    instrument_data.twowide  = strwidth("00")/2 - 1;
    instrument_data.threewide = strwidth("000")/2 - 1;
    instrument_data.fourwide = strwidth("0000")/2 - 1;
    instrument_data.fivewide = strwidth("00000")/2 - 1;
    instrument_data.sixwide = strwidth("000000")/2 - 1;
    instrument_data.eightwide = strwidth("00000000")/2 - 1;
    instrument_data.current = 0;
    instrument_data.antialias = getgdesc(GD_LINESMOOTH_RGB);

    if (firsttime)
    {
	char objfname[256];

	instrument_data.inst_list = NULL;

	strcpy(objfname, objdir);
	strcat(objfname, "plate1.d");
	plate1 = readobj(objfname);
	strcpy(objfname, objdir);
	strcat(objfname, "plate2.d");
	plate2 = readobj(objfname);
	strcpy(objfname, objdir);
	strcat(objfname, "plate3.d");
	plate3 = readobj(objfname);
	strcpy(objfname, objdir);
	strcat(objfname, "plate4.d");
	plate4 = readobj(objfname);
	strcpy(objfname, objdir);
	strcat(objfname, "plate5.d");
	plate5 = readobj(objfname);
	strcpy(objfname, objdir);
	strcat(objfname, "wlight.d");
	wlight = readobj(objfname);
	if (in_cmode && bits_cmode < 6)
	{
	    remap_geom(&wlight->glist[1]);
	    remap_geom(&wlight->glist[2]);
	}

	firsttime = FALSE;
    }
    else
    {
	kill_inst_list();
    }

    /*
     *  add_instruments
     */
    init_horizon(0.0, 4.0, 0.0, 0.8);
    init_airspeed_meter(-15.0, 6.0, 0.0, 0.6, maxspeed);
    init_mach_meter(-15.0, -7.0, 0.0, 0.6, 3.0, .5, 10);
    init_altimeter(15.0, 6.0, 0.0, 0.6);
    init_vertvel_meter(15.0, -7.0, 0.0, 0.6, 6000.0, 2000.0, 10);
    init_fuelgauge(-32.0, 6.0, 0.0, 0.6, 50000.0, 10000.0, 5, 1000);
    init_thrustthrottle(-32.0, -7.0, 0.0, 0.6, 25.0, 5);
    init_radar(30.0, 4.0, 0.0, 0.8);
    init_gmeter(-23.5, 2.5, 0.0, 0.6);
    init_flapspoiler(25.5, -9.0, 0.0, 0.4, 60, 60, 6, 60, 60, 6);
    init_gear(34.0, -9.0, 0.0, 0.4);
    init_text_meter(0.0, -10.8, 0.0, 0.58);
    init_stores_meter(0.0, -6.2, 0.0, 0.58);
    init_wlight(-23.5, -8.5, 0.0, 0.5, &g_limit, "G-LIMIT");
    init_wlight(-23.5, -11.5, 0.0, 0.5, &wing_stall, "WING STALL");

    set_instruments_time(1);
}


/*
 * Set colors according to night/day
 */
void set_instruments_time(int daytime)
{
    long olddrawmode;

    if (daytime)
    {
	if (!in_cmode)
	{
	    instrument_data.jamblack =		0xff010000;
	    instrument_data.text =		0xffdcdcdc;
	    instrument_data.textborder =	0xffa0a0a0;
	    instrument_data.textbackground =	0xff252525;
	    instrument_data.yellow =		0xff00d2d2;
	    instrument_data.lightneedle =	0xffe6e6e6;
	    instrument_data.darkneedle =	0xffc8c8c8;
	    instrument_data.redlamp =		0xff0000d0;
	    instrument_data.greenlamp =		0xff00d000;
	    instrument_data.backlittext =	0xff010101;
	}
	else {
	    instrument_data.jamblack =		C_BLACK;
	    instrument_data.text =		C_WHITE;
	    instrument_data.textborder =	C_GREY;
	    instrument_data.textbackground =	C_BLACK;
	    instrument_data.yellow =		C_ORANGE;
	    instrument_data.lightneedle =	C_GREY;
	    instrument_data.darkneedle =	C_GREY;
	    instrument_data.redlamp =		C_RED;
	    instrument_data.greenlamp =		C_GREEN;
	    instrument_data.backlittext =	C_BLACK;
	}
    }

    /* XXX Add night colors */

    instrument_data.daytime = daytime;
}


/*
 *  Call all drawing functions in the draw list after setting up
 *  viewing and lighting matrices.
 */
void draw_instruments()
{
    inst_list_t *p;
    static float identity[4][4] = { 1.0, 0.0, 0.0, 0.0,
				    0.0, 1.0, 0.0, 0.0,
				    0.0, 0.0, 1.0, 0.0,
				    0.0, 0.0, 0.0, 1.0 };

    viewport(inst_x1, inst_x2, inst_y1, inst_y2);

    perspective(100, INST_AR, 2.0, 1000.0);
    pushmatrix();

    frontbuffer(TRUE);

    COLOR(C_GREY);
    clear();
    frontbuffer(FALSE);
    if (!in_cmode)
	zclear();

    translate(0.0, 0.0, -155.0);

    if (!in_cmode)
	lmbind(LIGHT0, INST_LIGHT);

    p = instrument_data.inst_list;
    while (p)
    {
	(*(p->draw_func))(p->data);
	p = p->next;
    }

    popmatrix();

    instrument_data.force_update = 2;
}


/*
 * Call all update functions in update list
 */
void update_instruments(int forceupdate)
{
    inst_list_t *p;

    viewport(inst_x1, inst_x2, inst_y1, inst_y2);

    perspective(100, INST_AR, 2.0, 1000.0);

    pushmatrix();
    translate(0.0, 0.0, -155.0);

    p = instrument_data.inst_list;
    while (p)
    {
	(*(p->update_func))(p->data, instrument_data.force_update);
	p = p->next;
    }

    if (instrument_data.force_update > 0)
	instrument_data.force_update--;

    instrument_data.current = !instrument_data.current;

    if (planes[0]->status <= MEXPLODE && !forceupdate)	/* if exploding or crashed      */
    {
	COLOR(C_WHITE);
	setpattern(CRASH_PATTERN);	/* clear in crash pattern       */
	clear();
	setpattern(0);			/* reset pattern and color      */
    }

    popmatrix();
}


clear_inst1()
{
    static float verts[4][3] = {{-9.0, -9.0}, {-9.0,  9.0},
				{ 9.0,  9.0}, { 9.0, -9.0}};

    bgnpolygon();
    v2f(verts[0]);
    v2f(verts[1]);
    v2f(verts[2]);
    v2f(verts[3]);
    endpolygon();
}


clear_inst2()
{
    static float verts[4][3] = {{-2.1, -15.1}, { 2.1, -15.1},
				{ 2.1,  15.1}, {-2.1,  15.1}};

    bgnpolygon();
    v2f(verts[0]);
    v2f(verts[1]);
    v2f(verts[2]);
    v2f(verts[3]);
    endpolygon();
}


clear_inst4()
{
    static float verts[4][3] = {{-13.1, -3.1}, {-13.1,  3.1},
				{ 13.1,  3.1}, { 13.1, -3.1}};

    bgnpolygon();
    v2f(verts[0]);
    v2f(verts[1]);
    v2f(verts[2]);
    v2f(verts[3]);
    endpolygon();
}


clear_inst5()
{
    static float verts[4][3] = {{-13.1, -2.6}, {-13.1,  2.6},
				{ 13.1,  2.6}, { 13.1, -2.6}};

    bgnpolygon();
    v2f(verts[0]);
    v2f(verts[1]);
    v2f(verts[2]);
    v2f(verts[3]);
    endpolygon();
}


/************************************************************************
***				Horizon functions		      ***
************************************************************************/

typedef struct horizon_struct
{
    float px, py, pz;		/* Position of instrument */
    float size;			/* Size of instrument */
    short sm_l, sm_r, sm_b, sm_t;
    object_t *plateobject;
} horizon_t;


/*
 * Draw the artificial horizon
 */
draw_horizon(horizon_t *inst)
{
    static float bars[][2] = {{-6.6, -0.1}, {-3.0, -0.1},
			      { 3.0, -0.1}, { 6.6, -0.1}};

    static float w[][2] = {{-3.34, -0.60},
			   {-1.97, -2.03},
			   { 0.00, -0.00},
			   { 2.00, -2.00},
			   { 3.40, -0.60}};
    long ox, oy;

    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);

    /*
     *  get instrument screen mask
     */
    cmov2i(-9.0, -9.0);
    getcpos(&inst->sm_l, &inst->sm_b);
    cmov2i(9.0, 9.0);
    getcpos(&inst->sm_r, &inst->sm_t);
    getorigin(&ox, &oy);
    inst->sm_l -= ox;
    inst->sm_r -= ox;
    inst->sm_b -= oy;
    inst->sm_t -= oy;

    if (!in_cmode)
    {
	/*
	 *  draw overlays
	 */
	drawmode(PUPDRAW);

	color(P_ORANGE);
	linewidth(3);
	bgnline(); v2f(bars[0]); v2f(bars[1]); endline();
	bgnline(); v2f(bars[2]); v2f(bars[3]); endline();
	linewidth(2);
	bgnline();
	v2f(w[0]); v2f(w[1]); v2f(w[2]); v2f(w[3]); v2f(w[4]);
	endline();
	linewidth(1);
    }

    /*
     *  draw normal planes
     */
    drawmode(NORMALDRAW);

    frontbuffer(TRUE);

    COLOR(C_BLACK);
    clear_inst1();

    draw_plate(inst->plateobject, 0x3);

    frontbuffer(FALSE);

    popmatrix();
}

draw_horizon_ci(horizon_t *inst)
{
    static float bars[][2] = {{-6.6, -0.1}, {-3.0, -0.1},
			      { 3.0, -0.1}, { 6.6, -0.1}};

    long ox, oy;

    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);

    /*
     *  get instoment screen mask
     */
    cmov2i(-9.0, -9.0);
    getcpos(&inst->sm_l, &inst->sm_b);
    cmov2i(9.0, 9.0);
    getcpos(&inst->sm_r, &inst->sm_t);
    getorigin(&ox, &oy);
    inst->sm_l -= ox;
    inst->sm_r -= ox;
    inst->sm_b -= oy;
    inst->sm_t -= oy;

    /*
     *  draw normal planes
     */
    drawmode(NORMALDRAW);

    frontbuffer(TRUE);

    COLOR(C_BLACK);
    clear_inst1();

    drawmode(plate_ci_mode);
    drawobj(inst->plateobject, 0x3);
    drawmode(NORMALDRAW);

    frontbuffer(FALSE);

    popmatrix();
}

/*
 * Update the artificial horizon
 */
update_horizon(horizon_t *inst, int forceupdate)
{
    static float h_hi[][2] =  {{-9.0,   0.0},
			       { 9.0,   0.0},
			       { 9.0,  18.0},
			       {-9.0,  18.0}};
    static float h_low[][2] = {{ 9.0,   0.0},
			       {-9.0,   0.0},
			       {-9.0, -18.0},
			       { 9.0, -18.0}};
    static float bars[][2] = {{-3.0,  8.0}, {3.0,  8.0},
			      {-1.0,  6.0}, {1.0,  6.0},
			      {-1.5,  4.0}, {1.5,  4.0},
			      {-1.0,  2.0}, {1.0,  2.0},
			      {-3.0,  0.0}, {3.0,  0.0},
			      {-1.0, -2.0}, {1.0, -2.0},
			      {-1.5, -4.0}, {1.5, -4.0},
			      {-1.0, -6.0}, {1.0, -6.0},
			      {-3.0, -8.0}, {3.0, -8.0}};

    static float orange_bars[][2] = {{-6.6, -0.1}, {-3.0, -0.1},
				     { 3.0, -0.1}, { 6.6, -0.1}};

    static float w[][2] = {{-3.34, -0.60},
			   {-1.97, -2.03},
			   { 0.00, -0.00},
			   { 2.00, -2.00},
			   { 3.40, -0.60}};

    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);
    if (!in_cmode)
    {
	zbuffer(TRUE);
	lsetdepth(zmaxscreen, zmaxscreen);
    }
    scrmask(inst->sm_l, inst->sm_r, inst->sm_b, inst->sm_t);

    pushmatrix();
    rotate(-twist, 'z');
    translate(0.0, -0.01 * elevation, 0.0);

    COLOR(C_HBLUE);
    bgnpolygon();
    v2f(h_hi[0]);
    v2f(h_hi[1]);
    v2f(h_hi[2]);
    v2f(h_hi[3]);
    endpolygon();

    COLOR(C_INST_BROWN);
    bgnpolygon();
    v2f(h_low[0]);
    v2f(h_low[1]);
    v2f(h_low[2]);
    v2f(h_low[3]);
    endpolygon();

    COLOR(C_WHITE);
    bgnline(); v2f(bars[0]); v2f(bars[1]); endline();
    bgnline(); v2f(bars[2]); v2f(bars[3]); endline();
    bgnline(); v2f(bars[4]); v2f(bars[5]); endline();
    bgnline(); v2f(bars[6]); v2f(bars[7]); endline();
    bgnline(); v2f(bars[8]); v2f(bars[9]); endline();
    bgnline(); v2f(bars[10]); v2f(bars[11]); endline();
    bgnline(); v2f(bars[12]); v2f(bars[13]); endline();
    bgnline(); v2f(bars[14]); v2f(bars[15]); endline();
    bgnline(); v2f(bars[16]); v2f(bars[17]); endline();

    scrmask(0, xmaxwindow, 0, ymaxwindow);
    popmatrix();

    if (!in_cmode)
    {
	lsetdepth(zminscreen, zmaxscreen);
	zbuffer(FALSE);
    }
    else
    {
	color(ci_table[C_ORANGE]);
	linewidth(3);
	bgnline(); v2f(orange_bars[0]); v2f(orange_bars[1]); endline();
	bgnline(); v2f(orange_bars[2]); v2f(orange_bars[3]); endline();
	linewidth(2);
	bgnline();
	v2f(w[0]); v2f(w[1]); v2f(w[2]); v2f(w[3]); v2f(w[4]);
	endline();
	linewidth(1);
    }

    popmatrix();
}


/*
 * Initialize the horizon's private data and add its functions to
 * the drawing lists
 */
void init_horizon(float px, float py, float pz, float size)
{
    horizon_t *inst;

    inst = (horizon_t *)malloc(sizeof(*inst));
    bzero(inst, sizeof(*inst));
    inst->plateobject = plate1;
    inst->px = px;
    inst->py = py;
    inst->pz = pz;
    inst->size = size;

    append_inst_list(draw_horizon, update_horizon, inst);
}


/************************************************************************
***			warning light functions			      ***
************************************************************************/

typedef struct {
    float px, py, pz;		/* Position of instrument */
    float size;			/* Size of instrument */
    object_t *plateobject;
    char label[16];
    short *warning;
    short last_state[2];
} wlight_t;


/*
 * Draw the artificial wlight
 */
draw_wlight(wlight_t *inst)
{
    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);

    frontbuffer(TRUE);

    if (!in_cmode)
    {
	zbuffer(TRUE);
	lighting(TRUE);
	drawobj(inst->plateobject, 0x3);
	lighting(FALSE);
	zbuffer(FALSE);

	cpack(0xff010101);
    }
    else
    {
	drawmode(plate_ci_mode);
	drawobj(inst->plateobject, 0x9);
	drawmode(NORMALDRAW);
	drawobj(inst->plateobject, 0x2);

	color(ci_table[C_BLACK]);
    }

    cmov2(-0.12 * (strwidth(inst->label) / 2.0), -3.3);
    charstr(inst->label);

    frontbuffer(FALSE);

    popmatrix();
}



/*
 * Update the artificial wlight
 */
update_wlight(wlight_t *inst, int forceupdate)
{
    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);

    frontbuffer(TRUE);

    if (!in_cmode)
    {
	zbuffer(TRUE);
	lighting(TRUE);
    }
    if (inst->last_state[instrument_data.current] != *(inst->warning))
    {
	if (inst->last_state[instrument_data.current] = *(inst->warning))
	    drawobj(inst->plateobject, 0x4);
	else
	    drawobj(inst->plateobject, 0x2);
    }
    if (!in_cmode)
    {
	lighting(FALSE);
	zbuffer(FALSE);
    }

    frontbuffer(FALSE);

    popmatrix();
}



/*
 * Initialize the wlight's private data and add its functions to
 * the drawing lists
 */
void init_wlight(float px, float py, float pz, float size, short *warning, char *label)
{
    wlight_t *inst;

    inst = (wlight_t *)malloc(sizeof(*inst));
    bzero(inst, sizeof(*inst));
    inst->plateobject = wlight;
    inst->px = px;
    inst->py = py;
    inst->pz = pz;
    inst->size = size;
    inst->warning = warning;
    strncpy(inst->label, label, 16);

    append_inst_list(draw_wlight, update_wlight, inst);
}


/************************************************************************
***			Text Meter functions			      ***
************************************************************************/

#define TEXT_METER_LINES 2

typedef struct {
    float px, py, pz;		/* Position of instrument */
    float size;			/* Size of instrument */
    object_t *plateobject;
    char text[TEXT_METER_LINES][80];
    int textdrawn[2];
    int timeout[TEXT_METER_LINES];
} text_meter_t;


/*
 * Draw the text_meter
 */
draw_text_meter(text_meter_t *inst)
{
    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);

    drawmode(NORMALDRAW);

    frontbuffer(TRUE);

    COLOR(C_BLACK);
    clear_inst4();

    draw_plate(inst->plateobject, 0x3);

    frontbuffer(FALSE);

    popmatrix();
}


/*
 * Update the text_meter's state
 */
update_text_meter(text_meter_t *inst, int forceupdate)
{
    int i;

    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);

    for (i=0; i < TEXT_METER_LINES; i++)
    {
	if (inst->timeout[i] > 0)
	    inst->timeout[i]--;
	else if (inst->timeout[i] == 0)
	{
	    inst->timeout[i] = -1;
	    inst->text[i][0] = '\0';
	    inst->textdrawn[0] = 0;
	    inst->textdrawn[1] = 0;
	}
    }

    if (!inst->textdrawn[instrument_data.current])
    {
	zbuffer(!in_cmode);
	COLOR(C_BLACK);
	clear_inst4();
	zbuffer(FALSE);

	COLOR(C_WHITE);
	for (i=0; i < TEXT_METER_LINES; i++)
	{
	    cmov2(-12.0, 1.0 - i*2);
	    charstr(inst->text[i]);
	}
	inst->textdrawn[instrument_data.current] = 1;
    }
    popmatrix();
}

static text_meter_t *tm;


/*
 * Initialize the text_meter's private data and add its functions to
 * the drawing lists
 */
void init_text_meter(float px, float py, float pz, float size)
{
    text_meter_t *inst;
    int i;

    inst = (text_meter_t *)malloc(sizeof(*inst));
    bzero(inst, sizeof(*inst));
    inst->plateobject = plate4;
    inst->px = px;
    inst->py = py;
    inst->pz = pz;
    inst->size = size;
    for (i=0; i < TEXT_METER_LINES; i++)
    {
	inst->text[i][0] = 0;
	inst->timeout[i] = -1;
    }
    inst->textdrawn[0] = 1;
    inst->textdrawn[1] = 1;
    tm = inst;

    append_inst_list(draw_text_meter, update_text_meter, inst);
}


/*
 * set text_meter text
 */
void set_text_meter(int lnum, char *text, int timeout)
{
    strncpy(tm->text[lnum], text, 80);
    tm->textdrawn[0] = 0;
    tm->textdrawn[1] = 0;
    tm->timeout[lnum] = timeout;
}


/************************************************************************
***			Storess Meter functions			      ***
************************************************************************/

typedef struct {
    float px, py, pz;		/* Position of instrument */
    float size;			/* Size of instrument */
    int last_sw[2];
    int last_rk[2];
    object_t *plateobject;
} stores_meter_t;


/*
 * Draw the stores_meter
 */
draw_stores_meter(stores_meter_t *inst)
{
    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);

    if (in_cmode)
    {
	drawmode(NORMALDRAW);
	color(ci_table[C_BLACK]);
	clear_inst5();

	drawmode(plate_ci_mode);
	color(0);
	clear_inst5();
	color(P_MARKINGS);
    }
    else
    {
	drawmode(UNDERDRAW);

	color(U_INST);
	clear_inst5();

	color(MARKINGS);
    }

    cmov2(-12.0, -1.6);
    charstr("Sidewinders");
    cmov2(4.0, -1.6);
    charstr("Rockets");

    drawmode(NORMALDRAW);

    frontbuffer(TRUE);

    COLOR(C_BLACK);
    clear_inst5();

    draw_plate(inst->plateobject, 0x3);

    frontbuffer(FALSE);

    popmatrix();
}


/*
 * Update the stores_meter's state
 */
update_stores_meter(stores_meter_t *inst, int forceupdate)
{
    int i;

    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);

    if (inst->last_sw[instrument_data.current] != sidewinders ||
	inst->last_rk[instrument_data.current] != rockets ||
	forceupdate)
    {
	if (in_cmode)
	    zbuffer(TRUE);

	COLOR(C_BLACK);
	clear_inst5();

	if (in_cmode)
	    zbuffer(FALSE);

	if (MAX_SW >= 3)
	{
	    if (sidewinders >= 3)
		COLOR(C_RED);
	    else
		COLOR(C_DRED);
	    circf(-10.0, 1.0, 0.62);
	    COLOR(C_WHITE);
	    circ(-10.0, 1.0, 0.62);
	}

	if (MAX_SW >= 1)
	{
	    if (sidewinders >= 1)
		COLOR(C_RED);
	    else
		COLOR(C_DRED);
	    circf(-8.0, 1.0, 0.62);
	    COLOR(C_WHITE);
	    circ(-8.0, 1.0, 0.62);
	}

	if (MAX_SW >= 2)
	{
	    if (sidewinders >= 2)
		COLOR(C_RED);
	    else
		COLOR(C_DRED);
	    circf(-6.0, 1.0, 0.62);
	    COLOR(C_WHITE);
	    circ(-6.0, 1.0, 0.62);
	}

	if (MAX_SW >= 4)
	{
	    if (sidewinders >= 4)
		COLOR(C_RED);
	    else
		COLOR(C_DRED);
	    circf(-4.0, 1.0, 0.62);
	    COLOR(C_WHITE);
	    circ(-4.0, 1.0, 0.62);
	}

	if (MAX_RK >= 3)
	{
	    if (rockets >= 3)
		COLOR(C_RED);
	    else
		COLOR(C_DRED);
	    circf(10.0, 1.0, 0.62);
	    COLOR(C_WHITE);
	    circ(10.0, 1.0, 0.62);
	}

	if (MAX_RK >= 1)
	{
	    if (rockets >= 1)
		COLOR(C_RED);
	    else
		COLOR(C_DRED);
	    circf(8.0, 1.0, 0.62);
	    COLOR(C_WHITE);
	    circ(8.0, 1.0, 0.62);
	}

	if (MAX_RK >= 2)
	{
	    if (rockets >= 2)
		COLOR(C_RED);
	    else
		COLOR(C_DRED);
	    circf(6.0, 1.0, 0.62);
	    COLOR(C_WHITE);
	    circ(6.0, 1.0, 0.62);
	}

	if (MAX_RK >= 4)
	{
	    if (rockets >= 4)
		COLOR(C_RED);
	    else
		COLOR(C_DRED);
	    circf(4.0, 1.0, 0.62);
	    COLOR(C_WHITE);
	    circ(4.0, 1.0, 0.62);
	}

	inst->last_sw[instrument_data.current] = sidewinders;
	inst->last_rk[instrument_data.current] = rockets;
    }

    popmatrix();
}

static stores_meter_t *sm;


/*
 * Initialize the stores_meter's private data and add its functions to
 * the drawing lists
 */
void init_stores_meter(float px, float py, float pz, float size)
{
    stores_meter_t *inst;
    int i;

    inst = (stores_meter_t *)malloc(sizeof(*inst));
    bzero(inst, sizeof(*inst));
    inst->plateobject = plate5;
    inst->px = px;
    inst->py = py;
    inst->pz = pz;
    inst->size = size;
    sm = inst;

    append_inst_list(draw_stores_meter, update_stores_meter, inst);
}


/*
 * set stores_meter
 */
void set_stores_meter()
{
}


/************************************************************************
***				Altimeter functions		      ***
************************************************************************/


typedef struct altimeter_struct
{
    float px, py, pz;		/* Position of instrument */
    float size;			/* Size of instrument */
    float last_alt[2];		/* Previous altitudes of both buffers */
    float last_rot1000[2];
    float last_rot100[2];
    object_t *plateobject;
    int framec;
    int warningup;
    int warningdown;
    int numframes;
    int displayagain;
    float scale;
    int old10;
    float scrollalt;
    float scale10;
    char high10str[4];
    char low10str[4];
} altimeter_t;



/*
 * Draw the altimeter
 */
draw_altimeter(altimeter_t *inst)
{
    static float verts[4][3] = {{-9.0, -9.0, 0.0}, {-9.0, 9.0, 0.0},
				{9.0, 9.0, 0.0}, {9.0, -9.0, 0.0}};
    static float ticks[3][3] = { 0.0,7.7,0.0, 0.0,9.0,0.0, 0.0,8.3,0.0 };
    short sl, sr, sb, st;
    char s[4];
    int i, x;

    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);
    drawmode(UNDERDRAW);

    color(U_INST);
    clear_inst1();

    color(MARKINGS);
    for (x=0; x<3600; x+=360)
    {
	bgnline();
	v3f(ticks[0]);
	v3f(ticks[1]);
	endline();
	rotate(-360, 'z');
    }
    for (x=0; x<3600; x+=72)
    {
	if (x%360)
	{
	    bgnline();
	    v3f(ticks[2]);
	    v3f(ticks[1]);
	    endline();
	}
	rotate(-72, 'z');
    }
    pushviewport();
    getviewport(&sl, &sr, &sb, &st);
    viewport(sl-instrument_data.threewide, sr-instrument_data.threewide,
	     sb-instrument_data.chartall, st-instrument_data.chartall);
    cmov(0.0, -5.2, 0.0);
    charstr("ALT");
    popviewport();
    pushviewport();
    viewport(sl-instrument_data.charwide, sr-instrument_data.charwide,
	     sb-instrument_data.chartall, st-instrument_data.chartall);
    i = 0;
    for (x=0; x<3600; x+=360)
    {
	sprintf(s, "%d", i++);
	cmov(0.0, 7.0, 0.0);
	charstr(s);
	rotate(-360, 'z');
    }
    popviewport();
    drawmode(NORMALDRAW);
    frontbuffer(TRUE);

    COLOR(C_BLACK);
    clear_inst1();

    draw_plate(inst->plateobject, 0x3);

    frontbuffer(FALSE);
    popmatrix();
}

draw_altimeter_ci(altimeter_t *inst)
{
    static float verts[4][3] = {{-9.0, -9.0, 0.0}, {-9.0, 9.0, 0.0},
				{9.0, 9.0, 0.0}, {9.0, -9.0, 0.0}};
    static float ticks[3][3] = { 0.0,7.7,0.0, 0.0,9.0,0.0, 0.0,8.3,0.0 };
    short sl, sr, sb, st;
    char s[4];
    int i, x;

    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);

    color(ci_table[C_BLACK]);
    clear_inst1();

    drawmode(PUPDRAW);
    color(U_BLACK);
    clear_inst1();

    color(P_MARKINGS);
    for (x=0; x<3600; x+=360)
    {
	bgnline();
	v3f(ticks[0]);
	v3f(ticks[1]);
	endline();
	rotate(-360, 'z');
    }
    for (x=0; x<3600; x+=72)
    {
	if (x%360)
	{
	    bgnline();
	    v3f(ticks[2]);
	    v3f(ticks[1]);
	    endline();
	}
	rotate(-72, 'z');
    }
    pushviewport();
    getviewport(&sl, &sr, &sb, &st);
    viewport(sl-instrument_data.threewide, sr-instrument_data.threewide,
	     sb-instrument_data.chartall, st-instrument_data.chartall);
    cmov(0.0, -5.2, 0.0);
    charstr("ALT");
    popviewport();
    pushviewport();
    viewport(sl-instrument_data.charwide, sr-instrument_data.charwide,
	     sb-instrument_data.chartall, st-instrument_data.chartall);
    i = 0;
    for (x=0; x<3600; x+=360)
    {
	sprintf(s, "%d", i++);
	color(P_MARKINGS);
	cmov(0.0, 7.0, 0.0);
	charstr(s);
	rotate(-360, 'z');
    }
    popviewport();

    drawmode(plate_ci_mode);
    drawobj(inst->plateobject, 0x3);

    drawmode(NORMALDRAW);
    frontbuffer(TRUE);

    color(ci_table[C_BLACK]);
    clear_inst1();

    frontbuffer(FALSE);
    color(ci_table[C_BLACK]);
    clear_inst1();

    popmatrix();
}



/*
 * Update the altimeter's needles
 */
update_altimeter(altimeter_t *inst, int forceupdate)
{
    static float lowstripes[16][3] = { -1.5,-4.5,0.0, -2.25,-4.5,0.0,
		-1.0,-3.25,0.0, -1.0,-4.0,0.0, -3.0,-4.5,0.0, -3.75,-4.5,0.0,
		-1.25,-2.0,0.0, -1.0,-2.5,0.0, -4.5,-4.5,0.0, -4.5,-3.75,0.0,
		-2.75,-2.0,0.0, -2.0,-2.0,0.0, -4.5,-3.0,0.0, -4.5,-2.0,0.0,
		-3.5,-2.0,0.0, -1.0,-2.0,0.0 };
    static float box10[4][3]  = { -4.5,-4.5,0.0, -1.0,-4.5,0.0, -1.0,-2.0,0.0,
		-4.5,-2.0,0.0 };
    static float boxt10[4][3] = { -4.5,-2.0,0.0, -1.0,-2.0,0.0, -1.0,.5,0.0,
		-4.5,.5,0.0 };
    static float boxb10[4][3] = { -4.5,-7.0,0.0, -1.0,-7.0,0.0, -1.0,-4.5,0.0,
		-4.5,-4.5,0.0 };
    static float needle1000[5][3] = {-.3,0.0,0.0, -.3,4.0,0.0, 0.0,5.0,0.0,
		.3,4.0,0.0, .3,0.0,0.0};
    static float needle100[5][3]  = {-.2,0.0,0.0, -.2,5.0,0.0, 0.0,7.0,0.0,
		.2,5.0,0.0, .2,0.0,0.0 };
    static float needle1000box[5][3] = {-.7,-.8,0.0, -.7,5.3,0.0, .7,5.3,0.0,
		.7,-.8,0.0 };
    static float needle100box[5][3]  = {-.7,-.3,0.0, -.7,7.3,0.0, .7,7.3,0.0,
		.7,-.3,0.0};
    static float cx= -3.5, cy= -3.7, cz=0.0; /* Pos of text for 10K ft. meter */
    int current;
    int new10= 0;
    int old10= 0;
    char buf[5];
    float alt1000;
    float altitude;
    Plane pp = planes[0];

    altitude = pp->y - plane_height;

    current = instrument_data.current;

    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);
    if ((altitude != inst->last_alt[current]) || forceupdate ||
		(inst->framec + inst->displayagain))
    {
	if (inst->displayagain) inst->displayagain--;
	cpack(0x00000000);	/* Clear old display */
	pushmatrix();
	rot(inst->last_rot1000[current], 'z');
	drawneedlebox(needle1000box);
	popmatrix();
	pushmatrix();
	rot(inst->last_rot100[current], 'z');
	drawneedlebox(needle100box);
	popmatrix();
#ifndef NO_MS
	if (ms_samples)
	{
	    pushmatrix();
	    rot(inst->last_rot1000[!current], 'z');
	    drawneedlebox(needle1000box);
	    popmatrix();
	    pushmatrix();
	    rot(inst->last_rot100[!current], 'z');
	    drawneedlebox(needle100box);
	    popmatrix();
	}
#endif

	ICOLOR(instrument_data.textbackground);
	drawneedlebox(box10);

	new10 = (int)altitude/10000;
	old10 = (int)inst->last_alt[current]/10000;
	if ((new10 == 0)&&(old10 == 1))
	{
	    inst->warningdown = -1;
	    inst->warningup = 0;
	    if (!inst->framec) inst->framec = inst->numframes;
	}
	else if ((new10 == 1)&&(old10 == 0))
	{
	    inst->warningdown = 0;
	    inst->warningup = 1;
	    if (!inst->framec) inst->framec = 1;
	}

	if ((altitude < 10000) || (inst->warningup+inst->warningdown))
	{
	    if (inst->framec)
	    {
		pushmatrix();

		ICOLOR(instrument_data.text);
		cmov(cx, cy, cz);
		charstr("10");
		translate(0.0, inst->scale * inst->framec, 0.0);
		ICOLOR(instrument_data.textbackground);
		drawneedlebox(box10);
	    }
	    ICOLOR(instrument_data.yellow);
	    bgnpolygon();
	    v3f(lowstripes[0]);
	    v3f(lowstripes[1]);
	    v3f(lowstripes[2]);
	    v3f(lowstripes[3]);
	    endpolygon();
	    bgnpolygon();
	    v3f(lowstripes[4]);
	    v3f(lowstripes[5]);
	    v3f(lowstripes[6]);
	    v3f(lowstripes[15]);
	    v3f(lowstripes[7]);
	    endpolygon();
	    bgnpolygon();
	    v3f(lowstripes[8]);
	    v3f(lowstripes[9]);
	    v3f(lowstripes[10]);
	    v3f(lowstripes[11]);
	    endpolygon();
	    bgnpolygon();
	    v3f(lowstripes[12]);
	    v3f(lowstripes[13]);
	    v3f(lowstripes[14]);
	    endpolygon();
	    if (inst->framec)
	    {
		popmatrix();
		cpack(0x00000000);
		bgnpolygon();
		v3f(boxt10[0]);
		v3f(boxt10[1]);
		v3f(boxt10[2]);
		v3f(boxt10[3]);
		endpolygon();
		inst->framec = (inst->framec + inst->warningup
				+ inst->warningdown) % inst->numframes;
		if (!inst->framec)
		{
		    inst->warningup = inst->warningdown = 0;
		    inst->displayagain = 2;
		}
	    }
	}
	else if ((alt1000=(10000.0-fmod(altitude, 10000.0))) <
		 inst->scrollalt)
	{
	    pushmatrix();
	    ICOLOR(instrument_data.text);
	    translate(0.0,(inst->scrollalt-alt1000)*inst->scale10,0.0);
	    if (inst->old10 != new10)
	    {
		sprintf(inst->low10str,"%d",new10*10);
		sprintf(inst->high10str,"%d",(new10+1)*10);
	    }
	    cmov(cx,cy,cz);
	    charstr(inst->low10str);
	    translate(0.0, -2.5, 0.0);
	    cmov(cx,cy,cz);
	    charstr(inst->high10str);
	    popmatrix();
	    cpack(0x00000000);
	    drawneedlebox(boxt10);
	    drawneedlebox(boxb10);
	}
	else
	{
	    ICOLOR(instrument_data.text);
	    sprintf(buf,"%d",new10*10);
	    cmov(cx,cy,cz);
	    charstr(buf);
	}
	ICOLOR(instrument_data.textborder);
	bgnclosedline();
	v3f(box10[0]);
	v3f(box10[1]);
	v3f(box10[2]);
	v3f(box10[3]);
	endclosedline();
	inst->last_rot1000[current]=(int)(fmod(altitude,10000.0)*-.036);
	inst->last_rot100[current] =(int)(fmod(altitude, 1000.0)*-.36);

	drawneedle(inst->last_rot100[current], instrument_data.darkneedle,
		   needle100);
	drawneedle(inst->last_rot1000[current], instrument_data.lightneedle,
		   needle1000);
	inst->last_alt[current] = altitude;
    }
    popmatrix();
}

update_altimeter_ci(altimeter_t *inst, int forceupdate)
{
    static float lowstripes[16][3] = { -1.5,-4.5,0.0, -2.25,-4.5,0.0,
		-1.0,-3.25,0.0, -1.0,-4.0,0.0, -3.0,-4.5,0.0, -3.75,-4.5,0.0,
		-1.25,-2.0,0.0, -1.0,-2.5,0.0, -4.5,-4.5,0.0, -4.5,-3.75,0.0,
		-2.75,-2.0,0.0, -2.0,-2.0,0.0, -4.5,-3.0,0.0, -4.5,-2.0,0.0,
		-3.5,-2.0,0.0, -1.0,-2.0,0.0 };
    static float box10[4][3]  = { -4.5,-4.5,0.0, -1.0,-4.5,0.0, -1.0,-2.0,0.0,
		-4.5,-2.0,0.0 };
    static float boxt10[4][3] = { -4.5,-2.0,0.0, -1.0,-2.0,0.0, -1.0,.5,0.0,
		-4.5,.5,0.0 };
    static float boxb10[4][3] = { -4.5,-7.0,0.0, -1.0,-7.0,0.0, -1.0,-4.5,0.0,
		-4.5,-4.5,0.0 };
    static float needle1000[5][3] = {-.3,0.0,0.0, -.3,4.0,0.0, 0.0,5.0,0.0,
		.3,4.0,0.0, .3,0.0,0.0};
    static float needle100[5][3]  = {-.2,0.0,0.0, -.2,5.0,0.0, 0.0,7.0,0.0,
		.2,5.0,0.0, .2,0.0,0.0 };
    static float needle1000box[5][3] = {-.7,-.8,0.0, -.7,5.3,0.0, .7,5.3,0.0,
		.7,-.8,0.0 };
    static float needle100box[5][3]  = {-.6,-.3,0.0, -.6,7.3,0.0, .6,7.3,0.0,
		.6,-.3,0.0};
    static float cx= -3.5, cy= -3.7, cz=0.0; /* Pos of text for 10K ft. meter */
    int current;
    int new10= 0;
    int old10= 0;
    char buf[5];
    float alt1000;
    float altitude;
    Plane pp = planes[0];

    altitude = pp->y - plane_height;

    current = instrument_data.current;
    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);
    if ((altitude != inst->last_alt[current]) || forceupdate ||
		(inst->framec + inst->displayagain))
    {
	if (inst->displayagain) inst->displayagain--;
	color(ci_table[C_BLACK]);
	pushmatrix();
	rot(inst->last_rot1000[current], 'z');
	drawneedlebox(needle1000box);
	popmatrix();
	pushmatrix();
	rot(inst->last_rot100[current], 'z');
	drawneedlebox(needle100box);
	popmatrix();
	ICOLOR(instrument_data.textbackground);
	drawneedlebox(box10);

	new10 = (int)altitude/10000;
	old10 = (int)inst->last_alt[current]/10000;
	if ((new10 == 0)&&(old10 == 1))
	{
	    inst->warningdown = -1;
	    inst->warningup = 0;
	    if (!inst->framec) inst->framec = inst->numframes;
	}
	else if ((new10 == 1)&&(old10 == 0))
	{
	    inst->warningdown = 0;
	    inst->warningup = 1;
	    if (!inst->framec) inst->framec = 1;
	}

	if ((altitude < 10000) || (inst->warningup+inst->warningdown))
	{
	    if (inst->framec)
	    {
		pushmatrix();

		ICOLOR(instrument_data.text);
		cmov(cx, cy, cz);
		charstr("10");
		translate(0.0, inst->scale * inst->framec, 0.0);
		ICOLOR(instrument_data.textbackground);
		drawneedlebox(box10);
	    }
	    ICOLOR(instrument_data.yellow);
	    bgnpolygon();
	    v3f(lowstripes[0]);
	    v3f(lowstripes[1]);
	    v3f(lowstripes[2]);
	    v3f(lowstripes[3]);
	    endpolygon();
	    bgnpolygon();
	    v3f(lowstripes[4]);
	    v3f(lowstripes[5]);
	    v3f(lowstripes[6]);
	    v3f(lowstripes[15]);
	    v3f(lowstripes[7]);
	    endpolygon();
	    bgnpolygon();
	    v3f(lowstripes[8]);
	    v3f(lowstripes[9]);
	    v3f(lowstripes[10]);
	    v3f(lowstripes[11]);
	    endpolygon();
	    bgnpolygon();
	    v3f(lowstripes[12]);
	    v3f(lowstripes[13]);
	    v3f(lowstripes[14]);
	    endpolygon();
	    if (inst->framec)
	    {
		popmatrix();
		COLOR(C_BLACK);
		bgnpolygon();
		v3f(boxt10[0]);
		v3f(boxt10[1]);
		v3f(boxt10[2]);
		v3f(boxt10[3]);
		endpolygon();
		inst->framec = (inst->framec + inst->warningup
				+ inst->warningdown) % inst->numframes;
		if (!inst->framec)
		{
		    inst->warningup = inst->warningdown = 0;
		    inst->displayagain = 2;
		}
	    }
	}
	else if ((alt1000=(10000.0-fmod(altitude, 10000.0))) <
		 inst->scrollalt)
	{
	    pushmatrix();
	    ICOLOR(instrument_data.text);
	    translate(0.0,(inst->scrollalt-alt1000)*inst->scale10,0.0);
	    if (inst->old10 != new10)
	    {
		sprintf(inst->low10str,"%d",new10*10);
		sprintf(inst->high10str,"%d",(new10+1)*10);
	    }
	    cmov(cx,cy,cz);
	    charstr(inst->low10str);
	    translate(0.0, -2.5, 0.0);
	    cmov(cx,cy,cz);
	    charstr(inst->high10str);
	    popmatrix();
	    COLOR(C_BLACK);
	    drawneedlebox(boxt10);
	    drawneedlebox(boxb10);
	}
	else
	{
	    ICOLOR(instrument_data.text);
	    sprintf(buf,"%d",new10*10);
	    cmov(cx,cy,cz);
	    charstr(buf);
	}
	ICOLOR(instrument_data.textborder);
	bgnclosedline();
	v3f(box10[0]);
	v3f(box10[1]);
	v3f(box10[2]);
	v3f(box10[3]);
	endclosedline();
	inst->last_rot1000[current]=(int)(fmod(altitude,10000.0)*-.036);
	inst->last_rot100[current] =(int)(fmod(altitude, 1000.0)*-.36);

	drawneedle(inst->last_rot100[current], instrument_data.darkneedle,
		   needle100);
	drawneedle(inst->last_rot1000[current], instrument_data.lightneedle,
		   needle1000);
	inst->last_alt[current] = altitude;
    }
    popmatrix();
}



/*
 * Initialize the altimeter's private data and add its functions to
 * the drawing lists
 */
void init_altimeter(float px, float py, float pz, float size)
{
    altimeter_t *inst;

    inst = (altimeter_t *)malloc(sizeof(*inst));
    bzero(inst, sizeof(*inst));
    inst->plateobject = plate1;
    inst->px = px;
    inst->py = py;
    inst->pz = pz;
    inst->size = size;
    inst->last_alt[1] = inst->last_alt[0] = -1.0;
    inst->last_rot1000[0] = inst->last_rot1000[1] = 0.0;
    inst->last_rot100[0] = inst->last_rot100[1] = 0.0;
    inst->framec = 0;
    inst->numframes = 20;
    inst->scale = 2.5 / inst->numframes;
    inst->scrollalt = 1000.0;
    inst->scale10 = 2.5 / inst->scrollalt;
    inst->warningup = inst->warningdown = 0;
    inst->old10 = 0;
    inst->high10str[0] = inst->low10str[0] = '\0';

    if (in_cmode)
	append_inst_list(draw_altimeter_ci, update_altimeter_ci, inst);
    else
	append_inst_list(draw_altimeter, update_altimeter, inst);
}


/************************************************************************
***			Airspeed/machmeter indicator functions	      ***
************************************************************************/


typedef struct {
    float px, py, pz;		/* Position of instrument */
    float size;			/* Size of instrument */
    int last_speed[2];		/* Previous speed of both buffers */
    float last_rot[2];
    float last_machrot[2];
    object_t *plateobject;
    float stall_speed;
    float max_flaps;
    float max_speed;
    int machmeter;
    float maxmach;
    float machstep;
    int nummachticks;
} airspeedmach_t;



/*
 * Draw the airspeed indicator
 */
draw_airspeedmach(airspeedmach_t *inst)
{
    static float verts[4][3] = { -9.0,-9.0,0.0, -9.0,9.0,0.0, 9.0,9.0,0.0,
			9.0,-9.0,0.0 };
    static float ticks[2][3]      = { 0.0,8.0,0.0, 0.0,9.0,0.0 };
    static float smallticks[2][3] = { 0.0,8.3,0.0, 0.0,9.0,0.0 };
    static float machticks[2][3]  = { 0.0,4.5,0.0, 0.0,5.5,0.0 };
    static float machtinyticks[2][3] = { 0.0,5.0,0.0, 0.0,5.5,0.0 };
    short sl, sr, sb, st;
    int numberstep;
    float bigtickstep, numbertickstep, smalltickstep, tinytickstep;
    float machtickstep, machtinytickstep, machtinystep;
    float mach;
    int x;
    char buf[5];

    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);
    if (!in_cmode)
    {
	drawmode(UNDERDRAW);
	color(U_INST);
	clear_inst1();
	color(MARKINGS);
    }
    else
    {
	drawmode(PUPDRAW);
	color(U_BLACK);
	clear_inst1();
	color(P_MARKINGS);
    }

    bigtickstep = -30000.0 / inst->max_speed;
    numbertickstep = bigtickstep;
    if (inst->max_speed <= 300.0)
    {
	numberstep = 50;
	numbertickstep /= 2.0;
    }
    else
	numberstep = 100;

    smalltickstep = -6000.0 / inst->max_speed;
    tinytickstep = -3000.0 / inst->max_speed;

    pushmatrix();
    rot(-30.0,'z');
    for (x=0; x <= (int)inst->max_speed; x+= numberstep)
    {
	bgnline();
	v3f(ticks[0]);
	v3f(ticks[1]);
	endline();
	rot(numbertickstep,'z');
    }
    popmatrix();
    pushmatrix();
    pushviewport();
    getviewport(&sl,&sr,&sb,&st);
    viewport(sl-instrument_data.threewide, sr-instrument_data.threewide,
	     sb-instrument_data.chartall, st-instrument_data.chartall);
    cmov(0.0,1.2,0.0);
    charstr("KTS");
    popviewport();
    pushviewport();
    viewport(sl-instrument_data.fourwide, sr-instrument_data.fourwide,
	     sb-instrument_data.chartall, st-instrument_data.chartall);
    cmov(0.0,-1.2,0.0);
    charstr("MACH");
    popviewport();
    pushviewport();
    rot(-30.0,'z');
    viewport(sl-instrument_data.threewide, sr-instrument_data.threewide,
	    sb-instrument_data.chartall, st-instrument_data.chartall);
    for (x=0; x <= (int)inst->max_speed; x+= numberstep)
    {
	cmov(0.0, 6.8, 0.0);
	sprintf(buf,"%d",x);
	charstr(buf);
	rot(numbertickstep,'z');
    }
    popviewport();
    popmatrix();
    pushmatrix();
    rot(-30.0, 'z');
    for (x=0; (x < 300) && (x <= inst->max_speed); x += 10)
    {
	if (x%numberstep)
	{
	    bgnline();
	    v3f(smallticks[0]);
	    v3f(smallticks[1]);
	    endline();
	}
	rot(tinytickstep, 'z');
    }
    for (x=300; x <= inst->max_speed; x += 20)
    {
	if (x%100)
	{
	    bgnline();
	    v3f(smallticks[0]);
	    v3f(smallticks[1]);
	    endline();
	}
	rot(smalltickstep, 'z');
    }
    popmatrix();
    machtickstep = -300.0 * inst->machstep / inst->maxmach;
    machtinytickstep = machtickstep / inst->nummachticks;
    machtinystep = inst->machstep /
				(float) inst->nummachticks;
    if (inst->machmeter)
    {
	pushmatrix();
	rot(-30.0, 'z');
	for (mach=0.0; mach <= inst->maxmach;
	     mach += inst->machstep)
	{
	    bgnline();
	    v3f(machticks[0]);
	    v3f(machticks[1]);
	    endline();
	    rot(machtickstep, 'z');
	}
	popmatrix();
	pushmatrix();
	rot(-30.0, 'z');
	for (mach=0.0; mach < inst->maxmach;
	     mach += inst->machstep)
	{
	    rot(machtinytickstep, 'z');
	    for (x=1; x < inst->nummachticks; x++)
	    {
		bgnline();
		v3f(machtinyticks[0]);
		v3f(machtinyticks[1]);
		endline();
		rot(machtinytickstep, 'z');
	    }
	}
	popmatrix();
	pushviewport();
	pushmatrix();
	rot(-30.0, 'z');
	viewport(sl-instrument_data.threewide, sr-instrument_data.threewide,
		sb-instrument_data.chartall, st-instrument_data.chartall);
	for (mach=0.0; mach <= inst->maxmach; mach +=
					inst->machstep)
	{
	    cmov(0.0, 3.2, 0.0);
	    sprintf(buf,"%3.1f",mach);
	    charstr(buf);
	    rot(machtickstep, 'z');
	}
	popviewport();
	popmatrix();
    }

    drawmode(NORMALDRAW);
    frontbuffer(TRUE);

    COLOR(C_BLACK);
    clear_inst1();

    draw_plate(inst->plateobject, 0x3);

    frontbuffer(FALSE);
    popmatrix();
}


update_airspeedmach(airspeedmach_t *inst, int forceupdate)
{
    static float needle[5][3] = {-.2,0.0,0.0, -.2,5.5,0.0, 0.0,7.0,0.0,
		    .2,5.5,0.0, .2,0.0,0.0};
    static float needlebox[5][3] = {-.7,-.8,0.0, -.7,7.5,0.0, .7,7.5,0.0,
		    .7,-.8,0.0 };
    static float machneedle[5][3] = {-.2,0.0,0.0, -.2,2.8,0.0, 0.0,4.2,0.0,
		    .2,2.8,0.0, .2,0.0,0.0};
    static float machneedlebox[5][3] = {-.7,-.8,0.0, -.7,4.8,0.0, .7,4.8,0.0,
		    .7,-.8,0.0 };
    int current;
    static float machone = 700.0;
    current = instrument_data.current;

    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);
    if ((airspeed != inst->last_speed[current]) || forceupdate)
    {
	COLOR(C_BLACK);
	pushmatrix();
	rot(inst->last_rot[current], 'z');
	drawneedlebox(needlebox);
	popmatrix();
	pushmatrix();
	rot(inst->last_machrot[current], 'z');
	drawneedlebox(machneedlebox);
	popmatrix();
#ifndef NO_MS
	if (ms_samples)
	{
	    pushmatrix();
	    rot(inst->last_rot[!current], 'z');
	    drawneedlebox(needlebox);
	    popmatrix();
	    pushmatrix();
	    rot(inst->last_machrot[!current], 'z');
	    drawneedlebox(machneedlebox);
	    popmatrix();
	}
#endif

	inst->last_rot[current] = -300.0 * airspeed / inst->max_speed - 30.0;
	if (inst->last_rot[current] < -330.0)
	    inst->last_rot[current] = -330.0;
	else if (inst->last_rot[current] > -30.0)
	    inst->last_rot[current] = -30.0;
	inst->last_machrot[current] = -300 * airspeed /
				( inst->maxmach * machone ) - 30.0;
	if (inst->last_machrot[current] < -330.0)
	    inst->last_machrot[current] = -330.0;
	else if (inst->last_machrot[current] > -30.0)
	    inst->last_machrot[current] = -30.0;

	drawneedle(inst->last_machrot[current],
		   instrument_data.darkneedle, machneedle);
	drawneedle(inst->last_rot[current],
		   instrument_data.lightneedle, needle);
    }
    popmatrix();
}



void init_airspeedmach(float px, float py, float pz, float size,
			     float maxspeed, int machmeter, float maxmach,
			     float machstep, int nummachticks)
{
    airspeedmach_t *inst;

    inst = (airspeedmach_t *)malloc(sizeof(*inst));
    bzero(inst, sizeof(*inst));
    inst->plateobject = plate1;
    inst->px = px;
    inst->py = py;
    inst->pz = pz;
    inst->size = size;
    inst->max_speed = maxspeed;
    inst->last_speed[1] = inst->last_speed[0] = airspeed + 1.0;
    inst->machmeter = machmeter;
    inst->maxmach = maxmach;
    inst->machstep = machstep;
    inst->nummachticks = nummachticks;
    append_inst_list(draw_airspeedmach, update_airspeedmach, inst);
}


/************************************************************************
***			Airspeed indicator functions		     ****
************************************************************************/


typedef struct {
    float px, py, pz;		/* Position of instrument */
    float size;			/* Size of instrument */
    object_t *plateobject;
    int last_speed[2];		/* Previous speed of both buffers */
    float last_rot[2];
    float stall_speed;
    float max_flaps;
    float max_speed;
} airspeed_meter_t;


/*
 * Draw the airspeed indicator
 */
draw_airspeed_meter(airspeed_meter_t *inst)
{
    static float verts[4][3] = { -9.0,-9.0,0.0, -9.0,9.0,0.0, 9.0,9.0,0.0,
			9.0,-9.0,0.0 };
    static float ticks[2][3]      = { 0.0,8.0,0.0, 0.0,9.0,0.0 };
    static float smallticks[2][3] = { 0.0,8.3,0.0, 0.0,9.0,0.0 };
    short sl, sr, sb, st;
    int numberstep;
    float bigtickstep, numbertickstep, smalltickstep, tinytickstep;
    int x;
    char buf[5];

    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);

    if (!in_cmode)
    {
	drawmode(UNDERDRAW);
	color(U_INST);
	clear_inst1();
	color(MARKINGS);
    }
    else
    {
	drawmode(PUPDRAW);
	color(U_BLACK);
	clear_inst1();
	color(P_MARKINGS);
    }

    bigtickstep = -30000.0 / inst->max_speed;
    numbertickstep = bigtickstep;
    if (inst->max_speed <= 300.0)
    {
	numberstep = 50;
	numbertickstep /= 2.0;
    }
    else
	numberstep = 100;

    smalltickstep = -6000.0 / inst->max_speed;
    tinytickstep = -3000.0 / inst->max_speed;

    pushmatrix();
    rot(-30.0,'z');
    for (x=0; x <= (int)inst->max_speed; x+= numberstep)
    {
	bgnline();
	v3f(ticks[0]);
	v3f(ticks[1]);
	endline();
	rot(numbertickstep,'z');
    }
    popmatrix();
    pushmatrix();
    pushviewport();
    getviewport(&sl,&sr,&sb,&st);
    viewport(sl-instrument_data.threewide, sr-instrument_data.threewide,
	     sb-instrument_data.chartall, st-instrument_data.chartall);
    cmov(0.0,-4.0,0.0);
    charstr("KTS");
    popviewport();
    pushviewport();
    rot(-30.0,'z');
    viewport(sl-instrument_data.threewide, sr-instrument_data.threewide,
	    sb-instrument_data.chartall, st-instrument_data.chartall);
    for (x=0; x <= (int)inst->max_speed; x+= numberstep)
    {
	cmov(0.0, 6.8, 0.0);
	sprintf(buf,"%d",x);
	charstr(buf);
	rot(numbertickstep,'z');
    }
    popviewport();
    popmatrix();
    pushmatrix();
    rot(-30.0, 'z');
    for (x=0; (x < 300) && (x <= inst->max_speed); x += 10)
    {
	if (x%numberstep)
	{
	    bgnline();
	    v3f(smallticks[0]);
	    v3f(smallticks[1]);
	    endline();
	}
	rot(tinytickstep, 'z');
    }
    for (x=300; x <= inst->max_speed; x += 20)
    {
	if (x%100)
	{
	    bgnline();
	    v3f(smallticks[0]);
	    v3f(smallticks[1]);
	    endline();
	}
	rot(smalltickstep, 'z');
    }
    popmatrix();

    drawmode(NORMALDRAW);
    frontbuffer(TRUE);

    COLOR(C_BLACK);
    clear_inst1();

    draw_plate(inst->plateobject, 0x3);

    frontbuffer(FALSE);
    popmatrix();
}


update_airspeed_meter(airspeed_meter_t *inst, int forceupdate)
{
    static float needle[5][3] = {-.2,0.0,0.0, -.2,5.5,0.0, 0.0,7.0,0.0,
		    .2,5.5,0.0, .2,0.0,0.0};
    static float needlebox[5][3] = {-.7,-.8,0.0, -.7,7.5,0.0, .7,7.5,0.0,
		    .7,-.8,0.0 };
    int current;

    current = instrument_data.current;

    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);
    if ((airspeed != inst->last_speed[current]) || forceupdate)
    {
	COLOR(C_BLACK);
	pushmatrix();
	rot(inst->last_rot[current], 'z');
	drawneedlebox(needlebox);
	popmatrix();
#ifndef NO_MS
	if (ms_samples)
	{
	    pushmatrix();
	    rot(inst->last_rot[!current], 'z');
	    drawneedlebox(needlebox);
	    popmatrix();
	}
#endif

	inst->last_rot[current] = -300.0 * airspeed /
				inst->max_speed - 30.0;
	if (inst->last_rot[current] < -330.0)
	    inst->last_rot[current] = -330.0;
	else if (inst->last_rot[current] > -30.0)
	    inst->last_rot[current] = -30.0;

	drawneedle(inst->last_rot[current], instrument_data.lightneedle,
		   needle);
    }
    popmatrix();
}



void init_airspeed_meter(float px, float py, float pz, float size,
			 float maxspeed)
{
    airspeed_meter_t *inst;

    inst = (airspeed_meter_t *)malloc(sizeof(*inst));
    bzero(inst, sizeof(*inst));
    inst->px = px;
    inst->py = py;
    inst->pz = pz;
    inst->size = size;
    inst->plateobject = plate1;
    inst->max_speed = maxspeed;
    inst->last_speed[1] = inst->last_speed[0] = airspeed + 1.0;

    append_inst_list(draw_airspeed_meter, update_airspeed_meter, inst);
}


/************************************************************************
***			Mach indicator functions		     ****
************************************************************************/


typedef struct {
    float px, py, pz;		/* Position of instrument */
    float size;			/* Size of instrument */
    object_t *plateobject;
    int last_speed[2];		/* Previous speed of both buffers */
    float last_machrot[2];
    float maxmach;
    float machstep;
    int nummachticks;
} mach_meter_t;



/*
 * Draw the mach indicator
 */
draw_mach_meter(mach_meter_t *inst)
{
    static float verts[4][3] = { -9.0,-9.0,0.0, -9.0,9.0,0.0, 9.0,9.0,0.0,
			9.0,-9.0,0.0 };
    static float machticks[2][3]      = { 0.0,7.85,0.0, 0.0,9.0,0.0 };
    static float machtinyticks[2][3] = { 0.0,8.2,0.0, 0.0,9.0,0.0 };
    short sl, sr, sb, st;
    int numberstep;
    float machtickstep, machtinytickstep;
    float mach;
    int x;
    char buf[5];

    /*
     * SGI's original never initialized sl/sr/sb/st here (every other gauge
     * calls getviewport first) — it worked on IRIX because the stale stack
     * slots held the previous gauge's getviewport results. wasm's stack
     * layout differs, so read the viewport properly.
     */
    getviewport(&sl,&sr,&sb,&st);

    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);
    if (!in_cmode)
    {
	drawmode(UNDERDRAW);
	color(U_INST);
	clear_inst1();
	color(MARKINGS);
    }
    else
    {
	drawmode(PUPDRAW);
	color(U_BLACK);
	clear_inst1();
	color(P_MARKINGS);
    }

    pushviewport();
    viewport(sl-instrument_data.fourwide, sr-instrument_data.fourwide,
	     sb-instrument_data.chartall, st-instrument_data.chartall);
    cmov(0.0,-4.0,0.0);
    charstr("MACH");
    popviewport();

    machtickstep = -300.0 * inst->machstep / (inst->maxmach - 1.0);

    machtinytickstep = machtickstep / inst->nummachticks;
    pushmatrix();
    rot(-30.0, 'z');
    for (mach=1.0; mach <= inst->maxmach; mach += inst->machstep)
    {
	bgnline();
	v3f(machticks[0]);
	v3f(machticks[1]);
	endline();
	rot(machtickstep, 'z');
    }
    popmatrix();
    pushmatrix();
    rot(-30.0, 'z');
    for (mach=1.0; mach < inst->maxmach; mach +=
				inst->machstep)
    {
	rot(machtinytickstep, 'z');
	for (x=1; x < inst->nummachticks; x++)
	{
	    bgnline();
	    v3f(machtinyticks[0]);
	    v3f(machtinyticks[1]);
	    endline();
	    rot(machtinytickstep, 'z');
	}
    }
    popmatrix();
    pushviewport();
    pushmatrix();
    rot(-30.0, 'z');
    viewport(sl-instrument_data.threewide, sr-instrument_data.threewide,
		   sb-instrument_data.chartall, st-instrument_data.chartall);
    for (mach=1.0; mach <= inst->maxmach; mach +=
				inst->machstep)
    {
	cmov(0.0, 6.5, 0.0);
	sprintf(buf,"%3.1f",mach);
	charstr(buf);
	rot(machtickstep, 'z');
    }
    popviewport();
    popmatrix();

    drawmode(NORMALDRAW);
    frontbuffer(TRUE);

    COLOR(C_BLACK);
    clear_inst1();

    draw_plate(inst->plateobject, 0x3);

    frontbuffer(FALSE);
    popmatrix();
}


update_mach_meter(mach_meter_t *inst, int forceupdate)
{
    static float machneedle[5][3] = {-.2,0.0,0.0, -.2,5.5,0.0, 0.0,7.0,0.0,
		    .2,5.5,0.0, .2,0.0,0.0};
    static float machneedlebox[5][3] = {-.7,-.8,0.0, -.7,7.5,0.0, .7,7.5,0.0,
		    .7,-.8,0.0 };
    int current;
    static float machone = 700.0;

    current = instrument_data.current;

    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);
    if ((airspeed != inst->last_speed[current]) || forceupdate)
    {
	COLOR(C_BLACK);
	pushmatrix();
	rot(inst->last_machrot[current], 'z');
	drawneedlebox(machneedlebox);
	popmatrix();
#ifndef NO_MS
	if (ms_samples)
	{
	    pushmatrix();
	    rot(inst->last_machrot[!current], 'z');
	    drawneedlebox(machneedlebox);
	    popmatrix();
	}
#endif

	inst->last_machrot[current] = -300 * (airspeed - 700.0)  /
				( inst->maxmach * machone ) - 30.0;
	if (inst->last_machrot[current] < -330.0)
	    inst->last_machrot[current] = -330.0;
	else if (inst->last_machrot[current] > -22.0)
	    inst->last_machrot[current] = -22.0;

	drawneedle(inst->last_machrot[current], instrument_data.darkneedle,
		   machneedle);
    }
    popmatrix();
}



void init_mach_meter(float px, float py, float pz, float size,
		     float maxmach, float machstep, int nummachticks)
{
    mach_meter_t *inst;

    inst = (mach_meter_t *)malloc(sizeof(*inst));
    bzero(inst, sizeof(*inst));
    inst->px = px;
    inst->py = py;
    inst->pz = pz;
    inst->size = size;
    inst->plateobject = plate1;
    inst->last_speed[1] = inst->last_speed[0] = airspeed + 1.0;
    inst->maxmach = maxmach;
    inst->machstep = machstep;
    inst->nummachticks =  nummachticks;

    append_inst_list(draw_mach_meter, update_mach_meter, inst);
}


/************************************************************************
***		Vertical Velocity indicator functions		      ***
************************************************************************/


typedef struct {
    float px, py, pz;		/* Position of instrument */
    float size;			/* Size of instrument */
    object_t *plateobject;
    float last_vel[2];		/* Previous speed of both buffers */
    float last_rot[2];
    float max_vertvel;
    float min_vertvel;
    float divisions;
    int numsmallticks;
} vertvel_meter_t;



/*
 * Draw the airspeed indicator
 */
draw_vertvel_meter(vertvel_meter_t *inst)
{
    static float verts[4][3] = { -9.0,-9.0,0.0, -9.0,9.0,0.0, 9.0,9.0,0.0,
			9.0,-9.0,0.0 };
    static float ticks[2][3]      = { 0.0,7.7,0.0, 0.0,9.0,0.0 };
    static float smallticks[2][3] = { 0.0,8.2,0.0, 0.0,9.0,0.0 };
    short sl, sr, sb, st;
    float bigtickstep, smalltickstep;
    float smalldivision;
    float vel;
    char buf[5];

    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);

    if (!in_cmode)
    {
	drawmode(UNDERDRAW);
	color(U_INST);
	clear_inst1();
	color(MARKINGS);
    }
    else
    {
	drawmode(PUPDRAW);
	color(U_BLACK);
	clear_inst1();
	color(P_MARKINGS);
    }

    bigtickstep = -150.0 * inst->divisions / inst->max_vertvel;
    smalltickstep = bigtickstep / (float) inst->numsmallticks;
    smalldivision = inst->divisions / (float) inst->numsmallticks;

    pushviewport();
    getviewport(&sl,&sr,&sb,&st);
    viewport(sl-instrument_data.fivewide, sr-instrument_data.fivewide,
	     sb-instrument_data.chartall, st-instrument_data.chartall);
    cmov(0.0,-2.5,0.0);
    charstr("CLIMB");
    popviewport();
    pushmatrix();
    rot(90.0,'z');
    pushmatrix();
    for (vel=0.0; vel <= inst->max_vertvel; vel += inst->divisions)
    {
	bgnline();
	v3f(ticks[0]);
	v3f(ticks[1]);
	endline();
	rot(bigtickstep,'z');
    }
    popmatrix();
    pushmatrix();
    for (vel=0.0; vel <= inst->max_vertvel; vel += inst->divisions)
    {
	bgnline();
	v3f(ticks[0]);
	v3f(ticks[1]);
	endline();
	rot(-bigtickstep,'z');
    }
    popmatrix();
    pushviewport();
    viewport(sl-instrument_data.fourwide, sr-instrument_data.fourwide,
	    sb-instrument_data.chartall, st-instrument_data.chartall);
    pushmatrix();
    for (vel=0.0; vel <= inst->max_vertvel; vel += inst->divisions)
    {
	cmov(0.0, 6.2, 0.0);
	sprintf(buf,"%d",(int)vel);
	charstr(buf);
	rot(bigtickstep,'z');
    }
    popmatrix();
    pushmatrix();
    for (vel=0.0; vel <= inst->max_vertvel; vel += inst->divisions)
    {
	cmov(0.0, 6.2, 0.0);
	sprintf(buf,"%d",(int)vel);
	charstr(buf);
	rot(-bigtickstep,'z');
    }
    popmatrix();
    popviewport();
    pushmatrix();
    for (vel=0.0; vel <= inst->max_vertvel; vel += smalldivision)
    {
	if (fmod(vel, inst->divisions))
	{
	    bgnline();
	    v3f(smallticks[0]);
	    v3f(smallticks[1]);
	    endline();
	}
	rot(-smalltickstep, 'z');
    }
    popmatrix();
    pushmatrix();
    for (vel=0.0; vel <= inst->max_vertvel; vel += smalldivision)
    {
	if (fmod(vel, inst->divisions))
	{
	    bgnline();
	    v3f(smallticks[0]);
	    v3f(smallticks[1]);
	    endline();
	}
	rot(smalltickstep, 'z');
    }
    popmatrix();
    popmatrix();
    drawmode(NORMALDRAW);
    frontbuffer(TRUE);

    COLOR(C_BLACK);
    clear_inst1();

    draw_plate(inst->plateobject, 0x3);

    frontbuffer(FALSE);
    popmatrix();
}



update_vertvel_meter(vertvel_meter_t *inst, int forceupdate)
{
    static float needle[5][3] = {-.2,0.0,0.0, -.2,5.0,0.0, 0.0,6.5,0.0,
		    .2,5.0,0.0, .2,0.0,0.0};
    static float needlebox[4][3] = {-.8,-.8,0.0, -.8,6.9,0.0, .8,6.9,0.0,
		    .8,-.8,0.0 };
    int current;
    float vertvelocity;

    current = instrument_data.current;

    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);

    vertvelocity = climbspeed * 60;

    if ((vertvelocity != inst->last_vel[current]) || forceupdate)
    {
	COLOR(C_BLACK);
	pushmatrix();
	rot(inst->last_rot[current], 'z');
	drawneedlebox(needlebox);
	popmatrix();
#ifndef NO_MS
	if (ms_samples)
	{
	    pushmatrix();
	    rot(inst->last_rot[!current], 'z');
	    drawneedlebox(needlebox);
	    popmatrix();
	}
#endif

	if (vertvelocity > inst->max_vertvel)
	    inst->last_rot[current] = -60.0;
	else if (vertvelocity < inst->min_vertvel)
	    inst->last_rot[current] = 240.0;
	else
	    inst->last_rot[current] = 90.0 + -150.0 * vertvelocity /
				      inst->max_vertvel;
	drawneedle(inst->last_rot[current], instrument_data.darkneedle,
		   needle);
    }
    popmatrix();
}



void init_vertvel_meter(float px, float py, float pz, float size,
			float maxvel, float divisions, int numsmallticks)
{
    vertvel_meter_t *inst;

    inst = (vertvel_meter_t *)malloc(sizeof(*inst));
    bzero(inst, sizeof(*inst));
    inst->px = px;
    inst->py = py;
    inst->pz = pz;
    inst->size = size;
    inst->plateobject = plate1;
    inst->max_vertvel = maxvel;
    inst->min_vertvel = -1.0*maxvel;
    inst->divisions = divisions;
    inst->numsmallticks = numsmallticks;
    inst->last_vel[1] = inst->last_vel[0] = 1.0;
    append_inst_list(draw_vertvel_meter, update_vertvel_meter, inst);
}


/************************************************************************
***			radar/compass functions			      ***
************************************************************************/


typedef struct {
    float px, py, pz;		/* Position of instrument */
    float size;			/* Size of instrument */
    short sm_l, sm_r, sm_b, sm_t;
    object_t *plateobject;
    float ticks[72][2];
} radar_t;



/*
 * Draw the radar
 */
draw_radar(radar_t *inst)
{
    static float plane[13][3] =  {{ 0.0,  0.0}, { 0.2, -1.0}, { 1.2, -1.8},
				  { 1.2, -2.0}, { 0.2, -1.4}, { 0.2, -2.0},
				  { 0.5, -2.3}, {-0.5, -2.3}, {-0.2, -2.0},
				  {-0.2, -1.4}, {-1.2, -2.0}, {-1.2, -1.8},
				  {-0.2, -1.0}};
    long ox, oy;

    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);

    /*
     *  get instoment screen mask
     */
    cmov2i(-9.0, -9.0);
    getcpos(&inst->sm_l, &inst->sm_b);
    cmov2i(9.0, 9.0);
    getcpos(&inst->sm_r, &inst->sm_t);
    getorigin(&ox, &oy);
    inst->sm_l -= ox;
    inst->sm_r -= ox;
    inst->sm_b -= oy;
    inst->sm_t -= oy;

    drawmode(PUPDRAW);

    pushmatrix();
    scale(0.9, 0.9, 0.9);

    color(P_ORANGE);
    if (!dogfight)
    {
	bgnclosedline();
	v2f(plane[0]);
	v2f(plane[1]);
	v2f(plane[2]);
	v2f(plane[3]);
	v2f(plane[4]);
	v2f(plane[5]);
	v2f(plane[6]);
	v2f(plane[7]);
	v2f(plane[8]);
	v2f(plane[9]);
	v2f(plane[10]);
	v2f(plane[11]);
	v2f(plane[12]);
	endclosedline();
    }
    else
	rectf(-0.1, -0.1, 0.1, 0.1);

    popmatrix();

    drawmode(NORMALDRAW);

    frontbuffer(TRUE);

    COLOR(C_BLACK);
    clear_inst1();

    draw_plate(inst->plateobject, 0x3);

    frontbuffer(FALSE);
    popmatrix();
}


update_radar(radar_t *inst, int forceupdate)
{
    static float verts[4][2] = {{-9.0, -9.0}, {-9.0,  9.0},
				{ 9.0,  9.0}, { 9.0, -9.0}};
    static float n[][2] = {{-0.7,  6.0},	/* N */
			   {-0.7,  8.0},
			   { 0.7,  6.0},
			   { 0.7,  8.0}};
    static float e[][2] = {{ 6.0, -0.7},	/* E */
			   { 6.0,  0.7},
			   { 8.0,  0.7},
			   { 8.0, -0.7},
			   { 7.0,  0.7},
			   { 7.0, -0.3}};
    static float w[][2] = {{-8.0, -0.9},	/* W */
			   {-6.0, -0.4},
			   {-7.0,  0.0},
			   {-6.0,  0.4},
			   {-8.0,  0.9}};
    static float s[][2] = {{-0.7, -7.8},	/* S */
			   {-0.5, -8.0},
			   { 0.7, -8.0},
			   { 0.7, -7.0},
			   {-0.7, -7.0},
			   {-0.7, -6.0},
			   { 0.5, -6.0},
			   { 0.7, -6.2}};
    int i;

    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);

    lsetdepth(zmaxscreen, zmaxscreen);
    scrmask(inst->sm_l, inst->sm_r, inst->sm_b, inst->sm_t);
    if (!in_cmode)
	zbuffer(TRUE);

    COLOR(C_BLACK);
    clear_inst1();

    rotate(-azimuth, 'z');

    scale(0.9, 0.9, 0.9);

    COLOR(C_WHITE);
    for (i=0; i < 72; i += 2)
    {
	bgnline(); v2f(inst->ticks[i]); v2f(inst->ticks[i+1]); endline();
    }

    bgnline();
    v2f(n[0]);
    v2f(n[1]);
    v2f(n[2]);
    v2f(n[3]);
    endline();

    bgnline();
    v2f(e[0]);
    v2f(e[1]);
    v2f(e[2]);
    v2f(e[3]);
    endline();
    bgnline();
    v2f(e[4]);
    v2f(e[5]);
    endline();

    bgnline();
    v2f(w[0]);
    v2f(w[1]);
    v2f(w[2]);
    v2f(w[3]);
    v2f(w[4]);
    endline();

    bgnline();
    v2f(s[0]);
    v2f(s[1]);
    v2f(s[2]);
    v2f(s[3]);
    v2f(s[4]);
    v2f(s[5]);
    v2f(s[6]);
    v2f(s[7]);
    endline();

    scale(0.0004, -0.0004, 0.0004);   /* scale down (y=-z)    */
    draw_radar_objects();

    if (!in_cmode)
	zbuffer(FALSE);
    else
	if (plate_ci_mode == NORMALDRAW)
	    drawobj(inst->plateobject, 0x3);
    scrmask(0, xmaxwindow, 0, ymaxwindow);
    lsetdepth(zminscreen, zmaxscreen);

    popmatrix();
}



void init_radar(float px, float py, float pz, float size)
{
    radar_t *inst;
    int i, j;
    float r, sin, cos;

    inst = (radar_t *)malloc(sizeof(*inst));
    bzero(inst, sizeof(*inst));
    inst->px = px;
    inst->py = py;
    inst->pz = pz;
    inst->size = size;
    inst->plateobject = plate1;

    for (i=0, j=0; i < 3600; i += 100, j += 2)
    {
	gl_sincos(i, &sin, &cos);
	if (!(i%300) && (i%900))
	    r = 7.5;       /* long line    */
	else
	    r = 9.0;       /* short line   */
	inst->ticks[j][0] = 10.0 * sin;
	inst->ticks[j][1] = 10.0 * cos;
	inst->ticks[j+1][0] = r * sin;
	inst->ticks[j+1][1] = r * cos;
    }

    append_inst_list(draw_radar, update_radar, inst);
}


/************************************************************************
***			Gyro compass functions			      ***
************************************************************************/


typedef struct {
    float px, py, pz;		/* Position of instrument */
    float size;			/* Size of instrument */
    float last_head[2];		/* Previous heading of both buffers */
    float last_rot[2];
    object_t *plateobject;
    float ticks[36][6];
    float letters[27][3];
} compass_t;



/*
 * Draw the gyro compass
 */
draw_compass(compass_t *inst)
{
    static float verts[4][3] = { -9.0,-9.0,0.0, -9.0,9.0,0.0, 9.0,9.0,0.0,
			9.0,-9.0,0.0 };
    static float plane[13][3] =  { 0.0,0.0,0.6, .2,-1.0,0.6, 1.2,-1.8,0.6,
			1.2,-2.0,0.6, .2,-1.4,0.6, .2,-2.0,0.6, .5,-2.3, 0.6,
			-.5,-2.3,0.6, -.2,-2.0,0.6, -.2,-1.4,0.6, -1.2,-2.0,0.6,
			-1.2,-1.8,0.6, -.2,-1.0,0.6 };
    static float headmarks[8][3] = { -.2,-8.4,0.6, .2,-8.4,0.6, .2,-7.3,0.6,
			-.2,-7.3,0.6, -.2,8.4,0.6, .2,8.4,0.6, .2,7.3,0.6,
			-.2,7.3,0.6 };
    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);
    drawmode(UNDERDRAW);
    color(U_INST);
    clear_inst1();

    drawmode(PUPDRAW);
    color(P_MARKINGS);
    bgnclosedline();
    v3f(plane[0]);
    v3f(plane[1]);
    v3f(plane[2]);
    v3f(plane[3]);
    v3f(plane[4]);
    v3f(plane[5]);
    v3f(plane[6]);
    v3f(plane[7]);
    v3f(plane[8]);
    v3f(plane[9]);
    v3f(plane[10]);
    v3f(plane[11]);
    v3f(plane[12]);
    endclosedline();

    bgnpolygon();
    v3f(headmarks[0]);
    v3f(headmarks[1]);
    v3f(headmarks[2]);
    v3f(headmarks[3]);
    endpolygon();
    bgnpolygon();
    v3f(headmarks[4]);
    v3f(headmarks[5]);
    v3f(headmarks[6]);
    v3f(headmarks[7]);
    endpolygon();

    drawmode(NORMALDRAW);
    frontbuffer(TRUE);

    COLOR(C_BLACK);
    clear_inst1();

    draw_plate(inst->plateobject, 0x3);

    frontbuffer(FALSE);
    popmatrix();
}


update_compass(compass_t *inst, int forceupdate)
{
    static float verts[4][3] = { -9.0,-9.0,0.0, -9.0,9.0,0.0, 9.0,9.0,0.0,
			9.0,-9.0,0.0 };
    int current;
    int x;
    current = instrument_data.current;
    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);
    COLOR(C_BLACK);
    if (!in_cmode)
    {
	zbuffer(TRUE);
	clear_inst1();
	zbuffer(FALSE);
    }
    else
	clear_inst1();
    rot((float)azimuth, 'z');
    ICOLOR(instrument_data.text);
    for (x=0; x < 36; x++)
    {
	bgnline();
	v3f(inst->ticks[x]);
	v3f(inst->ticks[x]+3);
	endline();
    }
    bgnline();
    v3f(inst->letters[0]);
    v3f(inst->letters[1]);
    v3f(inst->letters[2]);
    v3f(inst->letters[3]);
    endline();
    bgnline();
    v3f(inst->letters[4]);
    v3f(inst->letters[5]);
    v3f(inst->letters[6]);
    v3f(inst->letters[7]);
    v3f(inst->letters[8]);
    endline();
    bgnline();
    v3f(inst->letters[9]);
    v3f(inst->letters[10]);
    v3f(inst->letters[11]);
    v3f(inst->letters[12]);
    endline();
    bgnline();
    v3f(inst->letters[13]);
    v3f(inst->letters[14]);
    endline();
    bgnline();
    v3f(inst->letters[15]);
    v3f(inst->letters[16]);
    v3f(inst->letters[17]);
    v3f(inst->letters[18]);
    v3f(inst->letters[19]);
    v3f(inst->letters[20]);
    v3f(inst->letters[21]);
    v3f(inst->letters[22]);
    v3f(inst->letters[23]);
    v3f(inst->letters[24]);
    v3f(inst->letters[25]);
    v3f(inst->letters[26]);
    endline();
    if (!in_cmode) ;
    popmatrix();
}



void init_compass(float px, float py, float pz, float size)
{
    compass_t *inst;
    int theta;
    float s,c;
    float outer_rad = 8.3;
    float big_inner_rad = 7.3;
    float small_inner_rad = 7.8;
    int i;

    inst = (compass_t *)malloc(sizeof(*inst));
    bzero(inst, sizeof(*inst));
    inst->px = px;
    inst->py = py;
    inst->pz = pz;
    inst->size = size;
    inst->plateobject = plate1;

    for (theta=i=0; theta < 360; theta += 10)
    {
	gl_sincos(theta*10, &s, &c);
	inst->ticks[i][0] = c * outer_rad;
	inst->ticks[i][1] = s * outer_rad;
	inst->ticks[i][2] = 0.0;
	if (theta % 30)
	{
	    inst->ticks[i][3] = c * small_inner_rad;
	    inst->ticks[i][4] = s * small_inner_rad;
	    inst->ticks[i][5] = 0.0;
	}
	else
	{
	    inst->ticks[i][3] = c * big_inner_rad;
	    inst->ticks[i][4] = s * big_inner_rad;
	    inst->ticks[i][5] = 0.0;
	}
	i++;
    }
    inst->letters[0][0]  = -0.5;
    inst->letters[0][1]  =  5.0;
    inst->letters[1][0]  = -0.5;
    inst->letters[1][1]  =  7.0;
    inst->letters[2][0]  =  0.5;
    inst->letters[2][1]  =  5.0;
    inst->letters[3][0]  =  0.5;
    inst->letters[3][1]  =  7.0;
    inst->letters[4][0]  = -7.0;
    inst->letters[4][1]  = -0.6;
    inst->letters[5][0]  = -5.0;
    inst->letters[5][1]  = -0.3;
    inst->letters[6][0]  = -6.0;
    inst->letters[6][1]  =  0.0;
    inst->letters[7][0]  = -5.0;
    inst->letters[7][1]  =  0.3;
    inst->letters[8][0]  = -7.0;
    inst->letters[8][1]  =  0.6;
    inst->letters[9][0]  =  7.0;
    inst->letters[9][1]  = -0.5;
    inst->letters[10][0] =  7.0;
    inst->letters[10][1] =  0.5;
    inst->letters[11][0] =  5.0;
    inst->letters[11][1] =  0.5;
    inst->letters[12][0] =  5.0;
    inst->letters[12][1] = -0.5;
    inst->letters[13][0] =  6.0;
    inst->letters[13][1] = -0.2;
    inst->letters[14][0] =  6.0;
    inst->letters[14][1] =  0.5;
    inst->letters[15][0] =  0.5;
    inst->letters[15][1] = -5.2;
    inst->letters[16][0] =  0.3;
    inst->letters[16][1] = -5.0;
    inst->letters[17][0] = -0.3;
    inst->letters[17][1] = -5.0;
    inst->letters[18][0] = -0.5;
    inst->letters[18][1] = -5.2;
    inst->letters[19][0] = -0.5;
    inst->letters[19][1] = -5.8;
    inst->letters[20][0] = -0.3;
    inst->letters[20][1] = -6.0;
    inst->letters[21][0] =  0.3;
    inst->letters[21][1] = -6.0;
    inst->letters[22][0] =  0.5;
    inst->letters[22][1] = -6.2;
    inst->letters[23][0] =  0.5;
    inst->letters[23][1] = -6.8;
    inst->letters[24][0] =  0.3;
    inst->letters[24][1] = -7.0;
    inst->letters[25][0] = -0.3;
    inst->letters[25][1] = -7.0;
    inst->letters[26][0] = -0.5;
    inst->letters[26][1] = -6.8;

    for (i=0; i <=26; i++)
	inst->letters[i][2] = 0.0;

    append_inst_list(draw_compass, update_compass, inst);
}


/************************************************************************
***			Thrust & Throttle functions		      ***
************************************************************************/


typedef struct {
    float px, py, pz;		/* Position of instrument */
    float size;			/* Size of instrument */
    int last_thrust[2];		/* Previous thrust of both buffers */
    int   last_sign[2];		/* Previous sign of thrust of both buffers */
    int last_throttle[2];	/* Previous throttle of both buffers */
    float last_thrustrot[2];
    float last_throttlerot[2];
    float tickstep;
    int numticks;
    object_t *plateobject;
} thrustthrottle_t;



/*
 * Draw the thrust & throttle instrument
 */
draw_thrustthrottle(thrustthrottle_t *inst)
{
    static float verts[4][3] = { -9.0,-9.0,0.0, -9.0,9.0,0.0, 9.0,9.0,0.0,
			9.0,-9.0,0.0 };
    static float ticks[2][3] = { 0.0,5.5,0.0, 0.0,4.5,0.0 };
    static float smallticks[2][3] = { 0.0,5.5,0.0, 0.0,5.0,0.0 };
    static float revbox[4][3] = {{-7.5, -0.4, 0.0}, {-4.5, -0.4, 0.0},
				 {-4.5, -2.4, 0.0}, {-7.5, -2.4, 0.0}};
    short sl, sr, sb, st;
    int shift;
    char buf[8];
    int x;
    int thstep, tickstep, thcount;
    float angstep, tickangstep;

    getviewport(&sl,&sr,&sb,&st);
    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);
    if (!in_cmode)
    {
	drawmode(UNDERDRAW);
	color(U_INST);
	clear_inst1();
	color(MARKINGS);
    }
    else
    {
	drawmode(PUPDRAW);
	color(U_BLACK);
	clear_inst1();
	color(P_MARKINGS);
    }

    for (x=0; x<2; x++)
    {
	pushmatrix();
	translate(0.0,-7.5,0.0);
	thstep = inst->tickstep;
	tickstep = thstep / inst->numticks;
	angstep = -110.0 * inst->tickstep / 100.0;
	tickangstep = angstep / (float) inst->numticks;
	pushmatrix();
	rot(55.0, 'z');
	for (thcount=0; thcount <= 100; thcount += tickstep)
	{
	    if (thcount % thstep)
	    {
		bgnline();
		v3f(smallticks[0]);
		v3f(smallticks[1]);
		endline();
	    }
	    else
	    {
		bgnline();
		v3f(ticks[0]);
		v3f(ticks[1]);
		endline();
	    }
	    rot(tickangstep, 'z');
	}
	popmatrix();
	pushviewport();
	viewport(sl-instrument_data.twowide, sr-instrument_data.twowide,
		sb-instrument_data.chartall, st-instrument_data.chartall);
	pushmatrix();
	rot(55.0, 'z');
	for (thcount=0; thcount <= 100; thcount += thstep)
	{
	    sprintf(buf,"%d",thcount);
	    cmov(0.0, 6.5, 0.0);
	    charstr(buf);
	    rot(angstep, 'z');
	}
	popviewport();
	popmatrix();
	popmatrix();
	scale(1.0,-1.0,1.0);
    }
    pushviewport();
    sprintf(buf,"%%");
    shift = strwidth(buf)/2 - 1;
    viewport(sl-shift, sr-shift, sb-instrument_data.chartall,
					st-instrument_data.chartall);
    cmov(0.0,-5.9,0.0);
    charstr(buf);
    cmov(0.0,4.7,0.0);
    charstr(buf);
    popviewport();
    pushviewport();
    viewport(sl-instrument_data.eightwide, sr-instrument_data.eightwide,
	     sb-instrument_data.chartall, st-instrument_data.chartall);
    cmov(0.0,5.9,0.0);
    charstr("THROTTLE");
    popviewport();
    pushviewport();
    viewport(sl-instrument_data.sixwide, sr-instrument_data.sixwide,
	     sb-instrument_data.chartall, st-instrument_data.chartall);
    cmov(0.0,-4.7,0.0);
    charstr("THRUST");
    popviewport();

    /*
     *  clear underlays form warning light area
     */
    color(U_BLACK);
    drawneedlebox(revbox);

    drawmode(NORMALDRAW);
    frontbuffer(TRUE);

    COLOR(C_BLACK);
    clear_inst1();

    draw_plate(inst->plateobject, 0x3);

    frontbuffer(FALSE);
    popmatrix();
}



update_thrustthrottle(thrustthrottle_t *inst, int forceupdate)
{
    static float throtneedle[5][3] = {{-0.2,  0.0, 0.0}, {-0.2, -3.1, 0.0},
				      { 0.0, -4.1, 0.0}, { 0.2, -3.1, 0.0},
				      { 0.2,  0.0, 0.0}};
    static float throtneedlebox[4][3] = {{-0.6, 0.35, 0.0}, {-0.6,-4.5,  0.0},
					  {0.6,-4.5,  0.0}, { 0.6, 0.35, 0.0}};
    static float thrustneedle[5][3] = {{-0.2, 0.0, 0.0}, {-0.2, 3.1, 0.0},
				       { 0.0, 4.1, 0.0}, { 0.2, 3.1, 0.0},
				       { 0.2, 0.0, 0.0}};
    static float thrustneedlebox[4][3] = {{-0.6,-0.35, 0.0}, {-0.6, 4.5, 0.0},
					  { 0.6, 4.5,  0.0}, { 0.6,-0.35,0.0}};
    static float revbox[4][3] = {{-7.5, -0.4, 0.0}, {-4.5, -0.4, 0.0},
				 {-4.5, -2.4, 0.0}, {-7.5, -2.4, 0.0}};
    int current;
    int sign = 1;

    current = instrument_data.current;

    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);

    if ((thrust != inst->last_thrust[current]) || forceupdate)
    {
	pushmatrix();
	translate(0.0,-7.5,0.0);
	COLOR(C_BLACK);
	pushmatrix();
	rot(inst->last_thrustrot[current], 'z');
	drawneedlebox(thrustneedlebox);
	popmatrix();
#ifndef NO_MS
	if (ms_samples)
	{
	    pushmatrix();
	    rot(inst->last_thrustrot[!current], 'z');
	    drawneedlebox(thrustneedlebox);
	    popmatrix();
	}
#endif

	if (_ABS(thrust) > 100)
	    inst->last_thrustrot[current] = -55.0;
	else
	    inst->last_thrustrot[current] =
					55.0 - fabs((110.0 * thrust) / 100.0);
	drawneedle(inst->last_thrustrot[current],
		   instrument_data.darkneedle, thrustneedle);
	popmatrix();
	inst->last_thrust[current] = thrust;
    }

    if ((throttle != inst->last_throttle[current]) || forceupdate)
    {
	if (throttle < 0) sign = -1;
	if (sign != inst->last_sign[current])
	{
	    inst->last_sign[current] = sign;
	    if (sign == 1)
	    {
		COLOR(C_DRED);
		drawneedlebox(revbox);
		ICOLOR(instrument_data.textborder);
		bgnclosedline();
		v3f(revbox[0]);
		v3f(revbox[1]);
		v3f(revbox[2]);
		v3f(revbox[3]);
		endclosedline();
		ICOLOR(instrument_data.backlittext);
		cmov(-7.2,-1.8,0.0);
		charstr("REV");
	    }
	    else
	    {
		COLOR(C_RED);
		drawneedlebox(revbox);
		ICOLOR(instrument_data.textborder);
		bgnclosedline();
		v3f(revbox[0]);
		v3f(revbox[1]);
		v3f(revbox[2]);
		v3f(revbox[3]);
		endclosedline();
		ICOLOR(instrument_data.backlittext);
		cmov(-7.2,-1.8,0.0);
		charstr("REV");
	    }
	}

	pushmatrix();
	translate(0.0,7.5,0.0);
	COLOR(C_BLACK);
	pushmatrix();
	rot(inst->last_throttlerot[current], 'z');
	drawneedlebox(throtneedlebox);
	popmatrix();
#ifndef NO_MS
	if (ms_samples)
	{
	    pushmatrix();
	    rot(inst->last_throttlerot[!current], 'z');
	    drawneedlebox(throtneedlebox);
	    popmatrix();
	}
#endif

	if (_ABS(throttle) > 100)
	    inst->last_throttlerot[current] = 55.0;
	else
	    inst->last_throttlerot[current] = fabs((110.0 * throttle) /
						   -100.0) - 55.0;
	drawneedle(inst->last_throttlerot[current],
		   instrument_data.darkneedle, throtneedle);
	popmatrix();
	inst->last_throttle[current] = throttle;
    }
    popmatrix();
}



void init_thrustthrottle(float px, float py, float pz, float size,
			 float tickstep, int numticks)
{
    thrustthrottle_t *inst;

    inst = (thrustthrottle_t *)malloc(sizeof(*inst));
    bzero(inst, sizeof(*inst));
    inst->px = px;
    inst->py = py;
    inst->pz = pz;
    inst->size = size;
    inst->plateobject = plate1;
    inst->numticks = numticks;
    inst->tickstep = tickstep;
    inst->last_thrust[0]= inst->last_thrust[1]= thrust + 1.0;
    inst->last_throttle[0]= inst->last_throttle[1]=
				throttle + 1.0;
    append_inst_list(draw_thrustthrottle, update_thrustthrottle, inst);
}



/************************************************************************
***				Fuel functions			      ***
************************************************************************/


typedef struct {
    float px, py, pz;		/* Position of instrument */
    float size;			/* Size of instrument */
    object_t *plateobject;
    float last_fuel[2];		/* Previous fuel of both buffers */
    float last_fuelrot[2];
    float maxfuel;
    float tickstep;
    int numticks;
    int scale;
} fuelgauge_t;



/*
 * Draw the fuel & consumption instrument
 */
draw_fuelgauge(fuelgauge_t *inst)
{
    static float verts[4][3] = {{-9.0, -9.0, 0.0}, {-9.0,  9.0, 0.0},
				{ 9.0,  9.0, 0.0}, { 9.0, -9.0, 0.0}};
    static float ticks[2][3] = {{0.0, 5.5, 0.0}, {0.0, 4.5, 0.0}};
    static float smallticks[2][3] = {{0.0, 5.5, 0.0}, {0.0, 5.0, 0.0}};
    short sl, sr, sb, st;
    int shift;
    char buf[8];
    int x;
    int mfuel, flstep, tickstep, flcount;
    float angstep, tickangstep;

    getviewport(&sl,&sr,&sb,&st);
    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);

    if (!in_cmode)
    {
	drawmode(UNDERDRAW);

	color(U_INST);
	clear_inst1();
	color(MARKINGS);
    }
    else
    {
	drawmode(PUPDRAW);

	color(U_BLACK);
	clear_inst1();
	color(P_MARKINGS);
    }

    mfuel = inst->maxfuel;/* / inst->scale;*/
    flstep = inst->tickstep;/* / inst->scale;*/
    tickstep = flstep / inst->numticks;
    angstep = -180.0 * inst->tickstep / inst->maxfuel;
    tickangstep = angstep / (float) inst->numticks;
    pushmatrix();
    rot(90.0, 'z');
    for (flcount=0; flcount <= mfuel; flcount += tickstep)
    {
	if (flcount % flstep)
	{
	    bgnline();
	    v3f(smallticks[0]);
	    v3f(smallticks[1]);
	    endline();
	}
	else
	{
	    bgnline();
	    v3f(ticks[0]);
	    v3f(ticks[1]);
	    endline();
	}
	rot(tickangstep, 'z');
    }
    popmatrix();

    pushviewport();

    sprintf(buf, "%d", (mfuel >> 1) / inst->scale);
    shift = (strwidth(buf) >> 1) - 1;
    viewport(sl-shift, sr-shift,
	     sb-instrument_data.chartall, st-instrument_data.chartall);
    pushmatrix();
    rot(90.0, 'z');
    for (flcount=0; flcount <= mfuel; flcount += flstep)
    {
	sprintf(buf, "%d", flcount / inst->scale);
	cmov(0.0, 6.5, 0.0);
	charstr(buf);
	rot(angstep, 'z');
    }
    popviewport();
    popmatrix();

    pushviewport();
    sprintf(buf,"x%d", inst->scale);
    shift = (strwidth(buf) >> 1) - 1;
    viewport(sl-shift, sr-shift,
	     sb-instrument_data.chartall, st-instrument_data.chartall);
    cmov(0.0,-5.9,0.0);
    charstr(buf);
    popviewport();

    pushviewport();
    shift = (strwidth("FUEL LBS") >> 1) - 1;
    viewport(sl-shift, sr-shift,
	     sb-instrument_data.chartall, st-instrument_data.chartall);
    cmov(0.0,-4.0,0.0);
    charstr("FUEL LBS");
    popviewport();

    drawmode(NORMALDRAW);
    frontbuffer(TRUE);

    COLOR(C_BLACK);
    clear_inst1();

    draw_plate(inst->plateobject, 0x3);

    frontbuffer(FALSE);
    popmatrix();
}


update_fuelgauge(fuelgauge_t *inst, int forceupdate)
{
    static float needle[5][3]    = { -.2,0.0,0.0, -.2,3.1,0.0, 0.0,4.1,0.0,
				.2,3.1,0.0, .2,0.0,0.0 };
    static float needlebox[4][3] = { -.6,-0.35,0.0, -.6,4.5,0.0, .6,4.5,0.0,
				.6,-0.35,0.0 };
    static float low_light[4][2] = {{-1.5, -1.0}, {-1.5, -3.0},
				    { 1.5, -3.0}, { 1.5, -1.0}};
    int current;

    current = instrument_data.current;

    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);

    if ((fuel != inst->last_fuel[current]) || forceupdate)
    {
	COLOR(C_BLACK);
	pushmatrix();
	rot(inst->last_fuelrot[current], 'z');
	drawneedlebox(needlebox);
	popmatrix();
#ifndef NO_MS
	if (ms_samples)
	{
	    pushmatrix();
	    rot(inst->last_fuelrot[!current], 'z');
	    drawneedlebox(needlebox);
	    popmatrix();
	}
#endif

	if (fuel < 00)
	    inst->last_fuelrot[current] = 90.0;
	else
	    inst->last_fuelrot[current] = -180.0 * fuel / (100 << 7) + 90.0;
	drawneedle(inst->last_fuelrot[current], instrument_data.darkneedle,
		   needle);

	if (fuel < (10<<7))	/* 10% or less fuel left */
	    COLOR(C_RED);
	else
	    COLOR(C_DRED);
	bgnpolygon();
	v2f(low_light[0]); v2f(low_light[1]);
	v2f(low_light[2]); v2f(low_light[3]);
	endpolygon();
	ICOLOR(instrument_data.textborder);
	bgnclosedline();
	v2f(low_light[0]); v2f(low_light[1]);
	v2f(low_light[2]); v2f(low_light[3]);
	endclosedline();

    }

    popmatrix();
}


static fuelgauge_t *fg;

void init_fuelgauge(float px, float py, float pz, float size,
		    float maxfuel, float tickstep, int numticks, int scale)
{
    fuelgauge_t *inst;

    inst = (fuelgauge_t *)malloc(sizeof(*inst));
    bzero(inst, sizeof(*inst));
    inst->px = px;
    inst->py = py;
    inst->pz = pz;
    inst->size = size;
    inst->plateobject = plate1;
    inst->maxfuel = maxfuel;
    inst->numticks = numticks;
    inst->tickstep = tickstep;
    inst->scale = scale;
    inst->last_fuel[0]= inst->last_fuel[1]= fuel + 1.0;
    fg = inst;

    append_inst_list(draw_fuelgauge, update_fuelgauge, inst);
}


void set_fuelgauge(float maxfuel, float tickstep, int numticks, int scale)
{
    fg->maxfuel = maxfuel;
    fg->tickstep = tickstep;
    fg->numticks = numticks;
    fg->scale = scale;
}



/************************************************************************
***			Flaps & Spoilers functions		      ***
************************************************************************/


typedef struct {
    float px, py, pz;		/* Position of instrument */
    float size;			/* Size of instrument */
    object_t *plateobject;
    float last_flap[2];		/* Previous flap of both buffers */
    float last_spoiler[2];	/* Previous spoiler of both buffers */
    float last_flaprot[2];
    float last_spoilerrot[2];
    int maxflap;
    int flaptickstep;
    int numflapticks;
    int maxspoiler;
    int spoilertickstep;
    int numspoilerticks;
} flapspoiler_t;



/*
 * Draw the flaps & spoilers instrument
 */
draw_flapspoiler(flapspoiler_t *inst)
{
    static float verts[4][3] = { -9.0,-9.0,0.0, -9.0,9.0,0.0, 9.0,9.0,0.0,
			9.0,-9.0,0.0 };
    static float ticks[2][3] = { 0.0,5.3,0.0, 0.0,4.3,0.0 };
    static float smallticks[2][3] = { 0.0,5.3,0.0, 0.0,4.7,0.0 };
    short sl, sr, sb, st;
    int shift;
    char buf[8];
    int x;
    int flcount, smalltickstep;
    float angstep, tickangstep;
    getviewport(&sl,&sr,&sb,&st);

    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);

    if (!in_cmode)
    {
	drawmode(UNDERDRAW);

	color(U_INST);
	clear_inst1();

	color(MARKINGS);
    }
    else
    {
	drawmode(PUPDRAW);

	color(U_BLACK);
	clear_inst1();

	color(P_MARKINGS);
    }

    if (inst->maxflap)
    {
	pushviewport();
	viewport(sl-instrument_data.fourwide, sr-instrument_data.fourwide,
		 sb-instrument_data.chartall, st-instrument_data.chartall);
	cmov(0.0,-5.5,0.0);
	charstr("FLAP");
	popviewport();

	pushmatrix();
	translate(0.0,-7.5,0.0);
	pushmatrix();

	smalltickstep = inst->flaptickstep / inst->numflapticks;
	angstep= -110.0 * (float)inst->flaptickstep /
		 (float)inst->maxflap;
	tickangstep = angstep / (float) inst->numflapticks;
	rot(55.0, 'z');
	for (flcount=0; flcount <= inst->maxflap;
	     flcount += smalltickstep)
	{
	    if (flcount % inst->flaptickstep)
	    {
		bgnline();
		v3f(smallticks[0]);
		v3f(smallticks[1]);
		endline();
	    }
	    else
	    {
		bgnline();
		v3f(ticks[0]);
		v3f(ticks[1]);
		endline();
	    }
	    rot(tickangstep, 'z');
	}
	popmatrix();

	pushviewport();
	viewport(sl-instrument_data.twowide, sr-instrument_data.twowide,
		 sb-instrument_data.chartall, st-instrument_data.chartall);
	translate(0.0,0.5,0.0);
	rot(55.0, 'z');
	for (flcount=0; flcount <= inst->maxflap;
	     flcount += inst->flaptickstep)
	{
	    sprintf(buf,"%d",flcount);
	    if (flcount==0)
	    {
		pushviewport();
		viewport(sl-instrument_data.charwide,
			 sr-instrument_data.charwide,
			 sb-instrument_data.chartall,
			 st-instrument_data.chartall);
	    }
	    cmov(0.0, 7.0, 0.0);
	    charstr(buf);
	    rot(angstep, 'z');
	    if (flcount==0)
		popviewport();
	}
	popviewport();
	popmatrix();
    }

    if (inst->maxspoiler)
    {
	pushviewport();
	viewport(sl-instrument_data.fivewide, sr-instrument_data.fivewide,
		 sb-instrument_data.chartall, st-instrument_data.chartall);
	cmov(0.0,5.5,0.0);
	charstr("SPOIL");
	popviewport();

	pushmatrix();
	translate(0.0,7.5,0.0);

	smalltickstep = inst->spoilertickstep /
			inst->numspoilerticks;
	angstep= 110.0 * (float)inst->spoilertickstep /
		 (float)inst->maxspoiler;
	tickangstep = angstep / (float) inst->numspoilerticks;
	pushmatrix();
	rot(125.0, 'z');
	for (flcount=0; flcount <= inst->maxspoiler;
	     flcount += smalltickstep)
	{
	    if (flcount % inst->spoilertickstep)
	    {
		bgnline();
		v3f(smallticks[0]);
		v3f(smallticks[1]);
		endline();
	    }
	    else
	    {
		bgnline();
		v3f(ticks[0]);
		v3f(ticks[1]);
		endline();
	    }
	    rot(tickangstep, 'z');
	}
	popmatrix();
	pushviewport();
	viewport(sl-instrument_data.twowide, sr-instrument_data.twowide,
		 sb-instrument_data.chartall, st-instrument_data.chartall);
	translate(0.0,-0.5,0.0);
	rot(125.0, 'z');
	for (flcount=0; flcount <= inst->maxspoiler;
	     flcount += inst->spoilertickstep)
	{
	    if (flcount==0)
	    {
		pushviewport();
		viewport(sl-instrument_data.charwide,
			 sr-instrument_data.charwide,
			 sb-instrument_data.chartall,
			 st-instrument_data.chartall);
	    }
	    sprintf(buf,"%d",flcount);
	    cmov(0.0, 7.0, 0.0);
	    charstr(buf);
	    rot(angstep, 'z');
	    if (flcount==0)
		popviewport();
	}
	popviewport();
	popmatrix();
    }

    drawmode(NORMALDRAW);
    frontbuffer(TRUE);

    COLOR(C_BLACK);
    clear_inst1();

    draw_plate(inst->plateobject, 0x3);

    frontbuffer(FALSE);
    popmatrix();
}


update_flapspoiler(flapspoiler_t *inst, int forceupdate)
{
    static float flapneedle[5][3]    = { -.3,0.0,0.0, -.3,4.1,0.0, 0.0,5.1,0.0,
					.3,4.1,0.0, .3,0.0,0.0 };
    static float flapneedlebox[4][3] = { -.6,-0.35,0.0, -.6,5.5,0.0, .6,5.5,0.0,
					.6,-0.35,0.0 };
    static float spoilneedle[5][3]   = { -.3,0.0,0.0, -.3,-4.1,0.0,
					0.0,-5.1,0.0, .3,-4.1,0.0, .3,0.0,0.0 };
    static float spoilneedlebox[4][3]= { -.6,0.35,0.0, -.6,-5.5,0.0,
					.6,-5.5,0.0, .6,0.35,0.0 };
    int current;

    current = instrument_data.current;

    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);

    if ((flaps != inst->last_flap[current] || forceupdate) &&
	inst->maxflap)
    {
	pushmatrix();
	translate(0.0,-7.5,0.0);
	COLOR(C_BLACK);
	pushmatrix();
	rot(inst->last_flaprot[current], 'z');
	drawneedlebox(flapneedlebox);
	popmatrix();
#ifndef NO_MS
	if (ms_samples)
	{
	    pushmatrix();
	    rot(inst->last_flaprot[!current], 'z');
	    drawneedlebox(flapneedlebox);
	    popmatrix();
	}
#endif

	if (flaps > inst->maxflap)
	    inst->last_flaprot[current] = -55.0;
	else if (flaps <= 0)
	    inst->last_flaprot[current] =  55.0;
	else
	    inst->last_flaprot[current] = -110.0 * (float)flaps
					/ (float)inst->maxflap + 55.0;
	drawneedle(inst->last_flaprot[current],
		   instrument_data.darkneedle, flapneedle);
	popmatrix();
	inst->last_flap[current] = flaps;
    }

    if ((spoilers != inst->last_spoiler[current] || forceupdate) &&
	inst->maxspoiler)
    {
	pushmatrix();
	translate(0.0,7.5,0.0);
	COLOR(C_BLACK);
	pushmatrix();
	rot(inst->last_spoilerrot[current], 'z');
	drawneedlebox(spoilneedlebox);
	popmatrix();
#ifndef NO_MS
	if (ms_samples)
	{
	    pushmatrix();
	    rot(inst->last_spoilerrot[!current], 'z');
	    drawneedlebox(spoilneedlebox);
	    popmatrix();
	}
#endif

	if (spoilers > inst->maxspoiler)
	    inst->last_spoilerrot[current] = 55.0;
	else if (spoilers < 0)
	    inst->last_spoilerrot[current] = -55.0;
	else
	    inst->last_spoilerrot[current] = 110.0 * spoilers
					/ (float)inst->maxspoiler - 55.0;
	drawneedle(inst->last_spoilerrot[current],
		   instrument_data.darkneedle, spoilneedle);
	popmatrix();
	inst->last_spoiler[current] = spoilers;
    }

    popmatrix();
}


static flapspoiler_t *fs;

void init_flapspoiler(float px, float py, float pz, float size,
		      int maxflap, int flaptickstep, int numflapticks,
		      int maxspoiler, int spoilertickstep, int numspoilerticks)
{
    flapspoiler_t *inst;

    inst = (flapspoiler_t *)malloc(sizeof(*inst));
    bzero(inst, sizeof(*inst));
    inst->px = px;
    inst->py = py;
    inst->pz = pz;
    inst->size = size;
    inst->plateobject = plate1;
    inst->maxflap = maxflap;
    inst->flaptickstep = flaptickstep;
    inst->numflapticks = numflapticks;
    inst->maxspoiler = maxspoiler;
    inst->spoilertickstep = spoilertickstep;
    inst->numspoilerticks = numspoilerticks;
    inst->last_flap[0] = inst->last_flap[1] = flaps + 10.0;
    inst->last_spoiler[0] = inst->last_spoiler[1] = spoilers + 10.0;
    fs = inst;

    append_inst_list(draw_flapspoiler, update_flapspoiler, inst);
}


void set_flapspoiler(int maxflap, int flaptickstep, int numflapticks,
		     int maxspoiler, int spoilertickstep, int numspoilerticks)
{
    fs->maxflap = maxflap;
    fs->flaptickstep = flaptickstep;
    fs->numflapticks = numflapticks;
    fs->maxspoiler = maxspoiler;
    fs->spoilertickstep = spoilertickstep;
    fs->numspoilerticks = numspoilerticks;
}


/************************************************************************
***				Landinggear functions		      ***
************************************************************************/


typedef struct {
    float px, py, pz;		/* Position of instrument */
    float size;			/* Size of instrument */
    object_t *plateobject;
    int last_state[2];
    int framec;
    int sliding;
    float transfactor;
    int numframes;
    int forcedraw;
    int forcenodraw;
} gear_t;


/*
 * Draw the landing gear indicator
 */
draw_gear(gear_t *inst)
{
    short sl, sr, sb, st;
    static float verts[4][3] = { -9.0,-9.0,0.0, -9.0,9.0,0.0, 9.0,9.0,0.0,
			9.0,-9.0,0.0 };

    getviewport(&sl,&sr,&sb,&st);

    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);

    if (!in_cmode)
    {
	drawmode(UNDERDRAW);

	color(U_INST);
	clear_inst1();

	color(MARKINGS);
    }
    else
    {
	drawmode(PUPDRAW);

	color(U_BLACK);
	clear_inst1();

	color(P_MARKINGS);
    }

    pushviewport();
    viewport(sl-instrument_data.fourwide, sr-instrument_data.fourwide,
	     sb-instrument_data.chartall, st-instrument_data.chartall);
    cmov(0.0,0.0,0.0);
    charstr("GEAR");
    popviewport();

    drawmode(NORMALDRAW);

    frontbuffer(TRUE);

    COLOR(C_BLACK);
    clear_inst1();

    draw_plate(inst->plateobject, 0x3);

    frontbuffer(FALSE);
    popmatrix();
}


update_gear_drawlamp()
{
    static float box[4][3]  = { -2.0,-1.25,0.0, -2.0,1.25,0.0, 2.0,1.25,0.0,
				2.0,-1.25,0.0 };
    bgnpolygon();
    v3f(box[0]);
    v3f(box[1]);
    v3f(box[2]);
    v3f(box[3]);
    endpolygon();
    ICOLOR(instrument_data.textborder);
    bgnclosedline();
    v3f(box[0]);
    v3f(box[1]);
    v3f(box[2]);
    v3f(box[3]);
    endclosedline();
}


update_gear_drawstripes()
{
    static float stripes[16][3] = { -2.0,.25,0.0, -2.0,1.25,0.0, -1.0,1.25,0.0,
				-2.0,-1.25,0.0, -2.0,-.5,0.0, -.25,1.25,0.0,
				.5,1.25,0.0, -.5,-1.25,0.0, -1.25,-1.25,0.0,
				1.25,1.25,0.0, 2.0,1.25,0.0, 1.0,-1.25,0.0,
				.25,-1.25,0.0, 2.0,.5,0.0, 2.0,-.25,0.0 };
    static float box[4][3]  = { -2.0,-1.25,0.0, -2.0,1.25,0.0, 2.0,1.25,0.0,
				2.0,-1.25,0.0 };
    ICOLOR(instrument_data.textbackground);
    bgnpolygon();
    v3f(box[0]);
    v3f(box[1]);
    v3f(box[2]);
    v3f(box[3]);
    endpolygon();
    ICOLOR(instrument_data.yellow);
    bgnpolygon();
    v3f(stripes[0]);
    v3f(stripes[1]);
    v3f(stripes[2]);
    endpolygon();
    bgnpolygon();
    v3f(stripes[3]);
    v3f(stripes[4]);
    v3f(stripes[5]);
    v3f(stripes[6]);
    endpolygon();
    bgnpolygon();
    v3f(stripes[7]);
    v3f(stripes[8]);
    v3f(stripes[9]);
    v3f(stripes[10]);
    endpolygon();
    bgnpolygon();
    v3f(stripes[11]);
    v3f(stripes[12]);
    v3f(stripes[13]);
    v3f(stripes[14]);
    endpolygon();
}


/*
 * Update the landing gear's instrument
 */
update_gear(gear_t *inst, int forceupdate)
{
    static float box[4][3]  = { -2.0,-1.25,0.0, -2.0,1.25,0.0, 2.0,1.25,0.0,
				2.0,-1.25,0.0 };
    static float ubox[4][3] = { -2.0,1.25,0.0, -2.0,3.9,0.0, 2.0,3.9,0.0,
				2.0,1.25,0.0 };
    int current;
    int gearstate;
    float uptrans;
    char buf[2];

    if (planes[0]->wheels == 0)
	gearstate = 0;
    else if (planes[0]->wheels == 10 && landing_gear_stuck != 0)
	gearstate = 2;
    else
	gearstate = 1;

    current = instrument_data.current;
    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);

    if ((gearstate != inst->last_state[current])||inst->forcenodraw||forceupdate)
    {
	if (gearstate == 0)
	{
	    inst->forcedraw = inst->framec = inst->sliding = 0;
	    pushmatrix();
	    translate(-4.0,-3.0,0.0);
	    ICOLOR(instrument_data.greenlamp);
	    update_gear_drawlamp();
	    translate(8.0,0.0,0.0);
	    ICOLOR(instrument_data.greenlamp);
	    update_gear_drawlamp();
	    translate(-4.0,7.0,0.0);
	    ICOLOR(instrument_data.greenlamp);
	    update_gear_drawlamp();
	    popmatrix();
	    inst->last_state[current] = gearstate;
	}
	else if (((gearstate == 1)&&(inst->last_state[current] == 0))
				||inst->forcenodraw)
	{
	    if (inst->forcenodraw)
		inst->forcenodraw--;
	    else
		inst->last_state[current] = gearstate;
	    inst->forcedraw = inst->framec = inst->sliding = 0;
	    pushmatrix();
	    translate(-4.0,-3.0,0.0);
	    ICOLOR(instrument_data.redlamp);
	    update_gear_drawlamp();
	    translate(8.0,0.0,0.0);
	    ICOLOR(instrument_data.redlamp);
	    update_gear_drawlamp();
	    translate(-4.0,7.0,0.0);
	    ICOLOR(instrument_data.redlamp);
	    update_gear_drawlamp();
	    popmatrix();
	}
	else if ((gearstate == 1)&&(inst->last_state[current] == 2))
	{
	    inst->sliding = 1;
	    if (!inst->framec) inst->framec = 1;
	}
	else if (gearstate == 2)
	{
	    inst->sliding = -1;
	    if (!inst->framec) inst->framec = inst->numframes;
	}
    }
    if (inst->sliding)
    {
	uptrans = inst->framec * inst->transfactor;
	pushmatrix();
	translate(-4.0,-3.0,0.0);
	ICOLOR(instrument_data.redlamp);
	bgnpolygon();
	v3f(box[0]);
	v3f(box[1]);
	v3f(box[2]);
	v3f(box[3]);
	endpolygon();
	pushmatrix();
	translate(0.0,uptrans,0.0);
	update_gear_drawstripes();
	popmatrix();
	COLOR(C_BLACK);
	bgnpolygon();
	v3f(ubox[0]);
	v3f(ubox[1]);
	v3f(ubox[2]);
	v3f(ubox[3]);
	endpolygon();
	ICOLOR(instrument_data.textborder);
	bgnclosedline();
	v3f(box[0]);
	v3f(box[1]);
	v3f(box[2]);
	v3f(box[3]);
	endclosedline();

	translate(8.0,0.0,0.0);
	ICOLOR(instrument_data.redlamp);
	bgnpolygon();
	v3f(box[0]);
	v3f(box[1]);
	v3f(box[2]);
	v3f(box[3]);
	endpolygon();
	pushmatrix();
	translate(0.0,uptrans,0.0);
	update_gear_drawstripes();
	popmatrix();
	COLOR(C_BLACK);
	bgnpolygon();
	v3f(ubox[0]);
	v3f(ubox[1]);
	v3f(ubox[2]);
	v3f(ubox[3]);
	endpolygon();
	ICOLOR(instrument_data.textborder);
	bgnclosedline();
	v3f(box[0]);
	v3f(box[1]);
	v3f(box[2]);
	v3f(box[3]);
	endclosedline();

	translate(-4.0,7.0,0.0);
	ICOLOR(instrument_data.redlamp);
	bgnpolygon();
	v3f(box[0]);
	v3f(box[1]);
	v3f(box[2]);
	v3f(box[3]);
	endpolygon();
	pushmatrix();
	translate(0.0,uptrans,0.0);
	update_gear_drawstripes();
	popmatrix();
	COLOR(C_BLACK);
	bgnpolygon();
	v3f(ubox[0]);
	v3f(ubox[1]);
	v3f(ubox[2]);
	v3f(ubox[3]);
	endpolygon();
	ICOLOR(instrument_data.textborder);
	bgnclosedline();
	v3f(box[0]);
	v3f(box[1]);
	v3f(box[2]);
	v3f(box[3]);
	endclosedline();
	popmatrix();

	inst->framec += inst->sliding;
	if (!inst->framec)
	{
	    inst->forcedraw = 2;
	    inst->sliding = 0;
	    inst->last_state[current] = inst->last_state[!current] = gearstate;
	}
	if (inst->framec >= inst->numframes)
	{
	    inst->forcenodraw = 2;
	    inst->framec = 0;
	    inst->sliding = 0;
	    inst->last_state[current] = inst->last_state[!current] = gearstate;
	}
    }
    else if (inst->forcedraw)
    {
	inst->forcedraw--;
	pushmatrix();
	translate(-4.0,-3.0,0.0);
	update_gear_drawstripes();
	ICOLOR(instrument_data.textborder);
	bgnclosedline();
	v3f(box[0]);
	v3f(box[1]);
	v3f(box[2]);
	v3f(box[3]);
	endclosedline();

	translate(8.0,0.0,0.0);
	update_gear_drawstripes();
	ICOLOR(instrument_data.textborder);
	bgnclosedline();
	v3f(box[0]);
	v3f(box[1]);
	v3f(box[2]);
	v3f(box[3]);
	endclosedline();

	translate(-4.0,7.0,0.0);
	update_gear_drawstripes();
	ICOLOR(instrument_data.textborder);
	bgnclosedline();
	v3f(box[0]);
	v3f(box[1]);
	v3f(box[2]);
	v3f(box[3]);
	endclosedline();
	popmatrix();
	inst->last_state[current] = gearstate;
    }
    popmatrix();
}



/*
 * Initialize the landing gear instrument
 */
void init_gear(float px, float py, float pz, float size)
{
    gear_t *inst;

    inst = (gear_t *)malloc(sizeof(*inst));
    bzero(inst, sizeof(*inst));
    inst->px = px;
    inst->py = py;
    inst->pz = pz;
    inst->size = size;
    inst->plateobject = plate1;
    inst->framec = 0;
    inst->last_state[0] = inst->last_state[1] = 1;
    inst->sliding = 0;
    inst->forcedraw = inst->forcenodraw = 0;
    inst->numframes = 4;
    inst->transfactor = 2.6 / inst->numframes;

    append_inst_list(draw_gear, update_gear, inst);
}



/************************************************************************
***			G-meter functions			      ***
************************************************************************/


typedef struct {
    float px, py, pz;		/* Position of instrument */
    float size;			/* Size of instrument */
    object_t *plateobject;
    float last_g[2];		/* Previous fuel of both buffers */
    float last_gheight[2];
    int numticks;
} gmeter_t;



/*
 * Draw the gmeter
 */
draw_gmeter(gmeter_t *inst)
{
    static float verts[4][3] = { -2.1,-15.1,0.0, 2.1,-15.1,0.0, 2.1,15.1,0.0,
			-2.1,15.1,0.0 };
    static float ticks[2][3]	   = { -2.0,0.0,0.0, -1.2,0.0,0.0 };
    static float lticks[2][3]	   = { 1.2,0.0,0.0, 2.0,0.0,0.0 };
    static float smallticks[2][3]  = { -2.0,0.0,0.0, -.8,0.0,0.0 };
    static float lsmallticks[2][3] = { 2.0,0.0,0.0, .8,0.0,0.0 };
    short sl, sr, sb, st;
    char buf[4];
    int x;
    float angstep, tickangstep;

    getviewport(&sl,&sr,&sb,&st);
    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);

    if (!in_cmode)
    {
	drawmode(UNDERDRAW);
	color(U_INST);
	clear_inst2();
	color(MARKINGS);
    }
    else
    {
	drawmode(PUPDRAW);
	color(U_BLACK);
	clear_inst2();
	color(P_MARKINGS);
    }

    for (x= -10; x<=10; x+=2)
    {
	pushmatrix();
	translate(0.0, 1.2*x, 0.0);
	bgnline();
	v3f(ticks[0]);
	v3f(ticks[1]);
	endline();
	bgnline();
	v3f(lticks[0]);
	v3f(lticks[1]);
	endline();
	if (x < 10)
	{
	    translate(0.0, 1.2, 0.0);
	    bgnline();
	    v3f(smallticks[0]);
	    v3f(smallticks[1]);
	    endline();
	    bgnline();
	    v3f(lsmallticks[0]);
	    v3f(lsmallticks[1]);
	    endline();
	}
	popmatrix();
    }
    pushviewport();
    viewport(sl-instrument_data.twowide, sr-instrument_data.twowide,
		sb-instrument_data.chartall, st-instrument_data.chartall);
    for (x= -10; x<=10; x+=20)
    {
	cmov(0.0, 1.2*x, 0.0);
	sprintf(buf,"%d",abs(x));
	charstr(buf);
    }
    viewport(sl-instrument_data.charwide, sr-instrument_data.charwide,
		sb-instrument_data.chartall, st-instrument_data.chartall);
    for (x= -8; x<=8; x+=2)
    {
	cmov(0.0, 1.2*x, 0.0);
	sprintf(buf,"%d",abs(x));
	charstr(buf);
    }
    cmov(0.0, -14.1, 0.0);
    charstr("G");
    popviewport();

    drawmode(NORMALDRAW);
    frontbuffer(TRUE);

    COLOR(C_BLACK);
    clear_inst2();

    draw_plate(inst->plateobject, 0x3);

    frontbuffer(FALSE);
    popmatrix();
}


update_gmeter(gmeter_t *inst, int forceupdate)
{
    static float needle[4][3]    = {{-1.55, -0.2, 0.2}, { 1.55, -0.2, 0.2},
				    { 1.55,  0.2, 0.2}, {-1.55,  0.2, 0.2}};
    static float needlebox[4][3] = {{-1.75, -0.5, 0.0}, { 1.75, -0.5, 0.0},
				    { 1.75,  0.3, 0.0}, {-1.75,  0.3, 0.0}};
    int current;
    float gload;

    current = instrument_data.current;
    gload = lift / GRAVITY;
    pushmatrix();
    translate(inst->px, inst->py, inst->pz);
    scale(inst->size, inst->size, inst->size);
    if ((gload != inst->last_g[current]) || forceupdate)
    {
	inst->last_g[current] = gload;
	COLOR(C_BLACK);
	pushmatrix();
	translate(0.0, inst->last_gheight[current], 0.0);
	bgnpolygon();
	v3f(needlebox[0]);
	v3f(needlebox[1]);
	v3f(needlebox[2]);
	v3f(needlebox[3]);
	endpolygon();
	popmatrix();
#ifndef NO_MS
	if (ms_samples)
	{
	    pushmatrix();
	    translate(0.0, inst->last_gheight[!current], 0.0);
	    bgnpolygon();
	    v3f(needlebox[0]);
	    v3f(needlebox[1]);
	    v3f(needlebox[2]);
	    v3f(needlebox[3]);
	    endpolygon();
	    popmatrix();
	}
#endif

	if (gload > 10.0)
	    inst->last_gheight[current] = -12.0;
	else if (gload < -10.0)
	    inst->last_gheight[current] = 12.0;
	else
	    inst->last_gheight[current] = -1.2 * gload;

	translate(0.0, inst->last_gheight[current], 0.0);
	ICOLOR(instrument_data.jamblack);
	setpattern(SHADOW_PATTERN);
	pushmatrix();
	translate(0.2, -0.2, 0.0);
	bgnpolygon();
	v3f(needle[0]);
	v3f(needle[1]);
	v3f(needle[2]);
	v3f(needle[3]);
	endpolygon();
	setpattern(0);
	popmatrix();

	COLOR(C_ORANGE);
	bgnpolygon();
	v3f(needle[0]);
	v3f(needle[1]);
	v3f(needle[2]);
	v3f(needle[3]);
	endpolygon();
    }
    popmatrix();
}


void init_gmeter(float px, float py, float pz, float size)
{
    gmeter_t *inst;

    inst = (gmeter_t *)malloc(sizeof(*inst));
    bzero(inst, sizeof(*inst));
    inst->px = px;
    inst->py = py;
    inst->pz = pz;
    inst->size = size;
    inst->plateobject = plate3;
    inst->last_g[0]= inst->last_g[1]= .1;

    append_inst_list(draw_gmeter, update_gmeter, inst);
}


void draw_plate(object_t *obj, unsigned long mode)
{
    if (!in_cmode)
    {
	zbuffer(TRUE);
	lighting(TRUE);
	drawobj(obj, 0x3);
	lighting(FALSE);
	zbuffer(FALSE);
    }
    else
    {
	drawmode(plate_ci_mode);
	drawobj(obj, 0x3);
	drawmode(NORMALDRAW);
    }
}

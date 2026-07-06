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
 *  flight/land1.c $Revision: 1.1 $
 */

#include "flight.h"


static unsigned short bcursor[] = {
	0xffff, 0xffff, 0xffff, 0xe007,
	0xe007, 0xe007, 0xe007, 0xe007,
	0xe007, 0xe007, 0xe007, 0xe007,
	0xe007, 0xffff, 0xffff, 0xffff,
};

static unsigned short nocursor[] = {
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
};


/*
 *  init_graphics() initilizes graphics for flight
 */
init_graphics(name)
    char *name;
{
    static Pattern16 shadow_pattern = {
	0x5555, 0xaaaa, 0x5555, 0xaaaa, 0x5555, 0xaaaa, 0x5555, 0xaaaa,
	0x5555, 0xaaaa, 0x5555, 0xaaaa, 0x5555, 0xaaaa, 0x5555, 0xaaaa,
    };
    static Pattern16 crash_pattern = {
	0x0007, 0x000e, 0x001c, 0x0038, 0x0070, 0x00e0, 0x01c0, 0x0380,
	0x0700, 0x0e00, 0x1c00, 0x3800, 0x7000, 0xe000, 0xc001, 0x8003,
    };

    static int firsttime = 1;	/* 0 after first call to init_graphics() */

    if (firsttime)
    {
	char gver[32];

	if (xmaxscreen == 0)
	    xmaxscreen = getgdesc(GD_XPMAX) - 1;
	if (ymaxscreen == 0)
	    ymaxscreen = getgdesc(GD_YPMAX) - 1;
	zminscreen = getgdesc(GD_ZMIN);
	zmaxscreen = getgdesc(GD_ZMAX);

#if 1
	prefposition(0, xmaxscreen, 0, ymaxscreen);
	noborder();
	foreground();
#else
	keepaspect(5,4);
#endif
	winopen(name);
	color(0);
	clear();
	icontitle(name);
	subpixel(1);

	init_window_size();

	/*
	 *  Decide if we need to run in color index mode.
	 */
	gversion(gver);
	if (((getgdesc(GD_BITS_NORM_DBL_RED) < 4 ||
	      strncmp(gver, "GL4D-", 5)    == 0 ||
	      strncmp(gver, "GL4DPI-", 7)  == 0 ||
	      strncmp(gver, "GL4DPI2-", 8) == 0 ||
	      strncmp(gver, "GL4DPIT-", 8) == 0 ||
	      strncmp(gver, "GL4DLG-", 7)  == 0 ||
	      strncmp(gver, "GL4DNP-", 7)  == 0) &&
	     (!force_rgb)) ||
	    getgdesc(GD_BITS_NORM_ZBUFFER) == 0 ||
	    getgdesc(GD_BITS_NORM_DBL_RED) == 0)
	    force_cmode = TRUE;

	doublebuffer();
	if (force_cmode)
	{
	    in_cmode = TRUE;
	    bits_cmode = MIN(bits_cmode, getgdesc(GD_BITS_NORM_DBL_CMODE));
	    shademodel(FLAT);
	}
	else
	    RGBmode();

#ifndef NO_MS
	if (getgdesc(GD_MULTISAMPLE) > 0)
	    mssize(4, 32, 0);
#endif
	underlay(2);
	overlay(0);
	gconfig();

    }

    viewport(0, xmaxwindow, 0, ymaxwindow);
    if (in_cmode)
	color(0);
    else
	cpack(0x0);
    clear();
    swapbuffers();
    clear();

    if (firsttime)
    {
	swapinterval(2);

#ifndef NO_MS
	if (getgdesc(GD_MULTISAMPLE) > 0)
	    ms_samples = getgconfig(GC_MS_SAMPLES);
	else
	    ms_samples = 0;
#endif

	if (getgdesc(GD_BITS_UNDR_SNG_CMODE) >= 2)
	    bits_under = 2;
	else
	    bits_under = 0;

	/*
	 *  setup data directories
	 */
	strncpy(sounddir, datadir, 108);
	strcat(sounddir, "sound/");	/* was 3-arg strcat; IRIX cc ignored the extra arg */
	strncpy(objdir, datadir, 108);
	if (in_cmode)
	    strcat(objdir, "ci/");	/* was 3-arg strcat */
	else
	    strcat(objdir, "rgb/");	/* was 3-arg strcat */

#ifdef AUDIO
	init_audio();
#endif
    }

    glcompat(GLC_OLDPOLYGON, FALSE);

    mmode(MVIEWING);
    identify_matrix(identmat);
    loadmatrix(identmat);

    if (firsttime)
    {
	init_lighting();
	init_texturing();
	set_fog_density(0);
	set_fog_color(0xff999999);

	defcursor(1, bcursor);		/* set up block cursor */
	curorigin(1, 8, 8);
	setcursor(1, 0, 0);

	deflinestyle(1, 0x3333);
	defpattern(CRASH_PATTERN, PATTERN_16, crash_pattern);
	defpattern(SHADOW_PATTERN, PATTERN_16, shadow_pattern);

	save_map();
	setup_colormaps();

	set_ftime(get_real_time());		/* set the time */

	init_instruments();

	qdevice(REDRAW);
	qdevice(MOUSEX);
	qdevice(MOUSEY);
	qdevice(MOUSE1);
	qdevice(MOUSE2);
	qdevice(MOUSE3);
	qdevice(LEFTARROWKEY);
	qdevice(RIGHTARROWKEY);
	qdevice(UPARROWKEY);
	qdevice(DOWNARROWKEY);
	qdevice(PAD0);
	qdevice(PAD1);
	qdevice(PAD2);
	qdevice(PAD3);
	qdevice(PAD4);
	qdevice(PAD5);
	qdevice(PAD6);
	qdevice(PAD7);
	qdevice(PAD8);
	qdevice(PAD9);
	qdevice(KEYBD);
	qdevice(F1KEY);
	qdevice(F2KEY);

	qdevice(SBTX);
	qdevice(SBTZ);
	qdevice(SBPICK);
	qdevice(SBBUT2);
	qdevice(SBBUT3);
	qdevice(SBBUT6);
	qdevice(SBBUT7);
	qdevice(SBBUT8);

	if (infile)
	{
	    qdevice(F9KEY);
	    qdevice(F10KEY);
	    qdevice(F11KEY);
	    qdevice(F12KEY);
	    qdevice(PAUSEKEY);
	    qdevice(HOMEKEY);
	}

	setvaluator(MOUSEX, mousex = xmiddle, 0, xmaxscreen);
	setvaluator(MOUSEY, mousey = ymiddle, 0, ymaxscreen);
	init_exp();
    }
    firsttime = 0;
}


void init_window_size()
{
    /* xmaxwindow etc. are int; IRIX long was 32-bit, ours is 64 — use temps
     * instead of the original (long *)&int casts */
    long gsx, gsy;
    getsize(&gsx, &gsy);
    xmaxwindow = gsx;
    ymaxwindow = gsy;
    xmaxwindow -= 1;
    ymaxwindow -= 1;
    getorigin(&gsx, &gsy);
    xorigin = gsx;
    yorigin = gsy;
    xmiddle = (xmaxwindow-1) >> 1;
    ymiddle = (ymaxwindow-1) >> 1;

    inst_x1 = 0;
    inst_x2 = xmaxwindow;
    inst_y1 = ((int)(66*(ymaxwindow/1023.0)));
    inst_y2 = (ymiddle-2);

    report_x1 = 0;
    report_x2 = xmaxwindow;
    report_y1 = 0;
    report_y2 = inst_y1-1;
}



#if 0
char alt_text[8];		/* global altitude text	*/
char mach_text[8];		/* global mach number text	*/
char g_text[8];			/* global g-force text	*/
#endif

draw_cross_hairs()
{
    COLOR(C_ORANGE);
    move2s(0, -3);
    draw2s(0, 3);
    move2s(-2, 0);
    draw2s(2, 0);
}

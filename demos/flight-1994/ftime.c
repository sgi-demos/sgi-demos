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
 *  flight/ftime.c $Revision: 1.1 $
 *
 *  procedures to set time sun position and shadow
 */

#include "flight.h"
#include "light.h"
#include "sys/types.h"
#include "time.h"
#include <stdio.h>

#define SUNRISE	(06*60)
#define SUNSET	(18*60)
#define NOON	(12*60)

#define CP_NITESKY	( 10 + ( 10<<8) + ( 20<<16))
#define CP_SKYTOP	( 60 + (140<<8) + (220<<16))
#define CP_HORIZON	(110 + (190<<8) + (250<<16))

#define RGB_NITESKY	 10,  10,  20
#define RGB_SUNRISE1	 80,  30,  20
#define RGB_SUNRISE2	120,  30,  20
#define RGB_HORIZON	110, 190, 250
#define RGB_SKYTOP	 60, 140, 220

#define FOG_NITE	0x0a, 0x0a, 0x10
#define FOG_SUNRISE1	0x30, 0x10, 0x10
#define FOG_SUNRISE2	0x40, 0x1a, 0x15
#define FOG_DAY		0x99, 0x90, 0x99


Matrix shadow_matrix;
int ftime;
int startftime;
int elapsetime;
long startclock;
float sunx = 0.0, suny = 1.0, sunz = 0.0;
int lightson;

long cp_sky, cp_W_horizon, cp_E_horizon, cp_ground;


set_ftime(t)
    int t;
{
    long angle;

    ftime = t % 1440;
    if (ftime < 0) ftime += 1440;
    startftime = elapsetime = ftime;
    startclock = time(0);
    angle = ((ftime<<1) + (ftime>>1)) - 900;	/* 2.5 * ftime - 900 */

    gl_sincos(angle, &suny, &sunx);
    set_sun(sunx, suny, sunz);
    set_lightpos(SUN, sunx, suny, sunz);
    set_skycolor();
    if (ftime > SUNRISE+60 && ftime < SUNSET-60)
	lightson = FALSE;
    else
	lightson = TRUE;
}

update_ftime()
{
    int newtime;
    long angle;

    if ((newtime = startftime+((startclock-time(0))/60)) > elapsetime)
    {
	elapsetime = newtime;
	ftime = newtime % 1440;
	angle = ((ftime<<1) + (ftime>>1)) - 900;	/* 2.5 * ftime - 900 */
	gl_sincos(angle, &suny, &sunx);
	set_sun(sunx, suny, sunz);
	set_lightpos(SUN, sunx, suny, sunz);
	set_skycolor();
    }
}


/*
 *  set colors of sky and horizon
 */
set_skycolor()
{
    if (in_cmode)
    {
	float ldiv;

	if (ftime > SUNRISE-60 && ftime < SUNRISE+60)
	{
	    ldiv = 1.0 + ((120-(ftime-(SUNRISE-60))) / 20.0);
	}
	else if (ftime > SUNSET-60 && ftime < SUNSET+60)
	{
	    ldiv = 1.0 + ((ftime-(SUNSET-60)) / 20.0);
	}
	else if (ftime >= SUNRISE+60 && ftime <= SUNSET-60)
	{
	    ldiv = 1.0;		/* day time */
	}
	else
	{
	    ldiv = 7.0;		/* night time */
	}

	init_normal_colormap(ldiv);
    }
    else
    {
	float delta;
	float l = ((SUNRISE - abs(ftime - NOON)) / (float)SUNRISE);
	float al = l + 0.1;

	l = (l > 0.7)? 0.7 : l;

	if (l > 0.1)
	    set_lightcolor(SUN, al*0.4, al*0.4, al*0.4,
			   (l < 0.44)? 0.44 : l, l, l);
	else if (l >= 0.0)
	    set_lightcolor(SUN, al*0.4, al*0.4, al*0.4, l*4.4, l, l);
	else if (l >= -0.1)
	    set_lightcolor(SUN, al*0.4, al*0.4, al*0.4, 0.0, 0.0, 0.0);
	else
	    set_lightcolor(SUN, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

	if (ftime >= SUNSET+60 || ftime < SUNRISE-60)
	{
	    cp_sky = cp_E_horizon = cp_W_horizon = CP_NITESKY;
	    set_fog_color(pack_color(FOG_NITE));
	}
	else if (ftime >= SUNRISE-60 && ftime < SUNRISE)
	{
	    delta =  (ftime + 60 - SUNRISE) / 60.0;
	    cp_sky = cp_W_horizon = CP_NITESKY;
	    cp_E_horizon = comp_color(delta, RGB_NITESKY, RGB_SUNRISE1);
	    set_fog_color(comp_color(delta, FOG_NITE, FOG_SUNRISE1));
	}
	else if (ftime >= SUNRISE && ftime < SUNRISE+30)
	{
	    delta =  (ftime - SUNRISE) / 30.0;
	    cp_sky = cp_W_horizon = CP_NITESKY;
	    cp_E_horizon = comp_color(delta, RGB_SUNRISE1, RGB_SUNRISE2);
	    set_fog_color(comp_color(delta, FOG_SUNRISE1, FOG_SUNRISE2));
	}
	else if (ftime >= SUNRISE+30 && ftime < SUNRISE+120)
	{
	    delta =  (ftime - (SUNRISE+30)) / 90.0;
	    cp_sky = comp_color(delta, RGB_NITESKY, RGB_SKYTOP);
	    cp_E_horizon = comp_color(delta, RGB_SUNRISE2, RGB_HORIZON);
	    cp_W_horizon = comp_color(delta, RGB_NITESKY, RGB_HORIZON);
	    set_fog_color(comp_color(delta, FOG_SUNRISE2, FOG_DAY));
	}
	else if (ftime >= SUNRISE+120 && ftime < SUNSET-120)
	{
	    cp_W_horizon = cp_E_horizon = CP_HORIZON;
	    cp_sky = CP_SKYTOP;
	    set_fog_color(pack_color(FOG_DAY));
	}
	else if (ftime >= SUNSET-120 && ftime < SUNSET-30)
	{
	    delta =  ((SUNSET-30) - ftime) / 90.0;
	    cp_sky = comp_color(delta, RGB_NITESKY, RGB_SKYTOP);
	    cp_W_horizon = comp_color(delta, RGB_SUNRISE2, RGB_HORIZON);
	    cp_E_horizon = comp_color(delta, RGB_NITESKY, RGB_HORIZON);
	    set_fog_color(comp_color(delta, FOG_SUNRISE2, FOG_DAY));
	}
	else if (ftime >= SUNSET-30 && ftime < SUNSET)
	{
	    delta =  (SUNSET - ftime) / 30.0;
	    cp_sky = cp_E_horizon = CP_NITESKY;
	    cp_W_horizon = comp_color(delta, RGB_SUNRISE1, RGB_SUNRISE2);
	    set_fog_color(comp_color(delta, FOG_SUNRISE1, FOG_SUNRISE2));
	}
	else if (ftime >= SUNSET && ftime < SUNSET+60)
	{
	    delta =  (SUNSET + 60 - ftime) / 60.0;
	    cp_sky = cp_E_horizon = CP_NITESKY;
	    cp_W_horizon = comp_color(delta, RGB_NITESKY, RGB_SUNRISE1);
	    set_fog_color(comp_color(delta, FOG_NITE, FOG_SUNRISE1));
	}
    }
}


set_sun(x, y, z)
    float x, y, z;
{
    identify_matrix (shadow_matrix);
    shadow_matrix[1][0] = -x/y;
    shadow_matrix[1][1] = 0.000001;
    shadow_matrix[1][2] = -z/y;
}


draw_shadow(pp, near)
    register Plane pp;
    int near;
{
    /*
     *  if it is between 5:59 PM and 6:01 AM don't draw the shadow
     */
    if (ftime >= SUNSET || ftime <= SUNRISE)
	return;

    /*
     *  cull
     */
    if (cull_shadow(pp, shadow_matrix[1][0], shadow_matrix[1][2]))
	return;

    zbuffer(FALSE);
    pushmatrix();
    multmatrix(shadow_matrix);
    translate(pp->x, pp->y, pp->z);
    rotate(pp->azimuth, 'y');
    rotate(pp->elevation, 'x');
    rotate(pp->twist, 'z');

    setpattern(SHADOW_PATTERN);
    if (!in_cmode)
	drawobj(planeobj[pp->type], (near ? PS_SHADOW : PS_FARSHADOW) |
				    (pp->weapon_state << PS_W_SHIFT));
    else
	drawobj(planeobj[pp->type], (near ? PS_SHADOW : PS_FARSHADOW));
    setpattern(0);
    popmatrix();
    if (!in_cmode)
	zbuffer(TRUE);
}


/*
 *  get_real_time() returns the timeofday in minutes
 */
get_real_time()
{
    struct tm *tm;
    long t;

    t = time(0);

    if(tm = localtime(&t))
	return(tm->tm_hour * 60 + tm->tm_min);
    else
	return 720;		/* 12:00 noon */
}


comp_color(delta, rmin, gmin, bmin, rmax, gmax, bmax)
    float delta;
    long rmin, gmin, bmin, rmax, gmax, bmax;
{
    return((rmin+(int)(delta*(rmax-rmin)))) +
	  ((gmin+(int)(delta*(gmax-gmin)))<<8) +
	  ((bmin+(int)(delta*(bmax-bmin)))<<16);
}

pack_color(r, g, b)
    long r, g, b;
{
    return(r + (g<<8) + (b<<16));
}

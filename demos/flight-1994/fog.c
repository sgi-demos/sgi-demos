/*
 * Copyright 1989, 1990, 1991, 1992, 1993, 1994, Silicon Graphics, Inc.
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
 *  flight/fog.c $Revision: 1.1 $
 */

#include "math.h"
#include "fcntl.h"
#include "stdio.h"
#include "flight.h"


#define MIN_FD		1
#define START_FD	67
#define MAX_FD		100


int fogon = FALSE;
int fog_d = START_FD;
unsigned long fog_c = 0xff999999;


set_fog_density(d)
    int d;
{
    float p[4];

    fog_d += d;
    if (fog_d < MIN_FD)
	fog_d = MIN_FD;
    else if (fog_d > MAX_FD)
	fog_d = MAX_FD;

    p[0] = 1.0 / fexp(fog_d/6.0);
    p[1] = (fog_c & 0xff) / 255.0;
    p[2] = ((fog_c >> 8) & 0xff) / 255.0;
    p[3] = ((fog_c >> 16) & 0xff) / 255.0;

    fogvertex(FG_DEFINE, p);
}


set_fog_color(c)
    unsigned long c;
{
    float p[4];

    fog_c = c;
    p[0] = 1.0 / fexp(fog_d/6.0);
    p[1] = (fog_c & 0xff) / 255.0;
    p[2] = ((fog_c >> 8) & 0xff) / 255.0;
    p[3] = ((fog_c >> 16) & 0xff) / 255.0;

    fogvertex(FG_DEFINE, p);
}


fog(b)
{
    if (fogon = b)
	fogvertex(FG_ON, (float *)0);
    else
	fogvertex(FG_OFF, (float *)0);
}


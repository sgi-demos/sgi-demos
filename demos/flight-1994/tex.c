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
 *  flight/tex.c $Revision: 1.1 $
 */

#include "fcntl.h"
#include "stdio.h"
#include "flight.h"

static float texps[] = {TX_MAGFILTER, TX_BILINEAR, TX_MINFILTER,
			   TX_MIPMAP_LINEAR, 0};
static float texps_point[] = {TX_MAGFILTER, TX_POINT, TX_MINFILTER,
			   TX_MIPMAP_POINT, 0};
static float tevps[] = {0};

int texon = FALSE;


init_texturing()
{
    long *image;
    unsigned char bw[128*128];
    int i;

    readtex("hills.t", bw, 128*128);
    texdef2d(1, 1, 128, 128, (unsigned long *)bw, 5, texps_point);
    tevdef(1, 0, tevps);
}


texturing(b)
{
    if (b)
    {
	texon = TRUE;
	texbind(0, 1);
	tevbind(0, 1);
    }
    else
    {
	texon = FALSE;
	texbind(0, 0);
	tevbind(0, 0);
    }
}


readtex(fname, buf, size)
    char *fname;
    unsigned long *buf;
{
    long ifd;
    char file[80];

    strcpy(file, datadir);
    strcat(file, fname);

    if((ifd = open(file, O_RDONLY)) == -1)
    {
	fprintf(stderr,"flight: can't open texture file %s\n", file);
	exit(1);
    }

    read(ifd, buf, size);

    close(ifd);
}

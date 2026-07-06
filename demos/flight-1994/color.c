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
 *  flight/color.c $Revision: 1.1 $
 */

#include "flight.h"

short ci_table[64];
unsigned long cpack_table[64];
short rgb_table[64][3];

static short pupmap[3][3];
static short normmap[64][3];


#define LOAD_RGB_TABLE(i, r, g, b)	\
{					\
    rgb_table[i][0] = r;		\
    rgb_table[i][1] = g;		\
    rgb_table[i][2] = b;		\
}

#define GET_RGB(i)	rgb_table[i][0], rgb_table[i][1], rgb_table[i][2]

#define SCALE_RGB(i, s)	(rgb_table[i][0] / s), \
			(rgb_table[i][1] / s), \
			(rgb_table[i][2] / s)

#define ADD_RGB(i, j, s)  MIN((rgb_table[i][0]+rgb_table[j][0]/s), 0xff), \
			  MIN((rgb_table[i][1]+rgb_table[j][1]/s), 0xff), \
			  MIN((rgb_table[i][2]+rgb_table[j][2]/s), 0xff)

void setup_colormaps()
{
    char mapfname[80],decfname[80];

ortho2(-0.5, xmaxwindow+0.5, -0.5, ymaxwindow+0.5); /*XXX*/

    init_color_tables();

    if (in_cmode)
    {
	init_normal_colormap(1.0);
    }

    drawmode(over_drawmode);
    if (in_cmode & new_inst)
    {
	mapcolor(P_GREY1, RGB_GREY_12);
	mapcolor(P_GREY2, RGB_GREY_9);
	mapcolor(P_MARKINGS, RGB_GREY_5);
    }
    else
	mapcolor(P_ORANGE, RGB_ORANGE);

    if (bits_under)
    {
	drawmode(UNDERDRAW);
	mapcolor(0, 0, 0, 0);				/* 0	*/
	if (!new_inst)
	    mapcolor(U_BROWN, 96, 80, 64);		/* 1	*/
	else
	{
	    mapcolor(U_INST, 50, 50, 50);		/* 1	*/
	    mapcolor(U_MARKINGS, 200, 200, 200);
	}
    }

    drawmode(NORMALDRAW);

    gflush();
}


void init_color_tables()
{
    load_rgb_table(C_BLACK, RGB_BLACK);
    load_rgb_table(C_WHITE, RGB_WHITE);
    load_rgb_table(C_RED, RGB_RED);
    load_rgb_table(C_DRED, RGB_DRED);
    load_rgb_table(C_GREEN, RGB_GREEN);
    load_rgb_table(C_BLUE, RGB_BLUE);
    load_rgb_table(C_YELLOW, RGB_YELLOW);
    load_rgb_table(C_ORANGE, RGB_ORANGE);
    load_rgb_table(C_INST_BROWN, RGB_INST_BROWN);
    load_rgb_table(C_HBLUE, RGB_HBLUE);
    load_rgb_table(C_GREY, RGB_GREY);
    load_rgb_table(C_MC_FLAME, RGB_MC_FLAME);
    load_rgb_table(C_MC_TRAIL, RGB_MC_TRAIL);
    load_rgb_table(C_DIRT, RGB_DIRT);
    load_rgb_table(C_SWAMP, RGB_SWAMP);
    load_rgb_table(C_SKY, RGB_SKY);
    load_rgb_table(C_GREY_0, RGB_GREY_0);
    load_rgb_table(C_GREY_1, RGB_GREY_1);
    load_rgb_table(C_GREY_2, RGB_GREY_2);
    load_rgb_table(C_GREY_3, RGB_GREY_3);
    load_rgb_table(C_GREY_4, RGB_GREY_4);
    load_rgb_table(C_GREY_5, RGB_GREY_5);
    load_rgb_table(C_GREY_6, RGB_GREY_6);
    load_rgb_table(C_GREY_7, RGB_GREY_7);
    load_rgb_table(C_GREY_8, RGB_GREY_8);
    load_rgb_table(C_GREY_9, RGB_GREY_9);
    load_rgb_table(C_GREY_10, RGB_GREY_10);
    load_rgb_table(C_GREY_11, RGB_GREY_11);
    load_rgb_table(C_GREY_12, RGB_GREY_12);
    load_rgb_table(C_SILVER_0, RGB_SILVER_0);
    load_rgb_table(C_SILVER_1, RGB_SILVER_1);
    load_rgb_table(C_SILVER_2, RGB_SILVER_2);
    load_rgb_table(C_SILVER_3, RGB_SILVER_3);
    load_rgb_table(C_SILVER_4, RGB_SILVER_4);
    load_rgb_table(C_SILVER_5, RGB_SILVER_5);
    load_rgb_table(C_SILVER_6, RGB_SILVER_6);
    load_rgb_table(C_SILVER_7, RGB_SILVER_7);
    load_rgb_table(C_SILVER_8, RGB_SILVER_8);
    load_rgb_table(C_SILVER_9, RGB_SILVER_9);
    load_rgb_table(C_PURPLE_0, RGB_PURPLE_0);
    load_rgb_table(C_PURPLE_1, RGB_PURPLE_1);
    load_rgb_table(C_PURPLE_2, RGB_PURPLE_2);
    load_rgb_table(C_PURPLE_3, RGB_PURPLE_3);
    load_rgb_table(C_PURPLE_4, RGB_PURPLE_4);
    load_rgb_table(C_LIME_0, RGB_LIME_0);
    load_rgb_table(C_LIME_1, RGB_LIME_1);
    load_rgb_table(C_LIME_2, RGB_LIME_2);
    load_rgb_table(C_LIME_3, RGB_LIME_3);
    load_rgb_table(C_LIME_4, RGB_LIME_4);
    load_rgb_table(C_TAN_0, RGB_TAN_0);
    load_rgb_table(C_TAN_1, RGB_TAN_1);
    load_rgb_table(C_TAN_2, RGB_TAN_2);
    load_rgb_table(C_TAN_3, RGB_TAN_3);
    load_rgb_table(C_TAN_4, RGB_TAN_4);
    load_rgb_table(C_ORANGE_0, RGB_ORANGE_0);
    load_rgb_table(C_ORANGE_1, RGB_ORANGE_1);
    load_rgb_table(C_ORANGE_2, RGB_ORANGE_2);
    load_rgb_table(C_ORANGE_3, RGB_ORANGE_3);
    load_rgb_table(C_ORANGE_4, RGB_ORANGE_4);

    if (in_cmode)
    {
	if (bits_cmode >= 6)
	{
	    ci_table[C_BLACK] = C_BLACK;
	    ci_table[C_WHITE] = C_WHITE;
	    ci_table[C_RED] = C_RED;
	    ci_table[C_DRED] = C_DRED;
	    ci_table[C_GREEN] = C_GREEN;
	    ci_table[C_BLUE] = C_BLUE;
	    ci_table[C_YELLOW] = C_YELLOW;
	    ci_table[C_ORANGE] = C_ORANGE;
	    ci_table[C_INST_BROWN] = C_INST_BROWN;
	    ci_table[C_HBLUE] = C_HBLUE;
	    ci_table[C_GREY] = C_GREY;
	    ci_table[C_MC_FLAME] = C_MC_FLAME;
	    ci_table[C_MC_TRAIL] = C_MC_TRAIL;
	    ci_table[C_DIRT] = C_DIRT;
	    ci_table[C_SWAMP] = C_SWAMP;
	    ci_table[C_SKY] = C_SKY;
	    ci_table[C_GREY_0] = C_GREY_0;
	    ci_table[C_GREY_1] = C_GREY_1;
	    ci_table[C_GREY_2] = C_GREY_2;
	    ci_table[C_GREY_3] = C_GREY_3;
	    ci_table[C_GREY_4] = C_GREY_4;
	    ci_table[C_GREY_5] = C_GREY_5;
	    ci_table[C_GREY_6] = C_GREY_6;
	    ci_table[C_GREY_7] = C_GREY_7;
	    ci_table[C_GREY_8] = C_GREY_8;
	    ci_table[C_GREY_9] = C_GREY_9;
	    ci_table[C_GREY_10] = C_GREY_10;
	    ci_table[C_GREY_11] = C_GREY_11;
	    ci_table[C_GREY_12] = C_GREY_12;
	    ci_table[C_SILVER_0] = C_SILVER_0;
	    ci_table[C_SILVER_1] = C_SILVER_1;
	    ci_table[C_SILVER_2] = C_SILVER_2;
	    ci_table[C_SILVER_3] = C_SILVER_3;
	    ci_table[C_SILVER_4] = C_SILVER_4;
	    ci_table[C_SILVER_5] = C_SILVER_5;
	    ci_table[C_SILVER_6] = C_SILVER_6;
	    ci_table[C_SILVER_7] = C_SILVER_7;
	    ci_table[C_SILVER_8] = C_SILVER_8;
	    ci_table[C_SILVER_9] = C_SILVER_9;
	    ci_table[C_PURPLE_0] = C_PURPLE_0;
	    ci_table[C_PURPLE_1] = C_PURPLE_1;
	    ci_table[C_PURPLE_2] = C_PURPLE_2;
	    ci_table[C_PURPLE_3] = C_PURPLE_3;
	    ci_table[C_PURPLE_4] = C_PURPLE_4;
	    ci_table[C_LIME_0] = C_LIME_0;
	    ci_table[C_LIME_1] = C_LIME_1;
	    ci_table[C_LIME_2] = C_LIME_2;
	    ci_table[C_LIME_3] = C_LIME_3;
	    ci_table[C_LIME_4] = C_LIME_4;
	    ci_table[C_TAN_0] = C_TAN_0;
	    ci_table[C_TAN_1] = C_TAN_1;
	    ci_table[C_TAN_2] = C_TAN_2;
	    ci_table[C_TAN_3] = C_TAN_3;
	    ci_table[C_TAN_4] = C_TAN_4;
	    ci_table[C_ORANGE_0] = C_ORANGE_0;
	    ci_table[C_ORANGE_1] = C_ORANGE_1;
	    ci_table[C_ORANGE_2] = C_ORANGE_2;
	    ci_table[C_ORANGE_3] = C_ORANGE_3;
	    ci_table[C_ORANGE_4] = C_ORANGE_4;
	}
	else /* use 4 bit color map */
	{
	    ci_table[C_BLACK] = SC_BLACK;
	    ci_table[C_WHITE] = SC_WHITE;
	    ci_table[C_RED] = SC_RED;
	    ci_table[C_DRED] = SC_BLACK;
	    ci_table[C_GREEN] = SC_GREEN;
	    ci_table[C_BLUE] = SC_BLUE;
	    ci_table[C_YELLOW] = SC_ORANGE;
	    ci_table[C_ORANGE] = SC_ORANGE;
	    ci_table[C_INST_BROWN] = SC_GREY;
	    ci_table[C_HBLUE] = SC_BLUE;
	    ci_table[C_GREY] = SC_GREY;
	    ci_table[C_MC_FLAME] = SC_GREY_0;
	    ci_table[C_MC_TRAIL] = SC_GREY_1;
	    ci_table[C_DIRT] = SC_DIRT;
	    ci_table[C_SWAMP] = SC_SWAMP;
	    ci_table[C_SKY] = SC_SKY;
	    ci_table[C_GREY_0] = SC_GREY_0;
	    ci_table[C_GREY_1] = SC_GREY_0;
	    ci_table[C_GREY_2] = SC_GREY_1;
	    ci_table[C_GREY_3] = SC_GREY_1;
	    ci_table[C_GREY_4] = SC_GREY_1;
	    ci_table[C_GREY_5] = SC_GREY_2;
	    ci_table[C_GREY_6] = SC_GREY_2;
	    ci_table[C_GREY_7] = SC_GREY_2;
	    ci_table[C_GREY_8] = SC_GREY_3;
	    ci_table[C_GREY_9] = SC_GREY_3;
	    ci_table[C_GREY_10] = SC_GREY_3;
	    ci_table[C_GREY_11] = SC_GREY_3;
	    ci_table[C_GREY_12] = SC_GREY_3;
	    ci_table[C_SILVER_0] = SC_GREY_0;
	    ci_table[C_SILVER_1] = SC_GREY_0;
	    ci_table[C_SILVER_2] = SC_GREY_1;
	    ci_table[C_SILVER_3] = SC_GREY_1;
	    ci_table[C_SILVER_4] = SC_GREY_1;
	    ci_table[C_SILVER_5] = SC_GREY_2;
	    ci_table[C_SILVER_6] = SC_GREY_2;
	    ci_table[C_SILVER_7] = SC_GREY_2;
	    ci_table[C_SILVER_8] = SC_GREY_3;
	    ci_table[C_SILVER_9] = SC_GREY_3;
	    ci_table[C_PURPLE_0] = SC_PURPLE_0;
	    ci_table[C_PURPLE_1] = SC_PURPLE_0;
	    ci_table[C_PURPLE_2] = SC_PURPLE_0;
	    ci_table[C_PURPLE_3] = SC_PURPLE_1;
	    ci_table[C_PURPLE_4] = SC_PURPLE_1;
	    ci_table[C_LIME_0] = SC_GREY_0;
	    ci_table[C_LIME_1] = SC_GREY_1;
	    ci_table[C_LIME_2] = SC_GREY_2;
	    ci_table[C_LIME_3] = SC_GREY_3;
	    ci_table[C_LIME_4] = SC_GREY_3;
	    ci_table[C_TAN_0] = SC_GREY_0;
	    ci_table[C_TAN_1] = SC_GREY_1;
	    ci_table[C_TAN_2] = SC_GREY_2;
	    ci_table[C_TAN_3] = SC_GREY_3;
	    ci_table[C_TAN_4] = SC_GREY_3;
	    ci_table[C_ORANGE_0] = SC_GREY_0;
	    ci_table[C_ORANGE_1] = SC_GREY_1;
	    ci_table[C_ORANGE_2] = SC_GREY_2;
	    ci_table[C_ORANGE_3] = SC_GREY_3;
	    ci_table[C_ORANGE_4] = SC_GREY_3;
	}
    }
    else
    {
	int i;

#if 1
	for (i = 0; i < 64; i++)
	    cpack_table[i] = rgb2cpack(GET_RGB(i));
#else
	cpack_table[C_BLACK] = rgb2cpack(RGB_BLACK);
	cpack_table[C_WHITE] = rgb2cpack(RGB_WHITE);
	cpack_table[C_RED] = rgb2cpack(RGB_RED);
	cpack_table[C_DRED] = rgb2cpack(RGB_DRED);
	cpack_table[C_GREEN] = rgb2cpack(RGB_GREEN);
	cpack_table[C_BLUE] = rgb2cpack(RGB_BLUE);
	cpack_table[C_YELLOW] = rgb2cpack(RGB_YELLOW);
	cpack_table[C_ORANGE] = rgb2cpack(RGB_ORANGE);
	cpack_table[C_INST_BROWN] = rgb2cpack(RGB_INST_BROWN);
	cpack_table[C_HBLUE] = rgb2cpack(RGB_HBLUE);
	cpack_table[C_GREY] = rgb2cpack(RGB_GREY);
	cpack_table[C_MC_FLAME] = rgb2cpack(RGB_MC_FLAME);
	cpack_table[C_MC_TRAIL] = rgb2cpack(RGB_MC_TRAIL);
	cpack_table[C_DIRT] = rgb2cpack(RGB_DIRT);
	cpack_table[C_SWAMP] = rgb2cpack(RGB_SWAMP);
	cpack_table[C_SKY] = rgb2cpack(RGB_SKY);
	cpack_table[C_GREY_0] = rgb2cpack(RGB_GREY_0);
	cpack_table[C_GREY_1] = rgb2cpack(RGB_GREY_1);
	cpack_table[C_GREY_2] = rgb2cpack(RGB_GREY_2);
	cpack_table[C_GREY_3] = rgb2cpack(RGB_GREY_3);
	cpack_table[C_GREY_4] = rgb2cpack(RGB_GREY_4);
	cpack_table[C_GREY_5] = rgb2cpack(RGB_GREY_5);
	cpack_table[C_GREY_6] = rgb2cpack(RGB_GREY_6);
	cpack_table[C_GREY_7] = rgb2cpack(RGB_GREY_7);
	cpack_table[C_GREY_8] = rgb2cpack(RGB_GREY_8);
	cpack_table[C_GREY_9] = rgb2cpack(RGB_GREY_9);
	cpack_table[C_GREY_10] = rgb2cpack(RGB_GREY_10);
	cpack_table[C_GREY_11] = rgb2cpack(RGB_GREY_11);
	cpack_table[C_GREY_12] = rgb2cpack(RGB_GREY_12);
	cpack_table[C_SILVER_0] = rgb2cpack(RGB_SILVER_0);
	cpack_table[C_SILVER_1] = rgb2cpack(RGB_SILVER_1);
	cpack_table[C_SILVER_2] = rgb2cpack(RGB_SILVER_2);
	cpack_table[C_SILVER_3] = rgb2cpack(RGB_SILVER_3);
	cpack_table[C_SILVER_4] = rgb2cpack(RGB_SILVER_4);
	cpack_table[C_SILVER_5] = rgb2cpack(RGB_SILVER_5);
	cpack_table[C_SILVER_6] = rgb2cpack(RGB_SILVER_6);
	cpack_table[C_SILVER_7] = rgb2cpack(RGB_SILVER_7);
	cpack_table[C_SILVER_8] = rgb2cpack(RGB_SILVER_8);
	cpack_table[C_SILVER_9] = rgb2cpack(RGB_SILVER_9);
	cpack_table[C_PURPLE_0] = rgb2cpack(RGB_PURPLE_0);
	cpack_table[C_PURPLE_1] = rgb2cpack(RGB_PURPLE_1);
	cpack_table[C_PURPLE_2] = rgb2cpack(RGB_PURPLE_2);
	cpack_table[C_PURPLE_3] = rgb2cpack(RGB_PURPLE_3);
	cpack_table[C_PURPLE_4] = rgb2cpack(RGB_PURPLE_4);
	cpack_table[C_LIME_0] = rgb2cpack(RGB_LIME_0);
	cpack_table[C_LIME_1] = rgb2cpack(RGB_LIME_1);
	cpack_table[C_LIME_2] = rgb2cpack(RGB_LIME_2);
	cpack_table[C_LIME_3] = rgb2cpack(RGB_LIME_3);
	cpack_table[C_LIME_4] = rgb2cpack(RGB_LIME_4);
	cpack_table[C_TAN_0] = rgb2cpack(RGB_TAN_0);
	cpack_table[C_TAN_1] = rgb2cpack(RGB_TAN_1);
	cpack_table[C_TAN_2] = rgb2cpack(RGB_TAN_2);
	cpack_table[C_TAN_3] = rgb2cpack(RGB_TAN_3);
	cpack_table[C_TAN_4] = rgb2cpack(RGB_TAN_4);
	cpack_table[C_ORANGE_0] = rgb2cpack(RGB_ORANGE_0);
	cpack_table[C_ORANGE_1] = rgb2cpack(RGB_ORANGE_1);
	cpack_table[C_ORANGE_2] = rgb2cpack(RGB_ORANGE_2);
	cpack_table[C_ORANGE_3] = rgb2cpack(RGB_ORANGE_3);
	cpack_table[C_ORANGE_4] = rgb2cpack(RGB_ORANGE_4);
#endif
    }
}


void init_normal_colormap(float div)
{
    static old_div = -1;

    if (div == old_div)
	return;

    if (bits_cmode >= 6)
    {
	mapcolor(C_BLACK,	RGB_BLACK);
	mapcolor(C_WHITE,	RGB_WHITE);
	mapcolor(C_RED,		RGB_RED);
	mapcolor(C_DRED,	RGB_DRED);
	mapcolor(C_GREEN,	RGB_GREEN);
	mapcolor(C_BLUE,	RGB_BLUE);
	mapcolor(C_YELLOW,	RGB_YELLOW);
	mapcolor(C_ORANGE,	RGB_ORANGE);
	mapcolor(C_INST_BROWN,	RGB_INST_BROWN);
	mapcolor(C_HBLUE,	RGB_HBLUE);
	mapcolor(C_GREY,	RGB_GREY);
	mapcolor(C_MC_FLAME,	ADD_RGB(C_MC_FLAME, C_MC_TRAIL, div));
	mapcolor(C_MC_TRAIL,	SCALE_RGB(C_MC_TRAIL, div));
	mapcolor(C_DIRT,	SCALE_RGB(C_DIRT, div));
	mapcolor(C_SWAMP,	SCALE_RGB(C_SWAMP, div));
	mapcolor(C_SKY,		SCALE_RGB(C_SKY, div));
	mapcolor(C_GREY_0,	SCALE_RGB(C_GREY_0, div));
	mapcolor(C_GREY_1,	SCALE_RGB(C_GREY_1, div));
	mapcolor(C_GREY_2,	SCALE_RGB(C_GREY_2, div));
	mapcolor(C_GREY_3,	SCALE_RGB(C_GREY_3, div));
	mapcolor(C_GREY_4,	SCALE_RGB(C_GREY_4, div));
	mapcolor(C_GREY_5,	SCALE_RGB(C_GREY_5, div));
	mapcolor(C_GREY_6,	SCALE_RGB(C_GREY_6, div));
	mapcolor(C_GREY_7,	SCALE_RGB(C_GREY_7, div));
	mapcolor(C_GREY_8,	SCALE_RGB(C_GREY_8, div));
	mapcolor(C_GREY_9,	SCALE_RGB(C_GREY_9, div));
	mapcolor(C_GREY_10,	SCALE_RGB(C_GREY_10, div));
	mapcolor(C_GREY_11,	SCALE_RGB(C_GREY_11, div));
	mapcolor(C_GREY_12,	SCALE_RGB(C_GREY_12, div));
	mapcolor(C_SILVER_0,	SCALE_RGB(C_SILVER_0, div));
	mapcolor(C_SILVER_1,	SCALE_RGB(C_SILVER_1, div));
	mapcolor(C_SILVER_2,	SCALE_RGB(C_SILVER_2, div));
	mapcolor(C_SILVER_3,	SCALE_RGB(C_SILVER_3, div));
	mapcolor(C_SILVER_4,	SCALE_RGB(C_SILVER_4, div));
	mapcolor(C_SILVER_5,	SCALE_RGB(C_SILVER_5, div));
	mapcolor(C_SILVER_6,	SCALE_RGB(C_SILVER_6, div));
	mapcolor(C_SILVER_7,	SCALE_RGB(C_SILVER_7, div));
	mapcolor(C_SILVER_8,	SCALE_RGB(C_SILVER_8, div));
	mapcolor(C_SILVER_9,	SCALE_RGB(C_SILVER_9, div));
	mapcolor(C_PURPLE_0,	SCALE_RGB(C_PURPLE_0, div));
	mapcolor(C_PURPLE_1,	SCALE_RGB(C_PURPLE_1, div));
	mapcolor(C_PURPLE_2,	SCALE_RGB(C_PURPLE_2, div));
	mapcolor(C_PURPLE_3,	SCALE_RGB(C_PURPLE_3, div));
	mapcolor(C_PURPLE_4,	SCALE_RGB(C_PURPLE_4, div));
	mapcolor(C_LIME_0,	SCALE_RGB(C_LIME_0, div));
	mapcolor(C_LIME_1,	SCALE_RGB(C_LIME_1, div));
	mapcolor(C_LIME_2,	SCALE_RGB(C_LIME_2, div));
	mapcolor(C_LIME_3,	SCALE_RGB(C_LIME_3, div));
	mapcolor(C_LIME_4,	SCALE_RGB(C_LIME_4, div));
	mapcolor(C_TAN_0,	SCALE_RGB(C_TAN_0, div));
	mapcolor(C_TAN_1,	SCALE_RGB(C_TAN_1, div));
	mapcolor(C_TAN_2,	SCALE_RGB(C_TAN_2, div));
	mapcolor(C_TAN_3,	SCALE_RGB(C_TAN_3, div));
	mapcolor(C_TAN_4,	SCALE_RGB(C_TAN_4, div));
	mapcolor(C_ORANGE_0,	SCALE_RGB(C_ORANGE_0, div));
	mapcolor(C_ORANGE_1,	SCALE_RGB(C_ORANGE_1, div));
	mapcolor(C_ORANGE_2,	SCALE_RGB(C_ORANGE_2, div));
	mapcolor(C_ORANGE_3,	SCALE_RGB(C_ORANGE_3, div));
	mapcolor(C_ORANGE_4,	SCALE_RGB(C_ORANGE_4, div));
    }
    else /* use 4 bit color map */
    {
	mapcolor(SC_BLACK,	RGB_BLACK);
	mapcolor(SC_WHITE,	RGB_WHITE);
	mapcolor(SC_RED,	RGB_RED);
	mapcolor(SC_GREEN,	RGB_GREEN);
	mapcolor(SC_BLUE,	RGB_BLUE);
	mapcolor(SC_ORANGE,	RGB_ORANGE);
	mapcolor(SC_GREY,	RGB_GREY);
	mapcolor(SC_DIRT,	SCALE_RGB(C_DIRT, div));
	mapcolor(SC_SWAMP,	SCALE_RGB(C_SWAMP, div));
	mapcolor(SC_SKY,	SCALE_RGB(C_SKY, div));
	mapcolor(SC_GREY_0,	SCALE_RGB(C_GREY_0, div));
	mapcolor(SC_GREY_1,	SCALE_RGB(C_GREY_2, div));
	mapcolor(SC_GREY_2,	SCALE_RGB(C_GREY_5, div));
	mapcolor(SC_GREY_3,	SCALE_RGB(C_GREY_8, div));
	mapcolor(SC_PURPLE_0,	SCALE_RGB(C_PURPLE_1, div));
	mapcolor(SC_PURPLE_1,	SCALE_RGB(C_PURPLE_3, div));
    }
}


void save_map()
{
    int i;

    drawmode(PUPDRAW);
    getmcolor(1, &pupmap[0][0], &pupmap[0][1], &pupmap[0][2]);
    getmcolor(2, &pupmap[1][0], &pupmap[1][1], &pupmap[1][2]);
    getmcolor(3, &pupmap[2][0], &pupmap[2][1], &pupmap[2][2]);
    drawmode(NORMALDRAW);

    if (in_cmode)
	for (i=0; i < (1<<bits_cmode); i++)
	    getmcolor(i, &normmap[i][0], &normmap[i][1], &normmap[i][2]);
}


void restore_map()
{
    int i;

    drawmode(PUPDRAW);
    mapcolor(1, pupmap[0][0], pupmap[0][1], pupmap[0][2]);
    mapcolor(2, pupmap[1][0], pupmap[1][1], pupmap[1][2]);
    mapcolor(3, pupmap[2][0], pupmap[2][1], pupmap[2][2]);
    drawmode(NORMALDRAW);

    if (in_cmode)
    {
	glcompat(GLC_SLOWMAPCOLORS, 1);
	for (i=0; i < (1<<bits_cmode); i++)
	    mapcolor(i, normmap[i][0], normmap[i][1], normmap[i][2]);
    }
}


unsigned long rgb2cpack(short r, short g, short b)
{
    return((0xff000000) | (b << 16) | (g <<  8) | (r));
}


void load_rgb_table(int i, short r, short g, short b)
{
    rgb_table[i][0] = r;
    rgb_table[i][1] = g;
    rgb_table[i][2] = b;
}

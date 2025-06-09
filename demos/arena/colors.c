#include <stdio.h>
#include <stdlib.h>
#include <gl.h>
#include "arena.h"

short smap[1024][3];

Pattern16 halftone = {0x5555, 0xAAAA, 0x5555, 0xAAAA, 0x5555, 0xAAAA,
		    0x5555, 0xAAAA, 0x5555, 0xAAAA, 0x5555, 0xAAAA,
		    0x5555, 0xAAAA, 0x5555, 0xAAAA};

int MASK_HUD;
int HUD_MASK;
int HUD_Y_MASK;

int HUD_GREEN;
int HUD_YELLOW;
int HUD_BLACK;
int HUD_RED;
int HUD_BLUE;

int BLUE1;
int BLUE2;
int GREEN1;
int GREEN2;

int LGRAY;
int MGRAY;
int DGRAY;

int SKY;

int bitplanes;

set_color_table()
{
    int i;

    /*
     *  patterns
     */
    defpattern(HALFTONE, 16, halftone);

    bitplanes = getplanes();
    
    if (bitplanes < 7)
    {
	BLUE1		= 8;
	BLUE2		= 9;
	GREEN1		= 10;
	GREEN2		= 11;
	LGRAY		= 12;
	MGRAY		= 13;
	DGRAY		= 14;
	SKY		= 15;
	HUD_GREEN	= GREEN;
	HUD_YELLOW	= YELLOW;
	HUD_BLACK	= BLACK;
	HUD_RED		= RED;
	HUD_BLUE	= BLUE;

	mapcolor(HUD_GREEN,    0, 255,   0);
	mapcolor(HUD_YELLOW, 255, 255,   0);
	mapcolor(HUD_BLACK,    0,   0,   0);
	mapcolor(HUD_RED,    255,   0,   0);
	mapcolor(HUD_BLUE,     0,   0, 255);
    }
    else
    {
	MASK_HUD	= 0x00f;	/* 0000 1111 */
	HUD_MASK	= 0x060;	/* 0110 0000 */
	HUD_Y_MASK	= 0x010;	/* 0001 0000 */

	HUD_YELLOW	= 0x010;	/* x001 xxxx */
	HUD_BLACK	= 0x020;	/* x01x xxxx */
	HUD_RED		= 0x040;	/* x10x xxxx */
	HUD_BLUE	= 0x060;	/* x11x xxxx */

	BLUE1	= 8;
	BLUE2	= 9;
	GREEN1	= 10;
	GREEN2	= 11;

	LGRAY	= 12;
	MGRAY	= 13;
	DGRAY	= 14;

	SKY	= 15;

	HUD_GREEN = GREEN;

	/*
	 * hud colors
	 */
	for(i=16; i < 128; i++)
	    switch(i >> 4)
	    {
		case 1:
		    mapcolor(i, 255, 255, 0);	/* HUD_YELLOW */
		    break;
		case 2:
		case 3:
		    mapcolor(i, 0, 0, 0);		/* HUD_BLACK */
		    break;
		case 4:
		case 5:
		    mapcolor(i, 255, 0, 0);		/* HUD_RED */
		    break;
		case 6:
		case 7:
		    mapcolor(i, 0, 0, 255);		/* HUD_BLUE */
		    break;
		default:
		    break;
	    }
    }

    /*
     * mechs colors
     */
    mapcolor(BLUE1,     32, 105, 153);
    mapcolor(BLUE2,     74,   0, 101);
    mapcolor(GREEN1,   107, 133,   0);
    mapcolor(GREEN2,    83,  68,   0);
    mapcolor(LGRAY,    190, 185, 185);
    mapcolor(MGRAY,    155, 150, 150);
    mapcolor(DGRAY,     70,  70,  70);
    mapcolor(SKY,       30, 210, 210);
}


save_map()
{
    int i;

    for (i = 0; i < 128; i++)
	getmcolor(i, &smap[i][0], &smap[i][1], &smap[i][2]);
}


restore_map()
{
    int i;

    for (i = 0; i < 128; i++)
	mapcolor(i, smap[i][0], smap[i][1], smap[i][2]);
}


/*****************************************************************
    Panel Library/Electropaint Copyright (c) 1986 David A. Tristram.
    Electropaint (TM) is a Registered U.S. Trademark of Tristram Visual.
    Tristram Visual can be contacted at www.tristram.com.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. 
*****************************************************************/
/*
 *	fade - 
 *		Make a background that fades windows out using a special
 *		pixel hack.
 *
 *				Paul Haeberli - 1985
 *
 */
#include "gl.h"
#include "device.h"

short tex[16];
int slow;

static int shifts[16] = {
    0, 2, 2, 0,
    1, 3, 3, 1,
    0, 2, 2, 0,
    1, 3, 3, 1,
};

static int wheres[16] = {
    0, 2, 0, 2,
    1, 3, 1, 3,
    1, 3, 1, 3,
    0, 2, 0, 2,
};

/* bkg-  the color you want to fade to
 * adv-  1 to advance to the next texture (the normal case)
 *	 0 to remain at the same one (for the back buffer, say)
 */

fadebackground(bkg, adv)
Colorindex bkg;
int adv;
{
static int state;

    int i, k;
    static int texno;
    register int shift, where, pattern;

    texno+=adv;
/*    texno=rand()%16;  band mode */

    while (texno>=16) texno -= 16; 
    for (i=0; i<16; i++)
      tex[i] = 0;
    shift = shifts[texno]; 	
    where = wheres[texno]; 	
    pattern = 0x1111<<shift;
    tex[where+0] = pattern;
    tex[where+4] = pattern;
    tex[where+8] = pattern;
    tex[where+12] = pattern;
    defpattern(2,16,tex);	/* define a pattern */
    color(bkg);
    setpattern(2);
    clear();
    setpattern(0);
}

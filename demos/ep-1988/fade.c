/*
 *	this software is in the public domain, it may not be resold
 *	or relicensed.  Do not remove this notice.  Send modifications
 *	and requests for most recent version to:
 *
 *	Author:  David A. Tristram
 *		 NASA  Ames Research Center
 *		 MS 258-5
 *		 Moffett Field, CA  94035
 *		 415-694-4404
 *		 dat@orville.nas.nasa.gov
 */
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

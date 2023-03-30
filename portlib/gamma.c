/*
 *	gamma - 
 *		Some support for gamma correction when reading and writing
 *    		color map entries.
 *
 *				Paul Haeberli - 1984
 *
 */
#include "math.h"
#include "port.h"
#include "gl.h"
#include "stdio.h"

FILE *configopen();

float gammacorrect();
float ungammacorrect();

static unsigned char rgamtable[256];
static unsigned char ggamtable[256];
static unsigned char bgamtable[256];
static unsigned char rungamtable[256];
static unsigned char gungamtable[256];
static unsigned char bungamtable[256];
static short firsted;

gammapcolor(index,r,g,b)
register int index,r,g,b;
float gamma;
{
	short i;

	if (!firsted) {
		readgamtables();
		firsted++;
	}
	r = rgamtable[r&0xff];
	g = ggamtable[g&0xff];
	b = bgamtable[b&0xff];
	mapcolor(index,r,g,b);
}

static makegamtables()
{
	register float gamval;
	register float val;
	register short i;
	int rbal, gbal, bbal; 

	gamval = getgamma();
	getcolorbal(&rbal,&gbal,&bbal);
	for (i=0; i<256; i++) {
		rgamtable[i] = 255*gammacorrect((rbal*i)/(255.0*255.0),gamval);
		ggamtable[i] = 255*gammacorrect((gbal*i)/(255.0*255.0),gamval);
		bgamtable[i] = 255*gammacorrect((bbal*i)/(255.0*255.0),gamval);
	}
	bzero(rungamtable,256);
	bzero(gungamtable,256);
	bzero(bungamtable,256);
	for (i=0; i<256; i++) {
		rungamtable[rgamtable[i]] = i;
		gungamtable[ggamtable[i]] = i;
		bungamtable[bgamtable[i]] = i;
	}
	fixup(rungamtable);
	fixup(gungamtable);
	fixup(bungamtable);
}

static fixup(cptr)
register unsigned char *cptr;
{
	register short i, lowval;

	for (i=256; i--; ) {
		if (*cptr == 0) 
			*cptr = lowval;
		else
			lowval = *cptr;
	}
}

gamgetmcolor(index,r,g,b)
int index;
unsigned short *r, *g, *b;
{
	static short firsted;
	unsigned short tr, tg, tb;

	if (!firsted) {
		readgamtables();
		firsted++;
	}
	getmcolor(index,&tr,&tg,&tb);
	*r = rungamtable[tr&0xff];
	*g = gungamtable[tg&0xff];
	*b = bungamtable[tb&0xff];
}

float gammacorrect( i, gamma)
float i, gamma;
{
    return pow(i,1.0/gamma);
}

float ungammacorrect( i, gamma)
float i, gamma;
{
    return pow(i,gamma);
}

newgamma()
{
    firsted = firsted = 0;
}

newgamtables()
{
    FILE *outf;

    if ((outf = configopen(".gamtables","w")) == 0) {
	fprintf(stderr,"couldn't open .gamtables\n");
	return;
    }
    makegamtables();
    fwrite(rgamtable,256,1,outf);
    fwrite(ggamtable,256,1,outf);
    fwrite(bgamtable,256,1,outf);
    fwrite(rungamtable,256,1,outf);
    fwrite(gungamtable,256,1,outf);
    fwrite(bungamtable,256,1,outf);
    fclose(outf);
}

readgamtables()
{
    FILE *inf;

    if ((inf = configopen(".gamtables","r")) == 0)  {
	newgamtables();
	if ((inf = configopen(".gamtables","r")) == 0)  {
	    fprintf(stderr,"couldn't open .gamtables\n");
	    return;
	}
    }
    fread(rgamtable,256,1,inf);
    fread(ggamtable,256,1,inf);
    fread(bgamtable,256,1,inf);
    fread(rungamtable,256,1,inf);
    fread(gungamtable,256,1,inf);
    fread(bungamtable,256,1,inf);
    fclose(inf);
}

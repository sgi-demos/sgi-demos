/*
 *	some support for gamma correction when reading and writing
 *	color map entries.
 *
 *			Paul Haeberli - 1984
 *
 */
#include "math.h"
#include "gl.h"
#include "democolors.h"
#include "port.h"

float gammacorrect();
float ungammacorrect();

static unsigned char gamtable[256];
static unsigned char ungamtable[256];
static short firsted;
static short unfirsted;

gammapcolor(index,r,g,b)
register int index,r,g,b;
/*float gamma; old typo accepted by compiler */
{
	short i;
	float gammaval;

	if(!firsted) {
		gammaval = getgamma();
		for(i=0; i<256; i++)
			gamtable[i] = (unsigned char)
			    (255*gammacorrect(i/255.0,gammaval));
		firsted++;
	}
	r = gamtable[r&0xff];
	g = gamtable[g&0xff];
	b = gamtable[b&0xff];
	mapcolor(index,r,g,b);
}

gamgetmcolor(index,r,g,b)
int index;
short *r, *g, *b;
{
	static short unfirsted;
	short i;
	float gammaval;
	short tr, tg, tb;

	if(!unfirsted) {
		gammaval = getgamma();
		for(i=0; i<256; i++)
			ungamtable[i] = (unsigned char)
			    (255*ungammacorrect(i/255.0,gammaval));
		unfirsted++;
	}
	getmcolor(index,&tr,&tg,&tb);
	*r = ungamtable[tr&0xff];
	*g = ungamtable[tg&0xff];
	*b = ungamtable[tb&0xff];
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
	unfirsted = firsted = 0;
}

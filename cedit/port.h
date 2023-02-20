/*
 *	Defines for colors used by window manager tools
 *
 *			Paul Haeberli - 1984
 *
 */
#ifndef PORTDEF
#define PORTDEF

#include "device.h"
#include "stdio.h"

#define MIN( a, b )	(((a) < (b)) ? (a) : (b))
#define MAX( a, b )	(((a) > (b)) ? (a) : (b))
#define ABS( a )	(((a) > 0) ? (a) : -(a))

float getgamma();

#define BACKGROUND1	9
#define BACKGROUND2	10

#define TITLETEXTIN	11
#define TITLETEXTOUT	12
#define INBORDER	13
#define OUTBORDER	14
#define HIOUTBORDER	15
#define HEADER		13

#define GREY( x )  	    (16+(x))		   /* shades of grey */
#define CMAP1( r , g, b )   (32+(r)+((g)<<2)+((b)<<4)) /* color map1 */
#define DESKTOP( x )	    (8+(x))		   /* desktop colors */

#define COLORSYS_RGB	1
#define COLORSYS_CMY	2
#define COLORSYS_HSV	3
#define COLORSYS_HLS	4
#define COLORSYS_YIQ	5

FILE *openipc();
FILE *closeipc();

#endif PORTDEF

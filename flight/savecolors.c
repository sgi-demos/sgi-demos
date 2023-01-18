/**************************************************************************
 *									  *
 *  Copyright (C)  1988 Silicon Graphics, Inc.	  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/


#include "gl.h"

struct {
	short r,g,b;
} savecolor[64];

savecolors()
{
	short i;

	for (i=0; i < 64; i++)
		getmcolor( i,&savecolor[i].r,&savecolor[i].g,&savecolor[i].b );
}

replacecolors()
{
	short i;

	for (i=0; i < 64; i++)
		mapcolor( i,savecolor[i].r,savecolor[i].g,savecolor[i].b );
}

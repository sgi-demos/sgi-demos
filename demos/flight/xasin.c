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

#include <gl.h>

#define then

extern int xatable1[], xatable2[], xatable3[];

Angle xasin (r)
    float r;
{
    register short neg;
    register int i;

    i = r * 1073741824.0;
    if (i < 0) {
	neg = 1;
	i = -i;
    }
    else neg = 0;

    if (i <= 929887697)		/* 0 - 60 degrees	*/
    then i = xatable1[(i+1048580) >> 21];

    else {
	i -= 1069655912;
	if (i < -20000)
	then i = xatable2[((-i)-20000) >> 18];	/* 60 - 85 degrees	*/
	else {
	    if (i > 0) 
	    then i = (i+1895) >> 13;
	    else i = 0;
	    if (i < 499)
	    then i = xatable3[i];	/* 85 - 90  degrees	*/
	    else i = 900;
	}
    }

    if (neg)
    then return (-i);
    else return (i);
}

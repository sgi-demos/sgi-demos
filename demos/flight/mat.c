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
gl_IdentifyMatrix(mat)
Matrix mat;
{
int i,j;

for (i = 0; i < 4; i++)
for (j = 0; j < 4; j++)
mat[i][j] = ((i == j) ? 1.0 : 0.0);
}

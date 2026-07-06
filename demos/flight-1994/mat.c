/*
 * Copyright 1990, 1991, 1992, 1993, 1994, Silicon Graphics, Inc.
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
 *  flight/mat.c $Revision: 1.1 $
 *
 *  matrix and vector math routines
 */
#include <stdio.h>
#include "flight.h"


void identify_matrix(Matrix mat)
{
    mat[0][0] = 1.0;
    mat[0][1] = 0.0;
    mat[0][2] = 0.0;
    mat[0][3] = 0.0;
    mat[1][0] = 0.0;
    mat[1][1] = 1.0;
    mat[1][2] = 0.0;
    mat[1][3] = 0.0;
    mat[2][0] = 0.0;
    mat[2][1] = 0.0;
    mat[2][2] = 1.0;
    mat[2][3] = 0.0;
    mat[3][0] = 0.0;
    mat[3][1] = 0.0;
    mat[3][2] = 0.0;
    mat[3][3] = 1.0;
}


/*
 *  Multiply mat1 * mat2 and return result in mat2
 */
void matrix_multiply(Matrix mat1, Matrix mat2)
{
    int i, j;
    float temp[4][4];

    for(i=0; i < 4; i++)
	for(j=0; j < 4; j++)
	    temp[j][i] = mat1[j][0]*mat2[0][i] + mat1[j][1]*mat2[1][i] +
			 mat1[j][2]*mat2[2][i] + mat1[j][3]*mat2[3][i];
    for(i=0; i < 4; i++)
	for(j=0; j < 4; j++)
	    mat2[j][i] = temp[j][i];
}


/*
 *  Multiply mat2 * mat1 and return result in mat2
 */
void matrix_post_multiply(Matrix mat1, Matrix mat2)
{
    int i, j;
    float temp[4][4];

    for(i=0; i < 4; i++)
	for(j=0; j < 4; j++)
	    temp[j][i] = mat2[j][0]*mat1[0][i] + mat2[j][1]*mat1[1][i] +
			 mat2[j][2]*mat1[2][i] + mat2[j][3]*mat1[3][i];
    for(i=0; i < 4; i++)
	for(j=0; j < 4; j++)
	    mat2[j][i] = temp[j][i];
}


/*
 *  Premultiply mat by rotation matrix. Return result in mat.
 */
void matrix_rotate(Matrix mat, int angle, char axis)
{
    float s, c;
    float tmp;

    gl_sincos(angle, &s, &c);

    if (axis == 'x' || axis == 'X')
    {
	tmp = c*mat[1][0] + s*mat[2][0];
	mat[2][0] = -s*mat[1][0] + c*mat[2][0];
	mat[1][0] = tmp;
	tmp = c*mat[1][1] + s*mat[2][1];
	mat[2][1] = -s*mat[1][1] + c*mat[2][1];
	mat[1][1] = tmp;
	tmp = c*mat[1][2] + s*mat[2][2];
	mat[2][2] = -s*mat[1][2] + c*mat[2][2];
	mat[1][2] = tmp;
	tmp = c*mat[1][3] + s*mat[2][3];
	mat[2][3] = -s*mat[1][3] + c*mat[2][3];
	mat[1][3] = tmp;
    }
    else if (axis == 'y' || axis == 'Y')
    {
	tmp = c*mat[0][0] + -s*mat[2][0];
	mat[2][0] = s*mat[0][0] + c*mat[2][0];
	mat[0][0] = tmp;
	tmp = c*mat[0][1] + -s*mat[2][1];
	mat[2][1] = s*mat[0][1] + c*mat[2][1];
	mat[0][1] = tmp;
	tmp = c*mat[0][2] + -s*mat[2][2];
	mat[2][2] = s*mat[0][2] + c*mat[2][2];
	mat[0][2] = tmp;
	tmp = c*mat[0][3] + -s*mat[2][3];
	mat[2][3] = s*mat[0][3] + c*mat[2][3];
	mat[0][3] = tmp;
    }
    else if (axis == 'z' || axis == 'Z')
    {
	tmp = c*mat[0][0] + s*mat[1][0];
	mat[1][0] = -s*mat[0][0] + c*mat[1][0];
	mat[0][0] = tmp;
	tmp = c*mat[0][1] + s*mat[1][1];
	mat[1][1] = -s*mat[0][1] + c*mat[1][1];
	mat[0][1] = tmp;
	tmp = c*mat[0][2] + s*mat[1][2];
	mat[1][2] = -s*mat[0][2] + c*mat[1][2];
	mat[0][2] = tmp;
	tmp = c*mat[0][3] + s*mat[1][3];
	mat[1][3] = -s*mat[0][3] + c*mat[1][3];
	mat[0][3] = tmp;
    }
}


/*
 *  Postmultiply mat by rotation matrix. Return result in mat.
 */
void matrix_post_rotate(Matrix mat, int angle, char axis)
{
    float s, c;
    float tmp;

    gl_sincos(angle, &s, &c);

    if (axis == 'x' || axis == 'X')
    {
	tmp = c*mat[0][1] + -s*mat[0][2];
	mat[0][2] = s*mat[0][1] + c*mat[0][2];
	mat[0][1] = tmp;
	tmp = c*mat[1][1] + -s*mat[1][2];
	mat[1][2] = s*mat[1][1] + c*mat[1][2];
	mat[1][1] = tmp;
	tmp = c*mat[2][1] + -s*mat[2][2];
	mat[2][2] = s*mat[2][1] + c*mat[2][2];
	mat[2][1] = tmp;
	tmp = c*mat[3][1] + -s*mat[3][2];
	mat[3][2] = s*mat[3][1] + c*mat[3][2];
	mat[3][1] = tmp;
    }
    else if (axis == 'y' || axis == 'Y')
    {
	tmp = c*mat[0][0] + s*mat[0][2];
	mat[0][2] = -s*mat[0][0] + c*mat[0][2];
	mat[0][0] = tmp;
	tmp = c*mat[1][0] + s*mat[1][2];
	mat[1][2] = -s*mat[1][0] + c*mat[1][2];
	mat[1][0] = tmp;
	tmp = c*mat[2][0] + s*mat[2][2];
	mat[2][2] = -s*mat[2][0] + c*mat[2][2];
	mat[2][0] = tmp;
	tmp = c*mat[3][0] + s*mat[3][2];
	mat[3][2] = -s*mat[3][0] + c*mat[3][2];
	mat[3][0] = tmp;
    }
    else if (axis == 'z' || axis == 'Z')
    {
	tmp = c*mat[0][0] + -s*mat[0][1];
	mat[0][1] = s*mat[0][0] + c*mat[0][1];
	mat[0][0] = tmp;
	tmp = c*mat[1][0] + -s*mat[1][1];
	mat[1][1] = s*mat[1][0] + c*mat[1][1];
	mat[1][0] = tmp;
	tmp = c*mat[2][0] + -s*mat[2][1];
	mat[2][1] = s*mat[2][0] + c*mat[2][1];
	mat[2][0] = tmp;
	tmp = c*mat[3][0] + -s*mat[3][1];
	mat[3][1] = s*mat[3][0] + c*mat[3][1];
	mat[3][0] = tmp;
    }
}


/*
 *  Premultiply mat by translation matrix.  Return result in mat.
 */
void matrix_translate(Matrix mat, float x, float y, float z)
{
    mat[3][0] = x*mat[0][0] + y*mat[1][0] + z*mat[2][0] + mat[3][0];
    mat[3][1] = x*mat[0][1] + y*mat[1][1] + z*mat[2][1] + mat[3][1];
    mat[3][2] = x*mat[0][2] + y*mat[1][2] + z*mat[2][2] + mat[3][2];
    mat[3][3] = x*mat[0][3] + y*mat[1][3] + z*mat[2][3] + mat[3][3];
}


/*
 *  multiply vector iv by a translation matrix mat.  Return result in ov.
 */
void mult_vec(Matrix mat, float iv[4], float ov[4])
{
    int i;

    for(i=0; i < 4; i++)
	ov[i] = iv[0]*mat[0][i] + iv[1]*mat[1][i] +
		iv[2]*mat[2][i] + iv[3]*mat[3][i];
}


/*
 *  print a matrix
 */
void matrix_print(Matrix mat)
{
    printf("mat = {{%f, %f, %f, %f}\n",
	   mat[0][0], mat[0][1], mat[0][2], mat[0][3]);
    printf("       {%f, %f, %f, %f}\n",
	   mat[1][0], mat[1][1], mat[1][2], mat[1][3]);
    printf("       {%f, %f, %f, %f}\n",
	   mat[2][0], mat[2][1], mat[2][2], mat[2][3]);
    printf("       {%f, %f, %f, %f}}\n",
	   mat[3][0], mat[3][1], mat[3][2], mat[3][3]);
}


/*
 *  find the position 'ov' that is 'len' away from 'iv0' in the direction of
 *  'iv1'.
 */
void vec_len(float *iv0, float *iv1, float len, float *ov)
{
    float x, y, z, delta;

    x = iv0[0] - iv1[0];
    y = iv0[1] - iv1[1];
    z = iv0[2] - iv1[2];

    delta = len / fsqrt(x*x + y*y + z*z);

    ov[0] = iv0[0] - x * delta;
    ov[1] = iv0[1] - y * delta;
    ov[2] = iv0[2] - z * delta;
}


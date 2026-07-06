/*
 * Copyright 1984-1991, 1992, 1993, 1994, Silicon Graphics, Inc.
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
 *  flight/density.c $Revision: 1.1 $
 */

float ro[75] =
{
    .0023081,		/* 1000 feet	*/
    .0022409,
    .0021752,
    .0021110,
    .0020482,		/* 5000 feet	*/
    .0019869,
    .0019270,
    .0018685,
    .0018113,
    .0017556,		/* 10000 feet	*/
    .0017011,
    .0016480,
    .0015961,
    .0015455,
    .0014962,		/* 15000 feet	*/
    .0014480,
    .0014011,
    .0013553,
    .0013107,
    .0012673,		/* 20000 feet	*/
    .0012249,
    .0011836,
    .0011435,
    .0011043,
    .0010663,		/* 25000 feet	*/
    .0010292,
    .00099311,
    .00095801,
    .00092387,
    .00089068,		/* 30000 feet	*/
    .00085841,
    .00082704,
    .00079656,
    .00076696,
    .00073820,		/* 35000 feet	*/
    .00071028,
    .00067800,
    .00064629,
    .00061608,
    .00058727,		/* 40000 feet	*/
    .00055982,
    .00053365,
    .00050871,
    .00048493,
    .00046227,		/* 45000 feet	*/
    .00044067,
    .00042008,
    .00040045,
    .00038175,
    .00036391,		/* 50000 feet	*/
    .00034692,
    .00033072,
    .00031527,
    .00030055,
    .00028652,		/* 55000 feet	*/
    .00027314,
    .00026039,
    .00024824,
    .00023665,
    .00022561,		/* 60000 feet	*/
    .00021508,
    .00020505,
    .00019548,
    .00018336,
    .00017767,		/* 65000 feet	*/
    .00016938,
    .00016148,
    .00015395,
    .00014678,
    .00013993,		/* 70000 feet	*/
    .00013341,
    .00012719,
    .00012126,
    .00011561,
    .00011022,		/* 75000 feet	*/
};

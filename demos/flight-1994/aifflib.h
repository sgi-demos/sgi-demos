/*
 * Copyright 1992, 1993, 1994, Silicon Graphics, Inc.
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
#ifndef __AIFFLIB_H
#define	__AIFFLIB_H

#define	AIFF_NOMEM		-1	/* too many files open */
#define	AIFF_OPENFAILURE	-2	/* can't open a file (check errno) */
#define	AIFF_BADFD		-3	/* bad file descriptor */
#define	AIFF_BADDATASIZE	-4	/* AIFF file has invalid data size */
#define	AIFF_BADHEADER		-5	/* AIFF file has a bad header */
#define	AIFF_NOTAIFF		-6	/* doesn't appear to be AIFF file */
#define	AIFF_NOFORMCHUNK	-7	/* can't find the FORM header */
#define	AIFF_BADCHUNK		-8	/* file is corrupt */
#define	AIFF_WRITEFAILURE	-9	/* can't write to file */
#define	AIFF_PARAMSFIXED	-10	/* can't change audio parameters */
#define	AIFF_BADCHANNELS	-11	/* unsupported number of channels */
#define	AIFF_BADWIDTH		-12	/* unsupported sample width (bits) */
#define	AIFF_BADRATE		-13	/* unsupported sample rate */

#ifdef __cplusplus
extern "C" {
#endif

typedef	int	AIFFfile;

/* all the functions returning int return -1 on error and set AIFFerrno */

AIFFfile	AIFFopen(const char* filename, const char* dir);
int	AIFFclose(AIFFfile fd);

/* accepts and returns number of samples not bytes */
int	AIFFwrite(AIFFfile fd, const void* buf, unsigned nsamp);
int	AIFFread(AIFFfile fd, void* buf, unsigned nsamp);
int	AIFFgetlength(AIFFfile fd);

int	AIFFgetchannels(AIFFfile fd);	/* returns 1 or 2 */
int	AIFFgetwidth(AIFFfile fd);	/* returns 8, 16, or 24 */
int	AIFFgetrate(AIFFfile fd);	/* returns 48000, 44100, 32000, etc. */
int	AIFFsetchannels(AIFFfile fd, int channels);	/* takes 1 or 2 */
int	AIFFsetwidth(AIFFfile fd, int width);	/* takes 8, 16, or 24 */
int	AIFFsetrate(AIFFfile fd, int rate);	/* takes 48000, 44100, etc. */

/*
 * functions to convert AL defines (AL_RATE_48000, AL_STEREO, etc.) to
 * real numbers (48000, 2, etc.)
 */
int	CONVERTchannelstoAL(int nchannels);
int	CONVERTwidthtoAL(int width);
int	CONVERTratetoAL(int rate);
int	CONVERTALtochannels(int ALnchannels);
int	CONVERTALtowidth(int ALwidth);
int	CONVERTALtorate(int ALrate);

extern int	AIFFerrno;

void	AIFFerror(const char *s);
char*	AIFFstrerror(int err);

#ifdef __cplusplus
}
#endif

#endif


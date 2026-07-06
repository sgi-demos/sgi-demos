/*
 * Copyright 1991, 1992, 1993, 1994, Silicon Graphics, Inc.
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
 * aifflib.c $Revision: 1.1 $
 *
 *	A library for reading and writing AIFF files
 *
 *		Chris Schoeneman	- 1991
 *		(borrowed heavily from playaiff and recordaiff)
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <audio.h>
#include "aifflib.h"


/*
 *  AIFF file typedef's and defines
 */
typedef struct
{
    long samprate;
    long nchannels;
    long sampwidth;
} audio_params_t;

typedef struct
{
    char id[4];
    long size;
} chunk_header_t;

#define CHUNK_ID     4
#define CHUNK_HEADER 8

typedef struct
{
    chunk_header_t header;
    int file_position;	/* not in AIFF file */
    char type[4];	/* should contain 'AIFF' for any audio IFF file */
} form_chunk_t;

#define FORM_CHUNK      12	/* including the header */
#define FORM_CHUNK_DATA 4

#define COMM_CHUNK      26	/* including the header */
#define COMM_CHUNK_DATA 18

typedef struct
{
    chunk_header_t header;
    int file_position;		/* not in AIFF file */
    short nchannels;
    unsigned long nsampframes;
    short sampwidth;
    long samprate;		/* not in AIFF file */
} comm_chunk_t;


#define SSND_CHUNK      16	/* including the header */
#define SSND_CHUNK_DATA 8

typedef struct
{
    chunk_header_t header;
    unsigned long offset;
    unsigned long blocksize;

    long file_position;	/* not in AIFF file */
    long sample_bytes;	/* not in AIFF file */
} ssnd_chunk_t;
/*
 *  end of AIFF typedef's and defines
 */

#define	MAXFILES	20

enum { FORM = 0, COMM = 1, SSND = 2};

#define	DEFAULT_CHANNELS	2
#define	DEFAULT_WIDTH		16
#define	DEFAULT_RATE		48000

static int		busy[MAXFILES],
			ssnd_remaining[MAXFILES],
			files = -1;
static long		writepos[MAXFILES][3];
static FILE*		aifffd[MAXFILES];
static audio_params_t	audioparams[MAXFILES];

int		AIFFerrno;
static char	*AIFFerrstr[]={
			"",
			"too many open files",
			"cannot open file",
			"invalid file id",
			"invalid data size",
			"invalid header",
			"not an AIFF file",
			"no FORM header",
			"invalid chunk",
			"write failure",
			"audio parameters are fixed",
			"unsupported number of channels",
			"unsupported sample width",
			"unsupported sample rate"};

static int	widthtobytes(int width);
static double	ConvertFromIeeeExtended(char*);
static void	ConvertToIeeeExtended(double, char*);

/*************************************************************************
 **	routines to read and write the AIFF format chunks		**
 *************************************************************************/
/*
 *  convert bytes in big endian order to a short
 */
static short	align_short(char* buf)
{
    int i;
    union { unsigned char b[sizeof(short)]; short s; } align_short;

    for (i = 0; i < sizeof(short); i++)
	align_short.b[i] = *buf++;
    return align_short.s;
}


/*
 *  convert bytes in big endian order to a long
 */
static long	align_long(char* buf)
{
    int i;
    union { unsigned char b[sizeof(long)]; long l; } align_long;

    for (i = 0; i < sizeof(long); i++)
	align_long.b[i] = *buf++;
    return align_long.l;
}


/*
 *  convert short to bytes in big endian order
 */
static void short_align(char* buf, short s)
{
    int i;
    char *scan = (char*)&s;

    for (i = 0; i < sizeof(short); i++)
	*buf++ = *scan++;
}


/*
 *  convert long to bytes in big endian order
 */
static void long_align(char* buf, long l)
{
    int i;
    char *scan = (char*)&l;

    for (i = 0; i < sizeof(long); i++)
	*buf++ = *scan++;
}


static int skip_chunk(AIFFfile fd, chunk_header_t* chunk_header)
{
    fseek(aifffd[fd], chunk_header->size, SEEK_CUR);
}


static int read_chunk_header(AIFFfile fd, chunk_header_t *chunk_header)
{
    char buf[CHUNK_HEADER];
    int i;

    if ((i = fread(buf, 1, CHUNK_HEADER, aifffd[fd])) != CHUNK_HEADER)
	return i;

    for (i=0; i<4; i++)
	chunk_header->id[i] = buf[i];
    chunk_header->size = align_long(buf+4);

    return CHUNK_HEADER;
}


static int read_form_chunk(AIFFfile fd, chunk_header_t *chunk_header,
			   form_chunk_t *form_data)
{
    char buf[FORM_CHUNK_DATA];

    if (chunk_header->size < 0)
    {
	AIFFerrno = AIFF_BADDATASIZE;
	return -1;
    }
    else if (chunk_header->size == 0)
    {
	AIFFerrno = AIFF_BADDATASIZE;
	return -1;
    }

    if (fread(buf, 1, FORM_CHUNK_DATA, aifffd[fd]) != FORM_CHUNK_DATA)
    {
	AIFFerrno = AIFF_BADHEADER;
	return -1;
    }
    if (strncmp(buf, "AIFF", 4))
    {
	AIFFerrno = AIFF_NOTAIFF;
	return -1;
    }
    return 0;
}


static int read_comm_chunk(AIFFfile fd, chunk_header_t *chunk_header)
{
    int i;
    char buf[COMM_CHUNK_DATA+1];
    comm_chunk_t comm_data;

    if (fread(buf, 1, COMM_CHUNK_DATA, aifffd[fd]) != COMM_CHUNK_DATA)
    {
	AIFFerrno = AIFF_BADCHUNK;
	return -1;
    }

    comm_data.nchannels = align_short(buf);
    comm_data.nsampframes = align_long(buf+4);
    comm_data.sampwidth = align_short(buf+6);

    /*
     * the sample rate value from the common chunk is an 80-bit IEEE extended
     * floating point number:
     * [s bit] [15 exp bits (bias=16383)] [64 mant bits (leading 1 not hidden)]
     *
     * turns out we can just grab bytes 2 and 3 (if bytes numbered 0 ... 9)
     * and cast them as an integer: the integer value equals the sample rate
     */
    comm_data.samprate = (long)ConvertFromIeeeExtended(buf+8);

    audioparams[fd].samprate = comm_data.samprate;
    audioparams[fd].nchannels = comm_data.nchannels;
    audioparams[fd].sampwidth = comm_data.sampwidth;

    if (widthtobytes(audioparams[fd].sampwidth) == -1)
    {
	AIFFerrno = AIFF_BADWIDTH;
	audioparams[fd].sampwidth = DEFAULT_WIDTH;
	return -1;
    }
    return 0;
}


/*
 *  AIFFread calls this if there is no more sound data in the current
 *  SSND chunk.  It searches for the next block and sets the
 *  ssnd_remaining entry to the length of the block
 */
static void read_ssnd_chunk(AIFFfile fd)
{
    char buf[SSND_CHUNK_DATA];
    int i;
    chunk_header_t chunk_header;

    /*
     *  if no sound left, search for next SSND block
     *
     *  NOTE: all chunks have been read through and checked for
     *  validity, so we assume read_chunk_header either returns
     *  zero for end of file or CHUNK_HEADER for a good block
     */
    while (read_chunk_header(fd, &chunk_header) != 0)
    {
	if (!strncmp(chunk_header.id, "SSND", 4))
	{
	    fread(buf, 1, SSND_CHUNK_DATA, aifffd[fd]);
	    ssnd_remaining[fd] = chunk_header.size - 2*sizeof(long);
	    if (ssnd_remaining[fd] != 0)
		break;
	}
	else
	    skip_chunk(fd, &chunk_header);
    }
}


static int write_form_chunk(AIFFfile fd)
{
    char buf[FORM_CHUNK];
    int i;

    strncpy(buf, "FORM", 4);		/* form header id */
    for (i=0; i<sizeof(long); i++)	/* form header size  - do later */
	buf[i+4] = 0x00;
    strncpy(buf+4+sizeof(long), "AIFF", 4);

    writepos[fd][FORM] = ftell(aifffd[fd]);

    if (fwrite(buf, 1, FORM_CHUNK, aifffd[fd]) != FORM_CHUNK)
    {
	AIFFerrno = AIFF_WRITEFAILURE;
	return -1;
    }

    return 0;
}


static int write_comm_chunk(AIFFfile fd)
{
    char buf[COMM_CHUNK];
    int i;

    strncpy(buf, "COMM", 4);			/* chunk id */
    long_align(buf+4,COMM_CHUNK_DATA);		/* chunk data size */
    short_align(buf+4+sizeof(long),		/* number channels */
		audioparams[fd].nchannels);
    long_align(buf+4+sizeof(long)+sizeof(short),	/* nsample frames */
	       0L);
    short_align(buf+4+2*sizeof(long)+sizeof(short),	/* sample width */
		audioparams[fd].sampwidth);
    ConvertToIeeeExtended((double)audioparams[fd].samprate, /* sample rate */
			  buf + 4 + 2*sizeof(long) + 2*sizeof(short));

    writepos[fd][COMM] = ftell(aifffd[fd]);

    if (fwrite(buf, 1, COMM_CHUNK, aifffd[fd]) != COMM_CHUNK)
    {
	AIFFerrno = AIFF_WRITEFAILURE;
	return -1;
    }

    ssnd_remaining[fd] = 0;

    return 0;
}


static int write_ssnd_chunk(AIFFfile fd)
{
    char buf[SSND_CHUNK];
    int i;

    strncpy(buf, "SSND", 4);
    for (i=0; i<3*sizeof(long); i++)  /* chunk data size */
	buf[i+4] = 0x00;

    writepos[fd][SSND] = ftell(aifffd[fd]);

    if (fwrite(buf, 1, SSND_CHUNK, aifffd[fd]) != SSND_CHUNK)
    {
	AIFFerrno = AIFF_WRITEFAILURE;
	return -1;
    }

    return 0;
}


static int update_form_chunk(AIFFfile fd, long total_bytes)
{
    fseek(aifffd[fd], writepos[fd][FORM]+4, SEEK_SET);
    total_bytes -= CHUNK_HEADER;

    if (fwrite(&total_bytes, 1, sizeof(long), aifffd[fd]) != sizeof(long))
    {
	AIFFerrno = AIFF_WRITEFAILURE;
	return -1;
    }

    return 0;
}


static int update_comm_chunk(AIFFfile fd, long sample_frames)
{
    fseek(aifffd[fd], writepos[fd][COMM]+CHUNK_HEADER+sizeof(short), SEEK_SET);

    if (fwrite(&sample_frames, 1, sizeof(long), aifffd[fd]) != sizeof(long))
    {
	AIFFerrno = AIFF_WRITEFAILURE;
	return -1;
    }

    return 0;
}


static int update_ssnd_chunk(AIFFfile fd, long sample_bytes)
{
    fseek(aifffd[fd], writepos[fd][SSND] + CHUNK_ID, SEEK_SET);
    sample_bytes += SSND_CHUNK_DATA;

    if (fwrite(&sample_bytes, 1, sizeof(long), aifffd[fd]) != sizeof(long))
    {
	AIFFerrno = AIFF_WRITEFAILURE;
	return -1;
    }

    return 0;
}


static AIFFfile	myopen(const char* filename, const char* dir)
{
    int i;
    FILE* fd;

    /*
     *  find first available space in table
     */

    for (i = 0; i < MAXFILES; i++)
	if (!busy[i])
	    break;
    if (i == MAXFILES)
    {
	AIFFerrno = AIFF_NOMEM;
	return -1;
    }

    /*
     *  open file
     */

    fd = fopen(filename, dir);
    if (!fd)
    {
	AIFFerrno = AIFF_OPENFAILURE;
	return -1;
    }

    /*
     *  fill table entries
     */

    aifffd[i] = fd;
    busy[i] = *dir;
    files++;

    return (AIFFfile)i;
}


static int myclose(AIFFfile fd)
{
    busy[fd] = 0;
    files--;
    return fclose(aifffd[fd]);
}


AIFFfile	AIFFopen(const char* filename, const char* dir)
{
    AIFFfile fd;
    int n;
    chunk_header_t chunk_header;
    form_chunk_t form_data;

    fd = myopen(filename, dir);
    if (fd < 0)
	return fd;

    switch (dir[0])
    {
	case 'r':
	{
	    chunk_header_t chunk_header;
	    form_chunk_t form_data;
	    long past_header;

	    if (read_chunk_header(fd, &chunk_header) != CHUNK_HEADER)
	    {
		myclose(fd);
		AIFFerrno = AIFF_BADHEADER;
		return -1;
	    }

	    if (strncmp(chunk_header.id, "FORM", 4))	/* form container */
	    {
		AIFFerrno = AIFF_NOFORMCHUNK;
		myclose(fd);
		return -1;
	    }

	    if (read_form_chunk(fd, &chunk_header, &form_data) < 0)
	    {
		myclose(fd);
		return -1;
	    }

	    /*
	     *  remember where interesting stuff starts
	     */
	    past_header = ftell(aifffd[fd]);

	    /*
	     *  search for last COMM chunk
	     */
	    while ((n = read_chunk_header(fd, &chunk_header)) != 0)
	    {
		if (n == CHUNK_HEADER)
		{
		    if (!strncmp(chunk_header.id, "COMM", 4))
			read_comm_chunk(fd, &chunk_header);
		    else
			skip_chunk(fd, &chunk_header);
		}
		else
		{
		    myclose(fd);
		    AIFFerrno = AIFF_BADHEADER;
		    return -1;
		}
	    }

	    /*
	     *  set file pointer to beginning of interesting stuff
	     */
	    fseek(aifffd[fd], past_header, SEEK_SET);
	    ssnd_remaining[fd] = 0;
	    break;
	}
	case 'w':
	{
	    /*
	     *  write the form chunk
	     */
	    if (write_form_chunk(fd) < 0)
	    {
		myclose(fd);
		return -1;
	    }

	    /*
	     *  set ssnd_remaining to a bogus value as a flag to write the COMM
	     */
	    ssnd_remaining[fd] = -1;

	    /*
	     *  set default values for audio parameters
	     */
	    AIFFsetchannels(fd,0);
	    AIFFsetwidth(fd,0);
	    AIFFsetrate(fd,0);

	    break;
	}
    }

    return fd;
}


int AIFFclose(AIFFfile fd)
{
    if (fd < 0 || fd >= MAXFILES || !busy[fd])
    {
	AIFFerrno = AIFF_BADFD;
	return -1;
    }

    if (busy[fd] == 'w')
    {
	long total = ftell(aifffd[fd]);

	if (update_form_chunk(fd, total) < 0)
	{
	    myclose(fd);
	    return -1;
	}

	total -= FORM_CHUNK + COMM_CHUNK + SSND_CHUNK;
	if (update_comm_chunk(fd, total / AIFFgetchannels(fd) /
				  widthtobytes(AIFFgetwidth(fd))) < 0)
	{
	    myclose(fd);
	    return -1;
	}

	if (update_ssnd_chunk(fd, total) < 0)
	{
	    myclose(fd);
	    return -1;
	}
    }

    return myclose(fd);
}


int AIFFwrite(AIFFfile fd, const void* buf, unsigned nsamp)
{
    int bytes_written;
    unsigned nbyte;

    if (fd < 0 || fd >= MAXFILES || !busy[fd])
    {
	AIFFerrno = AIFF_BADFD;
	return -1;
    }

    /*
     *  write COMM and SSND block headers if necessary
     */

    if (ssnd_remaining[fd] == -1)
    {
	if (write_comm_chunk(fd) < 0)
	{
	    AIFFerrno = AIFF_WRITEFAILURE;
	    return -1;
	}
	if (write_ssnd_chunk(fd) < 0)
	{
	    AIFFerrno = AIFF_WRITEFAILURE;
	    return -1;
	}
    }

    /*
     *  convert number of samples to number of bytes
     */
    nbyte = nsamp * widthtobytes(audioparams[fd].sampwidth);

    bytes_written = fwrite(buf, 1, nbyte, aifffd[fd]);

    /*
     *  convert bytes to samples
     */
    return bytes_written / widthtobytes(audioparams[fd].sampwidth);
}


int AIFFread(AIFFfile fd, void* buf, unsigned nsamp)
{
    int bytes_read, nbyte;

    if (fd < 0 || fd >= MAXFILES || !busy[fd])
    {
	AIFFerrno = AIFF_BADFD;
	return -1;
    }

    /*
     *  skip to next SSND block if necessary
     */

    if (ssnd_remaining[fd] == 0)
	read_ssnd_chunk(fd);

    /*
     *  convert number samples to number bytes
     */
    nbyte = nsamp * widthtobytes(audioparams[fd].sampwidth);

    /*
     *  get samples
     */
    /*
     *  FIXME:  AIFFread should always attempt to fill the buffer
     *		even if has to read the next SSND block to
     *		do it (and the one after that, etc.)
     */
    if (ssnd_remaining[fd] < nbyte)
	bytes_read = fread(buf, 1, ssnd_remaining[fd], aifffd[fd]);
    else
	bytes_read = fread(buf, 1, nbyte, aifffd[fd]);
    ssnd_remaining[fd] -= bytes_read;

    /*
     *  convert bytes to samples
     */
    return bytes_read / widthtobytes(audioparams[fd].sampwidth);
}


int AIFFgetlength(AIFFfile fd)
{
    if (fd < 0 || fd >= MAXFILES || !busy[fd])
    {
	AIFFerrno = AIFF_BADFD;
	return -1;
    }

    /*
     *  skip to next SSND block if necessary
     */
    if (ssnd_remaining[fd] == 0)
	read_ssnd_chunk(fd);

    return ssnd_remaining[fd] / widthtobytes(audioparams[fd].sampwidth);
}


int AIFFgetchannels(AIFFfile fd)
{
    if (fd < 0 || fd >= MAXFILES || !busy[fd])
    {
	AIFFerrno = AIFF_BADFD;
	return -1;
    }

    return audioparams[fd].nchannels;
}


int AIFFgetwidth(AIFFfile fd)
{
    if (fd < 0 || fd >= MAXFILES || !busy[fd])
    {
	AIFFerrno = AIFF_BADFD;
	return -1;
    }

    return audioparams[fd].sampwidth;
}


int AIFFgetrate(AIFFfile fd)
{
    if (fd < 0 || fd >= MAXFILES || !busy[fd])
    {
	AIFFerrno = AIFF_BADFD;
	return -1;
    }

    return audioparams[fd].samprate;
}


int AIFFsetchannels(AIFFfile fd, int channels)
{
    if (fd < 0 || fd >= MAXFILES || !busy[fd])
    {
	AIFFerrno = AIFF_BADFD;
	return -1;
    }

    /*
     *  make sure file is write and we haven't written any sound yet
     */

    if (ssnd_remaining[fd] != -1)
    {
	AIFFerrno = AIFF_PARAMSFIXED;
	return -1;
    }

    if (channels == 0)
	channels = DEFAULT_CHANNELS;
    audioparams[fd].nchannels = channels;

    return 0;
}


int AIFFsetwidth(AIFFfile fd, int width)
{
    if (fd < 0 || fd >= MAXFILES || !busy[fd])
    {
	AIFFerrno = AIFF_BADFD;
	return -1;
    }

    /*
     *  make sure file is write and we haven't written any sound yet
     */

    if (ssnd_remaining[fd] != -1)
    {
	AIFFerrno = AIFF_PARAMSFIXED;
	return -1;
    }

    if (width == 0)
	width = DEFAULT_WIDTH;
    audioparams[fd].sampwidth = width;

    return 0;
}


int AIFFsetrate(AIFFfile fd, int rate)
{
    if (fd < 0 || fd >= MAXFILES || !busy[fd])
    {
	AIFFerrno = AIFF_BADFD;
	return -1;
    }

    /*
     *  make sure file is write and we haven't written any sound yet
     */

    if (ssnd_remaining[fd] != -1)
    {
	AIFFerrno = AIFF_PARAMSFIXED;
	return -1;
    }

    if (rate == 0)
	rate = DEFAULT_RATE;
    audioparams[fd].samprate = rate;

    return 0;
}


static int widthtobytes(int width)
{
    switch (width)
    {
	case  8: return 1;
	case 16: return 2;
	case 24: return 4;		/* FIXME: is this 3 or 4 */
	default: return -1;
    }
}


int CONVERTchannelstoAL(int channels)
{
    switch (channels)
    {
	case 1: return AL_MONO;
	case 2: return AL_STEREO;
	default: AIFFerrno = AIFF_BADCHANNELS; return -1;
    }
}


int CONVERTALtochannels(int ALchannels)
{
    switch (ALchannels)
    {
	case AL_MONO:   return 1;
	case AL_STEREO: return 2;
	default: AIFFerrno = AIFF_BADCHANNELS; return -1;
    }
}


int CONVERTwidthtoAL(int width)
{
    switch (width)
    {
	case  8: return AL_SAMPLE_8;
	case 16: return AL_SAMPLE_16;
	case 24: return AL_SAMPLE_24;
	default: AIFFerrno = AIFF_BADWIDTH; return -1;
    }
}


int CONVERTALtowidth(int ALwidth)
{
    switch (ALwidth)
    {
	case AL_SAMPLE_8:  return 8;
	case AL_SAMPLE_16: return 16;
	case AL_SAMPLE_24: return 24;
	default: AIFFerrno = AIFF_BADWIDTH; return -1;
    }
}


int CONVERTratetoAL(int rate)
{
    switch (rate)
    {
	case 48000: return AL_RATE_48000;
	case 44100: return AL_RATE_44100;
	case 32000: return AL_RATE_32000;
	case 22050: return AL_RATE_22050;
	case 16000: return AL_RATE_16000;
	case 11025: return AL_RATE_11025;
	case  8000: return AL_RATE_8000;
	default: AIFFerrno = AIFF_BADRATE; return -1;
    }
}


int CONVERTALtorate(int ALrate)
{
    switch (ALrate)
    {
	case AL_RATE_48000: return 48000;
	case AL_RATE_44100: return 44100;
	case AL_RATE_32000: return 32000;
	case AL_RATE_16000: return 16000;
	case AL_RATE_8000:  return 8000;
	default: AIFFerrno = AIFF_BADRATE; return -1;
    }
}


void	AIFFerror(const char* s)
{
    if (s && *s)
	fprintf(stderr,"%s: ",s);
    fprintf(stderr,"%s\n",AIFFerrstr[-AIFFerrno]);
    AIFFerrno = 0;
}


char*	AIFFstrerror(int err)
{
    return AIFFerrstr[-err];
}


/*
 * Copyright (C) 1988-1991 Apple Computer, Inc.
 * All rights reserved.
 *
 * Machine-independent I/O routines for IEEE floating-point numbers.
 *
 * NaN's and infinities are converted to HUGE_VAL or HUGE, which
 * happens to be infinity on IEEE machines.  Unfortunately, it is
 * impossible to preserve NaN's in a machine-independent way.
 * Infinities are, however, preserved on IEEE machines.
 *
 * These routines have been tested on the following machines:
 *    Apple Macintosh, MPW 3.1 C compiler
 *    Apple Macintosh, THINK C compiler
 *    Silicon Graphics IRIS, MIPS compiler
 *    Cray X/MP and Y/MP
 *    Digital Equipment VAX
 *
 *
 * Implemented by Malcolm Slaney and Ken Turkowski.
 *
 * Malcolm Slaney contributions during 1988-1990 include big- and little-
 * endian file I/O, conversion to and from Motorola's extended 80-bit
 * floating-point format, and conversions to and from IEEE single-
 * precision floating-point format.
 *
 * In 1991, Ken Turkowski implemented the conversions to and from
 * IEEE double-precision format, added more precision to the extended
 * conversions, and accommodated conversions involving +/- infinity,
 * NaN's, and denormalized numbers.
 */
#ifndef HUGE_VAL
#define HUGE_VAL HUGE
#endif

#define UnsignedToFloat(u)    \
     (((double)((long)(u - 2147483647L - 1))) + 2147483648.0)
#define FloatToUnsigned(f)  \
    ((unsigned long)(((long)(f - 2147483648.0)) + 2147483647L + 1))


/****************************************************************
 * Extended precision IEEE floating-point conversion routines.
 ****************************************************************/

static double	ConvertFromIeeeExtended(char *bytes)
{
    double    f;
    long    expon;
    unsigned long hiMant, loMant;

    expon = ((bytes[0] & 0x7F) << 8) | (bytes[1] & 0xFF);
    hiMant    =    ((unsigned long)(bytes[2] & 0xFF) << 24)
	    |    ((unsigned long)(bytes[3] & 0xFF) << 16)
	    |    ((unsigned long)(bytes[4] & 0xFF) << 8)
	    |    ((unsigned long)(bytes[5] & 0xFF));
    loMant    =    ((unsigned long)(bytes[6] & 0xFF) << 24)
	    |    ((unsigned long)(bytes[7] & 0xFF) << 16)
	    |    ((unsigned long)(bytes[8] & 0xFF) << 8)
	    |    ((unsigned long)(bytes[9] & 0xFF));

    if (expon == 0 && hiMant == 0 && loMant == 0)
    {
	f = 0;
    }
    else
    {
	if (expon == 0x7FFF)	/* Infinity or NaN */
	{
	    f = HUGE_VAL;
	}
	else
	{
	    expon -= 16383;
	    f  = ldexp(UnsignedToFloat(hiMant), expon-=31);
	    f += ldexp(UnsignedToFloat(loMant), expon-=32);
	}
    }

    if (bytes[0] & 0x80)
	return -f;
    else
	return f;
}


static void ConvertToIeeeExtended(double num, char *bytes)
{
    int sign;
    int expon;
    double fMant, fsMant;
    unsigned long hiMant, loMant;

    if (num < 0)
    {
	sign = 0x8000;
	num *= -1;
    }
    else
    {
	sign = 0;
    }

    if (num == 0)
    {
	expon = 0; hiMant = 0; loMant = 0;
    }
    else
    {
	fMant = frexp(num, &expon);
	if ((expon > 16384) || !(fMant < 1))	/* Infinity or NaN */
	{
	    expon = sign|0x7FFF;		/* infinity */
	    hiMant = 0;
	    loMant = 0;
	}
	else	/* Finite */
	{
	    expon += 16382;
	    if (expon < 0)	/* denormalized */
	    {
		fMant = ldexp(fMant, expon);
		expon = 0;
	    }
	    expon |= sign;
	    fMant = ldexp(fMant, 32);
	    fsMant = floor(fMant);
	    hiMant = FloatToUnsigned(fsMant);
	    fMant = ldexp(fMant - fsMant, 32);
	    fsMant = floor(fMant);
	    loMant = FloatToUnsigned(fsMant);
	}
    }

    bytes[0] = expon >> 8;
    bytes[1] = expon;
    bytes[2] = hiMant >> 24;
    bytes[3] = hiMant >> 16;
    bytes[4] = hiMant >> 8;
    bytes[5] = hiMant;
    bytes[6] = loMant >> 24;
    bytes[7] = loMant >> 16;
    bytes[8] = loMant >> 8;
    bytes[9] = loMant;
}


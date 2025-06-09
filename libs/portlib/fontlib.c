/*
 *	fontlib - 
 *		Define a few functions to read and write fonts.
 *
 *				Paul Haeberli - 1985
 */
#include "stdio.h"
#include "gl.h"

#define FONTMAGIC	4345

writefont(file,ht,nc,chars,nr,raster)
int file;
short ht, nc, nr;
Fontchar chars[];
short raster[];
{
    long magic = FONTMAGIC;

    lseek(file,0,0);
    write(file,&magic,sizeof(long));
    write(file,&magic,sizeof(long)); /* this is where length would go */
    write(file,&ht,sizeof(short));
    write(file,&nc,sizeof(short));
    write(file,&nr,sizeof(short));
    write(file,chars,nc*sizeof(Fontchar));
    write(file,raster,nr*sizeof(short));
}

readfont(file,ht,nc,chars,nr,raster)
int file;
short *ht, *nc, *nr;
Fontchar chars[];
short raster[];
{
    long magic;

    lseek(file,0,0);
    read(file,&magic,sizeof(long));
    if (magic != FONTMAGIC) {
	fprintf(stderr,"bad magic number in font file\n");	
	exit(1);
    }
    read(file,&magic,sizeof(long)); /* this is where length would go */
    read(file,ht,sizeof(short));
    read(file,nc,sizeof(short));
    read(file,nr,sizeof(short));
    read(file,chars,*nc*sizeof(Fontchar));
    read(file,raster,*nr*sizeof(short));
}

loadfont(filename,n)
char filename[];
short n;
{
    short ht, nc, nr;
    Fontchar *chars;
    short *raster;
    int file;

    if ((file = pathopen(filename,0)) < 0)
       return 0;
    chars = (Fontchar *)malloc(256*sizeof(Fontchar));
    raster = (short *)malloc(256*256);
    if (chars == 0 || raster == 0) {
	fprintf(stderr,"loadfont: malloc failed\n");	
	exit(1);
    }
    readfont(file,&ht,&nc,chars,&nr,raster);
    defrasterfont(n,ht,nc,chars,nr,raster);
    free(chars);
    free(raster);
    return 1;
}

pathopen(filename,mode)
char filename[];
int mode;
{
    int file;

    if ((file=open(filename,mode)) >= 0)
	return file;
    return -1;
}

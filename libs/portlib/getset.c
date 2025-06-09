/*
 *	getset - 
 *		Get and set values stored in ~/.desktop and ~/.gamma
 *
 *				Paul Haeberli - 1984
 *
 */
#include "stdio.h"
#include "port.h"
#include "gl.h"

FILE *configopen();

restorecolors()
{
    int i;
    FILE *colors;
    int index, r, g, b;

    if ((colors = configopen(".desktop","r")) == 0) {
	gammapcolor(8,0,0,0);
	gammapcolor(9,173,173,173);
	gammapcolor(10,135,145,157);
	gammapcolor(11,230,230,230);
	gammapcolor(12,40,40,40);
	gammapcolor(13,240,240,240);
	gammapcolor(14,0,0,0);
	gammapcolor(15,255,0,0);
	return;
    }
    while (!feof(colors)) {
	fscanf(colors,"%d %d %d %d\n",&index,&r,&g,&b);
	gammapcolor(index,r,g,b);
    }
    fclose(colors);
}

savecolors()
{
    FILE *colors;
    int index;
    unsigned short r, g, b;

    if ((colors = configopen(".desktop","w")) == 0) {
	fprintf(stderr,"couldn't open .desktop\n");
	return;
    }
    for (index=0; index<8; index++) {
	gamgetmcolor(DESKTOP(index),&r,&g,&b);
	fprintf(colors,"%d %d %d %d\n",DESKTOP(index),r,g,b);
    }
    gamgetmcolor(7,&r,&g,&b);
    fprintf(colors,"%d %d %d %d\n",7,r,g,b);
    gamgetmcolor(0,&r,&g,&b);
    fprintf(colors,"%d %d %d %d\n",0,r,g,b);
    fclose(colors);
}

float getgamma()
{
    FILE *gamfile;
    float gam;

    if ((gamfile = configopen(".gamma","r")) )  {
        if (fscanf(gamfile,"%f\n",&gam) == 1) {
	    fclose(gamfile);
	    return gam;
	} else 
	    fclose(gamfile);
    }
    return 2.2;
}

setgamma( gam )
float gam;
{
    FILE *gamfile;

    if ((gamfile = configopen(".gamma","w")) == 0) {
	fprintf(stderr,"couldn't open .gamma\n");
	return;
    }
    fprintf(gamfile,"%f\n",gam);
    fclose(gamfile);
    newgamtables();
}

getcolorbal(r,g,b)
unsigned int *r, *g, *b;
{
    FILE *cbfile;

    if ((cbfile = configopen(".cbal","r")) ) { 
        if (fscanf(cbfile,"%d %d %d\n",r,g,b) == 3) {
	    if (*r>255)
		*r = 255;	
	    if (*g>255)
		*g = 255;	
	    if (*b>255)
		*b = 255;	
            fclose(cbfile);
            return;
        } else 
            fclose(cbfile);
    }
    *r = 255;
    *g = 255;
    *b = 255;
    return;
}

setcolorbal(r,g,b)
int r, g, b;
{
    FILE *cbfile;

    if ((cbfile = configopen(".cbal","w")) == 0) {
	fprintf(stderr,"couldn't open .cbal\n");
	return;
    }
    fprintf(cbfile,"%d %d %d\n",r,g,b);
    fclose(cbfile);
    newgamtables();
}

FILE *configopen( name, mode )
char name[];
char mode[];
{
    char homepath[100];
    FILE *f;
    char *cptr;

    cptr = (char *)getenv("HOME");
    if (!cptr)
	return 0;
    strcpy(homepath,cptr);
    strcat(homepath,"/");
    strcat(homepath,name);
    return fopen(homepath,mode);
}

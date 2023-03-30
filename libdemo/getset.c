/*
 *	set and set values stored in ~/.desktop and ~/.gamma
 *
 *			Paul Haeberli - 1984
 *
 */
#include <stdlib.h>
#include <string.h>
#include "stdio.h"
#include "gl.h"
#include "democolors.h"
#include "port.h"

/*#define DESKTOP(x)	(x+8)*/

FILE *configopen();

restoredesktop()
{
	int i;
	FILE *desktop;
	int index, r, g, b;

	if( (desktop = configopen(".desktop","r")) == 0) {
		mapcolor(8,0,0,0);
		mapcolor(9,173,173,173);
		mapcolor(10,135,145,157);
		mapcolor(11,230,230,230);
		mapcolor(12,40,40,40);
		mapcolor(13,240,240,240);
		mapcolor(14,0,0,0);
		mapcolor(15,255,0,0);
		return 0;
	}
	while(!feof(desktop)) {
		fscanf(desktop,"%d %d %d %d\n",&index,&r,&g,&b);
		mapcolor(index,r,g,b);
	}
	fclose(desktop);
}

savedesktop()
{
	FILE *desktop;
	int index;
	short r, g, b;

	if( (desktop = configopen(".desktop","w")) == 0) {
		fprintf(stderr,"couldn't open .desktop\n");
		return 0;
	}
	for(index=0; index<8; index++) {
		getmcolor(DESKTOP(index),&r,&g,&b);
		fprintf(desktop,"%d %d %d %d\n",DESKTOP(index),r,g,b);
	}
	getmcolor(7,&r,&g,&b);
	fprintf(desktop,"%d %d %d %d\n",7,r,g,b);
	getmcolor(0,&r,&g,&b);
	fprintf(desktop,"%d %d %d %d\n",0,r,g,b);
	fclose(desktop);
}

float getgamma()
{
	FILE *gamfile;
	float gam;

	if( (gamfile = configopen(".gamma","r")) == 0)
		return 2.2;
	fscanf(gamfile,"%f\n",&gam);
	fclose(gamfile);
	return gam;
}

setgamma( gam )
float gam;
{
	FILE *gamfile;

	if( (gamfile = configopen(".gamma","w")) == 0) {
		fprintf(stderr,"couldn't open .gamma\n");
		return 0;
	}
	fprintf(gamfile,"%f\n",gam);
	fclose(gamfile);
}

FILE *configopen( name, mode )
char name[];
char mode[];
{
	char homepath[100];
	FILE *f;
	char *cptr;

	cptr = (char *)getenv("HOME");
	if(!cptr)
		return 0;
	strcpy(homepath,cptr);
	strcat(homepath,"/");
	strcat(homepath,name);
	return fopen(homepath,mode);
}

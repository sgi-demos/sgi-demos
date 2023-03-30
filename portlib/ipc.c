/*
 *	ipc - 
 *		This implements the basis of a simple, dynamic ipc 
 *		mechanism.  
 *
 *				Paul Haeberli - 1985
 */
#include "device.h"

static int outf = -1;
static int inf = -1;
static int curofileno = 0;
static int curifileno = 0;

#define CHANNO(x)	((x)/100)
#define OUTPORTNO(x)	(OUTPUT0+((x)%100))
#define VALNO(chan,port) ( ((chan)*100) + (port)-OUTPUT0 )

writeipc(outport,buf,cnt)
int outport;
char *buf;
int cnt;
{
    char fname[100];
    register int fileno;

    if (!ISOUTPUT(outport)) {
	 printf("writeipc bad output portno %d\n",outport);
	 return;
    }
    fileno = VALNO(inchanget(),outport);
    if (fileno != curofileno) {
	if (outf != -1)
	    close(outf);
        sprintf(fname,"/tmp/ipc%d",fileno);
        outf = creat(fname,0666); 
	curofileno = fileno;
    }
    lseek(outf,0,0);
    write(outf,buf,cnt);
    sigport(outport,fileno);
}

readipc(fileno,buf,cnt)
int fileno;
char *buf;
int cnt;
{
    char fname[100];

    if (fileno != curifileno) {
	if (inf != -1)
	    close(inf);
        sprintf(fname,"/tmp/ipc%d",fileno);
        inf = open(fname,2); 
	curifileno = fileno;
    }
    lseek(inf,0,0);
    read(inf,buf,cnt);
    replycon(CHANNO(fileno));
}

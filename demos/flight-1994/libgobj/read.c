/*
 * Copyright 1989, 1990, 1991, 1992, 1993, 1994, Silicon Graphics, Inc.
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

#include "gobj.h"

#include <gl.h>
#include <stdio.h>
#include <fcntl.h>

static char ifname[80];
static FILE *ifp;
static int linenumber;

static char buf[240];
static int numbuf[500];

int mcount = 0;
mat_t *mlist = NULL;


object_t *readobj(char *fname)
{
    object_t *obj;
    int i;
    int at = 0;

    strncpy(ifname, fname, 80);
    if ((ifp = fopen(ifname, "r")) == NULL)
    {
	fprintf(stderr, "readobj: can't open \"%s\"\n", ifname);
	return (object_t *)(-1);
    }

    if (isbinary())
    {
	fclose(ifp);
	return(breadobj(ifname));
    }
    linenumber = 0;

    obj = (object_t *)malloc(sizeof(object_t));
    bzero(obj, sizeof(object_t));

    obj->radius = 100.0;	/* XXX */

    while (fillbuf())
    {
	switch (buf[0])
	{
	    case 'B':
		readnode_list(obj, atoi(&buf[1]));
		break;
	    case 'T':
		readtrans_list(obj, atoi(&buf[1]));
		break;
	    case 'G':
		readgeom_list(obj, atoi(&buf[1]));
		break;
	    case 'M':
		readmat_list(obj, atoi(&buf[1]));
		break;
	    case 'R':
		sscanf(buf, "R%f", &obj->radius);
		break;
	    case '0':
	    case '1':
	    case '2':
	    case '3':
	    case '4':
	    case '5':
	    case '6':
	    case '7':
	    case '8':
	    case '9':
		/*
		 *  old file compatibility
		 */
		{

		    switch(at++)
		    {
			case 0:
			    readnode_list(obj, atoi(buf));
			    break;
			case 1:
			    readtrans_list(obj, atoi(buf));
			    break;
			case 2:
			    readgeom_list(obj, atoi(buf));
			    break;
		        default:
			    readerror("syntax error");
			    break;
		    }
		}
		break;
	    default:
		readerror("unknown group type");
		break;
	}
    }

#if 0
    fillbuf();
    if (buf[0] == 'R')
    {
	sscanf(buf, "R%f", &obj->radius);
	fillbuf();
    }
    else
	obj->radius = 100.0;	/* XXX */

    obj->bcount = atoi(buf);
    obj->blist = (node_t *)malloc(sizeof(node_t) * obj->bcount);
    for (i=0; i < obj->bcount; i++)
	readnode(&obj->blist[i]);

    fillbuf();
    if (obj->tcount = atoi(buf))
	obj->tlist = (trans_t *)malloc(sizeof(trans_t) * obj->tcount);
    for (i=0; i < obj->tcount; i++)
	readtrans(&obj->tlist[i]);

    fillbuf();
    obj->gcount = atoi(buf);
    obj->glist = (geometry_t *)malloc(sizeof(geometry_t) * obj->gcount);
    bzero(obj->glist, sizeof(geometry_t) * obj->gcount);

    for (i=0; i < obj->gcount; i++)
    {
	fillbuf();
	obj->glist[i].type = atoi(buf);
	switch(obj->glist[i].type)
	{
	    case SSECTION:
	    case LTV_GEOM:
		readssect(&obj->glist[i]);
		break;
	    case FSECTION:
		readfsect(&obj->glist[i]);
		break;
	    case PSECTION:
		readpsect(&obj->glist[i]);
		break;
	    case CSECTION:
	    case CLS_GEOM:
	    case CDS_GEOM:
		readcsect(&obj->glist[i]);
		break;
	    case CPV_GEOM:
	    case CDV_GEOM:
		readcdvgeom(&obj->glist[i]);
		break;
	    case CPU_GEOM:
	    case CDU_GEOM:
		readcdugeom(&obj->glist[i]);
		break;
	    case TLPU_GEOM:
		read_tlpu_geom(&obj->glist[i]);
		break;
	    case IMU_GEOM:
		read_imu_geom(&obj->glist[i]);
		break;
	    case IMV_GEOM:
		read_imv_geom(&obj->glist[i]);
		break;
	    default:
		readerror("unknown section type (%d)",obj->glist[i].type);
	}
    }
#endif


    fclose(ifp);

    if (obj->mcount)
	resolve_mat(obj);

    return obj;
}


void readnode_list(object_t *obj, int count)
{
    int i;

    obj->bcount = count;
    obj->blist = (node_t *)malloc(sizeof(node_t) * obj->bcount);
    for (i=0; i < obj->bcount; i++)
	readnode(&obj->blist[i]);
}


void readtrans_list(object_t *obj, int count)
{
    int i;

    if (obj->tcount = count)
	obj->tlist = (trans_t *)malloc(sizeof(trans_t) * obj->tcount);
    for (i=0; i < obj->tcount; i++)
	readtrans(&obj->tlist[i]);
}


void readgeom_list(object_t *obj, int count)
{
    int i;

    obj->gcount = count;
    obj->glist = (geometry_t *)malloc(sizeof(geometry_t) * obj->gcount);
    bzero(obj->glist, sizeof(geometry_t) * obj->gcount);

    for (i=0; i < obj->gcount; i++)
    {
	fillbuf();
	obj->glist[i].type = atoi(buf);
	switch(obj->glist[i].type)
	{
	    case SSECTION:
	    case LTV_GEOM:
		readssect(&obj->glist[i]);
		break;
	    case FSECTION:
		readfsect(&obj->glist[i]);
		break;
	    case PSECTION:
		readpsect(&obj->glist[i]);
		break;
	    case CSECTION:
	    case CLS_GEOM:
	    case CDS_GEOM:
		readcsect(&obj->glist[i]);
		break;
	    case CPV_GEOM:
	    case CDV_GEOM:
		readcdvgeom(&obj->glist[i]);
		break;
	    case CPU_GEOM:
	    case CDU_GEOM:
		readcdugeom(&obj->glist[i]);
		break;
	    case TLPU_GEOM:
		read_tlpu_geom(&obj->glist[i]);
		break;
	    case IMU_GEOM:
		read_imu_geom(&obj->glist[i]);
		break;
	    case IMV_GEOM:
		read_imv_geom(&obj->glist[i]);
		break;
	    case IPU_GEOM:
		read_ipu_geom(&obj->glist[i]);
		break;
	    case IPV_GEOM:
		read_ipv_geom(&obj->glist[i]);
		break;
	    default:
		readerror("unknown section type");
	}
    }
}


void readmat_list(object_t *obj, int count)
{
    int i;

    obj->mcount = count;
    obj->mlist = (int *)malloc(sizeof(int) * obj->mcount);
    for (i=0; i < obj->mcount; i++)
	obj->mlist[i] = readmat();
}


void readnode(node_t *np)
{
    fillbuf();
    sscanf(buf, "%li,%li", (long *)&np->statebits, (long *)&np->modebits);	/* %i,%i on 32-bit IRIX; %li keeps hex parsing */
    np->tcount = readcnumlist(&np->tlist);
    np->scount = readblist(&np->slist, &np->stlist);
}


void readssect(geometry_t *sect)
{
    int i, j;
    char *bp;
    polygon_t *p;

    fillbuf();
    sscanf(buf, "%li", &sect->material);	/* %i on 32-bit IRIX; %li keeps hex parsing */
    fillbuf();
    sect->vcount = atoi(buf);
    sect->vlist = (float **)malloc(sizeof(float *) * sect->vcount);
    sect->nlist = (float **)malloc(sizeof(float *) * sect->vcount);
    for (i=0; i < sect->vcount; i++)
    {
	sect->vlist[i] = (float *)malloc(sizeof(float) * 3);
	sect->nlist[i] = (float *)malloc(sizeof(float) * 3);
	fillbuf();
	sscanf(buf, "%f,%f,%f,%f,%f,%f",
	       &sect->vlist[i][X], &sect->vlist[i][Y], &sect->vlist[i][Z],
	       &sect->nlist[i][X], &sect->nlist[i][Y], &sect->nlist[i][Z]);
    }

    fillbuf();
    sect->pcount = atoi(buf);
    sect->plist = (polygon_t *)malloc(sizeof(polygon_t) * sect->pcount);
    for (i=0; i < sect->pcount; i++)
    {
	p = &sect->plist[i];
	p->vcount = readnumlist(&p->vnlist);
	p->vlist = (float **)malloc(sizeof(float *) * p->vcount);
	p->nlist = (float **)malloc(sizeof(float *) * p->vcount);
	for (j=0; j < p->vcount; j++)
	{
	    p->vlist[j] = sect->vlist[p->vnlist[j]];
	    p->nlist[j] = sect->nlist[p->vnlist[j]];
	}
    }
}


void readfsect(geometry_t *sect)
{
    int i, j;
    char *bp;
    polygon_t *p;

    fillbuf();
    sscanf(buf, "%li", &sect->material);	/* %i on 32-bit IRIX; %li keeps hex parsing */
    fillbuf();
    sect->vcount = atoi(buf);
    sect->vlist = (float **)malloc(sizeof(float *) * sect->vcount);
    for (i=0; i < sect->vcount; i++)
    {
	sect->vlist[i] = (float *)malloc(sizeof(float) * 3);
	fillbuf();
	sscanf(buf, "%f,%f,%f",
	       &sect->vlist[i][X], &sect->vlist[i][Y], &sect->vlist[i][Z]);
    }

    fillbuf();
    sect->pcount = atoi(buf);
    sect->plist = (polygon_t *)malloc(sizeof(polygon_t) * sect->pcount);
    for (i=0; i < sect->pcount; i++)
    {
	p = &sect->plist[i];
	fscanf(ifp, "%f,%f,%f,",
	       &p->normal[X], &p->normal[Y], &p->normal[Z]);
	p->vcount = readnumlist(&p->vnlist);
	p->vlist = (float **)malloc(sizeof(float *) * p->vcount);
	for (j=0; j < p->vcount; j++)
	    p->vlist[j] = sect->vlist[p->vnlist[j]];
    }
}


void read_tlpu_geom(geometry_t *sect)
{
    int i, j;
    char *bp;
    polygon_t *p;

    fillbuf();
    sscanf(buf, "%li", &sect->material);	/* %i on 32-bit IRIX; %li keeps hex parsing */
    fillbuf();
    sect->vcount = atoi(buf);
    sect->vlist = (float **)malloc(sizeof(float *) * sect->vcount);
    sect->xlist = (float **)malloc(sizeof(float *) * sect->vcount);
    for (i=0; i < sect->vcount; i++)
    {
	sect->vlist[i] = (float *)malloc(sizeof(float) * 3);
	sect->xlist[i] = (float *)malloc(sizeof(float) * 2);
	fillbuf();
	sscanf(buf, "%f,%f,%f,%f,%f",
	       &sect->vlist[i][X], &sect->vlist[i][Y], &sect->vlist[i][Z],
	       &sect->xlist[i][0], &sect->xlist[i][1]);
    }

    fillbuf();
    sect->pcount = atoi(buf);
    sect->plist = (polygon_t *)malloc(sizeof(polygon_t) * sect->pcount);
    for (i=0; i < sect->pcount; i++)
    {
	p = &sect->plist[i];
	fscanf(ifp, "%f,%f,%f,",
	       &p->normal[X], &p->normal[Y], &p->normal[Z]);
	p->vcount = readnumlist(&p->vnlist);
	p->vlist = (float **)malloc(sizeof(float *) * p->vcount);
	p->xlist = (float **)malloc(sizeof(float *) * p->vcount);
	for (j=0; j < p->vcount; j++)
	{
	    p->vlist[j] = sect->vlist[p->vnlist[j]];
	    p->xlist[j] = sect->xlist[p->vnlist[j]];
	}
    }
}


void readpsect(geometry_t *sect)
{
    int i, j;
    char *bp;
    polygon_t *p;

    fillbuf();
    sscanf(buf, "%li", &sect->material);	/* %i on 32-bit IRIX; %li keeps hex parsing */
    fillbuf();
    sscanf(buf, "%f,%f,%f",
	   &sect->normal[X], &sect->normal[Y], &sect->normal[Z]);
    fillbuf();
    sect->vcount = atoi(buf);
    sect->vlist = (float **)malloc(sizeof(float *) * sect->vcount);
    for (i=0; i < sect->vcount; i++)
    {
	sect->vlist[i] = (float *)malloc(sizeof(float) * 3);
	fillbuf();
	sscanf(buf, "%f,%f,%f",
	       &sect->vlist[i][X], &sect->vlist[i][Y], &sect->vlist[i][Z]);
    }

    fillbuf();
    sect->pcount = atoi(buf);
    sect->plist = (polygon_t *)malloc(sizeof(polygon_t) * sect->pcount);
    for (i=0; i < sect->pcount; i++)
    {
	p = &sect->plist[i];
	p->vcount = readnumlist(&p->vnlist);
	p->vlist = (float **)malloc(sizeof(float *) * p->vcount);
	for (j=0; j < p->vcount; j++)
	    p->vlist[j] = sect->vlist[p->vnlist[j]];
    }
}


void readcsect(geometry_t *sect)
{
    int i, j;
    char *bp;
    polygon_t *p;

    fillbuf();
    sscanf(buf, "%li", &sect->color);	/* %i on 32-bit IRIX; %li keeps hex parsing */
    fillbuf();
    sect->vcount = atoi(buf);
    sect->vlist = (float **)malloc(sizeof(float *) * sect->vcount);
    for (i=0; i < sect->vcount; i++)
    {
	sect->vlist[i] = (float *)malloc(sizeof(float) * 3);
	fillbuf();
	sscanf(buf, "%f,%f,%f",
	       &sect->vlist[i][X], &sect->vlist[i][Y], &sect->vlist[i][Z]);
    }

    fillbuf();
    sect->pcount = atoi(buf);
    sect->plist = (polygon_t *)malloc(sizeof(polygon_t) * sect->pcount);
    for (i=0; i < sect->pcount; i++)
    {
	p = &sect->plist[i];
	p->vcount = readnumlist(&p->vnlist);
	p->vlist = (float **)malloc(sizeof(float *) * p->vcount);
	for (j=0; j < p->vcount; j++)
	    p->vlist[j] = sect->vlist[p->vnlist[j]];
    }
}


void readcdvgeom(geometry_t *sect)
{
    int i, j;
    char *bp;
    polygon_t *p;

    fillbuf();
    sect->vcount = atoi(buf);
    sect->vlist = (float **)malloc(sizeof(float *) * sect->vcount);
    sect->clist = (long *)malloc(sizeof(long) * sect->vcount);
    for (i=0; i < sect->vcount; i++)
    {
	sect->vlist[i] = (float *)malloc(sizeof(float) * 3);
	fillbuf();
	sscanf(buf, "%li,%f,%f,%f", &sect->clist[i],	/* %i on 32-bit IRIX; %li keeps hex parsing */ 
	       &sect->vlist[i][X], &sect->vlist[i][Y], &sect->vlist[i][Z]);
    }

    fillbuf();
    sect->pcount = atoi(buf);
    sect->plist = (polygon_t *)malloc(sizeof(polygon_t) * sect->pcount);
    for (i=0; i < sect->pcount; i++)
    {
	p = &sect->plist[i];
	p->vcount = readnumlist(&p->vnlist);
	p->vlist = (float **)malloc(sizeof(float *) * p->vcount);
	p->clist = (long *)malloc(sizeof(long) * p->vcount);
	for (j=0; j < p->vcount; j++)
	{
	    p->vlist[j] = sect->vlist[p->vnlist[j]];
	    p->clist[j] = sect->clist[p->vnlist[j]];
	}
    }
}


void readcdugeom(geometry_t *sect)
{
    int i, j;
    char *bp;
    polygon_t *p;

    fillbuf();
    sect->vcount = atoi(buf);
    sect->vlist = (float **)malloc(sizeof(float *) * sect->vcount);
    for (i=0; i < sect->vcount; i++)
    {
	sect->vlist[i] = (float *)malloc(sizeof(float) * 3);
	fillbuf();
	sscanf(buf, "%f,%f,%f",
	       &sect->vlist[i][X], &sect->vlist[i][Y], &sect->vlist[i][Z]);
    }

    fillbuf();
    sect->pcount = atoi(buf);
    sect->plist = (polygon_t *)malloc(sizeof(polygon_t) * sect->pcount);
    for (i=0; i < sect->pcount; i++)
    {
	p = &sect->plist[i];
	fscanf(ifp, "%li,", &p->color);	/* %i on 32-bit IRIX; %li keeps hex parsing */
	p->vcount = readnumlist(&p->vnlist);
	p->vlist = (float **)malloc(sizeof(float *) * p->vcount);
	for (j=0; j < p->vcount; j++)
	    p->vlist[j] = sect->vlist[p->vnlist[j]];
    }
}


void read_imu_geom(geometry_t *sect)
{
    int i,j,k;
    char *bp;
    polygon_t *p;

    fillbuf();
    sect->vcount = atoi(buf);
    sect->vlist = (float **)malloc(sizeof(float *) * sect->vcount);
    for (i=0; i < sect->vcount; i++) 
    {
	sect->vlist[i] = (float *)malloc(sizeof(float) * 3);
	fillbuf();
	sscanf(buf, "%f,%f,%f",
	       &sect->vlist[i][X], &sect->vlist[i][Y], &sect->vlist[i][Z]);
    }

    fillbuf();
    sect->pcount = atoi(buf);
    sect->plist = (polygon_t *)malloc(sizeof(polygon_t) * sect->pcount);
    for (i=0; i < sect->pcount; i++) 
    {
	p = &sect->plist[i];
	fscanf(ifp, "%li,%li,", &p->type, &p->color);	/* %d,%d on 32-bit IRIX; %li keeps hex parsing */
	p->vcount = readnumlist(&p->vnlist);
	p->vlist = (float **)malloc(sizeof(float *) * p->vcount);
	for (j=0; j < p->vcount; j++) {
	    p->vlist[j] = sect->vlist[p->vnlist[j]];
	}
    }
}


void read_imv_geom(geometry_t *sect)
{
    int i,j,k;
    char *bp;
    polygon_t *p;

    fillbuf();
    sect->vcount = atoi(buf);
    sect->vlist = (float **)malloc(sizeof(float *) * sect->vcount);
    sect->clist = (long *)malloc(sizeof(long) * sect->vcount);
    for (i=0; i < sect->vcount; i++)
    {
	sect->vlist[i] = (float *)malloc(sizeof(float) * 3);
	fillbuf();
	sscanf(buf, "%f,%f,%f,%ld",
	       &sect->vlist[i][X], &sect->vlist[i][Y], &sect->vlist[i][Z],
	       &sect->clist[i]);
    }

    fillbuf();
    sect->pcount = atoi(buf);
    sect->plist = (polygon_t *)malloc(sizeof(polygon_t) * sect->pcount);
    for (i=0; i < sect->pcount; i++)
    {
	p = &sect->plist[i];
	fscanf(ifp, "%li,", &p->type);	/* %d on 32-bit IRIX; %li keeps hex parsing */
	p->vcount = readnumlist(&p->vnlist);
	p->vlist = (float **)malloc(sizeof(float *) * p->vcount);
	for (j=0; j < p->vcount; j++) {
	    p->vlist[j] = sect->vlist[p->vnlist[j]];
	}
    }
}


void read_ipu_geom(geometry_t *sect)
{
    int i,j,k;
    char *bp;
    polygon_t *p;

    fillbuf();
    sect->vcount = atoi(buf);
    sect->vlist = (float **)malloc(sizeof(float *) * sect->vcount);
    for (i=0; i < sect->vcount; i++) 
    {
	sect->vlist[i] = (float *)malloc(sizeof(float) * 3);
	fillbuf();
	sscanf(buf, "%f,%f,%f",
	       &sect->vlist[i][X], &sect->vlist[i][Y], &sect->vlist[i][Z]);
    }

    fillbuf();
    sect->pcount = atoi(buf);
    sect->plist = (polygon_t *)malloc(sizeof(polygon_t) * sect->pcount);
    for (i=0; i < sect->pcount; i++) 
    {
	p = &sect->plist[i];
	fscanf(ifp, "%li,", &p->color);	/* %d on 32-bit IRIX; %li keeps hex parsing */
	p->vcount = readnumlist(&p->vnlist);
	p->vlist = (float **)malloc(sizeof(float *) * p->vcount);
	for (j=0; j < p->vcount; j++) {
	    p->vlist[j] = sect->vlist[p->vnlist[j]];
	}
    }
}


void read_ipv_geom(geometry_t *sect)
{
    int i,j,k;
    char *bp;
    polygon_t *p;

    fillbuf();
    sect->vcount = atoi(buf);
    sect->vlist = (float **)malloc(sizeof(float *) * sect->vcount);
    sect->clist = (long *)malloc(sizeof(long) * sect->vcount);
    for (i=0; i < sect->vcount; i++)
    {
	sect->vlist[i] = (float *)malloc(sizeof(float) * 3);
	fillbuf();
	sscanf(buf, "%f,%f,%f,%ld",
	       &sect->vlist[i][X], &sect->vlist[i][Y], &sect->vlist[i][Z],
	       &sect->clist[i]);
    }

    fillbuf();
    sect->pcount = atoi(buf);
    sect->plist = (polygon_t *)malloc(sizeof(polygon_t) * sect->pcount);
    for (i=0; i < sect->pcount; i++)
    {
	p = &sect->plist[i];
	p->vcount = readnumlist(&p->vnlist);
	p->vlist = (float **)malloc(sizeof(float *) * p->vcount);
	for (j=0; j < p->vcount; j++) {
	    p->vlist[j] = sect->vlist[p->vnlist[j]];
	}
    }
}


void readtrans(trans_t *t)
{
    fillbuf();
    t->type = atoi(buf);
    switch(t->type)
    {
	case ROTX:
	case ROTY:
	case ROTZ:
	    sscanf(buf, "%d,%d", &t->type, &t->angle);
	    break;
	case TRANSLATE:
	case SCALE:
	    sscanf(buf, "%d,%f,%f,%f", &t->type, &t->x, &t->y, &t->z);
	    break;
	default:
	    readerror("unknown translation type");
	    break;
    }
}
 

int readnumlist(int **nlist)
{
    char *bp;
    int i = 0;

    fillbuf();
    bp = buf;

    while (*bp != '\n' && *bp != '\0' && *bp != '#')
    {
	if (i >= 500)	/* added: numbuf[500] overflow corrupted the heap */
	{
	    readerror("number list longer than 500");
	    break;
	}
	switch (*bp)
	{
	    case '0':
	    case '1':
	    case '2':
	    case '3':
	    case '4':
	    case '5':
	    case '6':
	    case '7':
	    case '8':
	    case '9':
		numbuf[i++] = atoi(bp);
		while (*bp >= '0' && *bp <= '9')
		    bp++;
		break;
	    case ',':
		bp++;
		break;
	    case ' ':
	    case '\t':
		bp++;
		break;
	    case '\\':
		if (!fillbuf())	/* added: EOF mid-continuation looped forever */
		{
		    readerror("EOF in continuation");
		    buf[0] = '\0';
		}
		bp = buf;
		break;
	    case '\n':
	    case '\0':
	    case '#':
		break;
	    default:
		readerror("syntax error");
		bp++;	/* added: was not advancing -> infinite loop */
		break;
	}
    }

    *nlist = (int *)malloc(sizeof(int) * i);
    bcopy(numbuf, *nlist, i * sizeof(int));
    return(i);
}


int readcnumlist(int **nlist)
{
    char *bp;
    int i = 0;
    int count;
    int *list;

    fillbuf();
    bp = buf;

    count = atoi(bp);
    if (count == 0)
    {
	*nlist = NULL;
	return(0);
    }
    while (*bp >= '0' && *bp <= '9')
	bp++;
    list = (int *)malloc(sizeof(int) * count);
    *nlist = list;

    while (*bp != '\n' && *bp != '\0' && *bp != '#')
	switch (*bp)
	{
	    case '0':
	    case '1':
	    case '2':
	    case '3':
	    case '4':
	    case '5':
	    case '6':
	    case '7':
	    case '8':
	    case '9':
		if (i >= count)
		    readerror("too many numbers found");
		list[i++] = atoi(bp);
		while (*bp >= '0' && *bp <= '9')
		    bp++;
		break;
	    case ',':
	    case ' ':
	    case '\t':
		bp++;
		break;
	    case '\\':
		fillbuf();
		bp = buf;
		break;
	    case '\n':
	    case '\0':
	    case '#':
		break;
	    default:
		readerror("syntax error");
		break;
	}

    if (i != count)
	readerror("too few numbers found");

    return(count);
}


int readblist(int **nlist, int **tlist)
{
    char *bp;
    int i;
    int count;
    int *nl;
    int *tl;

    fillbuf();
    bp = buf;

    count = atoi(bp);
    if (count == 0)
    {
	*nlist = NULL;
	*tlist = NULL;
	return(0);
    }
    while (*bp >= '0' && *bp <= '9')
	bp++;

    nl = (int *)malloc(sizeof(int) * count);
    *nlist = nl;

    tl = (int *)malloc(sizeof(int) * count);
    *tlist = tl;
    for (i=0; i<count; i++)
	tl[i] = BRANCH;

    i = 0;

    while (*bp != '\n' && *bp != '\0' && *bp != '#')
	switch (*bp)
	{
	    case '0':
	    case '1':
	    case '2':
	    case '3':
	    case '4':
	    case '5':
	    case '6':
	    case '7':
	    case '8':
	    case '9':
		if (i >= count)
		    readerror("too many numbers found");
		nl[i++] = atoi(bp);
		while (*bp >= '0' && *bp <= '9')
		    bp++;
		break;
	    case 'B':
		tl[i] = BRANCH;
		bp++;
		break;
	    case 'G':
		tl[i] = GEOMETRY;
		bp++;
		break;
	    case ',':
	    case ' ':
	    case '\t':
		bp++;
		break;
	    case '\\':
		fillbuf();
		bp = buf;
		break;
	    case '\n':
	    case '\0':
	    case '#':
		break;
	    default:
		readerror("syntax error");
		break;
	}

    if (i != count)
	readerror("too few numbers found");

    return(count);
}


int readmat()
{
    float tmp[21];
    int i;

    fillbuf();
    tmp[0] = AMBIENT;
    sscanf(buf, "%f,%f,%f", &tmp[1], &tmp[2], &tmp[3]);
    fillbuf();
    tmp[4] = DIFFUSE;
    tmp[8] = ALPHA;
    sscanf(buf, "%f,%f,%f,%f", &tmp[5], &tmp[6], &tmp[7], &tmp[9]);
    fillbuf();
    tmp[10] = SPECULAR;
    sscanf(buf, "%f,%f,%f", &tmp[11], &tmp[12], &tmp[13]);
    fillbuf();
    tmp[14] = SHININESS;
    sscanf(buf, "%f", &tmp[15]);
    fillbuf();
    tmp[16] = EMISSION;
    sscanf(buf, "%f,%f,%f", &tmp[17], &tmp[18], &tmp[19]);
    tmp[20] = LMNULL;

    for (i=0; i < mcount; i++)
	if (bcmp(tmp, mlist[i].data, 20 * sizeof(float)) == 0)
	    return(i);

    if (mcount % 4 == 0)
	mlist = (mat_t *)realloc(mlist, (mcount+4) * sizeof(mat_t));

    mlist[mcount].id = mcount + 0x1000;
    bcopy(tmp, mlist[mcount].data, 21 * sizeof(float));
    mcount++;

    return(i);
}


void resolve_mat(object_t *obj)
{
    int i;
    geometry_t *g;

    for (i=0; i < obj->gcount; i++)
    {
	g = &obj->glist[i];
	switch(g->type)
	{
	    case SSECTION:
	    case LTV_GEOM:
	    case FSECTION:
	    case PSECTION:
	    case TLPU_GEOM:
		g->material = mlist[obj->mlist[g->material]].id;
		break;
	    default:
		break;
	}
    }
}


void readerror(char *errbuf)
{
    fprintf(stderr, "Error reading \"%s\"\n", ifname);
    fprintf(stderr, "Error: %s : line %d\n", errbuf, linenumber);
    exit(-1);
}


int fillbuf()
{
    do
    {
	if (fgets(buf, 240, ifp) == NULL)
	    return(0);
	linenumber++;
    }
    while (buf[0] == '\0' || buf[0] == '#');

    return(1);
}


int isbinary()
{
    if (getc(ifp) == '\0')
	return(TRUE);
    
    rewind(ifp);
    return(FALSE);
}


object_t *breadobj(char *fname)
{
    object_t *obj;
    int ifd;
    node_t *b;
    geometry_t *g;
    polygon_t *p;
    int i, j, k;

    ifd = open(fname, O_RDONLY);

    /*
     *  skip over the first byte that says this is a binary file
     */
    lseek(ifd, 1, 1);

    obj = (object_t *)malloc(sizeof(object_t));
    read(ifd, obj, sizeof(object_t));

    obj->blist = (node_t *)malloc(sizeof(node_t) * obj->bcount);
    read(ifd, obj->blist, sizeof(node_t) * obj->bcount);
    for (i=0; i < obj->bcount; i++)
    {
	b = &obj->blist[i];
	if (b->tcount)
	{
	    b->tlist = (int *)malloc(sizeof(int) * b->tcount);
	    read(ifd, b->tlist, sizeof(int) * b->tcount);
	}
	if (b->scount)
	{
	    b->slist = (int *)malloc(sizeof(int) * b->scount);
	    read(ifd, b->slist, sizeof(int) * b->scount);
	    b->stlist = (int *)malloc(sizeof(int) * b->scount);
	    read(ifd, b->stlist, sizeof(int) * b->scount);
	}
    }

    if (obj->tcount)
    {
	obj->tlist = (trans_t *)malloc(sizeof(trans_t) * obj->tcount);
	read(ifd, obj->tlist, sizeof(trans_t) * obj->tcount);
    }

    obj->glist = (geometry_t *)malloc(sizeof(geometry_t) * obj->gcount);
    read(ifd, obj->glist, sizeof(geometry_t) * obj->gcount);
    for (i=0; i < obj->gcount; i++)
    {
	g = &obj->glist[i];

	g->vlist = (float **)malloc(sizeof(float *) * g->vcount);
	for (j=0; j < g->vcount; j++)
	{
	    g->vlist[j] = (float *)malloc(sizeof(float) * 3);
	    read(ifd, g->vlist[j], sizeof(float)*3);
	}
	    
	if (g->nlist)
	{
	    g->nlist = (float **)malloc(sizeof(float *) * g->vcount);
	    for (j=0; j < g->vcount; j++)
	    {
		g->nlist[j] = (float *)malloc(sizeof(float) * 3);
		read(ifd, g->nlist[j], sizeof(float)*3);
	    }
	}

	if (g->clist)
	{
	    g->clist = (long *)malloc(sizeof(long) * g->vcount);
	    read(ifd, g->clist, sizeof(long) * g->vcount);
	}

	g->plist = (polygon_t *)malloc(sizeof(polygon_t) * g->pcount);
	read(ifd, g->plist, sizeof(polygon_t) * g->pcount);
	for (j=0; j < g->pcount; j++)
	{
	    p = &g->plist[j];

	    p->vlist = (float **)malloc(sizeof(float *) * p->vcount);
	    p->vnlist = (int *)malloc(sizeof(int) * p->vcount);
	    read(ifd, p->vnlist, sizeof(int) * p->vcount);
	    for (k=0; k < p->vcount; k++)
		p->vlist[k] = g->vlist[p->vnlist[k]];
	    if (g->nlist)
	    {
		p->nlist = (float **)malloc(sizeof(float *) * p->vcount);
		for (k=0; k < p->vcount; k++)
		    p->nlist[k] = g->nlist[p->vnlist[k]];
	    }
	    if (g->clist)
	    {
		p->clist = (long *)malloc(sizeof(long) * p->vcount);
		for (k=0; k < p->vcount; k++)
		    p->clist[k] = g->clist[p->vnlist[k]];
	    }
	}
    }

    close(ifd);
}

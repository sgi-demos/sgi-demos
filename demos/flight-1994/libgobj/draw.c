/*
 * Copyright 1984, 1991, 1992, 1993, 1994, Silicon Graphics, Inc.
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

static object_t *curobj;	/* current object */
static long curmode;		/* current mode bits */

static int gobj_inited = FALSE;


drawobj(obj, state)
    object_t *obj;
    long state;
{
    int i;

    if (!gobj_inited)
	init_gobj();

    curobj = obj;
    curmode = 0x0;

    drawnode(&obj->blist[0], state);

    modesoff();
}


init_gobj()
{
    int i;

    /*
     *  bind materials
     */
    for (i = 0; i < mcount; i++)
	lmdef(DEFMATERIAL, (short)mlist[i].id, 21, mlist[i].data);

    gobj_inited = TRUE;
}


drawnode(np, state)
    node_t *np;
    long state;
{
    int i, todraw;

    if (!(state & np->statebits))
	return;

    if (np->statebits & CULL)
    {
	if (cull(&curobj->glist[np->slist[0]]))
	    return;
	else
	    i = 1;
    }
    else
	i = 0;

    setmode(np->modebits);

    if (np->tcount)
    {
	pushmatrix();
	dotrans(np->tcount, np->tlist);
    }

    if ((np->modebits & M_EIGHTVIEW) != 0) 
    {  
	i = (state & EV_MASK) >> EV_SHIFT;
	todraw = i+1;
    }
    else
	todraw = np->scount;

    for (; i < todraw; i++)
    {
	if (np->stlist[i] == BRANCH)
	    drawnode(&curobj->blist[np->slist[i]], state);
	else
	    switch(curobj->glist[np->slist[i]].type)
	    {
		case SSECTION:
		    drawssect(&curobj->glist[np->slist[i]]);
		    break;
		case FSECTION:
		    drawfsect(&curobj->glist[np->slist[i]]);
		    break;
		case PSECTION:
		    drawpsect(&curobj->glist[np->slist[i]]);
		    break;
		case CPV_GEOM:
		    lsuspend(TRUE);
		    drawcpvgeom(&curobj->glist[np->slist[i]]);
		    lsuspend(FALSE);
		    break;
		case CPU_GEOM:
		    lsuspend(TRUE);
		    drawcpugeom(&curobj->glist[np->slist[i]]);
		    lsuspend(FALSE);
		    break;
		case CSECTION:
		    lsuspend(TRUE);
		    drawcsect(&curobj->glist[np->slist[i]]);
		    lsuspend(FALSE);
		    break;
		case LTV_GEOM:
		    drawltvgeom(&curobj->glist[np->slist[i]]);
		    break;
		case CLS_GEOM:
		    lsuspend(TRUE);
		    drawclsgeom(&curobj->glist[np->slist[i]]);
		    lsuspend(FALSE);
		    break;
		case CDV_GEOM:
		    lsuspend(TRUE);
		    drawcdvgeom(&curobj->glist[np->slist[i]]);
		    lsuspend(FALSE);
		    break;
		case CDU_GEOM:
		    lsuspend(TRUE);
		    drawcdugeom(&curobj->glist[np->slist[i]]);
		    lsuspend(FALSE);
		    break;
		case CDS_GEOM:
		    lsuspend(TRUE);
		    drawcdsgeom(&curobj->glist[np->slist[i]]);
		    lsuspend(FALSE);
		    break;
		case IMU_GEOM:
		    lsuspend(TRUE);
		    draw_imu_geom(&curobj->glist[np->slist[i]]);
		    lsuspend(FALSE);
		    break;
		case IMV_GEOM:
		    lsuspend(TRUE);
		    draw_imv_geom(&curobj->glist[np->slist[i]]);
		    lsuspend(FALSE);
		    break;
		case IPU_GEOM:
		    lsuspend(TRUE);
		    draw_ipu_geom(&curobj->glist[np->slist[i]]);
		    lsuspend(FALSE);
		    break;
		case IPV_GEOM:
		    lsuspend(TRUE);
		    draw_ipv_geom(&curobj->glist[np->slist[i]]);
		    lsuspend(FALSE);
		    break;
		case TLPU_GEOM:
		    if (getgdesc(GD_TEXTURE) > 0)
			draw_tlpu_geom(&curobj->glist[np->slist[i]]);
		    else
			drawfsect(&curobj->glist[np->slist[i]]);
		    break;
		default:
		    fprintf(stderr, 
			    "drawnode: unknown geom type (G%d), state %lx\n",
			    np->slist[i],state);
		    break;
	    }
    }

    if (np->tcount)
	popmatrix();
}


draw_imu_geom(sect)
    geometry_t *sect;
{
    int i, j, k;
    polygon_t *p;

    for (i = 0; i < sect->pcount; i++) 
    {
	p = &sect->plist[i];
	color(p->color);
	switch(p->type) 
	{
	    case 0:
		bgnpoint();
		for (j = 0; j < p->vcount; j++) 
		    v3f(p->vlist[j]);
		endpoint();
		break;
	    case 1:
		bgnline();
		for (j = 0; j < p->vcount; j++) 
		    v3f(p->vlist[j]);
		endline();
		break;
	    case 2:
		bgnpolygon();
		for (j = 0; j < p->vcount; j++) 
		    v3f(p->vlist[j]);
		endpolygon();
		break;
	    case 3:
		bgnclosedline();
		for (j = 0; j < p->vcount; j++) 
		    v3f(p->vlist[j]);
		endclosedline();
		break;
	    case 4:
		setpattern(3);
		bgnpolygon();
		for (j = 0; j < p->vcount; j++) 
		    v3f(p->vlist[j]);
		endpolygon();
		setpattern(0);
		break;
	    default:
		fprintf(stderr,"Unkown thing in eight-view node %d %d\n",
			p->type,i);
		break;
	}
    }
}


draw_imv_geom(sect)
    geometry_t *sect;
{
    int i, j, k;
    polygon_t *p;

    for (i = 0; i < sect->pcount; i++) 
    {
	p = &sect->plist[i];
	switch(p->type) 
	{
	    case 0:
		bgnpoint();
		for (j = 0; j < p->vcount; j++) 
		{
		    color(sect->clist[p->vnlist[j]]);
		    v3f(p->vlist[j]);
		}
		endpoint();
		break;
	    case 1:
		bgnline();
		for (j = 0; j < p->vcount; j++) 
		{
		    color(sect->clist[p->vnlist[j]]);
		    v3f(p->vlist[j]);
		}
		endline();
		break;
	    case 2:
		bgnpolygon();
		for (j = 0; j < p->vcount; j++) 
		{
		    color(sect->clist[p->vnlist[j]]);
		    v3f(p->vlist[j]);
		}
		endpolygon();
		break;
	    case 3:
		bgnclosedline();
		for (j = 0; j < p->vcount; j++) 
		{
		    color(sect->clist[p->vnlist[j]]);
		    v3f(p->vlist[j]);
		}
		endclosedline();
		break;
	    case 4:
		setpattern(3);
		bgnpolygon();
		for (j = 0; j < p->vcount; j++) 
		{
		    color(sect->clist[p->vnlist[j]]);
		    v3f(p->vlist[j]);
		}
		endpolygon();
		setpattern(0);
		break;
	    default:
		fprintf(stderr,"Unkown thing in eight-view node %d %d\n",
			p->type,i);
		break;
	}
    }
}


draw_ipu_geom(sect)
    geometry_t *sect;
{
    int i, j, k;
    polygon_t *p;

    for (i = 0; i < sect->pcount; i++) 
    {
	p = &sect->plist[i];
	color(p->color);
	bgnpolygon();
	for (j = 0; j < p->vcount; j++) 
	    v3f(p->vlist[j]);
	endpolygon();
    }
}


draw_ipv_geom(sect)
    geometry_t *sect;
{
    int i, j, k;
    polygon_t *p;

    for (i = 0; i < sect->pcount; i++) 
    {
	p = &sect->plist[i];
	bgnpolygon();
	for (j = 0; j < p->vcount; j++) 
	{
	    color(sect->clist[p->vnlist[j]]);
	    v3f(p->vlist[j]);
	}
	endpolygon();
    }
}


drawssect(sect)
    geometry_t *sect;
{
    int i, j;
    polygon_t *p;

    setmaterial(sect->material);

    for(i=0; i < sect->pcount; i++)
    {
	p = &sect->plist[i];
	bgnpolygon();
	/*
	out_vnlist(p->vlist, p->nlist, p->vcount);
	*/
	for(j=0; j < p->vcount; j++)
	{
	    n3f(p->nlist[j]);
	    v3f(p->vlist[j]);
	}
	endpolygon();
    }
}


drawltvgeom(sect)
    geometry_t *sect;
{
    int i, j;
    polygon_t *p;

    setmaterial(sect->material);

    for(i=0; i < sect->pcount; i++)
    {
	p = &sect->plist[i];
	bgntmesh();
	/*
	out_vnlist(p->vlist, p->nlist, p->vcount);
	*/
	for(j=0; j < p->vcount; j++)
	{
	    n3f(p->nlist[j]);
	    v3f(p->vlist[j]);
	}
	endtmesh();
    }
}


drawfsect(sect)
    geometry_t *sect;
{
    int i, j;
    polygon_t *p;

    setmaterial(sect->material);

    for(i=0; i < sect->pcount; i++)
    {
	p = &sect->plist[i];
	bgnpolygon();
	n3f(p->normal);
	/*
	out_vlist(p->vlist, p->vcount);
	*/
	for(j=0; j < p->vcount; j++)
	{
	    v3f(p->vlist[j]);
	}
	endpolygon();
    }
}


draw_tlpu_geom(sect)
    geometry_t *sect;
{
    int i, j;
    polygon_t *p;

    setmaterial(sect->material);

    for(i=0; i < sect->pcount; i++)
    {
	p = &sect->plist[i];
	bgnpolygon();
	n3f(p->normal);
	for(j=0; j < p->vcount; j++)
	{
	    t2f(p->xlist[j]);
	    v3f(p->vlist[j]);
	}
	endpolygon();
    }
}


drawpsect(sect)
    geometry_t *sect;
{
    int i, j;
    polygon_t *p;

    setmaterial(sect->material);

    n3f(sect->normal);
    for(i=0; i < sect->pcount; i++)
    {
	p = &sect->plist[i];
	bgnpolygon();
	/*
	out_vlist(p->vlist, p->vcount);
	*/
	for(j=0; j < p->vcount; j++)
	    v3f(p->vlist[j]);
	endpolygon();
    }
}


drawcpvgeom(sect)
    geometry_t *sect;
{
    int i, j;
    polygon_t *p;

    for(i=0; i < sect->pcount; i++)
    {
	p = &sect->plist[i];
	bgnpolygon();
	out_vclist(p->vlist, p->clist, p->vcount);
	endpolygon();
    }
}


drawcpugeom(sect)
    geometry_t *sect;
{
    int i, j;
    polygon_t *p;

    for(i=0; i < sect->pcount; i++)
    {
	p = &sect->plist[i];
	bgnpolygon();
	cpack(p->color);
	/*
	out_vlist(p->vlist, p->vcount);
	*/
	for(j=0; j < p->vcount; j++)
	{
	    v3f(p->vlist[j]);
	}
	endpolygon();
    }
}


drawcsect(sect)
    geometry_t *sect;
{
    int i, j;
    polygon_t *p;

    cpack(sect->color);

    for(i=0; i < sect->pcount; i++)
    {
	p = &sect->plist[i];
	bgnpolygon();
	for(j=0; j < p->vcount; j++)
	    v3f(p->vlist[j]);
	endpolygon();
    }
}


drawclsgeom(g)
    geometry_t *g;
{
    int i, j;
    polygon_t *p;

    cpack(g->color);

    for(i=0; i < g->pcount; i++)
    {
	p = &g->plist[i];
	bgnline();
	for(j=0; j < p->vcount; j++)
	    v3f(p->vlist[j]);
	endline();
    }
}


drawcdvgeom(sect)
    geometry_t *sect;
{
    int i, j;
    polygon_t *p;

    for(i=0; i < sect->pcount; i++)
    {
	p = &sect->plist[i];
	bgnpoint();
	out_vclist(p->vlist, p->clist, p->vcount);
	endpoint();
    }
}


drawcdugeom(sect)
    geometry_t *sect;
{
    int i, j;
    polygon_t *p;

    for(i=0; i < sect->pcount; i++)
    {
	p = &sect->plist[i];
	bgnpoint();
	cpack(p->color);
	/*
	out_vlist(p->vlist, p->vcount);
	*/
	for(j=0; j < p->vcount; j++)
	{
	    v3f(p->vlist[j]);
	}
	endpoint();
    }
}


drawcdsgeom(g)
    geometry_t *g;
{
    int i, j;
    polygon_t *p;

    cpack(g->color);

    for(i=0; i < g->pcount; i++)
    {
	p = &g->plist[i];
	bgnpoint();
	for(j=0; j < p->vcount; j++)
	    v3f(p->vlist[j]);
	endpoint();
    }
}


setmode(mode)
    long mode;
{
    int modeson = mode & (~curmode);
    int modesoff = (~mode) & curmode;

    if (modeson & MBACKFACE)
	backface(TRUE);
    else if (modesoff & MBACKFACE)
	backface(FALSE);

    if (modeson & MTRANSPERENT)
	blendfunction(BF_SA, BF_MSA);
    else if (modesoff & MTRANSPERENT)
	blendfunction(BF_ONE, BF_ZERO);

    if (modeson & MZMASK)
	zwritemask(0x0);
    else if (modesoff & MZMASK)
	zwritemask(0xffffff);

    if (modeson & MCMASK)
	wmpack(0x0);
    else if (modesoff & MCMASK)
	wmpack(0xffffffff);

#ifdef OLDXXX
    /*
     *  turn on modes that need to go on
     */
    switch(mode & ~curmode)
    {
	case 0x0:
	    break;
	case 0x1:
	    backface(TRUE);
	    break;
	case 0x2:
	    blendfunction(BF_SA, BF_MSA);
	    break;
	case 0x3:
	    backface(TRUE);
	    blendfunction(BF_SA, BF_MSA);
	    break;
	case 0x4:
	    zwritemask(0x0);
	    break;
	case 0x5:
	    backface(TRUE);
	    zwritemask(0x0);
	    break;
	case 0x6:
	    blendfunction(BF_SA, BF_MSA);
	    zwritemask(0x0);
	    break;
	case 0x7:
	    backface(TRUE);
	    blendfunction(BF_SA, BF_MSA);
	    zwritemask(0x0);
	    break;
	default:
	    break;
    }

    /*
     *  turn off modes that need to go on
     */
    switch((~mode) & curmode)
    {
	case 0x0:
	    break;
	case 0x1:
	    backface(FALSE);
	    break;
	case 0x2:
	    blendfunction(BF_ONE, BF_ZERO);
	    break;
	case 0x3:
	    backface(FALSE);
	    blendfunction(BF_ONE, BF_ZERO);
	    break;
	case 0x4:
	    zwritemask(0xffffff);
	    break;
	case 0x5:
	    backface(FALSE);
	    zwritemask(0xffffff);
	    break;
	case 0x6:
	    blendfunction(BF_ONE, BF_ZERO);
	    zwritemask(0xffffff);
	    break;
	case 0x7:
	    backface(FALSE);
	    blendfunction(BF_ONE, BF_ZERO);
	    zwritemask(0xffffff);
	    break;
	default:
	    break;
    }
#endif

    curmode = mode;
}


modesoff()
{
    if (curmode & MBACKFACE)
	backface(FALSE);

    if (curmode & MTRANSPERENT)
	blendfunction(BF_ONE, BF_ZERO);

    if (curmode & MZMASK)
	zwritemask(0xffffff);

    if (curmode & MCMASK)
	wmpack(0xffffffff);

#ifdef OLDXXX
    /*
     *  turn off modes that need to go on
     */
    switch(curmode)
    {
	case 0x0:
	    break;
	case 0x1:
	    backface(FALSE);
	    break;
	case 0x2:
	    blendfunction(BF_ONE, BF_ZERO);
	    break;
	case 0x3:
	    backface(FALSE);
	    blendfunction(BF_ONE, BF_ZERO);
	    break;
	case 0x4:
	    zwritemask(0xffffff);
	    break;
	case 0x5:
	    backface(FALSE);
	    zwritemask(0xffffff);
	    break;
	case 0x6:
	    blendfunction(BF_ONE, BF_ZERO);
	    zwritemask(0xffffff);
	    break;
	case 0x7:
	    backface(FALSE);
	    blendfunction(BF_ONE, BF_ZERO);
	    zwritemask(0xffffff);
	    break;
	default:
	    break;
    }
#endif
}


dotrans(tcount, tlist)
    int tcount;
    int *tlist;
{
    trans_t *t;
    int i;

    for(i=0; i < tcount; i++)
    {
	t = &curobj->tlist[tlist[i]];
	switch(t->type)
	{
	    case ROTX:
		rotate(t->angle, 'x');
		break;
	    case ROTY:
		rotate(t->angle, 'y');
		break;
	    case ROTZ:
		rotate(t->angle, 'z');
		break;
	    case TRANSLATE:
		translate(t->x, t->y, t->z);
		break;
	    case SCALE:
		scale(t->x, t->y, t->z);
		break;
	    default:
		break;
	}
    }
}


/*
 *  simple wire frame draw
 */
swdrawobj(obj)
    object_t *obj;
{
    int i;

    RGBcolor(255, 0, 0);

    for (i=0; i < obj->gcount; i++)
    {
	switch(obj->glist[i].type)
	{
	    case SSECTION:
	    case FSECTION:
	    case PSECTION:
	    case CSECTION:
	    case CLS_GEOM:
	    case IMU_GEOM:
	    case IMV_GEOM:
		swdrawsect(&obj->glist[i]);
		break;
	    default:
		break;
	}
    }
}


swdrawsect(sect)
    geometry_t *sect;
{
    int i, j;
    polygon_t *p;

    for(i=0; i < sect->pcount; i++)
    {
	p = &sect->plist[i];
	bgnclosedline();
	for(j=0; j < p->vcount; j++)
	{
	    v3f(p->vlist[j]);
	}
	endclosedline();
    }
}


/*
 *  point draw
 */
pdrawobj(obj)
    object_t *obj;
{
    int i;

    RGBcolor(255, 0, 0);

    for (i=0; i < obj->gcount; i++)
    {
	switch(obj->glist[i].type)
	{
	    case SSECTION:
	    case FSECTION:
	    case PSECTION:
	    case CSECTION:
	    case CLS_GEOM:
		pdrawsect(&obj->glist[i]);
		break;
	    default:
		break;
	}
    }
}


pdrawsect(sect)
    geometry_t *sect;
{
    int i;

    for(i=0; i < sect->vcount; i++)
    {
	bgnpoint();
	v3f(sect->vlist[i]);
	endpoint();
    }
}


/*
 *  pick point draw
 */
pickdrawobj(obj)
    object_t *obj;
{
    int i;

    RGBcolor(255, 0, 0);

    for (i=0; i < obj->gcount; i++)
    {
	loadname(i);
	pushname(-1);
	switch(obj->glist[i].type)
	{
	    case SSECTION:
	    case FSECTION:
	    case PSECTION:
	    case CSECTION:
	    case CLS_GEOM:
		pickdrawsect(&obj->glist[i]);
		break;
	    default:
		break;
	}
	popname();
    }
}


pickdrawsect(sect)
    geometry_t *sect;
{
    int i;

    for(i=0; i < sect->vcount; i++)
    {
	loadname(i);
	bgnpoint();
	v3f(sect->vlist[i]);
	endpoint();
    }
}


tpickdrawobj(obj, state)
    object_t *obj;
    long state;
{
    int i;

    curobj = obj;
    curmode = 0x0;

    tpickdrawnode(&obj->blist[0], state);
}


tpickdrawnode(np, state)
    node_t *np;
    long state;
{
    int i;

    if (!(state & np->statebits))
	return;

    if (np->statebits & CULL)
    {
	if (cull(&curobj->glist[np->slist[0]]))
	    return;
	else
	    i = 1;
    }
    else
	i = 0;

    if (np->tcount)
    {
	pushmatrix();
	dotrans(np->tcount, np->tlist);
    }

    for (; i < np->scount; i++)
    {
	if (np->stlist[i] == BRANCH)
	    tpickdrawnode(&curobj->blist[np->slist[i]], state);
	else
	    switch(curobj->glist[np->slist[i]].type)
	    {
		case SSECTION:
		case FSECTION:
		case PSECTION:
		case CSECTION:
		case CLS_GEOM:
		    loadname(np->slist[i]);
		    pushname(-1);
		    pickdrawsect(&curobj->glist[np->slist[i]]);
		    popname();
		    break;
		default:
		    break;
	    }
    }

    if (np->tcount)
	popmatrix();
}


/*
 *   Solid 2D draw (drop z component)
 */ 
s2ddrawobj(obj)
    object_t *obj;
{
    int i;

    curobj = obj;

    s2ddrawnode(&obj->blist[0]);
}


s2ddrawnode(np)
node_t *np;
{
    int i;

    if (np->tcount)
    {
	pushmatrix();
	dotrans(np->tcount, np->tlist);
    }

    for (i=0; i < np->scount; i++)
    {
	if (np->stlist[i] == BRANCH)
	    s2ddrawnode(&curobj->blist[np->slist[i]]);
	else
	    switch(curobj->glist[np->slist[i]].type)
	    {
		case IMU_GEOM:
		case IMV_GEOM:
		    s2ddrawsect(&curobj->glist[i]);
		    break;
		default:
		    break;
	    }
    }

    if (np->tcount)
	popmatrix();
}


s2ddrawsect(sect)
    geometry_t *sect;
{
    int i, j;
    polygon_t *p;

    for(i=0; i < sect->pcount; i++)
    {
	p = &sect->plist[i];
	bgnpolygon();
	for(j=0; j < p->vcount; j++)
	{
	    v2f(p->vlist[j]);
	}
	endpolygon();
    }
}


/* -------------- wire frame draw --------------- */

wdrawobj(obj, state)
    object_t *obj;
    long state;
{
    int i;

    curobj = obj;
    curmode = 0x0;

    wdrawnode(&obj->blist[0], state);

    modesoff();
}


wdrawnode(np, state)
    node_t *np;
    long state;
{
    int i;

    if (!(state & np->statebits))
	return;

    if (np->statebits & CULL)
    {
	if (cull(&curobj->glist[np->slist[0]]))
	    return;
	else
	    i = 1;
    }
    else
	i = 0;

    setmode(np->modebits);

    if (np->tcount)
    {
	pushmatrix();
	dotrans(np->tcount, np->tlist);
    }

    for (; i < np->scount; i++)
    {
	if (np->stlist[i] == BRANCH)
	    wdrawnode(&curobj->blist[np->slist[i]], state);
	else
	    switch(curobj->glist[np->slist[i]].type)
	    {
		case SSECTION:
		    wdrawssect(&curobj->glist[np->slist[i]]);
		    break;
		case FSECTION:
		    wdrawfsect(&curobj->glist[np->slist[i]]);
		    break;
		case PSECTION:
		    wdrawpsect(&curobj->glist[np->slist[i]]);
		    break;
		case CSECTION:
		    wdrawcsect(&curobj->glist[np->slist[i]]);
		    break;
		case CLS_GEOM:
		    drawclsgeom(&curobj->glist[np->slist[i]]);
		    break;
		default:
		    break;
	    }
    }

    if (np->tcount)
	popmatrix();
}


wdrawssect(sect)
    geometry_t *sect;
{
    int i, j;
    polygon_t *p;

    setmaterial(sect->material);

    for(i=0; i < sect->pcount; i++)
    {
	p = &sect->plist[i];
	bgnclosedline();
	for(j=0; j < p->vcount; j++)
	{
	    n3f(p->nlist[j]);
	    v3f(p->vlist[j]);
	}
	endclosedline();
    }
}


wdrawfsect(sect)
    geometry_t *sect;
{
    int i, j;
    polygon_t *p;

    setmaterial(sect->material);

    for(i=0; i < sect->pcount; i++)
    {
	p = &sect->plist[i];
	bgnclosedline();
	n3f(p->normal);
	for(j=0; j < p->vcount; j++)
	{
	    v3f(p->vlist[j]);
	}
	endclosedline();
    }
}


wdrawpsect(sect)
    geometry_t *sect;
{
    int i, j;
    polygon_t *p;

    setmaterial(sect->material);

    n3f(sect->normal);
    for(i=0; i < sect->pcount; i++)
    {
	p = &sect->plist[i];
	bgnclosedline();
	for(j=0; j < p->vcount; j++)
	    v3f(p->vlist[j]);
	endclosedline();
    }
}


wdrawcsect(sect)
    geometry_t *sect;
{
    int i, j;
    polygon_t *p;

    cpack(sect->color);

    for(i=0; i < sect->pcount; i++)
    {
	p = &sect->plist[i];
	bgnclosedline();
	for(j=0; j < p->vcount; j++)
	    v3f(p->vlist[j]);
	endclosedline();
    }
}


/* -------------- wire frame draw --------------- */

tswdrawobj(obj, state)
    object_t *obj;
    long state;
{
    int i;

    curobj = obj;
    curmode = 0x0;

    tswdrawnode(&obj->blist[0], state);
}


tswdrawnode(np, state)
    node_t *np;
    long state;
{
    int i;

    if (!(state & np->statebits))
	return;

    if (np->statebits & CULL)
    {
	if (cull(&curobj->glist[np->slist[0]]))
	    return;
	else
	    i = 1;
    }
    else
	i = 0;

    if (np->tcount)
    {
	pushmatrix();
	dotrans(np->tcount, np->tlist);
    }

    for (; i < np->scount; i++)
    {
	if (np->stlist[i] == BRANCH)
	    wdrawnode(&curobj->blist[np->slist[i]], state);
	else
	    switch(curobj->glist[np->slist[i]].type)
	    {
		case SSECTION:
		case FSECTION:
		case PSECTION:
		case CSECTION:
		case CLS_GEOM:
		    swdrawsect(&curobj->glist[np->slist[i]]);
		    break;
		default:
		    break;
	    }
    }

    if (np->tcount)
	popmatrix();
}



/* -------------- misc --------------- */

cull(g)
    geometry_t *g;
{
    int i, j;
    polygon_t *p;
    short fbbuf[10];

    feedback(fbbuf, 10);

    for(i=0; i < g->pcount; i++)
    {
	p = &g->plist[i];
	bgnpolygon();
	for(j=0; j < p->vcount; j++)
	    v3f(p->vlist[j]);
	endpolygon();
    }

    if (endfeedback(fbbuf))
	return(FALSE);
    else
	return(TRUE);
}


out_vlist(vlist, count)
    float **vlist;
    int count;
{
    int i;

    switch(count)
    {
	case 0:
	    break;
	case 1:
	    v3f(vlist[0]);
	    break;
	case 2:
	    v3f(vlist[0]);
	    v3f(vlist[1]);
	    break;
	case 3:
	    v3f(vlist[0]);
	    v3f(vlist[1]);
	    v3f(vlist[2]);
	    break;
	case 4:
	    v3f(vlist[0]);
	    v3f(vlist[1]);
	    v3f(vlist[2]);
	    v3f(vlist[3]);
	    break;
	case 5:
	    v3f(vlist[0]);
	    v3f(vlist[1]);
	    v3f(vlist[2]);
	    v3f(vlist[3]);
	    v3f(vlist[4]);
	    break;
	case 6:
	    v3f(vlist[0]);
	    v3f(vlist[1]);
	    v3f(vlist[2]);
	    v3f(vlist[3]);
	    v3f(vlist[4]);
	    v3f(vlist[5]);
	    break;
	case 7:
	    v3f(vlist[0]);
	    v3f(vlist[1]);
	    v3f(vlist[2]);
	    v3f(vlist[3]);
	    v3f(vlist[4]);
	    v3f(vlist[5]);
	    v3f(vlist[6]);
	    break;
	case 8:
	    v3f(vlist[0]);
	    v3f(vlist[1]);
	    v3f(vlist[2]);
	    v3f(vlist[3]);
	    v3f(vlist[4]);
	    v3f(vlist[5]);
	    v3f(vlist[6]);
	    v3f(vlist[7]);
	    break;
	case 9:
	    v3f(vlist[0]);
	    v3f(vlist[1]);
	    v3f(vlist[2]);
	    v3f(vlist[3]);
	    v3f(vlist[4]);
	    v3f(vlist[5]);
	    v3f(vlist[6]);
	    v3f(vlist[7]);
	    v3f(vlist[8]);
	    break;
	case 10:
	    v3f(vlist[0]);
	    v3f(vlist[1]);
	    v3f(vlist[2]);
	    v3f(vlist[3]);
	    v3f(vlist[4]);
	    v3f(vlist[5]);
	    v3f(vlist[6]);
	    v3f(vlist[7]);
	    v3f(vlist[8]);
	    v3f(vlist[9]);
	    break;
	default:
	    for(i=10; i < count; i++)
	    {
		v3f(vlist[i]);
	    }
	    break;
    }
}


out_vnlist(vlist, nlist, count)
    float **vlist;
    float **nlist;
    int count;
{
    int i;

    switch(count)
    {
	case 0:
	    break;
	case 1:
	    n3f(nlist[0]);
	    v3f(vlist[0]);
	    break;
	case 2:
	    n3f(nlist[0]);
	    v3f(vlist[0]);
	    n3f(nlist[1]);
	    v3f(vlist[1]);
	    break;
	case 3:
	    n3f(nlist[0]);
	    v3f(vlist[0]);
	    n3f(nlist[1]);
	    v3f(vlist[1]);
	    n3f(nlist[2]);
	    v3f(vlist[2]);
	    break;
	case 4:
	    n3f(nlist[0]);
	    v3f(vlist[0]);
	    n3f(nlist[1]);
	    v3f(vlist[1]);
	    n3f(nlist[2]);
	    v3f(vlist[2]);
	    n3f(nlist[3]);
	    v3f(vlist[3]);
	    break;
	case 5:
	    n3f(nlist[0]);
	    v3f(vlist[0]);
	    n3f(nlist[1]);
	    v3f(vlist[1]);
	    n3f(nlist[2]);
	    v3f(vlist[2]);
	    n3f(nlist[3]);
	    v3f(vlist[3]);
	    n3f(nlist[4]);
	    v3f(vlist[4]);
	    break;
	case 6:
	    n3f(nlist[0]);
	    v3f(vlist[0]);
	    n3f(nlist[1]);
	    v3f(vlist[1]);
	    n3f(nlist[2]);
	    v3f(vlist[2]);
	    n3f(nlist[3]);
	    v3f(vlist[3]);
	    n3f(nlist[4]);
	    v3f(vlist[4]);
	    n3f(nlist[5]);
	    v3f(vlist[5]);
	    break;
	case 7:
	    n3f(nlist[0]);
	    v3f(vlist[0]);
	    n3f(nlist[1]);
	    v3f(vlist[1]);
	    n3f(nlist[2]);
	    v3f(vlist[2]);
	    n3f(nlist[3]);
	    v3f(vlist[3]);
	    n3f(nlist[4]);
	    v3f(vlist[4]);
	    n3f(nlist[5]);
	    v3f(vlist[5]);
	    n3f(nlist[6]);
	    v3f(vlist[6]);
	    break;
	case 8:
	    n3f(nlist[0]);
	    v3f(vlist[0]);
	    n3f(nlist[1]);
	    v3f(vlist[1]);
	    n3f(nlist[2]);
	    v3f(vlist[2]);
	    n3f(nlist[3]);
	    v3f(vlist[3]);
	    n3f(nlist[4]);
	    v3f(vlist[4]);
	    n3f(nlist[5]);
	    v3f(vlist[5]);
	    n3f(nlist[6]);
	    v3f(vlist[6]);
	    n3f(nlist[7]);
	    v3f(vlist[7]);
	    break;
	case 9:
	    n3f(nlist[0]);
	    v3f(vlist[0]);
	    n3f(nlist[1]);
	    v3f(vlist[1]);
	    n3f(nlist[2]);
	    v3f(vlist[2]);
	    n3f(nlist[3]);
	    v3f(vlist[3]);
	    n3f(nlist[4]);
	    v3f(vlist[4]);
	    n3f(nlist[5]);
	    v3f(vlist[5]);
	    n3f(nlist[6]);
	    v3f(vlist[6]);
	    n3f(nlist[7]);
	    v3f(vlist[7]);
	    n3f(nlist[8]);
	    v3f(vlist[8]);
	    break;
	case 10:
	    n3f(nlist[0]);
	    v3f(vlist[0]);
	    n3f(nlist[1]);
	    v3f(vlist[1]);
	    n3f(nlist[2]);
	    v3f(vlist[2]);
	    n3f(nlist[3]);
	    v3f(vlist[3]);
	    n3f(nlist[4]);
	    v3f(vlist[4]);
	    n3f(nlist[5]);
	    v3f(vlist[5]);
	    n3f(nlist[6]);
	    v3f(vlist[6]);
	    n3f(nlist[7]);
	    v3f(vlist[7]);
	    n3f(nlist[8]);
	    v3f(vlist[8]);
	    n3f(nlist[9]);
	    v3f(vlist[9]);
	    break;
	default:
	    for(i=10; i < count; i++)
	    {
		n3f(nlist[i]);
		v3f(vlist[i]);
	    }
	    break;
    }
}



out_vclist(vlist, clist, count)
    float **vlist;
    long *clist;
    int count;
{
    int i;

    switch(count)
    {
	case 0:
	    break;
	case 1:
	    cpack(clist[0]);
	    v3f(vlist[0]);
	    break;
	case 2:
	    cpack(clist[0]);
	    v3f(vlist[0]);
	    cpack(clist[1]);
	    v3f(vlist[1]);
	    break;
	case 3:
	    cpack(clist[0]);
	    v3f(vlist[0]);
	    cpack(clist[1]);
	    v3f(vlist[1]);
	    cpack(clist[2]);
	    v3f(vlist[2]);
	    break;
	case 4:
	    cpack(clist[0]);
	    v3f(vlist[0]);
	    cpack(clist[1]);
	    v3f(vlist[1]);
	    cpack(clist[2]);
	    v3f(vlist[2]);
	    cpack(clist[3]);
	    v3f(vlist[3]);
	    break;
	case 5:
	    cpack(clist[0]);
	    v3f(vlist[0]);
	    cpack(clist[1]);
	    v3f(vlist[1]);
	    cpack(clist[2]);
	    v3f(vlist[2]);
	    cpack(clist[3]);
	    v3f(vlist[3]);
	    cpack(clist[4]);
	    v3f(vlist[4]);
	    break;
	case 6:
	    cpack(clist[0]);
	    v3f(vlist[0]);
	    cpack(clist[1]);
	    v3f(vlist[1]);
	    cpack(clist[2]);
	    v3f(vlist[2]);
	    cpack(clist[3]);
	    v3f(vlist[3]);
	    cpack(clist[4]);
	    v3f(vlist[4]);
	    cpack(clist[5]);
	    v3f(vlist[5]);
	    break;
	case 7:
	    cpack(clist[0]);
	    v3f(vlist[0]);
	    cpack(clist[1]);
	    v3f(vlist[1]);
	    cpack(clist[2]);
	    v3f(vlist[2]);
	    cpack(clist[3]);
	    v3f(vlist[3]);
	    cpack(clist[4]);
	    v3f(vlist[4]);
	    cpack(clist[5]);
	    v3f(vlist[5]);
	    cpack(clist[6]);
	    v3f(vlist[6]);
	    break;
	case 8:
	    cpack(clist[0]);
	    v3f(vlist[0]);
	    cpack(clist[1]);
	    v3f(vlist[1]);
	    cpack(clist[2]);
	    v3f(vlist[2]);
	    cpack(clist[3]);
	    v3f(vlist[3]);
	    cpack(clist[4]);
	    v3f(vlist[4]);
	    cpack(clist[5]);
	    v3f(vlist[5]);
	    cpack(clist[6]);
	    v3f(vlist[6]);
	    cpack(clist[7]);
	    v3f(vlist[7]);
	    break;
	case 9:
	    cpack(clist[0]);
	    v3f(vlist[0]);
	    cpack(clist[1]);
	    v3f(vlist[1]);
	    cpack(clist[2]);
	    v3f(vlist[2]);
	    cpack(clist[3]);
	    v3f(vlist[3]);
	    cpack(clist[4]);
	    v3f(vlist[4]);
	    cpack(clist[5]);
	    v3f(vlist[5]);
	    cpack(clist[6]);
	    v3f(vlist[6]);
	    cpack(clist[7]);
	    v3f(vlist[7]);
	    cpack(clist[8]);
	    v3f(vlist[8]);
	    break;
	case 10:
	    cpack(clist[0]);
	    v3f(vlist[0]);
	    cpack(clist[1]);
	    v3f(vlist[1]);
	    cpack(clist[2]);
	    v3f(vlist[2]);
	    cpack(clist[3]);
	    v3f(vlist[3]);
	    cpack(clist[4]);
	    v3f(vlist[4]);
	    cpack(clist[5]);
	    v3f(vlist[5]);
	    cpack(clist[6]);
	    v3f(vlist[6]);
	    cpack(clist[7]);
	    v3f(vlist[7]);
	    cpack(clist[8]);
	    v3f(vlist[8]);
	    cpack(clist[9]);
	    v3f(vlist[9]);
	    break;
	default:
	    for(i=10; i < count; i++)
	    {
		cpack(clist[i]);
		v3f(vlist[i]);
	    }
	    break;
    }
}


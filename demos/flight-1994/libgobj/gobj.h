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


/*
 *  array offsets
 */
#define X 0
#define Y 1
#define Z 2


/*
 *  types of geometry sections
 */
#define BRANCH		0
#define GEOMETRY	1


/*
 *  types of geometry sections
 *  1st letter C = color  L = Lighted  I = color indexed
 *  2nd letter P = polygonal  L = Line  D = point  T = tmesh  M = poly/line/pt
 *  3nd letter V = per vertex  U = per unit of(polygon, line, or points)
 *	       S = for the entire geometry section
 */
#define GEOM		 0
#define LPV_GEOM	 5
#define LPU_GEOM	 6
#define LPS_GEOM	 7
#define CPV_GEOM 	10
#define CPU_GEOM 	11
#define CPS_GEOM 	12

#define LLV_GEOM	13
#define LLU_GEOM	14
#define LLS_GEOM	15
#define CLV_GEOM	16
#define CLU_GEOM	17
#define CLS_GEOM 	18

#define LDV_GEOM	19
#define LDU_GEOM	20
#define LDS_GEOM	21
#define CDV_GEOM	22
#define CDU_GEOM	23
#define CDS_GEOM 	24

#define LTV_GEOM	25
#define LTU_GEOM	26
#define LTS_GEOM	27
#define CTV_GEOM	28
#define CTU_GEOM	29
#define CTS_GEOM 	30

#define IMV_GEOM	31
#define IMU_GEOM	32
#define IPV_GEOM	33
#define IPU_GEOM	34

#define TLPU_GEOM	100

#define SSECTION	 5
#define FSECTION	 6
#define PSECTION	 7
#define LSECTION	 8
#define CSSECTION	10
#define CFSECTION	11
#define CSECTION	12
#define CLSECTION	13


/*
 *  types of transforms
 */
#define ROTX		0
#define ROTY		1
#define ROTZ		2
#define TRANSLATE	3
#define SCALE		4

/*
 *  types of color index objects 
 */
#define CIDX_PNT	0
#define CIDX_LINE	1
#define CIDX_POLF	2
#define CIDX_POLY	3

/*
 *  mode bit information
 */
#define MBACKFACE	0x1
#define MTRANSPERENT	0x2
#define MZMASK		0x4
#define MCMASK		0x8

/*
 *  sritch bit information
 */
#define EV_RIGHT	0x1000000
#define EV_ABOVE	0x2000000
#define EV_BEHIND	0x4000000
#define EV_MASK		0x7000000
#define EV_SHIFT	24

/*
 *    Other 
 */
#define M_EIGHTVIEW     0x10000000

/*
 *  culling specified by high bit of state
 */
#define CULL 0x80000000

typedef struct trans {
    int type;			/* rotate translate or scale */
    int angle;			/* for rotate */
    float x, y, z;		/* for translate and scale */
} trans_t;


/*
 *  generic section
 */
typedef struct generic {
    int type;
} generic_t;


/*
 *  branch node section
 */
typedef struct node {
    int type;
    unsigned long statebits;
    unsigned long modebits;
    int tcount;			/* number of transforms */
    int *tlist;			/* list of transforms */
    int scount;			/* number of sections */
    int *slist;			/* list of sections numbers */
    int *stlist;		/* list of sections types */
} node_t;


typedef struct polygon {
    int vcount;
    int *vnlist;
    float **vlist;
    float **nlist;
    float **xlist;
    float normal[3];
    long color;
    long type;
    long *clist;
} polygon_t;


/*
 *  geometry section
 */
typedef struct geometry {
    int type;
    long material;
    long color;
    float normal[3];
    int pcount;
    polygon_t *plist;
    int vcount;
    float **vlist;
    float **nlist;
    float **xlist;
    long *clist;
} geometry_t;


typedef struct objct {
    int bcount;			/* number of branch nodes */
    node_t *blist;		/* list of branch nodes */
    int tcount;
    trans_t *tlist;
    int gcount;			/* number of geometry nodes */
    geometry_t *glist;		/* list of geometry nodes */
    int mcount;			/* number of material nodes */
    int *mlist;			/* list of material nodes */
    float radius;
} object_t;


/*
 *  material lists
 */

typedef struct {
    long id;
    float data[21];
} mat_t;

extern int mcount;		/* number of material nodes */
extern mat_t *mlist;		/* list of material nodes */


/*
 *  prototypes for read.c
 */
object_t *readobj(char *fname);

void readnode_list(object_t *obj, int count);

void readtrans_list(object_t *obj, int count);

void readgeom_list(object_t *obj, int count);

void readmat_list(object_t *obj, int count);

void readnode(node_t *np);

void readssect(geometry_t *sect);

void readfsect(geometry_t *sect);

void read_tlpu_geom(geometry_t *sect);

void readpsect(geometry_t *sect);

void readcsect(geometry_t *sect);

void readcdvgeom(geometry_t *sect);

void readcdugeom(geometry_t *sect);

void read_imu_geom(geometry_t *sect);

void read_imv_geom(geometry_t *sect);

void read_ipu_geom(geometry_t *sect);

void read_ipv_geom(geometry_t *sect);

void readtrans(trans_t *t);

int readnumlist(int **nlist);

int readcnumlist(int **nlist);

int readblist(int **nlist, int **tlist);

int readmat();

void resolve_mat(object_t *obj);

void readerror(char *errbuf);

int fillbuf();

int isbinary();

object_t *breadobj(char *fname);

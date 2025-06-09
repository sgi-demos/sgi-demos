/**************************************************************************
 *									  *
 * 		 Copyright (C) 1984, Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/


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
 *  1st letter C = color  L = Lighted
 *  2nd letter P = polygonal  L = Line  D = point
 *  3nd letter V = per vertex  U = per unit of(polygon, line, or points)
	       S = for the entire geometry section
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
 *  mode bit information
 */
#define MBACKFACE	0x1
#define MTRANSPERENT	0x2
#define MZMASK		0x4
#define MCMASK		0x8


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
    float normal[3];
    long color;
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
    long *clist;
} geometry_t;


typedef struct objct {
    int bcount;			/* number of branch nodes */
    node_t *blist;		/* list of branch nodes */
    int tcount;
    trans_t *tlist;
    int gcount;			/* number of geometry nodes */
    geometry_t *glist;		/* list of geometry nodes */
} object_t;


extern object_t *readobj();


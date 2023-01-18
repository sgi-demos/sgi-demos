/*
 *	 Kurt Akeley				31 October 1983
 *
 *	definitions for the new convex volume system
 */

/* values */
#define MAXFACE		200		/* maximum number of faces/cv	    */
#define MAXVERTEX	100		/* maximum number of vertexes/face  */
#define NOTVISIBLE	0x7fff		/* illegal color index to indicate  */
					/*   that a face is not visible     */
#define NODEPTH		-1
#define MAXFLOAT	20		/* maximum number of chars in float */
#define NULLOBJECT	-1
#define NIL		0
#define STARTPRIORITY	3

/* topsort values */
#define MAXSORT		MAXCV		/* maximum number of cvs or groups  */
					/*   that can be sorted		    */
#define MAXRELATION	(MAXCV*MAXCV)	/* maximum number of relations that */
					/*   can be specified for a sort    */

/* typedefs */
typedef long Name;			/* names are 32 bits		    */
typedef short Number;			/* numbers are only 16 bits	    */
#define LOCAL				/* static except during debug	    */

/* structure definitions */
struct _Face {
    Name name;				/* integer name of the face 	    */
    Object polyobj;			/* Object that draws the face 	    */
    Object normobj;			/* mult matrix object, only 1 for   */
					/*   every 4 faces		    */
    Boolean drawable;			/* true if face is ever to be drawn,*/
					/*   false for partition planes	    */
    Colorindex initcolor;		/* index used as basis for shaded   */
					/*   color computation		    */
    Colorindex compcolor;		/* computed color index based on    */
					/*   light source normal and initcol*/
    struct _Face *next;			/* allow faces to be linked	    */
    };
struct _Glob {
    Name name;				/* name of global value		    */
    float value;			/* floating value that is set while */
					/*   cv is defined and then	    */
					/*   accessed later		    */
    struct _Glob *next;			/* allow globs to be linked	    */
    };
struct _Cvrule {
    Name cvname;			/* name of decision cv		    */
    Name facename;			/* face within decision cv	    */
    short priority;			/* priority of this rule, 0 is	    */
					/*   highest, no upper limit.	    */
    Name fcvname;			/* name of cv to draw last if	    */
					/*   the test fails		    */
    Name bcvname;			/* name of cv to draw last if	    */
					/*   the test succeeds		    */
    Colorindex *compcolor;		/* pointer to computed color var    */
					/*   within the decision face	    */
    struct _Cv *frontcv, *backcv;	/* pointers to the cvs specified    */
					/*   by name as front and back      */
    Number frontnumber, backnumber;	/* values used only by the topsort  */
					/*   algorithm (range 1..n)	    */
    struct _Cvrule *next;		/* allow rules to be linked	    */
    };
struct _Cv {
    Name name;				/* integer name of the convex volume*/
    Number maxface;			/* number of faces (drawable or	    */
					/*   otherwise) in the cv	    */
    short matrixstate;			/* matrix state that must exist	    */
					/*   while the cv is computed/drawn */
    struct _Face *face;			/* list of faces		    */
    struct _Cv *next;			/* allow cvs to be linked	    */
    };
struct _Grouprule {
    Name groupname;			/* name of decision group	    */
    Name cvname;			/* name of decision cv	    	    */
    Name facename;			/* face within decision cv	    */
    short priority;			/* priority of this rule, 0 is	    */
					/*   highest, no upper limit.	    */
    Name fgroupname;			/* name of group to draw last if    */
					/*   the test fails		    */
    Name bgroupname;			/* name of group to draw last if    */
					/*   the test succeeds		    */
    Colorindex *compcolor;		/* pointer to computed color var    */
					/*   within the decision face	    */
    struct _Group *frontgroup;		/* pointers to the groups specified */
    struct _Group *backgroup;		/*   by name as front and back      */
    Number frontnumber, backnumber;	/* values used only by the topsort  */
					/*   algorithm (range 1..n)	    */
    struct _Grouprule *next;		/* allow rules to be linked	    */
    };
struct _Group {
    Name name;				/* integer name of group	    */
    Number maxcv;			/* number of cvs in the group	    */
    Number maxrule;			/* number of rules in the group     */
    struct _Cv *cv;			/* pointer to list of cvs	    */
    struct _Cvrule *rule;		/* pointer to list of rules	    */
    struct _Group *next;		/* allow groups to be linked	    */
    };
struct _Set {
    Number maxgroup;			/* number of groups in the set	    */
    Number maxrule;			/* number of rules in the set	    */
    struct _Grouprule *rule;		/* list of rules for ordering groups*/
    struct _Group *group;		/* list of groups		    */
    struct _Glob *glob;			/* list of global values	    */
    struct _Set *next;			/* for expansion, not used now	    */
    };

typedef struct _Face Face;
typedef struct _Glob Glob;
typedef struct _Cvrule Cvrule;
typedef struct _Cv Cv;
typedef struct _Grouprule Grouprule;
typedef struct _Group Group;
typedef struct _Set Set;

/* parser tokens */
#define BEGINGROUP		'['
#define ENDGROUP		']'
#define BEGINCV			'{'
#define ENDCV			'}'
#define BEGINFACE		'('
#define ENDFACE			')'
#define INITCOLOR		'c'
#define VERTEX			'v'
#define MATRIXSTATE		'm'
#define CVRULE			'r'
#define GROUPRULE		'R'
#define GLOBALVALUE		'g'
#define FLOATTOKEN		'f'
#define ERRORTOKEN		'e'
#define ENDTOKEN		EOF

/* parser modes */
#define DONE			0
#define OUT			1
#define INGROUP			2
#define INCV			3
#define INFACE			4

/* functions */
Set *makeSET ();
float globvalue ();
Group *findgroup ();
Cv *findcv ();
Face *findface ();
Glob *findglob ();
Boolean topsort ();
Boolean inittopsort ();

/* global variables */
extern Cv **cvrulemap;		/* map cvnumbers into cvs */
extern Number *cvsortlist;	/* list of sorted cvnumbers */
extern Group **grouprulemap;	/* map groupnumbers into groups */
extern Number *groupsortlist;	/* list of sorted groupnumbers */


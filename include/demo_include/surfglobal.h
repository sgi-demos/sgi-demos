#include "gl.h"
#include "device.h"

typedef Matrix Patch[4];    /* define a structure which holds the four
			    curves of the patch */

#define HALFSIZE 9.0

#define CURVE_PRECISION 14 

#define SHADOWS 8

#define XHALFSIZE HALFSIZE * 1.5
#define YHALFSIZE HALFSIZE
#define ZHALFSIZE HALFSIZE * 1.5

/* 3d cursor types */
#define	FULL_WIDTH 0
#define	SHADOW_CROSS 1
#define XY_Z_SHADOW 2
#define ZX_Y_SHADOW 3
#define YZ_X_SHADOW 4

/* the patch blending function to the interior of patches */
#define CCENTRAL 2
#define BCENTRAL 5

/* the patch blending funtion for the param low edge of the patches 
for generating the degenerate cubics along the edge */
#define CLOWEND 3
#define BLOWEND 6

/* the patch blending funtion for the param high edge of the patches 
for generating the degenerate cubics along the edge */
#define CHIGHEND 4
#define BHIGHEND 7

/* the blending function for Bezier curves */
#define BEZIER 1

/* the various texture ids */
#define WMANTBASE 20
#define HALFTONE 1+WMANTBASE
#define CROSSHATCH 2+WMANTBASE

/* the name for the buttons */
#define	BUTTONS 1

/* the name for the control points */
#define POINTS 2
#define XY 1
#define ZX 2
#define YZ 3

#define X_Y 0
#define Z_X 1
#define Y_Z 2

#define X 4
#define Y 2
#define Z 1

/* icons for the menu */
#define ROT_CROSS 1
#define VIEW_IT 2
#define REFLECT_XY 7
#define REFLECT_ZX 5
#define REFLECT_YZ 6
#define SUBDIVIDE_IN_U 4
#define SUBDIVIDE_IN_V 3

#define BIG 100000000

#define min(x,y)  (x < y ? x : y)
#define max(x,y)  (x > y ? x : y)
#define abs(x) (x > 0 ? x  : -x)

extern char *my_malloc();

    extern short iaa,ibb;
#define SETCURSOR(x,y,z) {iaa=getvaluator(MOUSEX); ibb=getvaluator(MOUSEY); setcursor(x,y,z); setvaluator(MOUSEX,iaa,0,1023); setvaluator(MOUSEY,ibb,0,767);}

    extern char  Hostname[], Loginname[], Password[];
    extern char  Filename[];
    extern char  Lockfile[];
    extern char  Initfile[];
    extern float Eps, Hsize, Delta_i;

    extern float 	*(Itervalues[256]);
    extern float 	*(Deltas[256]);
    extern int		Signs[256];
    extern float	*(Ind_deltas[4][4]);
    extern int		Updates_to_do;

    extern Coord Deltavalues[];
    extern int  Backgroundxrotation;
    extern int  Backgroundyrotation;
    extern int	Reflected_row, Reflected_col;
    extern int 	Row_reflected, Col_reflected;
    extern int 	Row_signx;
    extern int 	Col_signx;
    extern int 	Row_signy;
    extern int 	Col_signy;
    extern int 	Row_signz;
    extern int 	Col_signz;

    extern Object 	Three_d_pnt;
    extern Object 	Xy_pnt;
    extern Object 	Zx_pnt;
    extern Object 	Yz_pnt;

    extern int		Fovy;
    extern Coord	Aspect, Near, Far;
    extern Coord	Tx, Ty, Tz;

    extern float	Majordiv;
    extern float	Minordiv;
    extern Coord	Halfsize_x;
    extern Coord	Halfsize_y;
    extern Coord	Halfsize_z;
    extern Coord	Halfsize_conversion;

    extern Colorindex	Backgroundmask;
    extern Colorindex	Wallcolor;
    extern Colorindex	Majorcolor;
    extern Colorindex	Minorcolor;
    extern Colorindex	Cursormask;
    extern Colorindex	Cursorcolor;
    extern Colorindex	Drawingmask;
    extern Colorindex	Rubbermask;
    extern Colorindex	Rubbercolor;

    extern int		Clow, Rlow, Climit, Rlimit;

    extern Object	Background;
    extern Object	Menus;
    extern Object	Surface_points;
    extern Object	**Patch_points;
    extern Object	Surface;
    extern Object	Shadowsurface;
    extern Patch	***Subpatches;
    extern char		**Subpatchupdated;
    extern Patch	***ShadowsubpatchesX_Y;
    extern Patch	***ShadowsubpatchesY_Z;
    extern Patch	***ShadowsubpatchesZ_X;
    extern Object	Changing_shape;

    extern int		Lastpointrow;
    extern int		Lastpointcol;

    extern RGBvalue	Default_minor[3];
    extern RGBvalue	Default_major[3];
    extern RGBvalue	Default_walls[3];
    extern RGBvalue	Default_rubber[3];
    extern RGBvalue	Default_highcolor[3];

    extern RGBvalue	Default_red;
    extern RGBvalue	Default_green;
    extern RGBvalue	Default_blue;

    extern RGBvalue	Default_lo_comp;
    extern RGBvalue	Default_hi_comp;
    extern RGBvalue	Cursor_red;
    extern RGBvalue	Cursor_green;
    extern RGBvalue	Cursor_blue;
    extern RGBvalue	Default_comp_break;

    extern Coord	Cursor_x;
    extern Coord	Cursor_y;
    extern Coord	Cursor_z;

    extern Coord	**Pointsx;
    extern Coord	**Pointsy;
    extern Coord	**Pointsz;
    extern int		Nrows, Ncols;

    extern int		SurfShadow[3];
    extern int		Anyshadows;

    extern int		PointShadow[3];

    extern short	Staticprecision;
    extern short	Staticucurves;
    extern short	Staticvcurves;
    extern short	Shadowcurves;

    extern Matrix	Subdivbasis;

    extern Matrix	Unit;

    extern float	*Default_central_basis;
    extern float	*Default_high_basis;
    extern float	*Default_low_basis;

    extern int		Current_view;
    extern int		Points_rotated;
    extern int		Reflection_state[3];

    extern Coord	Change_amount;

    extern int		Rotation_limit;


#define WMANBASE 14
#define ERRORS	1+WMANBASE
#define HOURGLASS1 	4+WMANBASE
#define HOURGLASS2 	5+WMANBASE
#define HOURGLASS3 	6+WMANBASE
#define HOURGLASS4 	7+WMANBASE
#define HOURGLASS5 	8+WMANBASE
#define HOURGLASS6 	9+WMANBASE
#define MOUSE_0  13+WMANBASE
#define MOUSE_1  14+WMANBASE
#define MOUSE_2  15+WMANBASE
#define MOUSE_3  16+WMANBASE
#define MOUSE_4  17+WMANBASE
#define MOUSE_5  18+WMANBASE
#define MOUSE_6  19+WMANBASE
#define MOUSE_7  20+WMANBASE
#define INVMOUSE  21+WMANBASE
#define XCURS 22+WMANBASE
#define YCURS 23+WMANBASE
#define ZCURS 24+WMANBASE
#define GRAB 25+WMANBASE
#define XGRAB 26+WMANBASE
#define YGRAB 27+WMANBASE
#define ZGRAB 28+WMANBASE
#define QUESTION 29+WMANBASE

extern Matrix Itermat;
extern Matrix Itermat_transp;
extern Matrix Conversionmatrix;
extern Matrix Bezier ; 

extern Matrix Cardinal ;  

extern Matrix invCardinal ;  

extern Matrix Lowend_c_quad ;

extern Matrix Highend_c_quad ;

extern Matrix	B_spline ;

extern Matrix	invB_spline ;

extern Matrix	Lowend_b_quad ;

extern Matrix	Highend_b_quad ;

extern Matrix	subdivmat ; 

/* pkr */ extern int mouse_buttons ;

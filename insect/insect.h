
#define HALFTONE 1
#define PI 3.1415926536
	/*  resolution of movement  */
#define RES_INT 30
#define RES_FLOAT 30.0
	/*  stuff for making body  */
#define SIN30 (0.5)
#define COS30 (0.866025404)
#define SIN60 (0.866025404)
#define COS60 (0.5)
#define SIN15 (0.258819045)
#define COS15 (0.965925826)
#define COS45 (0.707106781)
#define SIN45 (0.707106781)
#define A2 0.088388348	/*  (1.0/ (8.0 * sqrt(2.0)))  */
#define R2 0.125	/*  (sqrt(2 * A2 * A2))  */
#define A1 0.411611652	/*  (0.5 - A2)  */
#define R1 0.420994836  /*  (sqrt(A1 * A1 + A2 * A2))  */
#define REACH 1.6

/* Eclipse 8 bit color stuff */
#define ECLIPSE8_GRID 2
#define ECLIPSE8_GRAY 1
#define ECLIPSE8_NCOLORS 10
#define ECLIPSE8_SKYBLUE 3

Object screen,viewit,shadow,body,hip[6],thigh[6],shin[6],kneeball[6];
Object body_shadow,hip_shadow,thigh_shadow,shin_shadow,kneeball_shadow;

Tag cphitag,cthetatag,cposittag,windowtag;

Angle knee[6];
Angle hip_phi[6];
Angle hip_theta[6];

extern Angle degrees();
extern float dot();
extern float integer();
extern float frac();
extern float fabso();

Coord sdepth;
float glsin,glcos;
float px,py;
float light[3],phi,theta;
Boolean legup[6];
float legx[6],legy[6];

float cx,cy,cz,cvx,cvy,cvz;
float dmr[6],fr[6];
Angle ctheta,cphi,cvtheta,cvphi;
Boolean follow;

Coord b1[4][3];
Coord b2[4][3];
Coord b3[4][3];
Coord b4[4][3];
Coord b5[4][3];
Coord b6[4][3];
Coord h1[4][3];
Coord h2[4][3];
Coord h3[3][3];
Coord t1[4][3];
Coord t2[3][3];
Coord t3[3][3];
Coord t4[3][3];
Coord t5[3][3];
Coord t6[3][3];
Coord t7[3][3];
Coord t8[4][3];
Coord s1[4][3];
Coord s2[4][3];
Coord s3[4][3];
Coord s4[4][3];
Coord s5[4][3];
Coord k1[4][3];
Coord k2[6][3];
Coord k3[6][3];
Coord b7[12][3];
Coord b8[12][3];
Icoord scr[4][2];


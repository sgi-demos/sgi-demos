
#define MAXPLAYERS 10

#define PI 3.14159265

/*
 *  color defs
 */
extern int MASK_HUD;
extern int HUD_MASK;
extern int HUD_Y_MASK;

extern int HUD_GREEN;
extern int HUD_YELLOW;
extern int HUD_BLACK;
extern int HUD_RED;
extern int HUD_BLUE;

extern int BLUE1;
extern int BLUE2;
extern int GREEN1;
extern int GREEN2;

extern int LGRAY;
extern int MGRAY;
extern int DGRAY;

extern int SKY;

extern bitplanes;

#ifdef CLOVER
#define MOUSE_CENT 300		/* mouse center position */
#else
#define MOUSE_CENT 300		/* mouse center position */
#endif

/*
 *  sectors
 */
#define NUMSECTORS	9
#define NORTHWEST	0
#define NORTH		1
#define NORTHEAST	2
#define WEST		3
#define EAST		4
#define SOUTHWEST	5
#define SOUTH		6
#define SOUTHEAST	7
#define INMAZE		8

/*
 *  draw sectors
 */
#define DRAW_SECT_M() if (sector[INMAZE] && visible_sect(INMAZE))\
		     draw_obj(sector[INMAZE])
#define DRAW_SECT_N() if (sector[NORTH] && visible_sect(NORTH))\
		     draw_obj(sector[NORTH])
#define DRAW_SECT_S() if (sector[SOUTH] && visible_sect(SOUTH))\
		     draw_obj(sector[SOUTH])
#define DRAW_SECT_E() if (sector[EAST] && visible_sect(EAST))\
		     draw_obj(sector[EAST])
#define DRAW_SECT_W() if (sector[WEST] && visible_sect(WEST))\
		     draw_obj(sector[WEST])
#define DRAW_SECT_NE() if (sector[NORTHEAST] && visible_sect(NORTHEAST))\
		     draw_obj(sector[NORTHEAST])
#define DRAW_SECT_SE() if (sector[SOUTHEAST] && visible_sect(SOUTHEAST))\
		     draw_obj(sector[SOUTHEAST])
#define DRAW_SECT_NW() if (sector[NORTHWEST] && visible_sect(NORTHWEST))\
		     draw_obj(sector[NORTHWEST])
#define DRAW_SECT_SW() if (sector[SOUTHWEST] && visible_sect(SOUTHWEST))\
		     draw_obj(sector[SOUTHWEST])
/*
 *  maze defs
 */
/*
#define MSIZ 16
#define MSHIFT 4
#define LOWBITS 017
*/
#define MSIZ 32
#define MSHIFT 5
#define LOWBITS 037
/*
#define MSIZ 64
#define MSHIFT 6
#define LOWBITS 077
*/
#define SHIFT 2
#define WL 4

#define GRID 8
#define BORDER 128
#define MAZE (WL*MSIZ)



/*
 *  types of things
 *
 *  bits	meaning
 *   0-1	shot number
 *   0-1	mech type
 *     2	is a player
 *   3-5	is a missile
 *     3	is a cannon
 *     4	is a rocket
 *     6	hit something
 *  7-10	what was hit
 *  7-10	all on means hit a wall
 *    11	object is dying
 *    12	object is explodeing
 *    13	Dead mech
 */
#define NOTHING		0x00000000
#define GREEN_MECH	0x00000000
#define BLUE_MECH	0x00000001
#define MECH_TYPE	0x00000003
#define SHOT_NUM	0x00000003
#define PLAYER		0x00000020
#define MISSILE		0x0000001C
#define CANNON		0x00000004
#define ROCKET		0x00000008
#define DID_HIT		0x00000040
#define HIT_WHAT	0x00000780
#define HIT_WALL	0x00000780
#define CLEAR_WHAT      0xfffff87f
#define WHAT_SHIFT      07
#define DEATH		0x00000800
#define EXPLODE		0x00001000
#define DEAD		0x00002000


typedef struct thing {
    unsigned int type;
    char name[12];
    int id;
    float xpos, ypos, zpos;
    float lastx, lastz;
    int sect, last_sect;
    float range;
    Angle yrot, rel_rot;
    /* robot state info */
    Angle anckle_rot, knee_rot;
    Angle torso_x_rot, torso_z_rot;
    struct thing *next;
} Thing;


typedef struct mech {
    Object mech_torso[4],
	   mech_lf_foot[4], mech_lb_foot[4],
	   mech_rf_foot[4], mech_rb_foot[4],
	   mech_ll_leg[4], mech_lu_leg[4],
	   mech_rl_leg[4], mech_ru_leg[4],
	   mech_ll_arm[4], mech_lu_arm[4],
	   mech_rl_arm[4], mech_ru_arm[4],
	   mech_r_hand;
} Mech;

extern Mech green_mech, blue_mech;

extern float get_range();
extern struct thing player[MAXPLAYERS], shots[MAXPLAYERS][3], *shot;

extern int speed, throttle, turn, thrust;
extern float velocity;
extern Coord xpos, ypos, zpos, lastx, lastz;
extern Angle wrot;

extern Object base_hud;
extern Tag MECH_ROT, MECH_POS, MECH_VIEW;

extern Object arena, maze_N, maze_S, maze_E, maze_W, maze_top_b, maze_top_t;

/* lists of objects by location */
extern struct thing *sector[];
extern struct thing *maze_obj[];

extern float radar_zoom;
extern double zoom;
extern Matrix hud_matrix;

extern struct thing *sort_obj();

extern int sect, last_sect;

extern short maze_w[MSIZ*MSIZ][4];
extern short maze_s[MSIZ*MSIZ];
#define N 0
#define E 1
#define S 2
#define W 3

#define HALFTONE 1

#define RANGE(obj) sqrt(pow(fabs(obj->xpos - xpos), 2.0) +\
			pow(fabs(obj->zpos - zpos), 2.0))
#define M_RANGE(obj) sqrt(pow(fabs(obj->xpos - mis->xpos), 2.0) +\
			  pow(fabs(obj->zpos - mis->zpos), 2.0))

extern int id;


extern int damage;		/* amount of damage taken */
extern int explode_counter;	/* explosion timer */
extern int was_shot;		/* was shot this frame */

#define ROLL(i) ((rand() >> 1) % i)

extern int did_colide;

extern int network;

extern int winw, winh;

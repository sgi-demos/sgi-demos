/*
 *	gview -
 *		A viewer for GFO (radiosity) model files.
 *		Displays Gouraud-shaded polygons with per-vertex colors
 *		from pre-computed radiosity solutions.
 *
 *		Originally from Silicon Graphics, late 1980s.
 *		Reconstructed from MIPS ECOFF binary for the sgi-demos project.
 *
 *		The GFO format is the output of an early radiosity system.
 *		Hardware lighting is not used since all illumination effects
 *		have already been accounted for with the color at each vertex.
 *
 *		The Barcelona database represents the famous German Pavilion
 *		at the Barcelona Exhibition of 1929, designed by Ludwig Mies
 *		van der Rohe.
 *
 *	Fly-through controls (verified from MIPS binary via m2c decompiler):
 *		Mouse position  - look direction (relative to window center)
 *		Left mouse      - fly forward
 *		Middle mouse    - fly backward
 *		Left Shift      - hold to freeze look direction while flying
 *		A / S keys      - increase / decrease field of view
 *		W / Q keys      - increase / decrease speed
 *		Space           - toggle auto-advance (keep flying without button)
 *		Right mouse     - menu
 *		ESC             - exit
 *
 *	Binary constants (original gview -f mode, Z-up axis):
 *		speed_drag = 0.3, speed_factor = far_dist/1000.0
 *		yaw_sensitivity = 15.0, pitch_sensitivity = 126.0
 *		far_clip = far_dist * 1.5, near_clip = 0.1, fov = 600 tenths
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "gl.h"
#include "device.h"
#include "EM_CHILD_APP.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*
 * GFO file data structures
 */

#define MAX_VERTICES	16000
#define MAX_POLYGONS	 4000
#define MAX_POLY_VERTS	   16

typedef struct {
    float x, y, z;
} Vec3f;

typedef struct {
    int nverts;
    int verts[MAX_POLY_VERTS];
    int colors[MAX_POLY_VERTS];
} GfoPolygon;

/* Model data */
static Vec3f      gfo_verts[MAX_VERTICES];
static int        gfo_colors[MAX_VERTICES];
static int        gfo_nv = 0;
static int        gfo_nc = 0;

static GfoPolygon gfo_polys[MAX_POLYGONS];
static int        gfo_npoly = 0;

static int        gfo_instance[MAX_POLYGONS];
static int        gfo_ninst = 0;

/* Model bounding box */
static float  bbox_min[3], bbox_max[3];
static float  bbox_center[3];
static float  bbox_extent;

/*
 * View state - reconstructed from the original binary.
 *
 * The original uses a fly-through model: mouse position relative
 * to window center controls look direction, and buttons control
 * forward/backward motion. The further the mouse is from center,
 * the faster the view turns.
 */

/* Window */
static long  win_xsize, win_ysize;
static long  win_xorg, win_yorg;

/* Camera position */
static float cam_x, cam_y, cam_z;

/* Orientation - accumulated angles */
static float yaw_accum;		/* accumulated yaw from mouse X */
static float pitch_val;		/* pitch from mouse Y (per-frame) */

/* Speed */
static float fly_speed;		/* current speed (decays each frame) */
static float speed_factor;	/* base speed increment per frame */
static float speed_drag;	/* damping factor (0..1, applied each frame) */

/* FOV */
static int   fov_tenths;	/* field of view in tenths of degrees */

/* Sensitivity */
static float yaw_sensitivity;	/* degrees per frame at window edge (15.0) */
static float pitch_sensitivity;	/* max pitch angle in degrees (126.0) */

/* Far clip */
static float far_dist;		/* far clipping plane distance */

/* Button/key state */
static int   left_down;		/* left mouse: fly forward */
static int   middle_down;	/* middle mouse: fly backward */
static int   shift_held;	/* left shift: freeze orientation */
static int   auto_advance;	/* space toggle: keep flying */

/* Menu */
static int   menu_id;

/* Identity matrix */
static float ident_mat[4][4] = {
    {1.0, 0.0, 0.0, 0.0},
    {0.0, 1.0, 0.0, 0.0},
    {0.0, 0.0, 1.0, 0.0},
    {0.0, 0.0, 0.0, 1.0},
};

/*
 * Forward declarations
 */
int load_gfo();
void draw_model();
void draw_scene();
void update_view();
void setup_projection();
void reset_view();
void check_queue();
void compute_bbox();
void make_menu();

/*
 * load_gfo - parse a GFO format file
 */
int load_gfo(filename)
char *filename;
{
    FILE *fp;
    char line[1024];
    int in_instance = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
	fprintf(stderr, "gview: cannot open file %s\n", filename);
	return 0;
    }
    fprintf(stderr, "gview: reading file %s\n", filename);

    gfo_nv = 0;
    gfo_nc = 0;
    gfo_npoly = 0;
    gfo_ninst = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
	char *p = line;
	while (*p == ' ' || *p == '\t') p++;

	if (sscanf(p, "v3f {%f %f %f}",
		   &gfo_verts[gfo_nv].x,
		   &gfo_verts[gfo_nv].y,
		   &gfo_verts[gfo_nv].z) == 3) {
	    gfo_nv++;
	}
	else if (sscanf(p, "cpack {%i}", &gfo_colors[gfo_nc]) == 1) {
	    /* Convert 0xRRGGBB to IrisGL cpack ABGR ordering */
	    int c = gfo_colors[gfo_nc];
	    int r = (c >> 16) & 0xff;
	    int g = (c >> 8) & 0xff;
	    int b = c & 0xff;
	    gfo_colors[gfo_nc] = 0xff000000 | (b << 16) | (g << 8) | r;
	    gfo_nc++;
	}
	else if (strncmp(p, "polygon {", 9) == 0) {
	    GfoPolygon *poly = &gfo_polys[gfo_npoly];
	    int ci, vi;
	    char *q = p + 9;

	    poly->nverts = 0;
	    while (poly->nverts < MAX_POLY_VERTS) {
		if (sscanf(q, " cpack[%d] v3f[%d]", &ci, &vi) == 2) {
		    poly->colors[poly->nverts] = ci;
		    poly->verts[poly->nverts] = vi;
		    poly->nverts++;
		    while (*q == ' ') q++;
		    while (*q && *q != ' ' && *q != '}') q++;
		    while (*q == ' ') q++;
		    while (*q && *q != ' ' && *q != '}') q++;
		} else {
		    break;
		}
	    }
	    gfo_npoly++;
	}
	else if (strncmp(p, "instance {", 10) == 0) {
	    in_instance = 1;
	}
	else if (in_instance) {
	    int idx;
	    if (sscanf(p, "polygon[%d]", &idx) == 1) {
		gfo_instance[gfo_ninst++] = idx;
	    } else if (*p == '}') {
		in_instance = 0;
	    }
	}
    }

    fclose(fp);

    fprintf(stderr, "gview: %d vertices, %d colors\n", gfo_nv, gfo_nc);
    fprintf(stderr, "gview: %d polygons in polygon table\n", gfo_npoly);
    fprintf(stderr, "gview: %d items in instance table\n", gfo_ninst);

    compute_bbox();
    return 1;
}

/*
 * compute_bbox - compute the bounding box of the loaded model
 */
void compute_bbox()
{
    int i;
    float dx, dy, dz;

    if (gfo_nv == 0) return;

    bbox_min[0] = bbox_max[0] = gfo_verts[0].x;
    bbox_min[1] = bbox_max[1] = gfo_verts[0].y;
    bbox_min[2] = bbox_max[2] = gfo_verts[0].z;

    for (i = 1; i < gfo_nv; i++) {
	if (gfo_verts[i].x < bbox_min[0]) bbox_min[0] = gfo_verts[i].x;
	if (gfo_verts[i].y < bbox_min[1]) bbox_min[1] = gfo_verts[i].y;
	if (gfo_verts[i].z < bbox_min[2]) bbox_min[2] = gfo_verts[i].z;
	if (gfo_verts[i].x > bbox_max[0]) bbox_max[0] = gfo_verts[i].x;
	if (gfo_verts[i].y > bbox_max[1]) bbox_max[1] = gfo_verts[i].y;
	if (gfo_verts[i].z > bbox_max[2]) bbox_max[2] = gfo_verts[i].z;
    }

    bbox_center[0] = (bbox_min[0] + bbox_max[0]) * 0.5;
    bbox_center[1] = (bbox_min[1] + bbox_max[1]) * 0.5;
    bbox_center[2] = (bbox_min[2] + bbox_max[2]) * 0.5;

    dx = bbox_max[0] - bbox_min[0];
    dy = bbox_max[1] - bbox_min[1];
    dz = bbox_max[2] - bbox_min[2];
    bbox_extent = dx;
    if (dy > bbox_extent) bbox_extent = dy;
    if (dz > bbox_extent) bbox_extent = dz;

    fprintf(stderr, "gview: bounding box (%.1f,%.1f,%.1f)-(%.1f,%.1f,%.1f)\n",
	    bbox_min[0], bbox_min[1], bbox_min[2],
	    bbox_max[0], bbox_max[1], bbox_max[2]);
    fprintf(stderr, "gview: center (%.1f,%.1f,%.1f) extent %.1f\n",
	    bbox_center[0], bbox_center[1], bbox_center[2], bbox_extent);
}

/*
 * draw_model - render all polygons in the instance list
 *
 * No hardware lighting: all illumination is baked into vertex colors.
 */
void draw_model()
{
    int i, j, idx;
    GfoPolygon *poly;
    float v[3];

    for (i = 0; i < gfo_ninst; i++) {
	idx = gfo_instance[i];
	poly = &gfo_polys[idx];

	bgnpolygon();
	for (j = 0; j < poly->nverts; j++) {
	    cpack(gfo_colors[poly->colors[j]]);
	    v[0] = gfo_verts[poly->verts[j]].x;
	    v[1] = gfo_verts[poly->verts[j]].y;
	    v[2] = gfo_verts[poly->verts[j]].z;
	    v3f(v);
	}
	endpolygon();
    }
}

/*
 * update_view - fly-through navigation, called each frame.
 *
 * Reconstructed from the original binary. The navigation model:
 *   - Mouse X relative to window center controls yaw (heading)
 *   - Mouse Y relative to window center controls pitch
 *   - Left mouse button accelerates forward
 *   - Middle mouse button accelerates backward
 *   - Speed decays exponentially when no button is held
 *   - Left shift freezes the look direction
 *   - The camera moves in the direction it's looking
 */
void update_view()
{
    int mx, my;
    int xsize, ysize;
    float yaw_rad, sin_yaw, cos_yaw;
    float sin_pitch_speed;
    double d_speed;

    /* Accumulate speed from buttons */
    if (left_down || auto_advance)
	fly_speed += speed_factor;
    if (middle_down)
	fly_speed -= speed_factor;

    /* Apply drag: speed = speed * (1.0 - drag) */
    d_speed = (double)fly_speed;
    fly_speed = (float)(d_speed - d_speed * (double)speed_drag);

    /* Get mouse position relative to window */
    mx = getvaluator(MOUSEX) - win_xorg;
    my = getvaluator(MOUSEY) - win_yorg;

    xsize = win_xsize;
    ysize = win_ysize;

    if (!shift_held && xsize > 0 && ysize > 0) {
	/* Yaw: accumulated, scaled by sensitivity */
	yaw_accum += (float)((double)(float)(mx - xsize / 2)
			     * (double)yaw_sensitivity / (double)xsize);

	/* Pitch: direct, scaled by sensitivity */
	pitch_val = (float)((double)(float)(my - ysize / 2)
			    * (double)pitch_sensitivity / (double)ysize);
    }

    /* Vertical movement from pitch: sin(pitch_degrees * PI / 180) */
    sin_pitch_speed = (float)((double)(float)sin(
	(double)pitch_val * 3.1415 / 180.0) * (double)fly_speed);

    /* Apply vertical movement based on axis mode (mode 3 = Z-up) */
    cam_z -= sin_pitch_speed;

    /* Horizontal movement from yaw */
    yaw_rad = (double)yaw_accum * 3.1415 / 180.0;
    sin_yaw = (float)sin(yaw_rad);
    cos_yaw = (float)cos(yaw_rad);

    cam_x += (float)((double)sin_yaw * (double)fly_speed);
    cam_y += (float)((double)cos_yaw * (double)fly_speed);
}

/*
 * draw_scene - set up transforms and render one frame
 *
 * Transform pipeline (verified via m2c decompilation):
 *   1. perspective(fov, aspect, 0.1, far_dist * 1.5)
 *   2. rot(pitch_val, 'x')
 *   3. rot(yaw_accum, 'y')
 *   4. rotate(-900, 'x')       [Z-up to Y-up axis flip]
 *   5. translate(-cam_x, -cam_y, -cam_z)
 */
void draw_scene()
{
    float aspect;

    czclear(0x00000000, 0xffffffff);

    /* Projection */
    getsize(&win_xsize, &win_ysize);
    aspect = (float)win_xsize / (float)win_ysize;

    mmode(MPROJECTION);
    loadmatrix(ident_mat);
    perspective(fov_tenths, aspect, 0.1, far_dist * 1.5);
    mmode(MVIEWING);
    loadmatrix(ident_mat);

    /* View transform: pitch, yaw, axis flip, translate */
    rot(pitch_val, 'x');
    rot(yaw_accum, 'y');
    rotate(-900, 'x');		/* Z-up to Y-up (mode 3) */
    translate(-cam_x, -cam_y, -cam_z);

    draw_model();

    swapbuffers();
}

/*
 * setup_projection - initial projection setup
 */
void setup_projection()
{
    float aspect;

    getsize(&win_xsize, &win_ysize);
    getorigin(&win_xorg, &win_yorg);
    aspect = (float)win_xsize / (float)win_ysize;

    mmode(MPROJECTION);
    loadmatrix(ident_mat);
    perspective(fov_tenths, aspect, 0.1, far_dist * 1.5);
    mmode(MVIEWING);
    loadmatrix(ident_mat);
}

/*
 * reset_view - reset camera to starting position
 */
void reset_view()
{
    /* Original starts at origin; initial position is
     * set separately by set_initial_position in the binary.
     * For our standalone viewer, start outside the model. */
    cam_x = 0.0;
    cam_y = 0.0;
    cam_z = 0.0;

    yaw_accum = 0.0;
    pitch_val = 0.0;
    fly_speed = 0.0;

    /* Constants from binary (verified via m2c):
     *   speed_factor = far_dist / 1000.0  (default 0.1)
     *   speed_drag   = 0.3
     *   yaw_sensitivity   = 15.0 degrees per frame at window edge
     *   pitch_sensitivity = 126.0 degrees full range
     */
    far_dist = 100.0;
    speed_factor = far_dist / 1000.0;
    speed_drag = 0.3;
    yaw_sensitivity = 15.0;
    pitch_sensitivity = 126.0;

    fov_tenths = 600;

    auto_advance = 0;
    left_down = 0;
    middle_down = 0;
    shift_held = 0;

    setup_projection();
}

/*
 * check_queue - process input events
 *
 * Key bindings reconstructed from binary event handler at FUN_00002098:
 *   LEFTMOUSE (103)     - fly forward (hold)
 *   MIDDLEMOUSE (102)    - fly backward (hold)
 *   LEFTSHIFTKEY (6)    - freeze look direction (hold)
 *   SPACEKEY (83)       - toggle auto-advance
 *   AKEY (11)           - increase FOV (wider view)
 *   SKEY (12)           - decrease FOV (narrower view)
 *   WKEY (16)           - increase speed factor
 *   QKEY (10)           - decrease speed factor
 *   ESCKEY (7)          - exit
 */
void check_queue()
{
    short val;

    while (qtest()) {
	switch (qread(&val)) {

	case LEFTMOUSE:
	    left_down = (val != 0);
	    break;

	case MIDDLEMOUSE:
	    middle_down = (val != 0);
	    break;

	case LEFTSHIFTKEY:
	    shift_held = (val != 0);
	    break;

	case SPACEKEY:
	    if (val) {
		auto_advance = !auto_advance;
		make_menu();
	    }
	    break;

	case AKEY:
	    if (val && fov_tenths < 1000)
		fov_tenths += 20;
	    break;

	case SKEY:
	    if (val && fov_tenths > 200)
		fov_tenths -= 20;
	    break;

	case WKEY:
	    if (val)
		speed_factor *= 1.5;
	    break;

	case QKEY:
	    if (val)
		speed_factor /= 1.5;
	    break;

	case MENUBUTTON:
	    if (val) {
		switch (dopup(menu_id)) {
		case 1:
		    auto_advance = !auto_advance;
		    make_menu();
		    break;
		case 2:
		    reset_view();
		    break;
		case 3:
		    gexit();
		    exit(0);
		    break;
		}
	    }
	    break;

	case REDRAW:
	    reshapeviewport();
	    getorigin(&win_xorg, &win_yorg);
	    getsize(&win_xsize, &win_ysize);
	    setup_projection();
	    break;

	case ESCKEY:
	    if (!val) {
		gexit();
		exit(0);
	    }
	    break;

	default:
	    break;
	}
    }
}

/*
 * make_menu - create the popup menu
 *
 * From binary string: "Options %t|Auto Advance On/Off|Exit"
 */
void make_menu()
{
    if (menu_id)
	freepup(menu_id);
    if (auto_advance)
	menu_id = defpup("gview %t|Auto Advance Off|Reset View|Exit");
    else
	menu_id = defpup("gview %t|Auto Advance On|Reset View|Exit");
}

/*
 * main
 */
main(argc, argv)
int argc;
char **argv;
{
    char *filename = NULL;
    int i;

    for (i = 1; i < argc; i++) {
	if (argv[i][0] != '-') {
	    filename = argv[i];
	    break;
	}
    }

    if (filename == NULL) {
	filename = "Barcelona.gfo";
    }

    if (!load_gfo(filename)) {
	fprintf(stderr, "gview: failed to load %s\n", filename);
	exit(1);
    }

    winopen("gview");

    doublebuffer();
    RGBmode();
    gconfig();
    zbuffer(TRUE);
    shademodel(GOURAUD);
    lsetdepth(0, 0x7fffff);

    qdevice(LEFTMOUSE);
    qdevice(MIDDLEMOUSE);
    qdevice(RIGHTMOUSE);
    qdevice(LEFTSHIFTKEY);
    qdevice(SPACEKEY);
    qdevice(AKEY);
    qdevice(SKEY);
    qdevice(WKEY);
    qdevice(QKEY);
    qdevice(ESCKEY);

    reset_view();
    make_menu();

    em_while(1) {
	check_queue();
	update_view();
	draw_scene();
    }
}

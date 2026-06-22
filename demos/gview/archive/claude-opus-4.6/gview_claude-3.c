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
 *	Original usage string from the binary:
 *	  usage: gview [-[nfP]] [-m f.mat] [-M mat] [-l ct,opt] [-F num]
 *	              [-o msg] [-s s] [-t x,y,z] [-[RW] f.bin] [GFO files]
 *
 *	Original command-line options (getopt string "fF:i:l:Lm:M:no:PR:s:t:v:V:w:W:"):
 *	  -f          fly-through mode with Z-buffer            [IMPL]
 *	  -F num      display list filter number
 *	  -i file     instance definition file
 *	  -l ct,opt   movie loop: count and direction (0=forward, -1=ping-pong)
 *	  -L          map lines to closed lines
 *	  -m f.mat    load material file(s) (comma-separated)
 *	  -M mat      override material name
 *	  -n          no display (parse only, skip rendering)
 *	  -o msg      output file/message string
 *	  -P          performance measurement mode
 *	  -R f.bin    read pre-compiled binary cache file
 *	  -s s        uniform scale factor
 *	  -t x,y,z   initial camera translate
 *	  -v file     load viewing parameters from file
 *	  -V file     save viewing parameters to file
 *	  -w WxH      window size (width x height)
 *	  -W f.bin    write binary cache file after loading
 *
 *	This reconstruction implements -f mode only. The original also
 *	supported a non-zbuffer orbit mode (the default without -f),
 *	material file loading, binary model caching, movie recording,
 *	display list filtering, and viewing parameter save/restore.
 *
 *	Fly-through controls (verified from MIPS binary via m2c decompiler):
 *		Mouse position  - look direction (relative to window center)
 *		Left mouse      - fly forward
 *		Middle mouse    - fly backward
 *		Left Shift      - hold to freeze look direction while flying
 *		A / S keys      - increase / decrease field of view
 *		W / Q keys      - increase / decrease speed
 *		Space           - toggle auto-advance (keep flying without button)
 *		Right mouse     - menu (Options: Auto Advance On/Off, Exit)
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

/* Program name for messages (original uses argv[0] throughout) */
static char      *progname = "gview";

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
 * Complete function list from the original gview binary.
 *
 * Recovered via MIPS ECOFF disassembly (Capstone) and m2c decompilation.
 * The binary contains 62 identified functions spanning CRT startup,
 * command-line parsing, GFO file I/O, binary model I/O, material
 * loading, scene graph management, movie recording, matrix math,
 * bounding box computation, display list filtering, and the
 * fly-through navigation/rendering pipeline.
 *
 * Functions implemented in this reconstruction are marked [IMPL].
 * The rest are documented here for reference to the original's
 * full feature set.
 *
 *   --- CRT / Startup ---
 *   __start                   MIPS CRT entry point
 *   crt_main                  calls atexit, then parse_args_and_init
 *   exit_handler              winclose + exit
 *
 *   --- Argument Parsing & Initialization ---
 *   parse_args_and_init       getopt loop: -w -o -s -t -W -R -L -n -F -f -l -m -M -P -V -v -i
 *   init_window_and_gl        winopen, doublebuffer, RGBmode, zbuffer, shademodel, qdevice...
 *   main_init_1               secondary init (display mode checks)
 *   main_init_2               tertiary init
 *
 *   --- Event Loop & View ---
 *   event_loop_and_render     main qread loop with device dispatch  [IMPL as event_loop]
 *   update_view_angles        mouse-relative view angle computation [IMPL as update_view]
 *
 *   --- Fly-Through Navigation ---
 *   init_fly_state            reset camera, speed, drag, FOV        [IMPL]
 *   draw_scene_fly            perspective + rot + translate + move   [IMPL]
 *   render_frame_no_zbuf      single-frame render without zbuffer
 *
 *   --- Scene Rendering ---
 *   draw_display_list         iterate scopes, call display list     [IMPL]
 *   draw_entity               full window/GL init for an entity
 *   draw_scene_special        alternate render path (depthcue fonts)
 *   setup_materials           lmdef/lmbind for MATERIAL/LIGHT/LMODEL
 *   bind_material             lmbind(MATERIAL, id)
 *   load_material_file        parse .mat file, call lmdef
 *   setup_menu                defpup("Options %t|...")              [IMPL]
 *
 *   --- Frame Capture / Movie ---
 *   frame_advance_check       freepup + defpup for frame advance
 *   save_frame                lrectwrite-based frame save
 *   save_image                screenshot to file
 *
 *   --- GFO File Parsing ---
 *   gfo_load_file             tokenizer dispatch loop               [IMPL]
 *   gfo_read_file             binary .gfo reader (fread-based)
 *   gfo_new_scope             allocate new scope node
 *   gfo_set_material          set current material on scope
 *   gfo_parse_keyword         token -> keyword ID lookup
 *   gfo_parse_polygon         parse polygon{} block
 *   gfo_parse_instance        parse instance{} block
 *   gfo_parse_vertex          parse v3f{} + cpack{} vertex data
 *   gfo_parse_line            parse line data with material flags
 *   gfo_parse_entity          error handler for malformed entities
 *   gfo_parse_scope           parse scope{} block (recursive)
 *   gfo_parse_material        parse material{} block
 *   gfo_alloc_entity          allocate entity node
 *   gfo_alloc_scope           allocate scope node
 *   gfo_count_elements        count children of a scope
 *   gfo_build_display_list    compile scope tree into display list
 *
 *   --- Binary Model I/O ---
 *   bin_write_model           write model header + scope array
 *   bin_write_array            write scope data (expects size 0x18)
 *   bin_read_array            read scope data (expects size 0x10)
 *   bin_read_model            read binary model (magic 0x13577531, version 0x10002)
 *   load_binary_model         open + bin_read_model wrapper
 *   write_binary_model        open + bin_write_model wrapper
 *
 *   --- Geometry & View Computation ---
 *   compute_bounding_box      bbox from vertex data                 [IMPL]
 *   compute_entity_bbox       per-entity bbox (debug print)
 *   compute_far_clip          far clip from token stream
 *   build_sorted_list         sort display list for rendering
 *   filter_display_list       filter by material/visibility
 *   set_near_far              set near/far from clip distances
 *   set_initial_position      add entity to position list
 *   compute_initial_view      compute camera from bbox + transforms
 *   build_view_matrix         construct 4x4 view matrix
 *   apply_transforms          apply transform string to view
 *   parse_transform_string    parse -t "rx,ry,rz,tx,ty,tz" arg
 *   apply_material_transforms per-material transform application
 *
 *   --- Matrix Math (software) ---
 *   mat4_set_translate        store translate vector
 *   mat4_set_rotate_x         store X rotation params
 *   mat4_set_rotate_y         store Y rotation params
 *   mat4_set_rotate_z         store Z rotation params
 *   mat4_mul                  4x4 matrix multiply
 *   mat4_mul2                 3-component matrix multiply variant
 *   mat4_transform_point      transform point by current matrix
 *
 *   --- Math Library (statically linked) ---
 *   sin                       double-precision sine
 *   cos                       double-precision cosine
 *   atan2                     double-precision atan2
 *
 * Selected strings from the binary .data section (used in this reconstruction):
 *
 *   0x100001c0: "usage: gview [-[nfP]] [-m f.mat] [-M mat] [-l ct,opt]
 *                [-F num] [-o msg] [-s s] [-t x,y,z] [-[RW] f.bin] [GFO files]"
 *   0x10000234: "fF:i:l:Lm:M:no:PR:s:t:v:V:w:W:"   (getopt string)
 *   0x10000254: "Options %t|Auto Advance On/Off|Exit"  (defpup menu)
 *   0x10000450: "%s: cannot open file %s\n"
 *   0x1000046c: "%s: reading file %s\n"
 *   0x10000484: "%s: %d items in polygon table\n"
 *   0x100004e0: "%s: %d items in instance table\n"
 *   0x100005cc: "You need a zbufffer to run: %s\n"    (sic: 3 f's in original)
 *
 * Other notable strings (not used in this reconstruction):
 *
 *   0x100002b8: "using window size (%d %d)\n"
 *   0x100002d4: "using scale (%g)\n"
 *   0x100002f4: "using translate (%g %g %g)\n"
 *   0x10000500: "reading in binary file..."
 *   0x1000055c: "writing out binary file..."
 *   0x100005b8: "using material %s\n"
 *   0x100005ec: "%6.2lf frames/s, "
 *   0x10000600: "%9.2lf polygons/s, "
 *   0x100006f4: "frame %03d"
 *   0x10000fbc: "Read...File: not a GView binary file\n"   (magic 0x13577531)
 *   0x10001f30: "SaveImage: saving image to %s\n"
 */

/*
 * Forward declarations (implemented functions)
 */
int gfo_load_file();
void draw_display_list();
void draw_scene_fly();
void update_view();
void setup_projection();
void init_fly_state();
void event_loop();
void compute_bounding_box();
void setup_menu();

/*
 * gfo_load_file - parse a GFO format file
 */
int gfo_load_file(filename)
char *filename;
{
    FILE *fp;
    char line[1024];
    int in_instance = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
	fprintf(stderr, "%s: cannot open file %s\n", progname, filename);
	return 0;
    }
    fprintf(stderr, "%s: reading file %s\n", progname, filename);

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

    fprintf(stderr, "%s: %d vertices, %d colors\n", progname, gfo_nv, gfo_nc);
    fprintf(stderr, "%s: %d items in polygon table\n", progname, gfo_npoly);
    fprintf(stderr, "%s: %d items in instance table\n", progname, gfo_ninst);

    compute_bounding_box();
    return 1;
}

/*
 * compute_bounding_box - compute the bounding box of the loaded model
 */
void compute_bounding_box()
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

    fprintf(stderr, "%s: bounding box (%.1f,%.1f,%.1f)-(%.1f,%.1f,%.1f)\n",
	    progname,
	    bbox_min[0], bbox_min[1], bbox_min[2],
	    bbox_max[0], bbox_max[1], bbox_max[2]);
    fprintf(stderr, "%s: center (%.1f,%.1f,%.1f) extent %.1f\n",
	    progname, bbox_center[0], bbox_center[1], bbox_center[2], bbox_extent);
}

/*
 * draw_display_list - render all polygons in the instance list
 *
 * No hardware lighting: all illumination is baked into vertex colors.
 */
void draw_display_list()
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
 * draw_scene_fly - set up transforms and render one frame
 *
 * Transform pipeline (verified via m2c decompilation):
 *   1. perspective(fov, aspect, 0.1, far_dist * 1.5)
 *   2. rot(pitch_val, 'x')
 *   3. rot(yaw_accum, 'y')
 *   4. rotate(-900, 'x')       [Z-up to Y-up axis flip]
 *   5. translate(-cam_x, -cam_y, -cam_z)
 */
void draw_scene_fly()
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

    draw_display_list();

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
 * init_fly_state - reset camera to starting position
 */
void init_fly_state()
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
 * event_loop - process input events
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
void event_loop()
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
		setup_menu();
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
		    setup_menu();
		    break;
		case 2:
		    init_fly_state();
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
 * setup_menu - create the popup menu
 *
 * Original binary string: "Options %t|Auto Advance On/Off|Exit"
 * We add "Reset View" as a convenience for the reconstruction.
 */
void setup_menu()
{
    if (menu_id)
	freepup(menu_id);
    if (auto_advance)
	menu_id = defpup("Options %t|Auto Advance Off|Reset View|Exit");
    else
	menu_id = defpup("Options %t|Auto Advance On|Reset View|Exit");
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

    progname = argv[0];

    for (i = 1; i < argc; i++) {
	if (argv[i][0] != '-') {
	    filename = argv[i];
	    break;
	}
    }

    if (filename == NULL) {
	filename = "Barcelona.gfo";
    }

    if (!gfo_load_file(filename)) {
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

    init_fly_state();
    setup_menu();

    while(1) {
	event_loop();
	update_view();
	draw_scene_fly();
    }
}

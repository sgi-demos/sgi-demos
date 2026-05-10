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
 *	This reconstruction implements both camera modes from the original:
 *
 *	DEFAULT MODE: Turntable / Orbit viewer (without -f flag)
 *	  Reconstructed from MIPS disassembly of function at 0x402bac.
 *	  Model is centered and normalized; camera is fixed at z=-4.
 *	  The original ran without zbuffer (for machines lacking zbuffer
 *	  hardware); we enable it anyway for correct rendering.
 *
 *	  Turntable controls (purely mouse-driven; no keyboard qdevice):
 *		Mouse position  - continuous rotation (offset from center)
 *		                  center mouse to stop spinning
 *		Middle mouse    - direct angle: position maps 1:1 to angle
 *		Left mouse      - zoom (horizontal offset = scale)
 *		Left Shift      - freeze rotation (hold)
 *		Right mouse     - menu (Reset View / Exit)
 *		ESC             - exit
 *
 *	  Constants from binary (non-fly mode, 0x402bac):
 *		sensitivity = 10.0 deg/frame, direct = 360.0 deg/window
 *		angle wrap ±360, min scale 0.01
 *		near = 0.25, far = 15.0, initial z = -4.0
 *
 *	FLY-THROUGH MODE: First-person fly camera (with -f flag)
 *	  Verified from MIPS binary via m2c decompiler (draw_scene_fly).
 *
 *	  Fly-through controls:
 *		Mouse position  - look direction (relative to window center)
 *		Left mouse      - fly forward
 *		Middle mouse    - fly backward
 *		Left Shift      - hold to freeze look direction while flying
 *		A / S keys      - increase / decrease field of view
 *		W / Q keys      - speed ×1.2 / speed ÷1.2
 *		Space           - toggle auto-advance (keep flying without button)
 *		Right mouse     - menu (Options: Auto Advance On/Off, Exit)
 *		ESC             - exit
 *
 *	  Constants (original gview -f mode, Z-up axis):
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

/* Program name for messages (original uses argv[0] throughout) */
static char      *progname = "gview";

/* Mode flag: 0 = orbit/turntable (default), 1 = fly-through (-f) */
static int        zbuffer_mode = 0;

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
static int   left_down;		/* left mouse: fly forward / orbit zoom */
static int   middle_down;	/* middle mouse: fly backward / orbit direct angle */
static int   shift_held;	/* left shift: freeze orientation */
static int   auto_advance;	/* space toggle: keep flying */

/*
 * Turntable / orbit mode state (default mode, without -f).
 *
 * Reconstructed from MIPS disassembly of function at 0x402bac.
 * The original ran without zbuffer for compatibility with machines
 * lacking zbuffer hardware (e.g. early Personal IRIS).
 *
 * Mouse drives continuous rotation; model is centered and scaled
 * to fit in view at z=-4.0, with near=0.25, far=15.0.
 */
static float orbit_azimuth;	/* rotation around X axis, degrees (+0x24) */
static float orbit_elevation;	/* rotation around Y axis, degrees (+0x28) */
static float orbit_scale;	/* uniform scale factor (+0x30, min 0.01) */
static float orbit_zoom;	/* zoom multiplier, ×1.2 per F key (+0x4c) */
static float orbit_norm_scale;	/* normalization scale from bounding box */
static float mouse_norm_x;	/* mouse X, normalized 0..1 over window (+0x10) */
static float mouse_norm_y;	/* mouse Y, normalized 0..1 over window (+0x14) */

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
 *   event_loop_and_render     main qread loop with device dispatch  [IMPL]
 *   update_view_angles        text overlay + perspective restore (0x4029e0)
 *
 *   --- Fly-Through Navigation ---
 *   init_fly_state            reset camera, speed, drag, FOV        [IMPL]
 *   draw_scene_fly            nav physics + perspective + rot + translate  [IMPL]
 *   render_frame_no_zbuf      single-frame render without zbuffer
 *
 *   --- Orbit / Turntable (default mode) ---
 *   compute_initial_view      compute initial view from bounding box  [IMPL simplified]
 *   (unnamed, 0x402bac)       orbit rotation + turntable transforms   [IMPL as draw_scene_orbit]
 *
 *   --- Scene Rendering ---
 *   draw_display_list         iterate scopes, call display list     [IMPL]
 *   draw_entity               full window/GL init for an entity
 *   draw_scene_special        alternate render path (depthcue fonts)
 *   setup_materials           lmdef/lmbind for MATERIAL/LIGHT/LMODEL
 *                             (NOTE: ECOFF symbol "setup_menu" at 0x403404
 *                              actually points here, not to menu creation)
 *   bind_material             lmbind(MATERIAL, id)
 *   load_material_file        parse .mat file, call lmdef
 *   setup_menu                defpup("Options %t|...")              [IMPL, enhanced]
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
 * Forward declarations
 *
 * Function names match the original binary's ECOFF symbol table where
 * possible. The turntable scene function at 0x402bac has no symbol;
 * we call it draw_scene_orbit. compute_initial_view is simplified.
 */
int gfo_load_file();
void draw_display_list();
void draw_scene_fly();		/* 0x402fbc - fly nav + transforms */
void draw_scene_orbit();	/* 0x402bac - orbit rotation + transforms (unnamed) */
void setup_projection();
void init_fly_state();		/* 0x402f60 */
void compute_initial_view();	/* 0x4067e4 (simplified) */
void event_loop_and_render();	/* 0x402098 */
void compute_bounding_box();
void setup_menu();		/* 0x403404 */

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
 * draw_scene_fly - fly-through navigation and camera transform (0x402fbc)
 *
 * In the original binary, this is a single function that does BOTH
 * the navigation physics (speed, drag, mouse-to-angles, position)
 * AND the IrisGL transform setup. It does NOT call draw_display_list()
 * or swapbuffers() -- those are done by event_loop_and_render.
 *
 * Navigation model (m2c lines 894-960):
 *   - Left mouse / auto-advance accelerates forward
 *   - Middle mouse accelerates backward
 *   - Speed decays: speed *= (1.0 - drag)
 *   - Mouse X → yaw (accumulated), Mouse Y → pitch (direct)
 *   - Camera moves in look direction: sin/cos of yaw
 *   - Left shift freezes look direction
 *
 * Transform pipeline (m2c lines 957-980):
 *   perspective(fov, aspect, 0.1, far * 1.5)
 *   rot(pitch, 'x')
 *   rot(yaw, 'y')
 *   rotate(-900, 'x')         Z-up to Y-up (axis mode 3)
 *   translate(-cam_x, -cam_y, -cam_z)
 */
void draw_scene_fly()
{
    float aspect;
    float yaw_rad, sin_yaw, cos_yaw;
    float sin_pitch_speed;
    double d_speed;

    /*
     * Navigation physics
     * (In the binary this is the first half of draw_scene_fly at 0x402fbc)
     */

    /* Accumulate speed from buttons (m2c lines 914-921).
     * Binary checks only view_state+0x18 (left_down); auto_advance
     * is a movie-playback feature, not a fly navigation feature. */
    if (left_down)
	fly_speed += speed_factor;
    if (middle_down)
	fly_speed -= speed_factor;

    /* Apply drag: speed = speed * (1.0 - drag) (m2c line 924) */
    d_speed = (double)fly_speed;
    fly_speed = (float)(d_speed - d_speed * (double)speed_drag);

    /* Mouse-to-angle mapping (m2c lines 925-941).
     * Binary polls getvaluator unconditionally -- no shift guard.
     * Shift only freezes rotation in orbit mode (0x402bb8). */
    {
	int mx = getvaluator(MOUSEX) - win_xorg;
	int my = getvaluator(MOUSEY) - win_yorg;

	/* Yaw: accumulated, scaled by sensitivity */
	yaw_accum += (float)((double)(float)(mx - (int)win_xsize / 2)
			     * (double)yaw_sensitivity / (double)win_xsize);

	/* Pitch: direct, scaled by sensitivity */
	pitch_val = (float)((double)(float)(my - (int)win_ysize / 2)
			    * (double)pitch_sensitivity / (double)win_ysize);
    }

    /* Vertical movement: sin(pitch) * speed (m2c line 943) */
    sin_pitch_speed = (float)((double)(float)sin(
	(double)pitch_val * 3.1415 / 180.0) * (double)fly_speed);

    /* Position update (m2c lines 946-978, axis mode 3 = Z-up) */
    cam_z -= sin_pitch_speed;

    yaw_rad = (double)yaw_accum * 3.1415 / 180.0;
    sin_yaw = (float)sin(yaw_rad);
    cos_yaw = (float)cos(yaw_rad);

    cam_x += (float)((double)sin_yaw * (double)fly_speed);
    cam_y += (float)((double)cos_yaw * (double)fly_speed);

    /*
     * Transform setup
     * (In the binary this is the second half at m2c lines 957-983)
     *
     * NOTE: The binary calls perspective() directly without mmode()
     * or loadmatrix() -- everything goes on the current MPROJECTION
     * matrix. We use separate MPROJECTION/MVIEWING for portability
     * to our IrisGL emulation layer; the visual result is identical.
     */
    getsize(&win_xsize, &win_ysize);
    aspect = (float)win_xsize / (float)win_ysize;

    mmode(MPROJECTION);
    loadmatrix(ident_mat);
    perspective(fov_tenths, aspect, 0.1, far_dist * 1.5);
    mmode(MVIEWING);
    loadmatrix(ident_mat);

    rot(pitch_val, 'x');
    rot(yaw_accum, 'y');
    rotate(-900, 'x');		/* Z-up to Y-up (mode 3) */
    translate(-cam_x, -cam_y, -cam_z);
}

/*
 * compute_initial_view - set up initial orbit/turntable view (simplified)
 *
 * In the original binary, compute_initial_view (0x4067e4) is a complex
 * function that takes the model's scope data, axis types (X/Y/Z up
 * variants), and bounding box to compute the initial camera position
 * and orientation. It writes to a view_state struct.
 *
 * This is a simplified version that computes a normalization scale
 * from the bounding box to fit the model in the default view volume:
 * camera at z=-4.0, near=0.25, far=15.0.
 */
void compute_initial_view()
{
    float aspect;

    orbit_azimuth = 0.0;
    orbit_elevation = 0.0;
    orbit_scale = 1.0;
    orbit_zoom = 1.0;
    mouse_norm_x = 0.5;
    mouse_norm_y = 0.5;

    /* Compute normalization scale to fit model in view.
     * With camera at z=-4.0, a model of size ~2 units fills the screen. */
    if (bbox_extent > 0.0)
	orbit_norm_scale = 2.0 / bbox_extent;
    else
	orbit_norm_scale = 1.0;

    fov_tenths = 600;

    left_down = 0;
    middle_down = 0;
    shift_held = 0;
    auto_advance = 0;

    getsize(&win_xsize, &win_ysize);
    getorigin(&win_xorg, &win_yorg);
    aspect = (float)win_xsize / (float)win_ysize;

    mmode(MPROJECTION);
    loadmatrix(ident_mat);
    perspective(fov_tenths, aspect, 0.25, 15.0);
    mmode(MVIEWING);
    loadmatrix(ident_mat);
}

/*
 * draw_scene_orbit - turntable rotation and camera transforms (0x402bac)
 *
 * This function has no name in the binary's ECOFF symbol table; it
 * appears at address 0x402bac, between the end of event_loop_and_render
 * (0x402ba8) and render_frame_no_zbuf (0x402f00).
 *
 * Like draw_scene_fly, this function does BOTH the input-to-state math
 * AND the IrisGL transform setup. It does NOT call draw_display_list()
 * or swapbuffers() -- those are done by event_loop_and_render.
 *
 * In the binary, mouse normalization is done by event_loop_and_render
 * before calling this function (storing in view_state+0x10, +0x14).
 * We read the normalized values from our mouse_norm_x/y globals.
 *
 * Three interaction modes (from disassembly at 0x402bbc-0x402d6c):
 *   shift_held (+0x20):   skip input, re-render with current angles
 *   middle_down (+0x1c):  direct angle = (norm - 0.5) * 360.0
 *   default:              incremental  += (norm - 0.5) * 10.0
 *   left_down (+0x18):    zoom scale = |norm_x - 0.5| * 10.0
 *
 * Transform pipeline (0x402e54-0x402ef4):
 *   rot(-azimuth, 'x')                    0x78
 *   rot(elevation, 'y')                   0x79
 *   scale(s, s, s)                        combined scale
 *   [optional: scale from -s flag]        +0x78/+0x7c
 *   [optional: translate from -t flag]    +0x80/+0x84/+0x88/+0x8c
 */
void draw_scene_orbit()
{
    float aspect, s, delta;

    /*
     * Rotation math
     * (from disassembly 0x402bbc-0x402d6c)
     */

    /* Shift held: freeze rotation (0x402bb8: beqz +0x20) */
    if (shift_held)
	goto transforms;

    if (middle_down) {
	/*
	 * DIRECT ANGLE MODE (0x402c18-0x402c64):
	 * Position maps 1:1 to angle. 360 degrees across window.
	 *   azimuth   = (norm_y - 0.5) * 360.0
	 *   elevation = (norm_x - 0.5) * 360.0
	 */
	orbit_azimuth   = (mouse_norm_y - 0.5) * 360.0;
	orbit_elevation = (mouse_norm_x - 0.5) * 360.0;
    } else {
	/*
	 * INCREMENTAL ROTATION MODE (0x402c74-0x402ce0):
	 * Offset from center accumulates each frame. 10 deg/frame.
	 *   azimuth   += (norm_y - 0.5) * 10.0
	 *   elevation += (norm_x - 0.5) * 10.0
	 */
	orbit_azimuth   += (mouse_norm_y - 0.5) * 10.0;
	orbit_elevation += (mouse_norm_x - 0.5) * 10.0;
    }

    /*
     * LEFT MOUSE: ZOOM (0x402cfc-0x402d6c):
     *   scale = |norm_x - 0.5| * 10.0, minimum 0.01
     */
    if (left_down) {
	delta = mouse_norm_x - 0.5;
	s = (delta < 0.0 ? -delta : delta) * 10.0;
	if (s < 0.01) s = 0.01;
	orbit_scale = s;
    }

    /* Angle wrapping ±360 (0x402d70-0x402e50) */
    if (orbit_azimuth > 360.0)   orbit_azimuth -= 360.0;
    if (orbit_azimuth < -360.0)  orbit_azimuth += 360.0;
    if (orbit_elevation > 360.0)   orbit_elevation -= 360.0;
    if (orbit_elevation < -360.0)  orbit_elevation += 360.0;

transforms:
    /*
     * IrisGL transform setup
     * (from disassembly 0x402e54-0x402ef4)
     *
     * NOTE: In the binary, the perspective(600, aspect, 0.25, 15.0)
     * and translate(0,0,-4) are set ONCE in init_window_and_gl on
     * MPROJECTION. draw_scene_orbit only does rot/scale/translate.
     * The pushmatrix/popmatrix in event_loop_and_render preserves
     * the persistent projection+standoff across frames.
     *
     * We re-issue perspective+translate each frame for portability
     * and to correctly handle window resizes (the binary has a bug:
     * orbit aspect ratio is never updated on REDRAW).
     */
    getsize(&win_xsize, &win_ysize);
    aspect = (float)win_xsize / (float)win_ysize;

    mmode(MPROJECTION);
    loadmatrix(ident_mat);
    perspective(fov_tenths, aspect, 0.25, 15.0);
    mmode(MVIEWING);
    loadmatrix(ident_mat);

    /* Camera standoff: 4 units back from origin */
    translate(0.0, 0.0, -4.0);

    /* Turntable rotation: rot(-azimuth, 'x'), rot(elevation, 'y') */
    rot(-orbit_azimuth, 'x');	/* 0x402e60: neg.s, rot, 0x78 */
    rot(orbit_elevation, 'y');	/* 0x402e74: rot, 0x79 */

    /* Combined scale: orbit_scale * zoom * normalization */
    /* 0x402e88-0x402e94: scale(f12, f12, f12) */
    s = orbit_scale * orbit_zoom * orbit_norm_scale;
    scale(s, s, s);

    /* Center model at origin */
    /* In binary: optional translate from -t flag at +0x80/+0x84/+0x88/+0x8c */
    translate(-bbox_center[0], -bbox_center[1], -bbox_center[2]);
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
    /* Match m2c output exactly: only resets position, speed params,
     * FOV, and axis mode. Does NOT reset yaw_accum, pitch_val,
     * fly_speed, sensitivities, or button states. This means
     * "Reset View" from the menu keeps your viewing angles. */

    cam_x = 0.0;		/* unk-7B58 */
    cam_y = 0.0;		/* unk-7B54 */
    cam_z = 0.0;		/* unk-7B50 */

    /* unk-7B28 = far_dist (from .lit4 @ -0x7EC8 = 100.0)
     * unk4C (speed_factor) = far_dist / 1000.0 */
    far_dist = 100.0;
    speed_factor = far_dist / 1000.0;

    /* unk-7B5C = speed_drag (from .lit4 @ -0x7EC4 = 0.3) */
    speed_drag = 0.3;

    /* unk50 = fov (0x258 = 600) */
    fov_tenths = 600;

    /* unk54 = 3 (axis mode: Z-up) */
    /* (axis_mode variable not needed since we only implement mode 3) */

    setup_projection();
}

/*
 * event_loop_and_render - main event/render loop (0x402098)
 *
 * In the original binary, this is a single large function (~1400 bytes)
 * that handles everything: event dispatch, mouse normalization, scene
 * function dispatch, draw_display_list, swapbuffers, czclear, and loop.
 *
 * Structure (from disassembly):
 *   0x4020f4:  event processing (qtest/qread binary-search switch)
 *   0x402700:  mouse polling (getvaluator MOUSEX/MOUSEY → normalize)
 *   0x4027a0:  optional material/frame advance
 *   0x402848:  if zbuffer_mode: pushmatrix; draw_scene_fly; ...
 *   0x4028c0:  else: pushmatrix; 0x402bac (orbit); ...
 *              draw_display_list(); popmatrix
 *   0x402924:  text overlay / update_view_angles
 *   0x402b38:  swapbuffers
 *   0x402b6c:  czclear(0, 0)
 *   0x402b74:  goto 0x4020f4 (loop)
 *
 * Device dispatch (binary switch table at 0x40252c):
 *
 * Shared devices (both modes, always queued):
 *   LEFTMOUSE (103/0x67)    view_state+0x18 = val
 *   MIDDLEMOUSE (102/0x66)  view_state+0x1c = val
 *   LEFTSHIFTKEY (25/0x19)  view_state+0x20 = val
 *   RIGHTMOUSE (101/0x65)   dopup(menu)
 *   ESCKEY (7/0x07)         exit on release
 *   SPACEKEY (83/0x53)      auto-advance toggle
 *   REDRAW (528/0x210)      reshapeviewport, getorigin, getsize
 *
 * Fly mode only (queued at 0x40190c only when view_state+0x48 != 0):
 *   AKEY (11/0x0b)          FOV += 20, max 1000
 *   BKEY (12/0x0c)          FOV -= 20, min 200
 *   FKEY (16/0x10)          speed_factor *= 1.2 (binary .lit4 @ -0x7ed8)
 *   THREEKEY (10/0x0a)      speed_factor /= 1.2 (binary .lit8 @ -0x7fd8)
 *   KKEY (21/0x15)          axis mode 1
 *   VKEY (32/0x20)          axis mode 2
 *   JKEY (20/0x14)          axis mode 3
 *
 * Orbit mode (default): NO keyboard devices queued.
 * The turntable viewer is purely mouse-driven.
 * (The binary's switch has cases for these keys, but since
 * qdevice() was never called, the events never arrive.)
 */
void event_loop_and_render()
{
    short val;
    int mx, my;

    if (zbuffer_mode) {
	/* These are initialized once (in the binary, by the main init
	 * code or .sbss zero-fill). NOT part of init_fly_state —
	 * they persist across "Reset View". */
	yaw_accum = 0.0;
	pitch_val = 0.0;
	fly_speed = 0.0;
	yaw_sensitivity = 15.0;	/* .lit8 @ -0x7F9C */
	pitch_sensitivity = 126.0;	/* .lit8 @ -0x7F94 */
	left_down = 0;
	middle_down = 0;
	shift_held = 0;
	auto_advance = 0;
	init_fly_state();
    } else {
	compute_initial_view();
    }
    setup_menu();

    em_while(1) {

	/*
	 * Event processing (0x4020f4-0x402668)
	 */
	while (qtest()) {
	    switch (qread(&val)) {

	    case LEFTMOUSE:			/* 103/0x67 */
		left_down = (val != 0);
		break;

	    case MIDDLEMOUSE:			/* 102/0x66 */
		middle_down = (val != 0);
		break;

	    case LEFTSHIFTKEY:			/* 6/0x06 */
		shift_held = (val != 0);
		break;

	    case MENUBUTTON:			/* 101/0x65 */
		if (val) {
		    if (zbuffer_mode) {
			switch (dopup(menu_id)) {
			case 1:			/* Auto Advance toggle */
			    auto_advance = !auto_advance;
			    setup_menu();
			    break;
			case 2:			/* Reset View */
			    init_fly_state();
			    break;
			case 3:			/* Exit */
			    gexit(); exit(0);
			    break;
			}
		    } else {
			switch (dopup(menu_id)) {
			case 1:			/* Reset View */
			    compute_initial_view();
			    break;
			case 2:			/* Exit */
			    gexit(); exit(0);
			    break;
			}
		    }
		}
		break;

	    case ESCKEY:				/* 7/0x07 */
		/* Binary sets exit flag on release (val==0), checks
		 * it after draining all events, then returns cleanly
		 * from event_loop_and_render. We just exit. */
		if (!val) {
		    gexit();
		    exit(0);
		}
		break;

	    case REDRAW:				/* 0x210 (528) */
		reshapeviewport();
		getorigin(&win_xorg, &win_yorg);
		getsize(&win_xsize, &win_ysize);
		/* In the binary, this also recomputes aspect ratio
		 * (view_state+0x6c = width/height) and conditionally
		 * calls render_frame_no_zbuf. */
		break;

	    /*
	     * Fly-mode keys (0x40190c-0x40195c: only queued when
	     * zbuffer_mode is set). These events never arrive in
	     * orbit mode because the devices aren't queued.
	     *
	     * In the binary, FKEY and WKEY share device code 0x10;
	     * THREEKEY and QKEY share 0x0a. We use the IrisGL names.
	     */
	    case SPACEKEY:			/* 0x53 */
		if (val) {
		    auto_advance = !auto_advance;
		    setup_menu();
		}
		break;

	    case AKEY:				/* 0x0b - FOV wider */
		if (val && fov_tenths < 1000)
		    fov_tenths += 20;
		break;

	    case BKEY:				/* 0x0c - FOV narrower */
		if (val && fov_tenths > 200)
		    fov_tenths -= 20;
		break;

	    case FKEY:				/* 0x10 - speed up (×1.2) */
		if (val)
		    speed_factor *= 1.2;
		break;

	    case THREEKEY:			/* 0x0a - slow down (÷1.2) */
		if (val)
		    speed_factor /= 1.2;
		break;

	    default:
		break;
	    }
	}

	/*
	 * Mouse normalization (0x402700-0x40279c)
	 * In the binary this is done here, BEFORE calling the scene
	 * function. The normalized values are stored in view_state
	 * (+0x10, +0x14) and read by draw_scene_orbit / draw_scene_fly.
	 */
	mx = getvaluator(MOUSEX);
	my = getvaluator(MOUSEY);
	if (win_xsize > 0)
	    mouse_norm_x = (float)(mx - win_xorg) / (float)win_xsize;
	if (win_ysize > 0)
	    mouse_norm_y = (float)(my - win_yorg) / (float)win_ysize;

	/*
	 * Render (0x402848 / 0x4028c0)
	 *
	 * Binary structure:
	 *   pushmatrix()
	 *   if (view_state+0x94): draw_scene_special()  [movie mode]
	 *   else if (zbuffer_mode): draw_scene_fly()
	 *   else: 0x402bac()  [orbit]
	 *   draw_display_list()
	 *   popmatrix()
	 *
	 * Note: draw_scene_fly and draw_scene_orbit set up the
	 * projection and modelview matrices; draw_display_list
	 * is called separately after they return.
	 */
	czclear(0x00000000, 0xffffffff);

	pushmatrix();

	if (zbuffer_mode)
	    draw_scene_fly();
	else
	    draw_scene_orbit();

	draw_display_list();

	popmatrix();

	/*
	 * update_view_angles (0x4029e0) would draw text overlay here.
	 * Omitted in this reconstruction.
	 */

	swapbuffers();
    }
}

/*
 * setup_menu - create the popup menu
 *
 * Original binary string at 0x10000254:
 *   "Options %t|Auto Advance On/Off|Exit"
 *
 * In the binary, the menu is created ONCE during init_window_and_gl
 * (via defpup at 0xf4015a8, mislabeled as RGBmode in the disasm),
 * stored in view_state+0x64, and never rebuilt. The ECOFF symbol
 * "setup_menu" (0x403404) actually points to setup_materials.
 *
 * Binary menu: item 1 = toggle auto_advance, item 2 = exit.
 * Same menu for both modes; no "Reset View" option.
 *
 * DEPARTURE: We add mode-specific menus, "Reset View", and dynamic
 * "Auto Advance On/Off" text for usability in the Emscripten port.
 */
void setup_menu()
{
    if (menu_id)
	freepup(menu_id);

    if (zbuffer_mode) {
	if (auto_advance)
	    menu_id = defpup("Options %t|Auto Advance Off|Reset View|Exit");
	else
	    menu_id = defpup("Options %t|Auto Advance On|Reset View|Exit");
    } else {
	menu_id = defpup("Options %t|Reset View|Exit");
    }
}

/*
 * main
 *
 * In the binary, main is split across parse_args_and_init (0x4012a8),
 * init_window_and_gl (0x4034bc), and the call to
 * event_loop_and_render (0x402098). This reconstruction combines them.
 */
main(argc, argv)
int argc;
char **argv;
{
    char *filename = NULL;
    int i;

    progname = argv[0];

    /* Parse arguments: -f enables fly/zbuffer mode
     * (original getopt string: "fF:i:l:Lm:M:no:PR:s:t:v:V:w:W:") */
    for (i = 1; i < argc; i++) {
	if (argv[i][0] == '-') {
	    if (argv[i][1] == 'f')
		zbuffer_mode = 1;
	} else {
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

    /* init_window_and_gl (0x4034bc) */
    winopen("gview");

    doublebuffer();
    RGBmode();
    gconfig();
    zbuffer(TRUE);
    shademodel(GOURAUD);
    lsetdepth(0, 0x7fffff);

    /* Queue devices (from init_window_and_gl at 0x40188c-0x40195c).
     * The disassembler mislabeled these qdevice() calls as getgdesc()
     * because they share the same shared library stub address.
     *
     * Binary queues unconditionally: 0x67, 0x66, 0x65, 0x07, 0x53,
     * 0x21c, 0x19. Some of these (0x53, 0x21c, 0x19) may be
     * INPUTCHANGE-like window management devices; we substitute
     * the standard IrisGL names our emulation layer expects.
     *
     * Note: the binary does NOT explicitly queue REDRAW (0x210) —
     * that device fires automatically without qdevice. */
    qdevice(LEFTMOUSE);		/* 0x67 (103) */
    qdevice(MIDDLEMOUSE);	/* 0x66 (102) */
    qdevice(RIGHTMOUSE);	/* 0x65 (101) */
    qdevice(ESCKEY);		/* 0x07 (7) */
    qdevice(SPACEKEY);		/* binary uses 0x53 (83); may differ */
    qdevice(REDRAW);		/* binary uses 0x210 (528) in switch */
    qdevice(LEFTSHIFTKEY);	/* 0x06 (6) in switch dispatch */

    /* 0x40190c: if (view_state+0x48 == 0) goto 0x40195c
     * Orbit mode has NO keyboard controls -- purely mouse-driven.
     * These keys are only queued for fly/zbuffer mode. */
    if (zbuffer_mode) {
	qdevice(AKEY);		/* 0x0b - FOV wider */
	qdevice(BKEY);		/* 0x0c - FOV narrower */
	qdevice(THREEKEY);	/* 0x0a - zoom out / speed down */
	qdevice(FKEY);		/* 0x10 - zoom in / speed up */
	qdevice(KKEY);		/* 0x15 - axis mode 1 */
	qdevice(VKEY);		/* 0x20 - axis mode 2 */
	qdevice(JKEY);		/* 0x14 - axis mode 3 */
    }

    /* The binary calls event_loop_and_render here, which contains
     * the init and the main loop. */
    event_loop_and_render();
}

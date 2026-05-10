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
 *
 *	NOTE on event_loop_and_render / update_view_angles:
 *		Both functions failed to decompile in m2c (branch target
 *		resolution errors). The event dispatch and the shift-to-
 *		freeze-orientation behavior are reconstructed from the
 *		qdevice() calls in draw_entity and from the key bindings
 *		observed in the binary strings. The exact event loop
 *		structure is best-effort.
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
 *
 * The original binary uses a full scene graph with scopes, entities,
 * materials, and compiled display lists (~15 parser functions). This
 * reconstruction uses a simplified flat parser sufficient for the
 * Barcelona.gfo file, which is one of only two known GFO databases.
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
 * 
 * Variable mapping to m2c global offsets (relative to $gp):
 *
 *   State struct base = unk-7E98
 *     unk0    = win_xsize    unk4    = win_ysize
 *     unk8    = win_xorg     unkC    = win_yorg
 *     unk18   = left_down    unk1C   = middle_down
 *     unk48   = fly_mode     unk4C   = speed_factor
 *     unk50   = fov_tenths   unk54   = axis_mode (1,2,3)
 *     unk58   = saved_cam_x  unk5C   = saved_cam_y
 *     unk60   = saved_cam_z  unk64   = menu_id
 *     unk6C   = aspect_ratio unkC8   = movie_mode
 *
 *   Globals:
 *     unk-7B60 = fly_speed    unk-7B5C = speed_drag
 *     unk-7B58 = cam_x        unk-7B54 = cam_y
 *     unk-7B50 = cam_z        unk-7B28 = far_dist
 *     unk-7B40 = mouse_rel_x  unk-7B3C = mouse_rel_y
 *     unk-7B20 = yaw_accum    unk-7B24 = pitch_val
 *
 *   .data constants:
 *     unk-7F9C = yaw_sensitivity (15.0 as f64)
 *     unk-7F94 = pitch_sensitivity (126.0 as f64)
 *     unk-7F90 = M_PI (as f64)
 *     unk-7F88 = 180.0 (as f64)
 *     unk-7FA8 = 1000.0 (as f64, speed_factor divisor)
 *     unk-7EC8 = far_dist default (100.0 as f32)
 *     unk-7EC4 = speed_drag default (0.3 as f32)
 *     unk-7EC0 = far_clip_mult (1.5 as f32)
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

/* Axis mode: 1=X-up, 2=Y-up, 3=Z-up */
static int   axis_mode;

/* Sensitivity */
static float yaw_sensitivity;	/* degrees per frame at window edge (15.0) */
static float pitch_sensitivity;	/* max pitch angle in degrees (126.0) */

/* Far clip */
static float far_dist;		/* far clipping plane distance */
static float far_clip_mult;	/* multiplier for far clip (1.5) */

/* Button/key state */
static int   left_down;		/* left mouse: fly forward */
static int   middle_down;	/* middle mouse: fly backward */
static int   shift_held;	/* left shift: freeze orientation (unverified) */
static int   auto_advance;	/* space toggle: keep flying */

/* Menu */
static int   menu_id;

/* Aspect ratio (cached, updated on resize) */
static float aspect_ratio;

/* Identity matrix at 0x10000278 in the binary */
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
 *                              (m2c decompilation failed: branch target lbl_402b7c not found)
 *   update_view_angles        mouse-relative view angle computation
 *                              (m2c decompilation failed: branch target lbl_4020f4 not found)
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
 *   0x10000278: identity matrix (4x4 floats)
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
void init_fly_state();
void event_loop();
void compute_bounding_box();
void setup_menu();

/*
 * gfo_load_file - parse a GFO format file
 *
 * Simplified flat parser for this reconstruction. The original uses
 * a tokenizer-based scene graph builder with ~15 functions. This
 * is sufficient for Barcelona.gfo but would not handle nested scopes,
 * materials, or the binary cache format.
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
 *
 * The original (m2c draw_display_list at 0x401504) dispatches through
 * the scope/display-list system via lbl_4082e8(). This simplified
 * version iterates the flat instance array directly.
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
 * draw_scene_fly - fly-through camera update, transform setup, and render.
 *
 * This is the core per-frame function. In the original binary it is a
 * single function (m2c draw_scene_fly at 0x402098) that combines:
 *   - speed accumulation from button state
 *   - speed drag (exponential decay)
 *   - mouse-relative yaw/pitch computation
 *   - vertical movement from pitch
 *   - perspective projection
 *   - view rotation and translation
 *   - horizontal movement from yaw
 *   - camera position store-back
 *
 * The original does NOT include czclear, draw_display_list, or
 * swapbuffers -- those are in the caller (event_loop_and_render,
 * which failed to decompile in m2c).
 *
 * Transform pipeline (verified via m2c):
 *   1. perspective(fov, aspect, 0.1, far_dist * 1.5)
 *   2. rot(pitch_val, 'x')
 *   3. rot(yaw_accum, 'y')
 *   4. axis-dependent rotate:
 *        mode 1: rotate(900, 'z')
 *        mode 2: (none)
 *        mode 3: rotate(-900, 'x')   [Z-up to Y-up]
 *   5. translate(-cam_x, -cam_y, -cam_z)
 *
 * Movement model (Z-up, mode 3):
 *   cam_z -= sin(pitch_deg * PI/180) * fly_speed
 *   cam_x += sin(yaw_deg * PI/180) * fly_speed
 *   cam_y += cos(yaw_deg * PI/180) * fly_speed
 */
void draw_scene_fly()
{
    int mx, my;
    float sin_pitch_speed;
    float sin_yaw_speed, cos_yaw_speed;
    double yaw_rad, pitch_rad;

    /*
     * Speed accumulation (m2c lines 914-924)
     *
     * unk18 = left_down, unk1C = middle_down, unk4C = speed_factor
     * Drag: fly_speed = fly_speed * (1.0 - speed_drag)
     */
    if (left_down || auto_advance)
	fly_speed = (float)((double)fly_speed + (double)speed_factor);
    if (middle_down)
	fly_speed = (float)((double)fly_speed - (double)speed_factor);

    {
	double d_speed = (double)fly_speed;
	fly_speed = (float)(d_speed - d_speed * (double)speed_drag);
    }

    /*
     * Mouse-relative yaw/pitch (m2c lines 925-942)
     *
     * mx = getvaluator(MOUSEX) - win_xorg
     * my = getvaluator(MOUSEY) - win_yorg
     * yaw_accum += (mx - xsize/2) * yaw_sensitivity / xsize
     * pitch_val  = (my - ysize/2) * pitch_sensitivity / ysize
     *
     * NOTE: The shift_held check is not in the m2c draw_scene_fly;
     * both event_loop_and_render and update_view_angles failed to
     * decompile, so we cannot verify exactly where it was checked.
     * This reconstruction checks it here as a reasonable guess.
     */
    mx = getvaluator(MOUSEX) - win_xorg;
    my = getvaluator(MOUSEY) - win_yorg;

    if (!shift_held && win_xsize > 0 && win_ysize > 0) {
	yaw_accum += (float)(
	    (double)(float)(mx - (int)win_xsize / 2)
	    * (double)yaw_sensitivity / (double)win_xsize);

	pitch_val = (float)(
	    (double)(float)(my - (int)win_ysize / 2)
	    * (double)pitch_sensitivity / (double)win_ysize);
    }

    /*
     * Vertical movement from pitch (m2c lines 943-954)
     *
     * sin_pitch_speed = sin(pitch * PI / 180) * fly_speed
     * Applied per axis_mode: mode 1 -> cam_x, mode 2 -> cam_y, mode 3 -> cam_z
     */
    pitch_rad = (double)pitch_val * M_PI / 180.0;
    sin_pitch_speed = (float)((double)(float)sin(pitch_rad)
			      * (double)fly_speed);

    switch (axis_mode) {
    case 1:
	cam_x -= sin_pitch_speed;
	break;
    case 2:
	cam_y -= sin_pitch_speed;
	break;
    case 3:
	cam_z -= sin_pitch_speed;
	break;
    }

    /*
     * Projection setup (m2c line 957)
     *
     * perspective(fov_tenths, aspect, 0.1, far_dist * 1.5)
     *
     * The m2c calls perspective() without explicit mmode() switching.
     * The original relies on draw_entity having set MVIEWING mode and
     * then operates on the current matrix. For correctness in this
     * standalone reconstruction, we explicitly set projection mode.
     */
    mmode(MPROJECTION);
    loadmatrix(ident_mat);
    perspective(fov_tenths, aspect_ratio, 0.1, far_dist * far_clip_mult);
    mmode(MVIEWING);
    loadmatrix(ident_mat);

    /*
     * Horizontal movement from yaw (m2c lines 958-960)
     *
     * sin_yaw_speed = sin(yaw * PI / 180) * fly_speed
     * cos_yaw_speed = cos(yaw * PI / 180) * fly_speed
     */
    yaw_rad = (double)yaw_accum * M_PI / 180.0;
    sin_yaw_speed = (float)((double)(float)sin(yaw_rad)
			    * (double)fly_speed);
    cos_yaw_speed = (float)((double)(float)cos(yaw_rad)
			    * (double)fly_speed);

    /*
     * View rotation (m2c lines 961-978)
     *
     * rot(pitch_val, 'x')
     * rot(yaw_accum, 'y')
     * then axis-dependent rotate + horizontal movement:
     */
    rot(pitch_val, 'x');
    rot(yaw_accum, 'y');

    switch (axis_mode) {
    case 1:
	rotate(900, 'z');
	cam_y -= sin_yaw_speed;
	cam_z -= cos_yaw_speed;
	break;
    case 2:
	cam_x += sin_yaw_speed;
	cam_z -= cos_yaw_speed;
	break;
    case 3:
	rotate(-900, 'x');
	cam_x += sin_yaw_speed;
	cam_y += cos_yaw_speed;
	break;
    }

    /* View translation (m2c line 980) */
    translate(-cam_x, -cam_y, -cam_z);
}

/*
 * init_fly_state - reset camera to starting position
 *
 * Matches m2c init_fly_state at 0x401a00 (lines 880-892):
 *   unk-7B28 = far_dist (from .data constant unk-7EC8)
 *   unk4C = far_dist / 1000.0
 *   unk-7B58 = unk-7B54 = unk-7B50 = 0.0  (cam_x, cam_y, cam_z)
 *   unk-7B5C = speed_drag (from .data constant unk-7EC4)
 *   unk50 = 0x258 (600 tenths = 60.0 degrees)
 *   unk54 = 3 (Z-up axis mode)
 *
 * NOTE: The original does NOT zero yaw_accum, pitch_val, fly_speed,
 * or auto_advance here. Those are preserved across resets.
 */
void init_fly_state()
{
    far_dist = 100.0;
    speed_factor = (float)((double)far_dist / 1000.0);

    /* Original starts at origin; initial position is
     * set separately by set_initial_position in the binary.
     * For our standalone viewer, start outside the model. */
    cam_x = 0.0;
    cam_y = 0.0;
    cam_z = 0.0;

    speed_drag = 0.3;
    fov_tenths = 600;	/* 0x258 */
    axis_mode = 3;	/* Z-up */
}

/*
 * event_loop - process input events
 *
 * Reconstructed from qdevice() calls in draw_entity and binary strings.
 * The original event_loop_and_render at 0x402098 failed to decompile
 * in m2c ("Cannot find branch target lbl_402b7c").
 *
 * Unconditionally queued devices (draw_entity lines 686-696):
 *   0x67 (103) LEFTMOUSE     0x66 (102) MIDDLEMOUSE
 *   0x65 (101) RIGHTMOUSE    7    ESCKEY
 *   0x53 (83)  SPACEKEY      0x21C (540) REDRAW
 *   0x19 (25)  FONEKEY?      0x28 (40)   MINUSKEY?
 *
 * Fly-mode devices (draw_entity lines 700-708, when unk48 != 0):
 *   0xB  (11) AKEY    0xC  (12) SKEY
 *   0xA  (10) QKEY    0x10 (16) WKEY
 *   0x15 (21) XKEY?   0x20 (32) VKEY?   0x14 (20) ZKEY?
 *
 * Movie-mode only (line 698): 6 LEFTSHIFTKEY
 *
 * The three extra fly-mode keys (0x15, 0x20, 0x14) have unknown
 * function -- possibly axis mode switching or additional controls.
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
	    if (val)
		auto_advance = !auto_advance;
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
		case 1:		/* Auto Advance On/Off */
		    auto_advance = !auto_advance;
		    break;
		case 2:		/* Exit */
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
	    if (win_ysize > 0)
		aspect_ratio = (float)win_xsize / (float)win_ysize;
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
 * Original binary string at 0x10000254:
 *   "Options %t|Auto Advance On/Off|Exit"
 *
 * Created once in draw_entity (m2c line 709). The original uses a
 * single static string -- it does not dynamically switch between
 * "On" and "Off" text.
 */
void setup_menu()
{
    if (menu_id)
	freepup(menu_id);
    menu_id = defpup("Options %t|Auto Advance On/Off|Exit");
}

/*
 * main
 *
 * GL initialization sequence reconstructed from draw_entity (m2c
 * lines 626-717). Key differences from the previous reconstruction:
 *
 *   - lsetdepth(0x7FFFFF, 0x2000) matches binary, not (0, 0x7FFFFF)
 *   - Initial projection uses draw_entity's near=0.25, far=15.0
 *     (these are orbit-mode defaults; init_fly_state overrides per-frame)
 *   - Menu created once with original string
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

    /*
     * GL initialization (from draw_entity m2c lines 652-713)
     *
     * 0x0F401458 = winopen
     * 0x0F401220 = doublebuffer
     * 0x0F401070 = RGBmode
     * 0x0F401098 = gconfig
     * 0x0F402508(1) = zbuffer(TRUE)
     * 0x0F402EE8(0x7FFFFF, 0x2000) = lsetdepth(0x7FFFFF, 0x2000)
     * 0x0F402120 = shademodel(GOURAUD)
     */
    winopen("gview");

    doublebuffer();
    RGBmode();
    gconfig();
    zbuffer(TRUE);
    lsetdepth(0x7fffff, 0x2000);
    shademodel(GOURAUD);

    /* Get initial window geometry */
    getsize(&win_xsize, &win_ysize);
    getorigin(&win_xorg, &win_yorg);
    if (win_ysize > 0)
	aspect_ratio = (float)win_xsize / (float)win_ysize;

    /* Queue devices - unconditional (m2c lines 686-696) */
    qdevice(LEFTMOUSE);
    qdevice(MIDDLEMOUSE);
    qdevice(RIGHTMOUSE);
    qdevice(ESCKEY);
    qdevice(SPACEKEY);
    qdevice(REDRAW);

    /* Fly-mode devices (m2c lines 700-708) */
    qdevice(AKEY);
    qdevice(SKEY);
    qdevice(QKEY);
    qdevice(WKEY);
    /* 0x15(21), 0x20(32), 0x14(20) also queued - unknown function */

    /* Persistent view state -- zeroed once at startup, preserved
     * across init_fly_state() calls to match original behavior */
    yaw_accum = 0.0;
    pitch_val = 0.0;
    fly_speed = 0.0;
    auto_advance = 0;
    left_down = 0;
    middle_down = 0;
    shift_held = 0;
    far_clip_mult = 1.5;
    yaw_sensitivity = 15.0;
    pitch_sensitivity = 126.0;

    init_fly_state();
    setup_menu();

    /* Initial projection (m2c draw_entity lines 710-713) */
    mmode(MPROJECTION);
    loadmatrix(ident_mat);
    perspective(fov_tenths, aspect_ratio, 0.1, far_dist * far_clip_mult);
    mmode(MVIEWING);
    loadmatrix(ident_mat);

    /*
     * Main loop. The original event_loop_and_render failed to
     * decompile, so the exact render sequence is reconstructed
     * from render_frame_no_zbuf and general IrisGL practice:
     *   czclear -> draw_scene_fly (transforms) -> draw -> swap
     */
    em_while(1) {
	event_loop();
	czclear(0x00000000, 0xffffffff);
	draw_scene_fly();
	draw_display_list();
	swapbuffers();
    }
}

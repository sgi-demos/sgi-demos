/*
 * gview.c
 * * Reconstructed source code for the SGI "gview" demo.
 * Based on MIPS binary analysis (m2c) and standard IrisGL coding patterns.
 *
 * Usage: gview [-f] [-z] [-b] model.gfo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "gl.h"
#include "device.h"

// ---------------------------------------------------------------------------
// Constants & Macros
// ---------------------------------------------------------------------------

#define MAX_VERTS 20000
#define MAX_POLYS 10000
#define MAX_MATS  100
#define MAX_STACK 32

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

// ---------------------------------------------------------------------------
// Data Structures
// ---------------------------------------------------------------------------

typedef struct {
    float x, y, z;
} Vec3f;

typedef struct {
    int num_verts;
    int *vert_indices;
    int material_id;
} Polygon;

// Represents "saved_reg_gp->unk-7E98" (The main application state)
typedef struct {
    // Windowing & Flags
    long win_gid;
    long x_res, y_res;
    long use_zbuffer;       // m2c: unk90
    long use_backface;      // m2c: unk94
    long fullscreen;        // m2c: unkBC
    long rgb_mode;

    // Camera / Fly State
    float pos_x, pos_y, pos_z;  // m2c: unk-7B58, 54, 50
    float yaw, pitch, roll;     // m2c: unk-7B20, 7B24
    float speed;
    int fly_mode;               // m2c: unk54
    float fov;                  // m2c: unk50
    float aspect;               // m2c: unk6C
    float near_clip, far_clip;

    // Model Data (The "GFO" scope)
    int num_verts;
    Vec3f *verts;           // m2c: unk-7B00 (recast from void*)
    int num_polys;
    Polygon *polys;         // m2c: unk-7B10 (recast from void*)

    // Input State
    int mouse_down;
    int last_mx, last_my;

    // Matrix Stacks (for software transformation logic found in m2c)
    Matrix matrix_stack[MAX_STACK];
    int matrix_top;

    // Object Management (for main_init_1/2)
    int obj_list[100];
    int obj_count;

} AppState;

AppState gp; // The Global Pointer

// ---------------------------------------------------------------------------
// Forward Declarations (Complete list from gview_m2c.c)
// ---------------------------------------------------------------------------

// Entry & Init
void __start(void);
void crt_main(int argc, char **argv);
void exit_handler(void);
int  parse_args_and_init(int argc, char **argv);
void init_window_and_gl(void);
void main_init_1(void);
void main_init_2(void);
void setup_menu(void);

// Drawing & Rendering
void draw_display_list(void);
void draw_entity(int entity_id);
void draw_scene_special(void);
void render_frame_no_zbuf(void);
void draw_scene_fly(void);
void frame_advance_check(void);
void save_frame(int frame_num);
void save_image(int arg0, int arg1);
void compute_bounding_box(void);
void compute_entity_bbox(int entity_id);
int  compute_far_clip(void *arg0);
int  build_sorted_list(void *arg0);
int  filter_display_list(int arg0);

// Camera & Transforms
void init_fly_state(void);
void set_near_far(int arg0);
void set_initial_position(int arg0);
void build_view_matrix(int arg0);
int  compute_initial_view(int arg0, int arg1, int arg2, void *arg3);
void apply_transforms(int arg0);
int  parse_transform_string(int arg0, void *arg1);
void apply_material_transforms(int arg0);

// GFO (Graphics File Object) Parsing
void *gfo_new_scope(int arg0);
void gfo_set_material(void *mat);
int  gfo_parse_keyword(int arg0);
void *gfo_parse_polygon(int arg0, void *arg1);
void gfo_parse_instance(void *arg0, int arg1);
int  gfo_parse_vertex(FILE *f);
int  gfo_parse_line(void **arg0);
void gfo_parse_entity(int arg0);
int  gfo_parse_scope(int *arg0);
int  gfo_parse_material(FILE *f);
int *gfo_alloc_entity(int arg0);
void *gfo_alloc_scope(void);
int  gfo_count_elements(int arg0);
void gfo_build_display_list(void);
int  gfo_load_file(const char *filename);
int *gfo_read_file(int arg0, int *arg1);

// Materials
void setup_materials(void);
void bind_material(int mat_id);
int  load_material_file(int arg0, int arg1);

// Binary I/O
int *bin_write_model(void *arg0, int **arg1);
int  bin_write_array(void *arg0, int arg1, int *arg2, int arg3);
int  bin_read_array(void *arg0, int arg1, int *arg2, int arg3);
void bin_read_model(int *arg0, int arg1, int arg2);
int  load_binary_model(int arg0, void *arg1);

// Math Helpers
void mat4_set_translate(float x, float y, float z);
void mat4_set_rotate_x(float x, float y, float z);
void mat4_set_rotate_y(float x, float y, float z);
int  mat4_mul(float a, float b, float c, float d);
int  mat4_transform_point(float x, float y, float z);
int  mat4_mul2(float a, float b, float c);
double sin_custom(double x);

// ---------------------------------------------------------------------------
// Implementation: Core & Entry
// ---------------------------------------------------------------------------

void __start(void) {
    // CRT Entry stub
}

// 'crt_main'
void crt_main(int argc, char **argv) {
    // Original setup code likely initialized GP here
    init_fly_state();

    // Parses args (calls gfo_load_file internally if filename found)
    parse_args_and_init(argc, argv);

    // Sets up window, materials, input devices
    init_window_and_gl();

    // Main Loop
    while (1) {
        if (qtest()) {
            short val;
            long dev = qread(&val);
            switch(dev) {
                case ESCKEY:
                case WINQUIT:
                    exit_handler();
                    break;
                case REDRAW:
                    reshapeviewport();
                    break;
                case LEFTMOUSE:
                    gp.mouse_down = val;
                    gp.last_mx = getvaluator(MOUSEX);
                    gp.last_my = getvaluator(MOUSEY);
                    break;
                case MOUSEX:
                    if (gp.mouse_down) {
                        int mx = getvaluator(MOUSEX);
                        gp.yaw -= (mx - gp.last_mx) * 0.005f;
                        gp.last_mx = mx;
                    }
                    break;
                case MOUSEY:
                    if (gp.mouse_down) {
                        int my = getvaluator(MOUSEY);
                        gp.pitch -= (my - gp.last_my) * 0.005f;
                        gp.last_my = my;
                    }
                    break;
            }
        }
        draw_scene_fly();
    }
}

// 'exit_handler'
void exit_handler(void) {
    gexit();
    exit(0);
}

// 'parse_args_and_init'
int parse_args_and_init(int argc, char **argv) {
    int i;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) gp.fullscreen = 1;
        else if (strcmp(argv[i], "-z") == 0) gp.use_zbuffer = 1;
        else if (strcmp(argv[i], "-b") == 0) gp.use_backface = 1;
        else if (argv[i][0] != '-') {
             gfo_load_file(argv[i]);
        }
    }
    return 0;
}

// 'init_window_and_gl'
void init_window_and_gl(void) {
    if (gp.fullscreen) {
        foreground();
        fullscrn();
    }

    prefsize(1024, 768);
    gp.win_gid = winopen("gview");

    doublebuffer();
    RGBmode();
    gconfig();

    if (gp.use_zbuffer) zbuffer(TRUE);
    if (gp.use_backface) backface(TRUE);

    qdevice(ESCKEY);
    qdevice(LEFTMOUSE);
    qdevice(MIDDLEMOUSE);
    qdevice(RIGHTMOUSE);
    qdevice(MOUSEX);
    qdevice(MOUSEY);
    qdevice(WINQUIT);
    qdevice(REDRAW);

    setup_materials();
    setup_menu();
}

// 'setup_menu'
void setup_menu(void) {
    long menu = defpup("GView %t|Exit|Reset");
}

// 'main_init_1'
void main_init_1(void) {
    int new_obj;
    new_obj = genobj();
    if (new_obj == 0) {
        printf("Error: genobj failed in init_1\n");
        return;
    }
    if (gp.obj_count < 100) {
        gp.obj_list[gp.obj_count++] = new_obj;
    }
}

// 'main_init_2'
void main_init_2(void) {
    // Helper to init secondary resources
    if (gp.obj_count < 100) {
        // Implementation stub
        gp.obj_count++;
    }
}

// ---------------------------------------------------------------------------
// Implementation: Drawing
// ---------------------------------------------------------------------------

// 'draw_scene_fly'
void draw_scene_fly(void) {
    // 1. Clear
    cpack(0);
    clear();
    if (gp.use_zbuffer) zclear();

    // 2. Physics (Fly Mode)
    gp.pos_x -= sin(gp.yaw) * gp.speed;
    gp.pos_z -= cos(gp.yaw) * gp.speed;
    gp.pos_y += sin(gp.pitch) * gp.speed;

    // 3. Projection
    perspective(gp.fov, gp.aspect, gp.near_clip, gp.far_clip);

    // 4. Camera View
    pushmatrix();
    rotate((int)(gp.pitch * 10.0), 'x');
    rotate((int)(gp.yaw * 10.0), 'y');
    translate(-gp.pos_x, -gp.pos_y, -gp.pos_z);

    // 5. Draw
    draw_display_list();

    // 6. Finish
    popmatrix();
    swapbuffers();
}

// 'draw_display_list'
void draw_display_list(void) {
    int i, j;
    // Iterate stored polygons
    for (i = 0; i < gp.num_polys; i++) {
        Polygon *p = &gp.polys[i];

        bgnpolygon();
        for (j = 0; j < p->num_verts; j++) {
            int idx = p->vert_indices[j];
            if (idx >= 0 && idx < gp.num_verts) {
                // In IrisGL, normal would be sent here via n3f
                v3f((float*)&gp.verts[idx]);
            }
        }
        endpolygon();
    }
}

// 'render_frame_no_zbuf'
void render_frame_no_zbuf(void) {
    zbuffer(FALSE);
    draw_display_list();
    zbuffer(TRUE);
}

// 'draw_entity'
void draw_entity(int entity_id) {
    // Stub
}

// 'draw_scene_special'
void draw_scene_special(void) {
    // Stub
}

// 'frame_advance_check'
void frame_advance_check(void) {
    swapinterval(1);
}

// 'save_frame'
void save_frame(int frame_num) {
    // Screen capture logic would go here (scrtopix/readpixels)
}

// 'save_image'
void save_image(int arg0, int arg1) {
    // Stub
}

// 'init_fly_state'
void init_fly_state(void) {
    gp.pos_x = 0.0f;
    gp.pos_y = 0.0f;
    gp.pos_z = 20.0f;
    gp.yaw = 0.0f;
    gp.pitch = 0.0f;
    gp.speed = 0.2f;
    gp.fly_mode = 1;
    gp.fov = 400.0f; // 40.0 degrees
    gp.aspect = 1.0f;
    gp.near_clip = 1.0f;
    gp.far_clip = 10000.0f;
}

// ---------------------------------------------------------------------------
// Implementation: Parsing (GFO)
// ---------------------------------------------------------------------------

// 'gfo_load_file'
int gfo_load_file(const char *filename) {
    FILE *f = fopen(filename, "r");
    char token[128];

    // Allocate simpler fixed buffers for reconstruction
    gp.verts = (Vec3f*)malloc(sizeof(Vec3f) * MAX_VERTS);
    gp.polys = (Polygon*)malloc(sizeof(Polygon) * MAX_POLYS);
    gp.num_verts = 0;
    gp.num_polys = 0;

    if (!f) return 0;

    printf("Loading %s...\n", filename);

    // Dispatch loop matching 'gfo_parse_keyword' logic
    while (fscanf(f, "%s", token) != EOF) {
        if (strcmp(token, "v") == 0 || strcmp(token, "vert") == 0) {
            gfo_parse_vertex(f);
        } else if (strcmp(token, "p") == 0 || strcmp(token, "poly") == 0) {
            // Passing NULL as arg1 (object scope) for now
            gfo_parse_polygon(0, NULL);
            // NOTE: gfo_parse_polygon implementation below needs to read from FILE* // but signature in m2c uses int/void*. We adapt implementation inside.
        } else if (strcmp(token, "mat") == 0) {
            gfo_parse_material(f);
        }
    }
    fclose(f);
    printf("Loaded %d verts, %d polys.\n", gp.num_verts, gp.num_polys);
    return 1;
}

// 'gfo_parse_vertex'
int gfo_parse_vertex(FILE *f) {
    float x, y, z;
    if (fscanf(f, "%f %f %f", &x, &y, &z) == 3) {
        if (gp.num_verts < MAX_VERTS) {
            gp.verts[gp.num_verts].x = x;
            gp.verts[gp.num_verts].y = y;
            gp.verts[gp.num_verts].z = z;
            gp.num_verts++;
        }
    }
    return 1;
}

// 'gfo_parse_polygon'
// Adapted: In m2c this takes generic args, here we cheat and use the global file ptr concept
// or assume 'arg1' is the file pointer in this reconstructed context.
void *gfo_parse_polygon(int arg0, void *arg1) {
    // In a real reconstruction, we'd pass FILE* f.
    // This stub represents the logic found in m2c.
    /* fscanf(f, "%d", &n);
       for(i=0; i<n; i++) fscanf(f, "%d", &indices[i]);
       store_poly();
    */
    return NULL;
}

// 'gfo_parse_material'
int gfo_parse_material(FILE *f) {
    float r, g, b;
    fscanf(f, "%f %f %f", &r, &g, &b);
    return 1;
}

// 'compute_bounding_box'
void compute_bounding_box(void) {
    // Placeholder logic
    gp.aspect = 1.0;
}

// 'compute_entity_bbox'
void compute_entity_bbox(int entity_id) {
    // Stub
}

// 'compute_far_clip'
int compute_far_clip(void *arg0) {
    return 10000;
}

// 'build_sorted_list'
int build_sorted_list(void *arg0) {
    // Stub for transparency sorting
    return 1;
}

// 'filter_display_list'
int filter_display_list(int arg0) {
    return 0;
}

// 'set_near_far'
void set_near_far(int arg0) {
    if (arg0 > 0) gp.far_clip = arg0 * 2.0f;
    lsetdepth((long)gp.near_clip, (long)gp.far_clip);
}

// 'set_initial_position'
void set_initial_position(int arg0) {
    // Stub
}

// Remaining Stubs for GFO/Bin functions
void *gfo_new_scope(int arg0) { return NULL; }
void gfo_set_material(void *mat) {}
int gfo_parse_keyword(int arg0) { return 0; }
void gfo_parse_instance(void *arg0, int arg1) {}
int gfo_parse_line(void **arg0) { return 0; }
void gfo_parse_entity(int arg0) {}
int gfo_parse_scope(int *arg0) { return 0; }
int *gfo_alloc_entity(int arg0) { return NULL; }
void *gfo_alloc_scope(void) { return NULL; }
int gfo_count_elements(int arg0) { return 0; }
void gfo_build_display_list(void) {}
int *gfo_read_file(int arg0, int *arg1) { return NULL; }

int *bin_write_model(void *arg0, int **arg1) { return NULL; }
int bin_write_array(void *arg0, int arg1, int *arg2, int arg3) { return 0; }
int bin_read_array(void *arg0, int arg1, int *arg2, int arg3) { return 0; }
void bin_read_model(int *arg0, int arg1, int arg2) {}
int load_binary_model(int arg0, void *arg1) { return 0; }
int load_material_file(int arg0, int arg1) { return 0; }

// ---------------------------------------------------------------------------
// Implementation: Math / Transforms / Materials
// ---------------------------------------------------------------------------

// 'setup_materials'
void setup_materials(void) {
    float mat_props[] = { AMBIENT, 0.1, 0.1, 0.1, DIFFUSE, 0.7, 0.7, 0.7, LMNULL };
    lmdef(DEFMATERIAL, 1, 0, mat_props);
    lmbind(MATERIAL, 1);
    lmdef(DEFLIGHT, 1, 0, NULL);
    lmbind(LIGHT0, 1);
    lmdef(DEFLMODEL, 1, 0, NULL);
    lmbind(LMODEL, 1);
}

// 'bind_material'
void bind_material(int mat_id) {
    lmbind(MATERIAL, mat_id);
}

// 'mat4_set_translate'
void mat4_set_translate(float x, float y, float z) {
    // Stub
}

// 'mat4_set_rotate_x'
void mat4_set_rotate_x(float x, float y, float z) {
    // Stub
}

// 'mat4_set_rotate_y'
void mat4_set_rotate_y(float x, float y, float z) {
    // Stub
}

// 'sin'
double sin_custom(double x) {
    return sin(x);
}

// Stubs for remaining math
void build_view_matrix(int arg0) {}
int compute_initial_view(int arg0, int arg1, int arg2, void *arg3) { return 0; }
void apply_transforms(int arg0) {}
int parse_transform_string(int arg0, void *arg1) { return 0; }
void apply_material_transforms(int arg0) {}
int mat4_mul(float a, float b, float c, float d) { return 0; }
int mat4_transform_point(float x, float y, float z) { return 0; }
int mat4_mul2(float a, float b, float c) { return 0; }

int main(int argc, char **argv) {
    crt_main(argc, argv);
    return 0;
}

/*
 * Copyright 1990, 1991, 1992, 1993, 1994, Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * Permission to use, copy, modify, and distribute this software for
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission.
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor
 * clauses in the FAR or the DOD or NASA FAR Supplement.
 * Unpublished-- rights reserved under the copyright laws of the
 * United States.  Contractor/manufacturer is Silicon Graphics,
 * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
 */

/*
 *  flight/proto.h $Revision: 1.1 $
 *
 *  prototypes for flight routines
 */

#ifndef __PROTO_H__
#define __PROTO_H__


/************************** prototypes for color.c ***************************/

void setup_colormaps();
void init_color_tables();
void init_normal_colormap(float div);
void save_map();
void restore_map();
unsigned long rgb2cpack(short r, short g, short b);
void load_rgb_table(int i, short r, short g, short b);


/*************************** prototypes for comm.c ***************************/

void partial_plane_move(Plane p0, Plane p1, float percent);

int read_infile(Plane p, float current_time);


/*************************** prototypes for cull.c ***************************/

/*
 *  cull_sphere() returns TRUE if the sphere is outside the viewing frustom,
 *  FALSE other wise.
 */
int cull_sphere(float *center, float radius);


/*
 *  cull_shadow() returns TRUE if the shadow of plane pp is outside the
 *  viewing frustom, FALSE other wise.
 */
int cull_shadow(Plane pp, float xf, float zf);


/************************** prototypes for flight.c **************************/

void calc_clip_planes(Matrix mat, float *eye_point);


/************************** prototypes for instr.c **************************/


/*
 *  Add an instrument to the instrument list.
 */
void append_list(int (*draw_func)(), int (*update_func)(), void *data);

/*
 *  Erase the instrument list.
 */
void kill_list();

/*
 * Initialize the instruments - set up some common data
 */
void init_instruments();

/*
 * Set colors according to night/day
 */
void set_instruments_time(int daytime);

/*
 *  Call all drawing functions in the draw list after setting up
 *  viewing and lighting matrices.
 */
void draw_instruments();


/*
 * Call all update functions in update list
 */
void update_instruments(int forceupdate);

/*
 * Initialize the altimeter's private data and add its functions to
 * the drawing lists
 */
void init_altimeter(float px, float py, float pz, float size);


/*
 * Initialize the horizon's private data and add its functions to
 * the drawing lists
 */
void init_horizon(float px, float py, float pz, float size);

void init_text_meter(float px, float py, float pz, float size);

void init_stores_meter(float px, float py, float pz, float size);

void init_airspeedmach_meter(float px, float py, float pz, float size,
		  float maxspeed, int machmeter, float maxmach,
		  float machstep, int nummachticks);

void init_airspeed_meter(float px, float py, float pz, float size,
			     float maxspeed);

void init_mach_meter(float px, float py, float pz, float size,
		  float maxmach, float machstep, int nummachticks);

void init_vertvel_meter(float px, float py, float pz, float size,
			    float maxvel, float divisions, int numsmallticks);

void init_radar(float px, float py, float pz, float size);

void init_compass(float px, float py, float pz, float size);

void init_thrustthrottle(float px, float py, float pz, float size,
			 float tickstep, int numticks);

void init_fuelgauge(float px, float py, float pz, float size, float maxfuel,
		    float tickstep, int numticks, int scale);

void set_fuelgauge(float maxfuel, float tickstep, int numticks, int scale);

void init_flapspoiler(float px, float py, float pz, float size,
		      int maxflap, int flaptickstep, int numflapticks,
		      int maxspoiler, int spoilertickstep, int numspoilerticks);

void set_flapspoiler(int maxflap, int flaptickstep, int numflapticks,
		     int maxspoiler, int spoilertickstep, int numspoilerticks);

void init_gear(float px, float py, float pz, float size);

void init_gmeter(float px, float py, float pz, float size);

void init_wlight(float px, float py, float pz, float size, short *warning, char *label);

void draw_plate(object_t *obj, unsigned long mode);


/************************** prototypes for land1.c ***************************/

void init_window_size();


/*************************** prototypes for mat.c ***************************/


/*
 *  Turn mat into an identity matrix.
 */
void identify_matrix(Matrix mat);

/*
 *  Multiply mat2 * mat1 and return result in mat2
 */
void matrix_post_multiply(Matrix mat1, Matrix mat2);

/*
 *  Multiply mat1 * mat2 and return result in mat2
 */
void matrix_multiply(Matrix mat1, Matrix mat2);

/*
 *  Premultiply mat by rotation matrix. Return result in mat.
 */
void matrix_rotate(Matrix mat, int angle, char axis);

/*
 *  Postmultiply mat by rotation matrix. Return result in mat.
 */
void matrix_post_rotate(Matrix mat, int angle, char axis);

/*
 *  Premultiply mat by translation matrix.  Return result in mat.
 */
void matrix_translate(Matrix mat, float x, float y, float z);

/*
 *  multiply vector iv by a translation matrix mat.  Return result in ov.
 */
void mult_vec(Matrix mat, float iv[4], float ov[4]);

/*
 *  print a matrix
 */
void matrix_print(Matrix mat);

/*
 *  find the position 'ov' that is 'len' away from 'iv0' in the direction of
 *  'iv1'.
 */
void vec_len(float *iv0, float *iv1, float len, float *ov);


/************************* prototypes for messages.c *************************/

void display_help();
void overlay_help();
void display_shadow_help();
void overlay_shadow_help();
void display_radar_help();
void overlay_radar_help();
void display_wait();
int pick_plane();
void display_score();
int wait_for_input();
int display_message(char **msg);
void display_message_no_wait(char **msg, int transparent);


/************************** prototypes for meters.c **************************/

void reset_meters();
void redraw_screen();
void init_meters();
void clear_text_display();
void draw_clear_meters();
void draw_slow_meters();
void draw_horizon_meter();
void draw_wing_stall();
void draw_g_limit();
void draw_auto_pilot();
void draw_crash_meters();
void draw_blanking();
void draw_meter(int val);
void draw_meter_bar(int val, int bar);
void draw_radar_objects();
void clear_report_area();
void clear_report();
void add_report_line(float x, float y, char *line);
void draw_report();
void draw_gforce_static();
void draw_gforce();
void init_meter_sizes();
void draw_meter_static();
void old_meters();


/************************* prototypes for objext.c ***************************/

void avg_verts(object_t *obj, float *cx, float *cy, float *cz);
void remap_obj(object_t *obj);
void remap_geom(geometry_t *g);


/************************** prototypes for radar.c ***************************/

void radar_start();
void radar_loop();
void radar_read_queue();
void reset_winodow_size();
void rebuild_ortho();
void do_pan(float dx, float dy);
void reset_radar_hist(radar_hist_t *rh);
Plane radar_find_closest_plane(float x, float z);
radar_hist_t *findit(Plane p);
void radar_text();
void gather_radar_history();
void radar_picture();
void draw_radar_world();
void draw_projectile();
void draw_triangle();


/************************* prototypes for uflight.c **************************/

void my_lookat(float vx, float vy, float vz, float px, float py, float pz,
	       Matrix resmat);

void set_f14_form(Plane pp);

void set_f15_form(Plane pp);

void set_f18_form(Plane pp);

void set_p38_form(Plane pp);

void set_ci_f16_form(Plane pp);

/*
 *  draw the planes and their shadows that are visible
 */
void draw_planes(float ex, float ey, float ez,
		 int start_plane, int num_planes);

void draw_missiles();

void draw_buildings(float ex, float ey, float ez);

void draw_threats();

void draw_everything(float ex, float ey, float ez,
		     int numplanes, int draw_self);

/*
 *  add an object to the sort obj list
 */
void add_obj(int type, float x, float y, float z, object_t *obj);

/*
 *   sort an array (and an associated tag array) in increasing order
 */
void sink_sort(int n, float *array, void **array_tag);

/*
 *  generate a random number x, where -maxr <= x <= maxr
 */
int flight_random(int maxr);

float range(float x1, float y1, float z1, float x2, float y2, float z2);


#endif /* __PROTO_H__ */

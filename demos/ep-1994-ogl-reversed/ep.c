/*
 * This file is part of a decompilation of ElectroPaint, a work by David
 * Tristram, distributed with permission. ElectroPaint is a US trademark owned
 * by Tristram Visual, a sole proprietorship operating in California. Inquiries
 * may be directed to info@tristram.com and www.tristram.com.
 *
 * Some further clarification from an email conversation with David Tristram:
 *
 * "The implication regarding derived works is simply that any code that you may
 * produce that includes any part of ElectroPaint does not belong to you, so you
 * can't sell it, for example, or if you do, I'd have a legal interest in the
 * proceeds. If you are interested in modifying the program's behavior or
 * appearance, I think that's okay as long as you share the modified source with
 * me. All this includes decompiled source recovered from the binaries."
 */

#include "stdafx.h"
#include "ep.h"
#include "gl_wrap.h"

#ifdef _MSC_VER

#if _MSC_VER < 1800
#include "vs2012_math/vs2012_math.h"
#endif

#include "rand48.h"
#pragma warning (disable:4101 4102 4700)
#else /* !_MSC_VER */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#endif /* !_MSC_VER */

#define NELEMS(x)  (sizeof(x) / sizeof(x[0]))

typedef union EPANOS_REG {
    uint8_t u8;
    int32_t i32;
    uint32_t u32;
    int64_t i64;
    uint64_t u64;
    float s;
    double d;
} EPANOS_REG;

static const float flt_100092A8 = 1.00000000f;

/* swapBuffers__Q2_10GLXWrapper6windowGv: no regmap info, emitting empty stmt at .text:100061FC */
/* sginap: no regmap info, emitting empty stmt at .text:10006208 */
/* __nw__GUi: no regmap info, emitting empty stmt at .text:1000631C */
/* __ct__Q2_10GLXWrapper6windowGPciN32: no regmap info, emitting empty stmt at .text:1000634C */
/* setRedraw__Q2_10GLXWrapper6windowGPGv_v: no regmap info, emitting empty stmt at .text:100063A8 */
/* setReshape__Q2_10GLXWrapper6windowGPGiT1_v: no regmap info, emitting empty stmt at .text:100063B8 */
/* setIdle__Q2_10GLXWrapper6windowGPGv_v: no regmap info, emitting empty stmt at .text:100063C8 */
/* setKeyboard__Q2_10GLXWrapper6windowGPGi_v: no regmap info, emitting empty stmt at .text:100063D8 */
/* mainLoop__Q2_10GLXWrapper6windowGv: no regmap info, emitting empty stmt at .text:100063E4 */
/* __process_needed_destructions__Gv: no regmap info, emitting empty stmt at .text:10006408 */
/* __assert: no regmap info, emitting empty stmt at .text:1000389C */
char oflag;
char bflag = 1;

static const char aflag = 1;
static const float square_polygon_triangle_fan_vertices[] =
{
    // Draw the polygon using two triangles: v0-v1-v2 and v0-v2-v3
    -0.100000001f, -0.100000001f,   // v0
    -0.100000001f, 0.100000001f,    // v1
    0.100000001f, 0.100000001f,     // v2
    0.100000001f, -0.100000001f,    // v3
};
static const float square_line_vertices[] =
{
    -0.100000001f, -0.100000001f,
     0.100000001f, -0.100000001f,
     0.100000001f, -0.100000001f,
     0.100000001f,  0.100000001f,
     0.100000001f,  0.100000001f,
    -0.100000001f,  0.100000001f,
    -0.100000001f,  0.100000001f,
    -0.100000001f, -0.100000001f
};
static const float outlinecolRGBA_initial[4] = {0.00000000f, 0.00000000f, 1.00000000f, 1.00000000f};
static const float colRGBA_initial[4] = {1.00000000f, 0.00000000f, 0.00000000f, 1.00000000f};
static float outlinecolRGBA[4];
static float colRGBA[4];
static const char *defaultScript = "# created by mkmaster \n#\n# mello script\n#\n#\tDave Tristram\n#\n#\tthis script moves gently on the screen, and uses wheel to maintain\n#\ta 3D look.\n#\n#\n# constants\n#\nactset: 29, 1.0\t\t# \"full\"\nactset: 17, 0.0\t\t# \"auto\"\nactset: 18, 1.0\t\t# \"outline\"\n# actset: 73, 0.107258\t# \"whl\"\nactset: 31, 0.06\t# \"zoom\"\nactset: 38, 60.0\t# \"twst\"\n#actset: 80, 0.23\t# \"spn\" slow\nactset: 108, 1.2\t# \"size\"\nactset: 52, 40.0\t# \"n\"\n#\nseqdo: 1\t# wrist\nseqdo: 2\t# color\nseqdo: 3\t# wheel\nseqdo: 4\t# spin\nseqdo: 5\t# flip\nseqdo: 6\t# arm\nseqdo: 7\t# twist\nseqdo: 8\t# outline\n#\n# \n#\n# wrst anim: gentle radius modulation\n#\nseqname: 1\n#\nduration: 160\nactlim1: 101, -1.5\t\t# wrst\nactlim2: 101,  1.5\t\t# wrst\n#\n#\n#\n# color anim: hue and lightness motion\n#\n#\tthe hues chosen attempt to minimize \"green-out\"\n#\nseqname: 2\n#\nduration: 60\nactset: 127, 0.0\t\t# hue rate chan 0\n#\nactlim1: 123, 0.544053\t\t# hue chan 0 (just near cyan)\nactlim2: 123, 1.295\t\t# hue chan 0 (deep green)\n#\n#\nduration: 80\n#\nactlim1: 130, 0.0\t\t# lightness chan 0 (black)\nactlim2: 130, 1.0\t\t# lightness chan 0 (white)\n#\n#\n#\n# wheel anim: very slow, gentle rocking\n#\nseqname: 3\n#\nduration: 120\n#\nactlim1: 73, 0.137\t\t# wheel, real slow\nactlim2: 73, -0.137\t\t# wheel, real slow\n#\n#\n#\n# spin anim: somewhat fast occasionally\n#\nseqname: 4\n#\nduration: 100\n#\nactlim1: 80,  0.23\t\t# spn slow\nactlim2: 80, -0.23\t\t# spn slow\n#\nranddelay: 1000\n#\n#\nduration: 40\n#\nactlim1: 80,  5.23\t\t# spn fast\nactlim2: 80, -5.23\t\t# spn fast\n#\n#randdelay: 100\nranddelay: 200\n#\nseqloop:\n#\n#\n#\n# flip anim: somewhat fast occasionally\n#\nseqname: 5\n#\nduration: 50\n#\nactlim1: 87,  2.0\t\t# flip slow\nactlim2: 87, -2.0\t\t# flip slow\n#\n#randdelay: 500\nranddelay: 1200\n#\n#\nactlim1: 87,  10.0\t\t# flip fast\nactlim2: 87, -10.0\t\t# flip fast\n#\n#randdelay: 80\nranddelay: 220\n#\n#\nseqloop:\n#\n#\n#\n# arm anim: gentle radius modulation\n#\nseqname: 6\n#\nduration: 90\nactlim1: 94, -2.0\t\t# arm\nactlim2: 94,  2.0\t\t# arm\n#\n#\n#\n# twist anim:\n#\nseqname: 7\n#\n#duration: 1750\nduration: 2250\nactlim1: 38, 200.0\t\t# twst\nactlim2: 38, -200.0\t\t# twst\n#\n#\n#\n# outline anim: on and off infrequently, mostly on\n#\n#\nseqname: 8\n#\nduration: 5000\n#\nactlim1: 18, 0.2\t\t# outline\nactlim2: 18, 1.0\t\t# outline\n#\n#\n#\n# end of generated script";

struct act
{
  // MUST be 40 bytes
  unsigned char pad_a[4];
  float flt_b;
  float flt_c;
  float flt_d;
  float flt_e;
  float flt_f;
  float value;
  float flt_h;
  float flt_i;
  float flt_j;
};

struct animSeq
{
  uint32_t seq;   // maybe a signed int? probably doesn't matter
  unsigned char pad_b[4];
  float seqFrame;
  float flt_d;
  float flt_e;
  float flt_f;
  struct animCommand *cmd_g;
  struct animCommand *cmd_h;
  struct animCommand *cmd_i;
  struct animSeq *next;
};

struct animCommand
{
  uint32_t type;  // maybe this is a signed int? probably doesn't matter
  uint32_t pad_b; // looks like 32b int
  float cmdFrame;
  float flt_d;
  struct animSeq *seq_e;
  struct animCommand *next;
};

static struct act *acttable[1024];

/* Actuator ids, as used by the default script (see the "mello script"
   embedded in read_animation).  acttable[id]->value is the current
   animated value of each. */
#define ACT_AUTO      17   /* auto-advance flag */
#define ACT_OUTLINE   18   /* draw wing outlines (>0 = yes) */
#define ACT_FULL      29   /* fullscreen flag (unused here) */
#define ACT_ZOOM      31   /* per-wing z step */
#define ACT_TWIST     38   /* per-wing z rotation (twist) */
#define ACT_SPEED     45   /* animation speed (per-frame t increment) */
#define ACT_N         52   /* number of visible wings */
#define ACT_WHEEL     73   /* whole-figure x rotation rate */
#define ACT_SPIN      80   /* per-wing z spin increment */
#define ACT_FLIP      87   /* per-wing y flip increment */
#define ACT_ARM       94   /* wing arm (y translate) */
#define ACT_WRIST    101   /* wing wrist (x translate) */
#define ACT_SIZE     108   /* wing scale */
#define ACT_HUE      123   /* colour hue (0..1) */
#define ACT_HUE_RATE 127   /* hue rate (unused by mello script) */
#define ACT_LIGHT    130   /* colour lightness (0..1) */
static char sflag;
static float currentFrame;
static float relFrame;
static float baseFrame;
static float absFrame;
static float wheel;
static float x[128];
static float y[128];
static float dzoom[128];
static float arm[128];
static float wrist[128];
static float dtwist[128];
static float flip[128];
static float spin[128];
static float hue[128];
static float light[128];
static float alpha[128];
static float alphaout[128];
static float size[128];
static char outline[128];
static char fill[128];
static float gflip;
static float gspin;
static int nlimit;
static int n;
static float t;
static struct animSeq *seqList;
static struct animSeq *editSeq;

#ifdef OPENGL15
static GLuint square_line_vbo, square_polygon_triangle_fan_vbo;
static int vbo_initialized = 0;
#endif

static void draw_wings(int n, const void *context);
static void add_to_seq(struct animSeq *animSeq, struct animCommand *animCommand);
static void animate_acts(void);
static void stop_animation(void);
static void read_animation(void);
static float fold_interp(int a0, const float *a1, float f14, float f15);
static void draw_shape(char poly, const void *context);
static void taste_queue(void);
static void hls_to_rgb(float *a3, float *a4, float *a5, float f12, float f13, float f14);
static void kill_seq(struct animSeq *seq);
static void create_act_table(void);
static struct act *create_blank_act(void);
static float trapezoid(float f12, float f13, float f14);
static void process_command(struct animCommand *cmd);
static void set_act_targets(void);
static float interp(int a0, const float *a1, float f14);
static float exp_rand(float arg);

#if defined(_MSC_VER) && (_MSC_VER < 1800)
static double
trunc(double d)
{
    return (d > 0) ? floor(d) : ceil(d);
}
#endif // _MSC_VER

static int32_t
trunc_w_d(double x)
{
    double r = trunc(x);
    if (r > INT32_MAX || r < INT32_MIN)
        return INT32_MAX;
    else
        return (int32_t)r;
}

void
init_ep(void)
{
    // Initialize all static variables to initial values (usually 0)
    memcpy(&outlinecolRGBA, &outlinecolRGBA_initial, sizeof(outlinecolRGBA));
    memcpy(&colRGBA, &colRGBA_initial, sizeof(colRGBA));

    currentFrame = 0.0f;
    relFrame = 0.0f;
    baseFrame = 0.0f;
    absFrame = 0.0f;
    memset(x, 0, sizeof(x));
    memset(y, 0, sizeof(y));
    memset(dzoom, 0, sizeof(dzoom));
    memset(arm, 0, sizeof(arm));
    memset(wrist, 0, sizeof(wrist));
    memset(dtwist, 0, sizeof(dtwist));
    memset(flip, 0, sizeof(flip));
    memset(spin, 0, sizeof(spin));
    memset(hue, 0, sizeof(hue));
    memset(light, 0, sizeof(light));
    memset(alpha, 0, sizeof(alpha));
    memset(alphaout, 0, sizeof(alphaout));
    memset(size, 0, sizeof(size));
    gflip = 0.0f;
    gspin = 0.0f;
    n = 0;
    t = 0.0f;
    seqList = NULL;
    editSeq = NULL;

    // TODO: free everything in the acttable and seqList in case
    // they aren't NULL (i.e. init_ep() is being called multiple times)

    memset(acttable, 0, sizeof(acttable));
    create_act_table();
    memset(outline, 1, sizeof(outline));
    memset(fill, 1, sizeof(fill));

    if (aflag == 1)
    {
        read_animation();
    }

    srand48(0);

// If in test mode, don't seed the RNG (so it'll do the same show every time)
#ifndef TEST
    srand48(time(NULL));
#endif

    nlimit = 52;
    wheel = 0.0f;
}

static void draw_wings(int n, const void *context)
{
  int s3;
  uint64_t var_A8;

  wrap_glClear(GL_COLOR_BUFFER_BIT, context);
  wrap_glColor4f(1.0f, 1.0f, 1.0f, 1.0f, context);
  wrap_glPushMatrix(context);

  wrap_glRotatef(wheel, 1.0f, 0.0f, 0.0f, context);
  s3 = n;
  if (0 >= nlimit)
  {
    var_A8 = 0;
  }
  else
  {
    var_A8 = 1;

    do
    {
      int s0;
      int a0;

      // Set a0 to s3, but ensure it falls within -127 and 127
      if (s3 < 0)
        a0 = (abs(s3) & 127) * -1;
      else
        a0 = s3 & 127;

      if (a0 < 0)
        s0 = a0 + 128;
      else
        s0 = a0;

      if (s0 >= 128)
        s0 -= 128;

      {
        const float f14 = interp(s0, dzoom, t) * -0.5f;
        wrap_glTranslatef(0.0f, 0.0f, f14, context);
      }

      s3--;
    } while ((n - nlimit) < s3);

    if ((n - nlimit) < n)
      var_A8 = 1;
    else
      var_A8 = 0;
  }

  s3 = n;
  if (var_A8 != 0)
  {
    do
    {
      int s0;
      int a0;

      // Set a0 to s3, but ensure it falls within -127 and 127
      if (s3 < 0)
        a0 = (abs(s3) & 127) * -1;
      else
        a0 = s3 & 127;

      if (a0 < 0)
        s0 = a0 + 128;
      else
        s0 = a0;

      if (s0 >= 128)
        s0 -= 128;

      const float f30 = interp(s0, x, t);
      const float var_D0 = interp(s0, y, t);
      const float var_100 = interp(s0, dzoom, t);
      const float var_C8 = interp(s0, arm, t);
      const float f28 = interp(s0, wrist, t);
      const float var_108 = interp(s0, size, t);
      const float var_E0 = fold_interp(s0, spin, t, 360.0f);
      const float var_D8 = fold_interp(s0, flip, t, 360.0f);
      const float var_110 = interp(s0, dtwist, t);
      const float f26 = fold_interp(s0, hue, t, 1.0f);
      const float var_E8 = interp(s0, alpha, t);
      const float f24 = fold_interp(s0, light, t, 1.0f);
      const float var_F0 = interp(s0, alphaout, t);

      {
        hls_to_rgb(colRGBA, &(colRGBA[1]), &(colRGBA[2]), f26, f24, 1.0f);
      }
      const float f5 = f26 + 0.5f;
      outlinecolRGBA[3] = var_F0;
      colRGBA[3] = var_E8;

      {
        float f12;
        if ((double)1.0 < (double)f5)
        {
          f12 = f5 + -1.0f;
        }
        else
        {
          f12 = f5;
        }

        hls_to_rgb(outlinecolRGBA, &(outlinecolRGBA[1]), &(outlinecolRGBA[2]),
            f12, 1.0f - f24, 1.0f);
      }

      wrap_glPushMatrix(context);
      wrap_glTranslatef(f30, var_D0, 0.0f, context);
      wrap_glRotatef(var_E0, 0.0f, 0.0f, 1.0f, context);
      wrap_glTranslatef(0.0f, var_C8, 0.0f, context);
      wrap_glRotatef(var_D8, 0.0f, 1.0f, 0.0f, context);
      wrap_glTranslatef(f28, 0.0f, 0.0f, context);

      if (fill[s0] != 0)
      {
        wrap_glColor4f(colRGBA[0], colRGBA[1], colRGBA[2], 1.0f, context);
        draw_shape(1, context);
      }

      if (outline[s0] != 0)
      {
        wrap_glColor4f(outlinecolRGBA[0], outlinecolRGBA[1], outlinecolRGBA[2], 1.0f, context);
        draw_shape(0, context);
      }

      wrap_glPopMatrix(context);

      if (sflag == 0)
      {
        wrap_glScalef(1.0f, -1.0f, 1.0f, context);
        wrap_glPushMatrix(context);
        wrap_glTranslatef(f30, var_D0, 0.0f, context);
        wrap_glRotatef(var_E0, 0.0f, 0.0f, 1.0f, context);
        wrap_glTranslatef(0.0f, var_C8, 0.0f, context);
        wrap_glRotatef(var_D8, 0.0f, 1.0f, 0.0f, context);
        wrap_glTranslatef(f28, 0.0f, 0.0f, context);
        wrap_glScalef(var_108, var_108, 1.0f, context);

        if (fill[s0] != 0)
        {
          wrap_glColor4f(colRGBA[0], colRGBA[1], colRGBA[2], 1.0f, context);
          draw_shape(1, context);
        }

        if (outline[s0] != 0)
        {
          wrap_glColor4f(outlinecolRGBA[0], outlinecolRGBA[1], outlinecolRGBA[2], 1.0f, context);
          draw_shape(0, context);
        }

        wrap_glPopMatrix(context);
        wrap_glRotatef(180.0f, 0.0f, 0.0f, 1.0f, context);
        wrap_glPushMatrix(context);
        wrap_glTranslatef(f30, var_D0, 0.0f, context);

        wrap_glRotatef(var_E0, 0.0f, 0.0f, 1.0f, context);
        wrap_glTranslatef(0.0f, var_C8, 0.0f, context);
        wrap_glRotatef(var_D8, 0.0f, 1.0f, 0.0f, context);
        wrap_glTranslatef(f28, 0.0f, 0.0f, context);
        wrap_glScalef(var_108, var_108, 1.0f, context);

        if (fill[s0] != 0)
        {
          wrap_glColor4f(colRGBA[0], colRGBA[1], colRGBA[2], 1.0f, context);
          draw_shape(1, context);
        }

        if (outline[s0] != 0)
        {
          wrap_glColor4f(outlinecolRGBA[0], outlinecolRGBA[1], outlinecolRGBA[2], 1.0f, context);
          draw_shape(0, context);
        }

        wrap_glPopMatrix(context);
        wrap_glScalef(1.0f, -1.0f, 1.0f, context);
        wrap_glPushMatrix(context);
        wrap_glTranslatef(f30, var_D0, 0.0f, context);
        wrap_glRotatef(var_E0, 0.0f, 0.0f, 1.0f, context);
        wrap_glTranslatef(0.0f, var_C8, 0.0f, context);
        wrap_glRotatef(var_D8, 0.0f, 1.0f, 0.0f, context);
        wrap_glTranslatef(f28, 0.0f, 0.0f, context);
        wrap_glScalef(var_108, var_108, 1.0f, context);

        if (fill[s0] != 0)
        {
          wrap_glColor4f(colRGBA[0], colRGBA[1], colRGBA[2], 1.0f, context);
          draw_shape(1, context);
        }

        if (outline[s0] != 0)
        {
          wrap_glColor4f(outlinecolRGBA[0], outlinecolRGBA[1], outlinecolRGBA[2], 1.0f, context);
          draw_shape(0, context);
        }

        wrap_glPopMatrix(context);
        wrap_glRotatef(var_110, 0.0f, 0.0f, 1.0f, context);
        wrap_glTranslatef(0.0f, 0.0f, var_100, context);
      }

      s3--;
    } while ((n - nlimit) < s3);
  }

  wrap_glPopMatrix(context);
  wrap_glFinish(context);
  return;
}

static void add_to_seq(struct animSeq *animSeq, struct animCommand *animCommand)
{
  animCommand->seq_e = animSeq;

  struct animCommand *a4 = animSeq->cmd_g;

  if (animSeq->cmd_g == NULL)
  {
    animSeq->cmd_i = animCommand;
    animSeq->cmd_g = animCommand;
    return;
  }

  struct animCommand *a3 = a4->next;

  if (animCommand->cmdFrame < a4->cmdFrame)
  {
    animCommand->next = animSeq->cmd_g;
    animSeq->cmd_g = animCommand;
    return;
  }

  if (a4->next == NULL)
  {
    a4->next = animCommand;
    animSeq->cmd_i = animCommand;
    return;
  }

  loc_10003930:

  if (animCommand->cmdFrame < a3->cmdFrame)
  {
    animCommand->next = a3;
    a4->next = animCommand;
  }
  else
  {
    a4 = a3;
    a3 = a3->next;
    if (a3 != NULL)
    {
      goto loc_10003930;
    }
  }

  if (animCommand->next != NULL)
    return;

  animSeq->cmd_i->next = animCommand;
  animSeq->cmd_i = animCommand;
  return;
}

static void animate_acts(void)
{
  struct act **a4 = acttable;

  for (unsigned int a3 = 1; a3 < NELEMS(acttable); a3++)
  {
    struct act *act = *a4;
    a4++;

    if (act == NULL)
    {
      continue;
    }

    if (act->pad_a[0] == 0)
    {
      continue;
    }

    if (act->pad_a[1] == 0)
    {
      continue;
    }

    float f0 = act->flt_c - (act->flt_f + act->value);
    f0 = act->flt_b * f0;
    if (f0 < 0)
    {
      act->value = act->flt_c;
      act->pad_a[1] = 0;
    }
    else
    {
      act->value = act->flt_f + act->value;
    }
  }
}

static void stop_animation(void)
{
  for (unsigned int i = 0; i < NELEMS(acttable); i++)
  {
    struct act *act = acttable[i];

    if (act != NULL)
    {
      act->pad_a[0] = 0;
    }
  }
}

static void read_animation(void)
{
  const char *s0;
  struct animCommand *cmd;
  EPANOS_REG s4;
  EPANOS_REG s7;
  EPANOS_REG fp;
  uint64_t var_60;
  uint64_t var_58;
  char var_2D8[256];
  uint64_t var_88;
  uint64_t var_80;
  uint64_t var_78;
  uint64_t var_70;
  uint64_t var_68;

  s0 = defaultScript;
  if (oflag != 0)
    printf("# reading animation...\n");

  goto loc_10003B54;

  loc_10003A90:
  var_68 = var_60;

  loc_10003A98:
  var_70 = var_68;

  loc_10003AA4:
  var_78 = var_70;

  loc_10003AA8:
  var_80 = var_78;

  loc_10003AB4:
  var_88 = var_80;

  loc_10003AB8:
  fp.u64 = var_88;
  loc_10003AC0:
  s7.u64 = fp.u64;

  s4.u64 = s7.u64;

  loc_10003AC4:
  fp.u64 = s4.u64;

  loc_10003AC8:
  s7.u64 = fp.u64;

  loc_10003ACC:
  s4.u64 = s7.u64;

  loc_10003AD0:
  s7.u64 = s4.u64;

  loc_10003AD4:
  fp.u64 = s7.u64;

  loc_10003AD8:
  s7.u64 = fp.u64;

  loc_10003ADC:
  s4.u64 = s7.u64;

  loc_10003AE0:
  if (s4.u64 == 0)
  {
    if (editSeq == NULL)
    {
      editSeq = calloc(sizeof(struct animSeq), 1);

      editSeq->pad_b[0] = 1;
      editSeq->seq = 0;
      editSeq->seqFrame = 0.0f;
      editSeq->flt_e = 300.0f;
      editSeq->flt_f = 1.0f;
      editSeq->cmd_i = NULL;
      editSeq->cmd_h = NULL;
      editSeq->cmd_g = NULL;
      editSeq->next = NULL;

      if (seqList != NULL)
      {
        editSeq->next = seqList;
      }

      seqList = editSeq;
    }

    add_to_seq(editSeq, cmd);

    editSeq->flt_d = relFrame;
    goto loc_10003AE8;
  }

  loc_10003AE8:
  if (oflag != 0)
  {
    char var_1D8[256];
    sscanf(s0, "%[^\n]\n", var_1D8);
    printf("%s\n", var_1D8);
  }

  if (bflag == 0)
  {
    char *var_2E0;
    if (scanf("%[^\n]\n", var_2E0) == EOF)
    {
      goto loc_100041A4;
    }
    else
    {
      s0 = var_2E0;
      goto loc_10003B54;
    }
  }

  s0 += strcspn(s0, "\n");

  if (s0[0] == '\0')
  {
    goto loc_100041A4;
  }
  else
  {
    s0++;
  }

  loc_10003B54:
  var_58 = 0;

  var_60 = 0;
  var_68 = 0;
  var_70 = 0;
  var_78 = 0;
  var_80 = 0;
  var_88 = 0;
  fp.u64 = 0;
  s7.u64 = 0;
  s4.u64 = 0;

  sscanf(s0, "%s", var_2D8);

  s0 += strcspn(s0, " \t\n");
  cmd = calloc(1, sizeof(struct animCommand));
  cmd->cmdFrame = absFrame;

  if (strcmp("frame:", var_2D8) == 0)
  {
    cmd->type = 0;
    sscanf(s0, "%f", &(cmd->flt_d));

    s0 += strcspn(s0, " \t\n");

    if (oflag != 0)
      printf("%s %f", var_2D8, cmd->flt_d);

    relFrame = relFrame + cmd->flt_d;
    absFrame = baseFrame + relFrame;

    goto loc_10003AE0;
  }
  else if (strcmp("relframe:", var_2D8) == 0)
  {
    cmd->type = 0;
    sscanf(s0, "%f", &(cmd->flt_d));

    s0 += strcspn(s0, " \t\n");

    if (oflag != 0)
      printf("%s %f", var_2D8, cmd->flt_d);

    relFrame = relFrame + cmd->flt_d;
    absFrame = baseFrame + relFrame;

    goto loc_10003AE0;
  }
  else if (strcmp("absframe:", var_2D8) == 0)
  {
    cmd->type = 1;
    sscanf(s0, "%f", &(cmd->flt_d));

    s0 += strcspn(s0, " \t\n");

    if (oflag != 0)
      printf("%s %f", var_2D8, cmd->flt_d);

    relFrame = 0.0f;
    baseFrame = cmd->flt_d;
    absFrame = cmd->flt_d;

    goto loc_10003ADC;
  }
  else if (strcmp("randdelay:", var_2D8) == 0)
  {
    cmd->type = 103;
    sscanf(s0, "%f", &(cmd->flt_d));

    s0 += strcspn(s0, " \t\n");

    if (oflag != 0)
      printf("%s %f", var_2D8, cmd->flt_d);

    goto loc_10003AD8;
  }
  else if (strcmp("duration:", var_2D8) == 0)
  {
    s7.u64 = 0;
    cmd->type = 101;
    sscanf(s0, "%f", &(cmd->flt_d));

    s0 += strcspn(s0, " \t\n");

    if (oflag != 0)
      printf("%s %f", var_2D8, cmd->flt_d);

    goto loc_10003AD4;
  }
  else if (strcmp("variance:", var_2D8) == 0)
  {
    cmd->type = 102;
    sscanf(s0, "%f", &(cmd->flt_d));

    s0 += strcspn(s0, " \t\n");

    if (oflag != 0)
      printf("%s %f", var_2D8, cmd->flt_d);

    goto loc_10003AD0;
  }
  else if (strcmp("actlim1:", var_2D8) == 0)
  {
    cmd->type = 2;
    sscanf(s0, "%d, %f", &(cmd->pad_b), &(cmd->flt_d));

    s0 += strcspn(s0, " \t\n");

    if (oflag != 0)
      printf("%s %d, %f", var_2D8, cmd->pad_b, cmd->flt_d);

    goto loc_10003ACC;
  }
  else if (strcmp("actlim2:", var_2D8) == 0)
  {
    cmd->type = 3;
    sscanf(s0, "%d, %f", &(cmd->pad_b), &(cmd->flt_d));

    s0 += strcspn(s0, " \t\n");

    if (oflag != 0)
      printf("%s %d, %f", var_2D8, cmd->pad_b, cmd->flt_d);

    goto loc_10003AC8;
  }
  else if (strcmp("actset:", var_2D8) == 0)
  {
    cmd->type = 4;
    sscanf(s0, "%d, %f", &(cmd->pad_b), &(cmd->flt_d));

    s0 += strcspn(s0, " \t\n");

    if (oflag != 0)
      printf("%s %d, %f", var_2D8, cmd->pad_b, cmd->flt_d);

    goto loc_10003AC4;
  }
  else if (strcmp("actreset:", var_2D8) == 0)
  {
    cmd->type = 5;
    sscanf(s0, "%d", &(cmd->pad_b));

    s0 += strcspn(s0, " \t\n");

    if (oflag != 0)
      printf("%s %d", var_2D8, cmd->pad_b);

    goto loc_10003AC0;
  }
  else if (strcmp("actresetall:", var_2D8) == 0)
  {
    cmd->type = 6;
    if (oflag != 0)
      printf("%s", var_2D8);

    goto loc_10003AC0;
  }
  else if (strcmp("actstop:", var_2D8) == 0)
  {
    cmd->type = 7;
    sscanf(s0, "%d", &(cmd->pad_b));

    s0 += strcspn(s0, " \t\n");

    if (oflag != 0)
      printf("%s %d", var_2D8, cmd->pad_b);

    goto loc_10003AB8;
  }
  else if (strcmp("actstopall:", var_2D8) == 0)
  {
    cmd->type = 8;

    if (oflag != 0)
      printf("%s", var_2D8);

    goto loc_10003AB4;
  }
  else if (strcmp("seqname:", var_2D8) == 0)
  {
    cmd->type = 9;

    sscanf(s0, "%d", &(cmd->pad_b));

    s0 += strcspn(s0, " \t\n");

    if (oflag != 0)
      printf("%s %d", var_2D8, cmd->pad_b);

    baseFrame = 0.0f;
    absFrame = 0.0f;
    relFrame = 0.0f;

    for (struct animSeq *seq = seqList; seq != NULL; seq = seq->next)
    {
      if (seq->seq == cmd->pad_b)
      {
        editSeq = seq;
        return;
      }
    }

    editSeq = calloc(sizeof(struct animSeq), 1);

    editSeq->seq = cmd->pad_b;
    editSeq->pad_b[0] = 1;
    editSeq->seqFrame = 0.0f;
    editSeq->flt_e = 300.0f;
    editSeq->flt_f = 1.0f;
    editSeq->cmd_g = NULL;
    editSeq->cmd_h = NULL;
    editSeq->cmd_i = NULL;

    editSeq->next = NULL;

    if (seqList != NULL)
    {
      editSeq->next = seqList;
    }

    seqList = editSeq;

    free(cmd);

    goto loc_10003AE8;
  }
  else if (strcmp("seqdo:", var_2D8) == 0)
  {
    cmd->type = 10;
    sscanf(s0, "%d", &(cmd->pad_b));

    s0 += strcspn(s0, " \t\n");

    if (oflag != 0)
      printf("%s %d", var_2D8, cmd->pad_b);

    goto loc_10003AA8;
  }
  else if (strcmp("seqloop:", var_2D8) == 0)
  {
    cmd->type = 12;

    if (oflag != 0)
      printf("%s", var_2D8);

    goto loc_10003AA4;
  }
  else if (strcmp("seqstop:", var_2D8) == 0)
  {
    cmd->type = 11;
    sscanf(s0, "%d", &(cmd->pad_b));

    s0 += strcspn(s0, " \t\n");

    if (oflag != 0)
      printf("%s %d", var_2D8, cmd->pad_b);

    goto loc_10003A98;
  }
  else if (strcmp("seqrepeat:", var_2D8) == 0)
  {
    cmd->type = 13;
    sscanf(s0, "%d", &(cmd->pad_b));

    s0 += strcspn(s0, " \t\n");

    if (oflag != 0)
    {
      printf("%s %d", var_2D8, cmd->pad_b);

      printf("warning: %s not implemented\n", var_2D8);
    }

    free(cmd);
    goto loc_10003AE8;
  }
  else if (strcmp("seqkill:", var_2D8) == 0)
  {
    cmd->type = 14;
    sscanf(s0, "%d", &(cmd->pad_b));

    s0 += strcspn(s0, " \t\n");

    if (oflag != 0)
      printf("%s %d", var_2D8, cmd->pad_b);

    goto loc_10003A90;
  }
  else if (strcmp("seqkillall:", var_2D8) == 0)
  {
    cmd->type = 15;
    var_60 = var_58;

    if (oflag != 0)
      printf("%s", var_2D8);

    goto loc_10003A90;
  }
  else if (strncmp("#", var_2D8, 1) == 0)
  {
    if (oflag != 0)
      printf("%s", var_2D8);

    free(cmd);

    goto loc_10003AE8;
  }
  else
  {
    if (oflag != 0)
      printf("bad command: %s", var_2D8);

    free(cmd);

    var_58 = 1;
    var_60 = var_58;
    goto loc_10003A90;
  }

  loc_100041A4:
  for (struct animSeq *seq = seqList; seq != NULL; seq = seq->next)
  {
    if (seq->seq == 0)
    {
      seq->cmd_h = seq->cmd_g;
      break;
    }
  }

  if (oflag != 0)
    printf("# done reading animation\n");

  if (seqList == NULL)
  {
    return;
  }

  if (oflag != 0)
    printf("seq %d at %.2f\n", seqList->seq, seqList->seqFrame);

  struct animSeq *seq = seqList;
  struct animCommand *s0cmd = seq->cmd_g;

  while (1)
  {
    if (s0cmd != NULL)
    {
      if (oflag != 0)
        printf("  cmd %d,\t%d\t%f\n", s0cmd->type, s0cmd->pad_b, s0cmd->flt_d);

      s0cmd = s0cmd->next;
      continue;
    }
    else
    {
      seq = seq->next;

      if (seq == NULL)
      {
        return;
      }

      if (oflag != 0)
        printf("seq %d at %.2f\n", seq->seq, seq->seqFrame);

      s0cmd = seq->cmd_g;

      continue;
    }
  }
}

static float fold_interp(int a0, const float *a1, float f14, float f15)
{
  int a4 = a0 - 1;

  if (a0 <= 0)
  {
    a4 = a4 + 128;
  }

  const float f5 = a1[a0];
  const float f6 = a1[a4];
  float f8 = f15 * 0.5f;
  const float f4 = f5 - f6;
  const float f7 = 1.0f - f14;

  if (f8 < f4)
  {
    float f0 = f6 + f15;

    float f1 = f5 * f14;
    f0 = f7 * f0;
    f0 = f0 + f1;
    return f0;
  }

  const float f10 = f15 * -0.5f;
  f8 = f7 * f6;

  if (f4 < f10)
  {
    float f0 = f5 + f15;
    f0 = f14 * f0;
    f0 = f8 + f0;
    return f0;
  }
  else
  {
    float f0 = f5 * f14;
    f0 = f8 + f0;
    return f0;
  }
}

#ifdef OPENGL10
// OpenGL 1.0 implementation
static void draw_shape(char poly, const void *context)
{
    if (poly == 0)
    {
        wrap_glBegin(GL_LINES, context);
        for (size_t i=0; i < NELEMS(square_line_vertices); i+=2)
        {
            wrap_glVertex2f(square_line_vertices[i], square_line_vertices[i+1], context);
        }
        wrap_glEnd(context);
    }
    else
    {
        wrap_glBegin(GL_TRIANGLE_FAN, context);
        for (size_t i=0; i < NELEMS(square_polygon_triangle_fan_vertices); i+=2)
        {
            wrap_glVertex2f(square_polygon_triangle_fan_vertices[i], square_polygon_triangle_fan_vertices[i+1], context);
        }
        wrap_glEnd(context);
    }
}
#elif OPENGL11
// Implementation using vertex arrays, for OpenGL 1.1+ and OpenGL ES 1.0
static void draw_shape(char poly, const void *context)
{
  if (poly == 0)
  {
    wrap_glEnableClientState(GL_VERTEX_ARRAY, context);
    wrap_glVertexPointer(2, GL_FLOAT, 0, square_line_vertices, context);
    wrap_glDrawArrays(GL_LINES, 0, NELEMS(square_line_vertices) / 2, context);
    wrap_glDisableClientState(GL_VERTEX_ARRAY, context);
  }
  else
  {
    wrap_glEnableClientState(GL_VERTEX_ARRAY, context);
    wrap_glVertexPointer(2, GL_FLOAT, 0, square_polygon_triangle_fan_vertices, context);
    wrap_glDrawArrays(GL_TRIANGLE_FAN, 0, NELEMS(square_polygon_triangle_fan_vertices) / 2, context);
    wrap_glDisableClientState(GL_VERTEX_ARRAY, context);
  }
}
#elif OPENGL15
// Implementation using vertex buffer objects, for OpenGL 1.5+ and OpenGL ES 1.1+
static void draw_shape(char poly, const void *context)
{
  if (poly == 0)
  {
    glBindBuffer(GL_ARRAY_BUFFER, square_line_vbo); // bind the buffer
    wrap_glEnableClientState(GL_VERTEX_ARRAY, context);
    wrap_glVertexPointer(2, GL_FLOAT, 0, 0, context);
    wrap_glDrawArrays(GL_LINES, 0, NELEMS(square_line_vertices) / 2, context);
    wrap_glDisableClientState(GL_VERTEX_ARRAY, context);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind the buffer
  }
  else
  {
    glBindBuffer(GL_ARRAY_BUFFER, square_polygon_triangle_fan_vbo); // bind the buffer
    wrap_glEnableClientState(GL_VERTEX_ARRAY, context);
    wrap_glVertexPointer(2, GL_FLOAT, 0, 0, context);
    wrap_glDrawArrays(GL_TRIANGLE_FAN, 0, NELEMS(square_polygon_triangle_fan_vertices) / 2, context);
    wrap_glDisableClientState(GL_VERTEX_ARRAY, context);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind the buffer
  }
}
#else
#error Define OPENGL10, OPENGL11, or OPENGL15 depending on what your system supports
#endif // OPENGL10

static void taste_queue(void)
{
  struct animSeq *seq;
  struct animCommand *cmd;
  EPANOS_REG f6;
  EPANOS_REG f7;
  EPANOS_REG f8;
  EPANOS_REG f9;
  
  currentFrame = currentFrame + 1.0f;

  for (seq = seqList; seq != NULL; seq = seq->next)
  {
    double f4 = (double)currentFrame + 0.5;
    cmd = seq->cmd_h;
    if ((double)seq->seqFrame < f4)
    {
      ;
    }
    else
    {
      continue;
    }

    if (seq->pad_b[0] == 0)
    {
      continue;
    }

    if (cmd == NULL)
    {
      continue;
    }

    f6.s = cmd->cmdFrame;
    f6.s = f6.s + seq->seqFrame;
    f6.d = f6.s;
    if (f6.d < f4)
    {
      ;
    }
    else
    {
      continue;
    }

    loc_10004F7C:
    process_command(cmd);

    f9.s = seq->seqFrame;
    f8.s = currentFrame;
    cmd = seq->cmd_h;
    if (seq->pad_b[0] == 0)
    {
      continue;
    }

    if (cmd == NULL)
    {
      continue;
    }

    f7.s = cmd->cmdFrame;
    f8.d = f8.s;
    f7.s = f7.s + f9.s;
    f8.d = f8.d + 0.5;
    f7.d = f7.s;
    if (f7.d < f8.d)
    {
      goto loc_10004F7C;
    }
  }
}

static void hls_to_rgb(float *a3, float *a4, float *a5, float f12, float f13, float f14)
{
  float f20;

  if ((double)f13 <= 0.5)
  {
    f20 = f14 + 1.0f;
    f20 = f13 * f20;
  }
  else
  {
    float f21 = f13 * f14;

    f20 = f13 + f14;
    f20 = f20 - f21;
  }

  if (f14 == 0.0f)
  {
    *a5 = f13;
    *a4 = f13;
    *a3 = f13;
    return;
  }

  float val_arg_1 = (f13 * 2.0f) - f20;

  double val_arg_3 = f12 * 360.00000000000000;

  // there used to be a conversion to single-precision for val_arg_3 (to copy to var_50, used as
  // arg 3 to the *a4 call below) and then it would be converted back to double-precision.
  // necessarily there would be a loss of precision for subsequent calculations
  // (adding -120 for the *a5 call), but I haven't seen any visual sign of it

  *a3 = trapezoid(val_arg_1, f20, val_arg_3 + 120.00000000000000);

  *a4 = trapezoid(val_arg_1, f20, val_arg_3);

  *a5 = trapezoid(val_arg_1, f20, val_arg_3 + -120.00000000000000);

  return;
}

static void kill_seq(struct animSeq *seq)
{
  if (seq == NULL)
  {
    return;
  }

  seq->pad_b[0] = 0;
  if (seq == seqList)
  {
    seqList = seqList->next;
    struct animCommand *cmd = seqList->cmd_g;
    while (cmd != NULL)
    {
      struct animCommand *next = cmd->next;
      free(cmd);

      cmd = next;
    }

    free(seq);
  }

  struct animSeq *a3 = seqList;

  {
    struct animSeq *a2 = seqList->next;

    if (a2 == NULL)
    {
      return;
    }

    while (a2 != seq)
    {
      a3 = a2;
      a2 = a2->next;
      if (a2 != NULL)
      {
        continue;
      }
      else
      {
        return;
      }
    }
  }

  a3->next = seq->next;

  {
    struct animCommand *cmd = seq->cmd_g;
    while (cmd != NULL)
    {
      struct animCommand *next = cmd->next;
      free(cmd);

      cmd = next;
    }
  }

  free(seq);

  return;
}

static void create_act_table(void)
{
  acttable[ACT_OUTLINE] = create_blank_act();
  acttable[ACT_WHEEL] = create_blank_act();
  acttable[ACT_ZOOM] = create_blank_act();
  acttable[ACT_TWIST] = create_blank_act();
  acttable[ACT_SPIN] = create_blank_act();
  acttable[ACT_SIZE] = create_blank_act();
  acttable[ACT_N] = create_blank_act();
  acttable[ACT_N]->value = 52.0000000f;
  acttable[ACT_WRIST] = create_blank_act();
  acttable[ACT_HUE_RATE] = create_blank_act();
  acttable[ACT_HUE] = create_blank_act();
  acttable[ACT_FLIP] = create_blank_act();
  acttable[ACT_ARM] = create_blank_act();
  acttable[ACT_SPEED] = create_blank_act();
  acttable[ACT_SPEED]->value = flt_100092A8;
  acttable[ACT_LIGHT] = create_blank_act();

  return;
}

static struct act *create_blank_act(void)
{
  struct act *ret = calloc(1, sizeof(struct act));
  
  ret->flt_b = flt_100092A8;
  ret->flt_i = 0.600000024f;

  return ret;
}

static float trapezoid(float f12, float f13, float f14)
{
  EPANOS_REG f1;
  const double f3 = 60.000000000000000;
  const float f5 = 240.000000f;
  const float f6 = 180.000000f;
  const float f7 = 360.000000f;

  if (f7 < f14)
  {
    f14 = f14 + -360.0f;
  }

  if (f14 < 0.0f)
    f14 = f14 + f7;

  if (f14 < 60.0000000f)
  {
    double f2 = f14;
    f2 = f2 / f3;
    f1.s = f13 - f12;
    f1.d = f1.s;
    f1.d = f1.d * f2;
    double f0 = f12 + f1.d;
    return f0;
  }

  if (f14 < f6)
    return f13;

  if (f14 < f5)
  {
    ;
  }
  else
  {
    return f12;
  }

  double f2 = (double)(f5 - f14);
  f2 = f2 / f3;
  f1.s = f13 - f12;
  f1.d = f1.s;
  double f0 = f12;
  f1.d = f1.d * f2;
  f0 = f0 + f1.d;
  return f0;
}

static void process_command(struct animCommand *cmd)
{
  if (oflag != 0)
  {
    printf("proc: currentFrame %.2f, seq %d,\tseqFrame %f, cmdtype %d, cmdFrame %f\n",
        currentFrame, cmd->seq_e->seq, cmd->seq_e->seqFrame, cmd->type, cmd->cmdFrame);
  }

  {
    switch (cmd->type)
    {
      case 0:
      case 1:   // fallthrough intended: these handlers had the same code
      case 6:
      case 9:
      case 13:
      {
        cmd->seq_e->cmd_h = cmd->seq_e->cmd_h->next;
        return;
      }
      break;

      case 2:
      {
        struct act *act = acttable[cmd->pad_b];

        if (act != NULL)
        {
          if (act->flt_e >= cmd->flt_d)
          {
            act->flt_e = cmd->flt_d;
          }
        }

        cmd->seq_e->cmd_h = cmd->seq_e->cmd_h->next;
        return;
      }
      break;

      case 3:
      {
        struct act *act = acttable[cmd->pad_b];

        if (act != NULL)
        {
          if (act->flt_e < cmd->flt_d)
          {
            if (cmd->flt_d >= act->flt_d)
              act->flt_d = cmd->flt_d;
          }
          else
          {
            if (act->flt_e >= act->flt_d)
              act->flt_d = act->flt_e;

            if (act->flt_e >= cmd->flt_d)
            {
              act->flt_e = cmd->flt_d;
            }
          }

          act->flt_h = cmd->seq_e->flt_e;
          act->pad_a[0] = 1;
          act->flt_i = cmd->seq_e->flt_f;
        }
        cmd->seq_e->cmd_h = cmd->seq_e->cmd_h->next;
        return;
      }
      break;

      case 4:
      {
        struct act *act = acttable[cmd->pad_b];
        if (act != NULL)
          act->value = cmd->flt_d;

        cmd->seq_e->cmd_h = cmd->seq_e->cmd_h->next;
        return;
      }
      break;

      case 101:
      {
        if ((double)cmd->flt_d < 1.0)
          cmd->seq_e->flt_e = 1.0;
        else
          cmd->seq_e->flt_e = cmd->flt_d;

        cmd->seq_e->cmd_h = cmd->seq_e->cmd_h->next;
        return;
      }
      break;

      case 102:
      {
        double f4 = cmd->flt_d;

        if (f4 < 0)
        {
          f4 = 0;
        }
        else
        {
          if (1.0 < f4)
          {
            f4 = 1.0;
          }
        }

        cmd->seq_e->flt_f = f4;

        cmd->seq_e->cmd_h = cmd->seq_e->cmd_h->next;
        return;
      }
      break;

      case 103:
      {
        EPANOS_REG f4;
        EPANOS_REG f6;
        EPANOS_REG f7;

        f7.d = (double)exp_rand(1.0f) * 2.0;
        f6.d = (double)cmd->flt_d * f7.d;
        f4.s = cmd->flt_d * (1.0f - cmd->seq_e->flt_f);
        f4.d = f4.s;
        f4.d += (double)cmd->seq_e->flt_f * f6.d;

        cmd->seq_e->seqFrame = (double)cmd->seq_e->seqFrame + f4.d;

        cmd->seq_e->cmd_h = cmd->seq_e->cmd_h->next;
        return;
      }
      break;

      case 8:
      {
        stop_animation();
        cmd->seq_e->cmd_h = cmd->seq_e->cmd_h->next;
        return;
      }
      break;

      case 10:
      {
        struct animSeq *seq = seqList;
        while (seq != NULL)
        {
          if (seq->seq != cmd->pad_b)
          {
            seq = seq->next;
            continue;
          }
          else
          {
            break;
          }
        }

        if (seq != NULL)
        {
          seq->cmd_h = seq->cmd_g;
          seq->seqFrame = currentFrame;
        }

        if (cmd->seq_e == seq)
        {
          return;
        }

        cmd->seq_e->cmd_h = cmd->seq_e->cmd_h->next;
        return;
      }
      break;

      case 11:
      {
        struct animSeq *seq = seqList;

#if 0
        // Turned this very confusing block into the code below, hopefully it works
        if (seq != NULL)
        {
          if (seq->seq != cmd->pad_b)
          {
            seq = seq->next;
            loc_10004D48:

            if (seq != NULL)
            {
              if (seq->seq == cmd->pad_b)
              {
                seq->cmd_h = NULL;
              }
              else
              {
                seq = seq->next;
                goto loc_10004D48;
              }
            }
            goto loc_10004D60;
          }
        }

        if (seq != NULL)
        {
          seq->cmd_h = NULL;
        }
#endif

        for (; seq != NULL; seq = seq->next)
        {
          if (seq->seq == cmd->pad_b)
          {
            seq->cmd_h = NULL;
          }
        }

        loc_10004D60:
        if (cmd->seq_e == seq)
        {
          return;
        }

        cmd->seq_e->cmd_h = cmd->seq_e->cmd_h->next;
        return;
      }
      break;

      case 12:
      {
        cmd->seq_e->cmd_h = cmd->seq_e->cmd_g;
        cmd->seq_e->seqFrame += cmd->seq_e->flt_d;
        return;
      }
      break;

      case 14:
      {
        struct animSeq *seq = seqList;

        if (seqList != NULL)
        {
          while (seq->seq != cmd->pad_b)
          {
            seq = seq->next;

            if (seq != NULL)
              continue;
            else
              break;
          }
        }

        if (cmd->seq_e != seq)
        {
          return;
        }

        if (seq == NULL)
          cmd->seq_e->cmd_h = cmd->seq_e->cmd_h->next;
        else
          kill_seq(seq);

        return;
      }
      break;

      case 15:
      {
        struct animSeq *seq = seqList;

        for (; seq != NULL; seq = seq->next)
        {
          if (cmd->seq_e != seq)
          {
            kill_seq(seq);
            break;
          }

          // I think this is redundant--the default/"bad command type" block already does this
          cmd->seq_e->cmd_h = cmd->seq_e->cmd_h->next;
        }
        goto def_100049B4;
      }
      break;

      case 7:
      {
        if (acttable[cmd->pad_b] != NULL)
        {
          acttable[cmd->pad_b]->pad_a[0] = 0;
        }

        cmd->seq_e->cmd_h = cmd->seq_e->cmd_h->next;
        return;
      }
      break;

      case 5:
      {
        struct act *act = acttable[cmd->pad_b];
        if (act != NULL)
          act->value = act->flt_j;

        cmd->seq_e->cmd_h = cmd->seq_e->cmd_h->next;
        return;
      }
      break;

      default:
        goto def_100049B4;
    }
  }
  def_100049B4:

  printf("warning: bad command type (%d) in sequence cmd->seq\n", cmd->type);
  cmd->seq_e->cmd_h = cmd->seq_e->cmd_h->next;
  return;
}

void ep_display(const void *context)
{
  int s3 = 0;

  if ((double)1.0 <= (double)(t + acttable[ACT_SPEED]->value))
  {
    t = 0;

    n = (n + 1) & 127; // range of 'n' is 0 to 127

    s3 = 1;
  }

  if (aflag != 0)
  {
    taste_queue();
    set_act_targets();
    animate_acts();
  }

  y[n] = 0;
  x[n] = 0;
  dzoom[n] = acttable[ACT_ZOOM]->value;
  arm[n] = acttable[ACT_ARM]->value;
  wrist[n] = acttable[ACT_WRIST]->value;

  const float var_50 = acttable[ACT_WHEEL]->value;

  dtwist[n] = acttable[ACT_TWIST]->value;

  nlimit = trunc_w_d(floor((double) acttable[ACT_N]->value));

  if (0.0 < (double)acttable[ACT_OUTLINE]->value)
    outline[n] = 1;
  else
    outline[n] = 0;

  float f5 = acttable[ACT_HUE]->value;

  hue[n] = acttable[ACT_HUE]->value;

  if (1.0f <= acttable[ACT_HUE]->value)
  {
    f5 = f5 + -1.0f;
    hue[n] = f5;
  }

  if (f5 <= 1.0f)
  {
    hue[n] = f5 + 1.0f;
  }

  light[n] = acttable[ACT_LIGHT]->value;

  if (s3 != 0)
  {
    gflip = fmodf(gflip + acttable[ACT_FLIP]->value, 360.0f);
    gspin = fmodf(gspin + acttable[ACT_SPIN]->value, 360.0f);

    flip[n] = gflip;
    spin[n] = gspin;
  }

  wheel = fmodf(wheel - var_50, 360.0f);

  draw_wings(n, context);

  t = t + acttable[ACT_SPEED]->value;

  //t9.u64 = (uint64_t) swapBuffers__Q2_10GLXWrapper6windowGv;

  return;
}

static void set_act_targets(void)
{
  struct act **s0 = acttable;
  float f1;
  float f5;
  const float f20 = 1.00000000f;

  for (unsigned int s1=0; s1 < NELEMS(acttable); s1++,s0++)
  {
    struct act *act = *s0;

    if (act == NULL)
    {
      continue;
    }

    if (act->pad_a[0] == 0)
    {
      continue;
    }

    if (act->pad_a[1] != 0)
    {
      continue;
    }

    act->pad_a[1] = 1;

    {
      float f0 = drand48();
      f1 = act->flt_e;
      float f2 = f20 - f0;
      f0 = act->flt_d * f0;
      f1 = f1 * f2;
      f0 = f0 + f1;
      act->flt_c = f0;
    }
    {
      float f2 = act->flt_i;
      f1 = act->flt_h;
      float f3 = exp_rand(f20) * 2.00000000f;
      float f4 = f20 - f2;
      f3 = f1 * f3;
      f1 = f1 * f4;
      f2 = f2 * f3;
      f1 = f1 + f2;
    }
    f5 = f20;

    if (f1 < f20)
      ;
    else
    {
      float f7 = act->flt_i;
      f5 = act->flt_h;
      float f8 = exp_rand(f20) * 2.00000000f;
      float f9 = f20 - f7;
      f8 = f5 * f8;
      f5 = f5 * f9;
      f7 = f7 * f8;
      f5 = f5 + f7;
    }

    {
      float f4 = act->flt_c;
      f4 = f4 - act->flt_f;
      f4 = f4 / f5;
      s0++;
      act->flt_f = f4;

      if (0 < f4)
        f4 = f20;
      else
        f4 = -1.00000000f;

      act->flt_b = f4;
    }

    if (s1 < NELEMS(acttable)-1)
    {
      s1++;
    }
    else
    {
      return;
    }
  }
}

void ep_reshape(const int width, const int height)
{
#ifdef OPENGL15
  if (!vbo_initialized)
  {
    glGenBuffers(1, &square_line_vbo);  // generate a buffer
    glBindBuffer(GL_ARRAY_BUFFER, square_line_vbo); // use the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(square_line_vertices), square_line_vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind the buffer

    glGenBuffers(1, &square_polygon_triangle_fan_vbo);  // generate a buffer
    glBindBuffer(GL_ARRAY_BUFFER, square_polygon_triangle_fan_vbo); // use the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(square_polygon_triangle_fan_vertices), square_polygon_triangle_fan_vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind the buffer

    vbo_initialized = 1;
  }
#endif

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    ep_gluPerspective(300.0,
                   (double)((float)width / (float)height),
                   0.01,
                   10000.0);
    glTranslatef(0.0f, 0.0f, -4.0f);
    glMatrixMode(GL_MODELVIEW);
}

static float interp(int a0, const float *a1, float f14)
{
  int a4 = a0 - 1;

  if (a0 <= 0)
  {
    a4 = a4 + 128;
  }

  const float f2 = 1.0f - f14;
  return (a1[a0] * f14) + (a1[a4] * f2);
}

static float exp_rand(float arg)
{
  assert ((double)arg > 0.0);

  return (double)expm1(drand48() * (double)arg) / (double)expm1(1.0);
}

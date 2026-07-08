/*****************************************************************
    sgi-demos: IRIS GL implementations of the ElectroPortis GL shims
    declared in gl_wrap.h.  See that header for the mapping rationale.
*****************************************************************/
#include "gl_wrap.h"

/* wrap_glBegin/glVertex2f/glEnd buffer vertices, then ep_gl_end() emits
   them to IRIS GL according to the primitive kind.  The shapes are tiny
   (a 4-vertex square fan, an 8-vertex line outline), so a small fixed
   buffer is ample. */
#define EP_MAXV 64
static GLenum ep_prim_mode;
static Coord  ep_vbuf[EP_MAXV][2];
static int    ep_vcount;

/* OpenGL rasterizes NOTHING for zero-area triangles and zero-length
   lines, and ep depends on that: its display loop never fills the size[]
   history array, so the three mirrored copies of every wing are drawn
   under scale(0,0,1) and are invisible on the real screensaver.  The
   IRIS GL rasterizers here plot such degenerate primitives as single
   pixels, which showed up as spurious swirling "particles".  So track a
   degenerate flag through the matrix stack (all of ep's push/pop/scale
   flow through these shims) and skip primitive emission while set. */
static int ep_degenerate = 0;
static int ep_deg_stack[32];
static int ep_deg_sp = 0;

/* Shipped-1994 mode (off by default for this reversed build; M toggles).
   The OpenGL rewrite of Electropaint accidentally diverged from the IRIS
   GL ep in two ways: (1) it lost the size wiring, so the 3 mirrored copies
   of every wing are drawn under scale(0,0,1) -- invisible on real OpenGL,
   killing the IRIS-era 4-fold symmetry; (2) it passed the IRIS
   perspective() angle "300" (tenths of a degree) to gluPerspective, which
   reads degrees, giving an inverted frustum with an effective 60-degree
   FOV at eye distance 4 (vs the IRIS 30 degrees at polarview distance 10).

   Default (0): faithful to the IRIS GL ep -- mirrors restored (the
   collapsing scale is treated as identity) and the intended camera.  This
   reversed build restores that IRIS-GL look by default -- the opposite of
   the decompiled build, which defaults to the shipped-1994 look.
   M / shipped (1): what the 1994 binary actually rendered -- one visible
   copy per wing (degenerates discarded as real OpenGL rasterization
   would) and the accidental wide flipped camera. */
int ep_shipped_ogl = 0;

void
ep_gl_pushmatrix(void)
{
    pushmatrix();
    if (ep_deg_sp < 32)
        ep_deg_stack[ep_deg_sp++] = ep_degenerate;
}

void
ep_gl_popmatrix(void)
{
    popmatrix();
    if (ep_deg_sp > 0)
        ep_degenerate = ep_deg_stack[--ep_deg_sp];
}

void
ep_gl_scalef(GLfloat x, GLfloat y, GLfloat z)
{
    /* z can't collapse ep's 2D squares; x or y ~0 flattens them */
    int collapses = (x < 1e-6f && x > -1e-6f) || (y < 1e-6f && y > -1e-6f);

    if (collapses && !ep_shipped_ogl)
        return;                 /* restore the mirror: identity, not 0 */

    scale((float)x, (float)y, (float)z);
    if (collapses)
        ep_degenerate = 1;      /* real OpenGL would draw nothing */
}

void
ep_gl_begin(GLenum mode)
{
    ep_prim_mode = mode;
    ep_vcount = 0;
}

void
ep_gl_vertex2f(GLfloat x, GLfloat y)
{
    if (ep_vcount < EP_MAXV) {
        ep_vbuf[ep_vcount][0] = x;
        ep_vbuf[ep_vcount][1] = y;
        ep_vcount++;
    }
}

void
ep_gl_end(void)
{
    int i;

    if (ep_degenerate) {
        ep_vcount = 0;   /* collapsed to a point: real GL draws nothing */
        return;
    }

    if (ep_prim_mode == GL_LINES) {
        /* GL_LINES: independent segments, one per vertex pair */
        for (i = 0; i + 1 < ep_vcount; i += 2) {
            bgnline();
            v2f(ep_vbuf[i]);
            v2f(ep_vbuf[i + 1]);
            endline();
        }
    } else if (ep_prim_mode == GL_LINE_LOOP) {
        bgnclosedline();
        for (i = 0; i < ep_vcount; i++) v2f(ep_vbuf[i]);
        endclosedline();
    } else {
        /* GL_TRIANGLE_FAN / GL_TRIANGLES / GL_POLYGON: a convex fill */
        bgnpolygon();
        for (i = 0; i < ep_vcount; i++) v2f(ep_vbuf[i]);
        endpolygon();
    }
}

void
ep_gl_clear(GLbitfield mask)
{
    /* glClear uses glClearColor (black); IRIS clear() uses the current
       colour, so force black first (drawit sets a colour right after). */
    static float black[3] = { 0.0f, 0.0f, 0.0f };
    (void)mask;
    c3f(black);
    clear();
}

void
ep_gl_color4f(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    /* ep draws opaque (alpha always 1.0); IRIS GL c3f suffices */
    float c[3];
    (void)a;
    c[0] = r; c[1] = g; c[2] = b;
    c3f(c);
}

/* ep only ever rotates about a single primary axis; IRIS rotate() takes
   tenths of a degree and an axis character. */
void
ep_gl_rotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
    char axis = (x != 0.0f) ? 'x' : ((y != 0.0f) ? 'y' : 'z');
    rotate((Angle)(angle * 10.0f), axis);
}

void
ep_gl_matrixmode(GLenum mode)
{
    mmode(mode == GL_PROJECTION ? MPROJECTION : MVIEWING);
}

void
ep_gl_loadidentity(void)
{
    static Matrix ident = {
        {1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0},
        {0.0, 0.0, 0.0, 1.0}
    };
    loadmatrix(ident);
}

/* glFrustum is exactly IRIS GL window() */
void
ep_gl_frustum(GLdouble l, GLdouble r, GLdouble b, GLdouble t,
              GLdouble near, GLdouble far)
{
    window((Coord)l, (Coord)r, (Coord)b, (Coord)t, (Coord)near, (Coord)far);
}

/* Replaces the fork's gluperspective.c.  ep's reshape passes fovy=300,
   which is the ORIGINAL IRIS GL perspective() convention: tenths of a
   degree (= 30 deg), not the 300 degrees a literal gluPerspective would
   read.  Map straight to IRIS perspective() so we get the intended view
   (the fork's gluPerspective produced a Y-flipped frustum that IRIS
   window() clips away). */
void
ep_gluPerspective(double fovy, double aspect, double near, double far)
{
    if (ep_shipped_ogl) {
        /* emulate the binary's gluPerspective(300 degrees): an inverted
           frustum with an effective 60-degree FOV; ep's reshape then
           applies its own -4 eye translation */
        perspective((Angle)(fovy * 2.0), (float)aspect, (Coord)near, (Coord)far);
        scale(1.0f, -1.0f, 1.0f);
    } else {
        /* as the IRIS GL ep framed it: 30 degrees at polarview distance
           10 -- ep's reshape contributes -4, we add the remaining -6 */
        perspective((Angle)fovy, (float)aspect, (Coord)near, (Coord)far);
        translate(0.0, 0.0, -6.0);
    }
}

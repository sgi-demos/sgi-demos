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
    perspective((Angle)fovy, (float)aspect, (Coord)near, (Coord)far);
}

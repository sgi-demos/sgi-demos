/*****************************************************************
    sgi-demos: retarget ElectroPortis's GL abstraction onto IRIS GL.

    ElectroPortis (Brendan Shanks's clean decompilation of the OpenGL IRIX
    Electropaint) draws through a tiny set of wrap_gl* calls that on most
    platforms are #defined straight to OpenGL.  This replacement gl_wrap.h
    maps them instead onto the IRIS GL primitives that sgi-demos already
    implements, so the real OpenGL Electropaint renders through the same
    rasterizer as every other demo -- no OpenGL needed.

    ep.c is built with -DOPENGL10 (immediate mode), whose surface is:
      wrap_glBegin/glVertex2f/glEnd, wrap_glColor4f, wrap_glPush/PopMatrix,
      wrap_glRotatef/Translatef/Scalef, wrap_glClear, wrap_glFinish; plus
      direct glViewport/glMatrixMode/glLoadIdentity/glTranslatef in reshape
      and glFrustum (via ep_gluPerspective).  Each maps 1:1 to IRIS GL.
*****************************************************************/
#pragma once

#include <gl.h>
#include <device.h>
#include "ep_gluperspective.h"

/* OpenGL scalar types ep.c uses (IRIS gl.h does not define these) */
typedef float          GLfloat;
typedef double         GLdouble;
typedef int            GLint;
typedef unsigned int   GLuint;
typedef int            GLsizei;
typedef unsigned int   GLenum;
typedef unsigned int   GLbitfield;
typedef unsigned char  GLubyte;
typedef void           GLvoid;

/* GL enums ep.c passes to the shims below (values arbitrary but distinct) */
#define GL_COLOR_BUFFER_BIT 0x00004000
#define GL_DEPTH_BUFFER_BIT 0x00000100
#define GL_LINES            0x0001
#define GL_LINE_LOOP        0x0002
#define GL_TRIANGLES        0x0004
#define GL_TRIANGLE_STRIP   0x0005
#define GL_TRIANGLE_FAN     0x0006
#define GL_POLYGON          0x0009
#define GL_PROJECTION       0x1701
#define GL_MODELVIEW        0x1700
#define GL_FLAT             0x1D00
#define GL_SMOOTH           0x1D01
/* referenced only by the OPENGL11/15 branches (not compiled here) */
#define GL_FLOAT            0x1406
#define GL_VERTEX_ARRAY     0x8074
#define GL_ARRAY_BUFFER     0x8892
#define GL_STATIC_DRAW      0x88E4
#define GL_UNSIGNED_BYTE    0x1401
#define GL_RGBA             0x1908

/* implemented in gl_wrap_sgi.c */
void ep_gl_begin(GLenum mode);
void ep_gl_vertex2f(GLfloat x, GLfloat y);
void ep_gl_end(void);
void ep_gl_clear(GLbitfield mask);
void ep_gl_color4f(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
void ep_gl_rotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
void ep_gl_matrixmode(GLenum mode);
void ep_gl_loadidentity(void);
void ep_gl_frustum(GLdouble l, GLdouble r, GLdouble b, GLdouble t,
                   GLdouble near, GLdouble far);

/* ep.c's immediate-mode drawing -> IRIS GL */
#define wrap_glColor4f(r, g, b, a, ctx)   ep_gl_color4f((r), (g), (b), (a))
#define wrap_glPushMatrix(ctx)            pushmatrix()
#define wrap_glPopMatrix(ctx)             popmatrix()
#define wrap_glTranslatef(x, y, z, ctx)   translate((Coord)(x), (Coord)(y), (Coord)(z))
#define wrap_glScalef(x, y, z, ctx)       scale((float)(x), (float)(y), (float)(z))
#define wrap_glRotatef(a, x, y, z, ctx)   ep_gl_rotatef((a), (x), (y), (z))
#define wrap_glBegin(mode, ctx)           ep_gl_begin(mode)
#define wrap_glVertex2f(x, y, ctx)        ep_gl_vertex2f((x), (y))
#define wrap_glEnd(ctx)                   ep_gl_end()
#define wrap_glClear(mask, ctx)           ep_gl_clear(mask)
#define wrap_glFinish(ctx)                ((void)0)

/* direct gl* calls in ep.c's reshape (OPENGL10 path) -> IRIS GL */
#define glViewport(x, y, w, h) \
    viewport((Screencoord)(x), (Screencoord)((x) + (w) - 1), \
             (Screencoord)(y), (Screencoord)((y) + (h) - 1))
#define glMatrixMode(m)         ep_gl_matrixmode(m)
#define glLoadIdentity()        ep_gl_loadidentity()
#define glTranslatef(x, y, z)   translate((Coord)(x), (Coord)(y), (Coord)(z))
#define glFrustum(l, r, b, t, n, f) ep_gl_frustum((l), (r), (b), (t), (n), (f))

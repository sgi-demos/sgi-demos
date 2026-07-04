#ifndef __RASTERIZER_H__
#define __RASTERIZER_H__

#include "basic_types.h"

#define DRAW_TRIANGLES 0
#define DRAW_LINES 1
#define DRAW_POINTS 2

int32_t rasterizer_winopen(char *title);
void rasterizer_rgbmode(int enable);
void rasterizer_clear(uint8_t r, uint8_t g, uint8_t b, short color_index);
void rasterizer_zclear(uint32_t z);
void rasterizer_czclear(uint8_t r, uint8_t g, uint8_t b, short color_index, uint32_t z);
void rasterizer_swap();
void rasterizer_copy_front_to_back();
void rasterizer_copy_back_to_front();

unsigned char* rasterizer_frontbuffer();
void rasterizer_draw(uint32_t type, uint32_t count, screen_vertex *v); // count is the number of primitives.
void rasterizer_bitmap(uint32_t width, uint32_t rowbytes, uint32_t height, screen_vertex *sv, uint8_t *bits);
void rasterizer_alpha_blit(uint32_t width, uint32_t rowbytes, uint32_t height, screen_vertex *sv, uint8_t *alpha, uint8_t r, uint8_t g, uint8_t b);
void rasterizer_setpattern(uint16_t pattern[16]);
void rasterizer_pattern(int enable);
void rasterizer_cbuffer_draw(int enable_front, int enable_back);
void rasterizer_zbuffer(int enable);
void rasterizer_linewidth(float w);
void rasterizer_frame_sync(void);

// The framebuffer tracks the window size: called once after the window
// exists (with its initial size) and again on every window resize. The
// rasterizer (re)allocates its buffers at the new size; contents are
// cleared. The transition is atomic: by the time this returns, the new
// buffers are the active draw/display targets.
void rasterizer_resize(uint32_t width, uint32_t height);

//
// Dual rendering modes: the rasterizer_* API above dispatches through a
// function table to one of two implementations, selected at startup in
// rasterizer.c:
//   - gles2:     GPU rasterizer on OpenGL ES2  (gles2_rasterizer.c) — default
//   - reference: CPU scanline rasterizer  (reference_rasterizer.c) — for
//                reference/debugging (GLES2_RASTERIZER=ref / ?rast=ref)
//
typedef struct rasterizer_funcs
{
    int32_t (*winopen)(char *title);
    void (*rgbmode)(int enable);
    void (*clear)(uint8_t r, uint8_t g, uint8_t b, short color_index);
    void (*zclear)(uint32_t z);
    void (*czclear)(uint8_t r, uint8_t g, uint8_t b, short color_index, uint32_t z);
    void (*swap)(void);
    void (*copy_front_to_back)(void);
    void (*copy_back_to_front)(void);
    unsigned char* (*frontbuffer)(void);
    void (*draw)(uint32_t type, uint32_t count, screen_vertex *v);
    void (*bitmap)(uint32_t width, uint32_t rowbytes, uint32_t height, screen_vertex *sv, uint8_t *bits);
    void (*alpha_blit)(uint32_t width, uint32_t rowbytes, uint32_t height, screen_vertex *sv, uint8_t *alpha, uint8_t r, uint8_t g, uint8_t b);
    void (*setpattern)(uint16_t pattern[16]);
    void (*pattern)(int enable);
    void (*cbuffer_draw)(int enable_front, int enable_back);
    void (*zbuffer)(int enable);
    void (*linewidth)(float w);
    void (*frame_sync)(void);
    void (*resize)(uint32_t width, uint32_t height);
} rasterizer_funcs;

const rasterizer_funcs* ref_rasterizer_get_funcs(void);
const rasterizer_funcs* gles2_rasterizer_get_funcs(void);

#endif /* __RASTERIZER_H__ */

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
unsigned char* rasterizer_frontbuffer();
void rasterizer_draw(uint32_t type, uint32_t count, screen_vertex *v); // count is the number of primitives.
void rasterizer_bitmap(uint32_t width, uint32_t rowbytes, uint32_t height, screen_vertex *sv, uint8_t *bits);
void rasterizer_setpattern(uint16_t pattern[16]);
void rasterizer_pattern(int enable);
void rasterizer_cbuffer_draw(int enable_front, int enable_back);
void rasterizer_zbuffer(int enable);
void rasterizer_linewidth(float w);

#endif /* __RASTERIZER_H__ */


#ifndef __BASIC_TYPES_H__
#define __BASIC_TYPES_H__

#include <stdlib.h>
#include <stdint.h>

typedef float viewport_t[6];
typedef float matrix4x4f[16];
typedef float vec4f[4];
typedef float vec3f[3];
typedef uint16_t vec3us[3];
typedef uint16_t vec4us[4];
typedef uint8_t vec3ub[3];
typedef uint8_t vec4ub[4];

#ifndef bool
typedef uint8_t bool;
#endif

#ifndef false
#define false 0
#define true 1
#endif

// Color index accompanying each screen vertex in color-map mode. The RGB
// fields always carry the colormap-resolved color; ci additionally records
// which index produced it so the rasterizer can maintain a per-pixel color
// index buffer (the SGI hardware palette LUT emulation — see
// rasterizer_resolve_ci_to_rgb). SCREEN_VERTEX_CI_NONE marks vertices with
// no index: shim UI (menus) and RGB-mode geometry.
#define SCREEN_VERTEX_CI_NONE 0xFFFF

typedef struct screen_vertex
{
    int32_t x, y;   // pixels in 1/SCREEN_VERTEX_V2_SCALE fixed point; signed
                    // so coordinate differences are safe, 32-bit so any
                    // realistic framebuffer size fits (2^31/32 = 67M pixels)
    uint32_t z;
    uint8_t r, g, b, a;
    uint16_t ci;    // color index (CI mode), or SCREEN_VERTEX_CI_NONE
} screen_vertex;

#define SCREEN_VERTEX_V2_SCALE 32

#endif /* __BASIC_TYPES_H__ */

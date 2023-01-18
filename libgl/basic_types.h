
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

typedef struct screen_vertex
{
    uint16_t x, y;
    uint32_t z;
    uint8_t r, g, b, a;
} screen_vertex;

#define SCREEN_VERTEX_V2_SCALE 32

#endif // __BASIC_TYPES_H__

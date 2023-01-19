#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "basic_types.h"

extern const matrix4x4f identity_4x4f;

#define STACK_MAX 8

typedef struct matrix4x4f_stack
{
    matrix4x4f s[STACK_MAX];

    int top;

    int inverse_needs_calculation;
    matrix4x4f inverse;
} matrix4x4f_stack;

typedef struct viewport_stack
{
    viewport_t s[STACK_MAX];
    int top;
} viewport_stack_t;

// This syntax ensures that a non-inline version of these functions
// is made available as an externally-linkable function in this
// compilation unit.

extern void vec4f_set(vec4f v, float x, float y, float z, float w);
extern void vec3f_set(vec3f v, float x, float y, float z);
extern void vec4f_set(vec4f v, float x, float y, float z, float w);
extern void vec3f_copy(vec3f d, const vec3f s);
extern void vec4f_copy(vec4f d, const vec4f s);
extern void vec4f_subtract(vec4f i1, vec4f i2, vec4f out);
extern void vec3f_scale(vec3f i1, float v, vec3f out);
extern void vec4f_scale(vec4f i1, float v, vec4f out);
extern void vec3f_mult(vec3f i1, vec3f i2, vec3f out);
extern void vec4f_mult(vec4f i1, vec4f i2, vec4f out);
extern void vec3f_blend(vec3f i1, vec3f i2, float t, vec3f out);
extern void vec4f_blend(vec4f i1, vec4f i2, float t, vec4f out);
extern void vec4f_add(vec4f i1, vec4f i2, vec4f out);
extern void vec3f_add(vec3f i1, vec3f i2, vec3f out);
extern float vec3f_dot(vec3f i1, vec3f i2);
extern float vec4f_dot(vec4f i1, vec4f i2);
extern void vec3f_normalize(vec3f i1, vec3f out);
extern void vec4f_normalize(vec4f i1, vec4f out);
extern void vec3f_cross(vec3f v0, vec3f v1, vec3f result);
extern void matrix4x4f_copy(matrix4x4f d, const matrix4x4f s);
extern void matrix4x4f_translate(float x, float y, float z, float matrix[16]);
extern void matrix4x4f_scale(float x, float y, float z, float matrix[16]);
extern void matrix4x4f_rotate(float a, float x, float y, float z, float matrix[16]);
extern void matrix4x4f_mult_matrix4x4f(const matrix4x4f m1, const matrix4x4f m2, matrix4x4f r);
extern void matrix4x4f_mult_vec4f_(const matrix4x4f m, const vec4f in, vec4f out);
extern void matrix4x4f_mult_vec4f(const matrix4x4f m, const vec4f in, vec4f out);
extern void vec3f_mult_matrix4x4f(const vec3f in, const matrix4x4f m, vec3f out);
extern void vec4f_mult_matrix4x4f(const vec4f in, const matrix4x4f m, vec4f out);
extern float *matrix4x4f_stack_top(matrix4x4f_stack *m);
extern void matrix4x4f_stack_init(matrix4x4f_stack *m);
extern int matrix4x4f_stack_push(matrix4x4f_stack *stack);
extern int matrix4x4f_stack_pop(matrix4x4f_stack *stack);
extern void matrix4x4f_stack_load(matrix4x4f_stack *stack, const matrix4x4f m);
extern void matrix4x4f_stack_mult(matrix4x4f_stack *stack, const matrix4x4f m);
extern void viewport_copy(viewport_t d, const viewport_t s);
extern int viewport_stack_push(viewport_stack_t *stack);
extern int viewport_stack_pop(viewport_stack_t *stack);
extern float *viewport_stack_top(viewport_stack_t *stack);
extern void vec3ub_set(vec3ub v, uint8_t x, uint8_t y, uint8_t z);
extern float vec3f_length(vec3f i1);
extern float vec4f_length(vec4f i1);


#endif /* __VECTOR_H__ */

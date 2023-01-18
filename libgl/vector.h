#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "basic_types.h"

extern const matrix4x4f identity_4x4f;

//----------------------------------------------------------------------------
// Vector math; vector operations, matrix operations, matrix stack operations

inline void vec3ub_set(vec3ub v, uint8_t x, uint8_t y, uint8_t z)
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

inline void vec3f_set(vec3f v, float x, float y, float z)
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

inline void vec4f_set(vec4f v, float x, float y, float z, float w)
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = w;
}

inline void vec3f_copy(vec3f d, const vec3f s)
{
    memcpy(d, s, sizeof(vec3f));
}

inline void vec4f_copy(vec4f d, const vec4f s)
{
    memcpy(d, s, sizeof(vec4f));
}

inline void vec4f_subtract(vec4f i1, vec4f i2, vec4f out)
{
    for(int i = 0; i < 4; i++)
        out[i] = i1[i] - i2[i];
}

inline void vec3f_scale(vec3f i1, float v, vec3f out)
{
    for(int i = 0; i < 3; i++)
        out[i] = i1[i] * v;
}

inline void vec4f_scale(vec4f i1, float v, vec4f out)
{
    for(int i = 0; i < 4; i++)
        out[i] = i1[i] * v;
}

inline void vec3f_mult(vec3f i1, vec3f i2, vec3f out)
{
    for(int i = 0; i < 3; i++)
        out[i] = i1[i] * i2[i];
}

inline void vec4f_mult(vec4f i1, vec4f i2, vec4f out)
{
    for(int i = 0; i < 4; i++)
        out[i] = i1[i] * i2[i];
}

inline void vec3f_blend(vec3f i1, vec3f i2, float t, vec3f out)
{
    for(int i = 0; i < 3; i++)
        out[i] = i1[i] * (1 - t) + i2[i] * t;
}

inline void vec4f_blend(vec4f i1, vec4f i2, float t, vec4f out)
{
    for(int i = 0; i < 4; i++)
        out[i] = i1[i] * (1 - t) + i2[i] * t;
}

inline void vec4f_add(vec4f i1, vec4f i2, vec4f out)
{
    for(int i = 0; i < 4; i++)
        out[i] = i1[i] + i2[i];
}

inline void vec3f_add(vec3f i1, vec3f i2, vec3f out)
{
    for(int i = 0; i < 3; i++)
        out[i] = i1[i] + i2[i];
}

inline float vec3f_dot(vec3f i1, vec3f i2)
{
    float dot = 0;
    for(int i = 0; i < 3; i++)
        dot += i1[i] * i2[i];
    return dot;
}

inline float vec4f_dot(vec4f i1, vec4f i2)
{
    float dot = 0;
    for(int i = 0; i < 4; i++)
        dot += i1[i] * i2[i];
    return dot;
}

inline float vec3f_length(vec3f i1)
{
    return sqrtf(i1[0] * i1[0] + i1[1] * i1[1] + i1[2] * i1[2]);
}

inline void vec3f_normalize(vec3f i1, vec3f out)
{
    float d = 1.0f / vec3f_length(i1);
    for(int i = 0; i < 3; i++)
        out[i] = i1[i] * d;
}

inline float vec4f_length(vec4f i1)
{
    return sqrtf(i1[0] * i1[0] + i1[1] * i1[1] + i1[2] * i1[2] + i1[3] * i1[3]);
}

inline void vec4f_normalize(vec4f i1, vec4f out)
{
    float d = 1.0f / vec4f_length(i1);
    for(int i = 0; i < 4; i++)
        out[i] = i1[i] * d;
}

inline void vec3f_cross(vec3f v0, vec3f v1, vec3f result)
{
    result[0] = v0[1] * v1[2] - v0[2] * v1[1];
    result[1] = v0[2] * v1[0] - v0[0] * v1[2];
    result[2] = v0[0] * v1[1] - v0[1] * v1[0];
}

inline void matrix4x4f_copy(matrix4x4f d, const matrix4x4f s)
{
    memcpy(d, s, sizeof(matrix4x4f));
}

inline void matrix4x4f_translate(float x, float y, float z, float matrix[16])
{
    matrix4x4f_copy(matrix, identity_4x4f);
    matrix[12] = x;
    matrix[13] = y;
    matrix[14] = z;
}

inline void matrix4x4f_scale(float x, float y, float z, float matrix[16])
{
    matrix4x4f_copy(matrix, identity_4x4f);
    matrix[0] = x;
    matrix[5] = y;
    matrix[10] = z;
}

inline void matrix4x4f_rotate(float a, float x, float y, float z, float matrix[16])
{
    float c, s, t;

    c = (float)cos(a);
    s = (float)sin(a);
    t = 1.0f - c;

    matrix[0] = t * x * x + c;
    matrix[1] = t * x * y + s * z;
    matrix[2] = t * x * z - s * y;
    matrix[3] = 0;

    matrix[4] = t * x * y - s * z;
    matrix[5] = t * y * y + c;
    matrix[6] = t * y * z + s * x;
    matrix[7] = 0;

    matrix[8] = t * x * z + s * y;
    matrix[9] = t * y * z - s * x;
    matrix[10] = t * z * z + c;
    matrix[11] = 0;

    matrix[12] = 0;
    matrix[13] = 0;
    matrix[14] = 0;
    matrix[15] = 1;
}

void matrix4x4f_print(char *label, matrix4x4f m);

inline void matrix4x4f_mult_matrix4x4f(const matrix4x4f m1, const matrix4x4f m2, matrix4x4f r)
{
    matrix4x4f t;
    int i, j;

    for(j = 0; j < 4; j++)
        for(i = 0; i < 4; i++)
           t[i * 4 + j] = m1[i * 4 + 0] * m2[0 * 4 + j] +
               m1[i * 4 + 1] * m2[1 * 4 + j] +
               m1[i * 4 + 2] * m2[2 * 4 + j] +
               m1[i * 4 + 3] * m2[3 * 4 + j];

    matrix4x4f_copy(r, t);
}

int matrix4x4f_invert(const matrix4x4f mat, matrix4x4f inv);

inline void matrix4x4f_mult_vec4f_(const matrix4x4f m, const vec4f in, vec4f out)
{
    int i;
    vec4f t;

    for(i = 0; i < 4; i++)
        out[i] =
            m[0 + i] * in[0] +
            m[4 + i] * in[1] +
            m[8 + i] * in[2] +
            m[12 + i] * in[3];
}

inline void matrix4x4f_mult_vec4f(const matrix4x4f m, const vec4f in, vec4f out)
{
    int i;
    vec4f t;

    for(i = 0; i < 4; i++)
        t[i] =
            m[0 + i] * in[0] +
            m[4 + i] * in[1] +
            m[8 + i] * in[2] +
            m[12 + i] * in[3];
    vec4f_copy(out, t);
}

inline void vec3f_mult_matrix4x4f(const vec3f in, const matrix4x4f m, vec3f out)
{
    int i;
    vec3f t;

    for(i = 0; i < 3; i++)
        t[i] =
            in[0] * m[0 + i * 4] +
            in[1] * m[1 + i * 4] +
            in[2] * m[2 + i * 4];
    vec3f_copy(out, t);
}

inline void vec4f_mult_matrix4x4f(const vec4f in, const matrix4x4f m, vec4f out)
{
    int i;
    vec4f t;

    for(i = 0; i < 4; i++)
        t[i] =
            in[0] * m[0 + i * 4] +
            in[1] * m[1 + i * 4] +
            in[2] * m[2 + i * 4] +
            in[3] * m[3 + i * 4];
    vec4f_copy(out, t);
}

void vec4f_print(char *label, const vec4f v);

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

inline float *matrix4x4f_stack_top(matrix4x4f_stack *m)
{
    return m->s[m->top];
}

inline void matrix4x4f_stack_init(matrix4x4f_stack *m)
{
    m->top = 0;
    m->inverse_needs_calculation = 1;
}

float *matrix4x4f_stack_get_inverse(matrix4x4f_stack *stack);

inline int matrix4x4f_stack_push(matrix4x4f_stack *stack)
{
    if(stack->top == STACK_MAX - 1) {
        return 0;
    } else {
        matrix4x4f_copy(stack->s[stack->top + 1], stack->s[stack->top]);
        stack->inverse_needs_calculation = 1;
        stack->top++;
        return 1;
    }
}

inline int matrix4x4f_stack_pop(matrix4x4f_stack *stack)
{
    if(stack->top == 0) {
        return 0;
    } else {
        stack->top--;
        stack->inverse_needs_calculation = 1;
        return 1;
    }
}

inline void matrix4x4f_stack_load(matrix4x4f_stack *stack, const matrix4x4f m)
{
    matrix4x4f_copy(stack->s[stack->top], m);
    stack->inverse_needs_calculation = 1;
#if 0
    printf("matrix stack loaded\n");
    for(int i = 0 ; i < 4; i++)
        printf("    %f %f %f %f\n", 
            stack->s[stack->top][i * 4 + 0],
            stack->s[stack->top][i * 4 + 1],
            stack->s[stack->top][i * 4 + 2],
            stack->s[stack->top][i * 4 + 3]);
#endif
}

inline void matrix4x4f_stack_mult(matrix4x4f_stack *stack, const matrix4x4f m)
{
    matrix4x4f_mult_matrix4x4f(m, stack->s[stack->top], stack->s[stack->top]);
    stack->inverse_needs_calculation = 1;
#if 0
    printf("matrix stack multiplied\n");
    for(int i = 0 ; i < 4; i++)
        printf("    %f %f %f %f\n", 
            stack->s[stack->top][i * 4 + 0],
            stack->s[stack->top][i * 4 + 1],
            stack->s[stack->top][i * 4 + 2],
            stack->s[stack->top][i * 4 + 3]);
#endif
}

inline void viewport_copy(viewport_t d, const viewport_t s)
{
    memcpy(d, s, sizeof(viewport_t));
}

inline int viewport_stack_push(viewport_stack_t *stack)
{
    if (stack->top == STACK_MAX - 1) {
        return 0;
    } else {
        viewport_copy(stack->s[stack->top + 1], stack->s[stack->top]);
        stack->top++;
        return 1;
    }
}

inline int viewport_stack_pop(viewport_stack_t *stack)
{
    if (stack->top == 0) {
        return 0;
    } else {
        stack->top--;
        return 1;
    }
}

inline float *viewport_stack_top(viewport_stack_t *stack)
{
    return stack->s[stack->top];
}

#endif /* __VECTOR_H__ */

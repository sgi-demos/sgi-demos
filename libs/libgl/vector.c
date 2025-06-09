#include "vector.h"

const matrix4x4f identity_4x4f = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1,
};

void matrix4x4f_print(char *label, matrix4x4f m)
{
    printf("%s:\n", label);
    for(int j = 0; j < 4; j++) {
        for(int i = 0; i < 4; i++) {
            printf("%6.2f ", m[j*4 + i]);
        }
        printf("\n");
    }
    printf("\n");
}

float matrix4x4f_determinant(const matrix4x4f mat)
{
    return (mat[0] * mat[5] - mat[1] * mat[4]) *
        (mat[10] * mat[15] - mat[11] * mat[14]) + 
        (mat[2] * mat[4] - mat[0] * mat[6]) *
	(mat[9] * mat[15] - mat[11] * mat[13]) + 
        (mat[0] * mat[7] - mat[3] * mat[4]) *
	(mat[9] * mat[14] - mat[10] * mat[13]) + 
        (mat[1] * mat[6] - mat[2] * mat[5]) *
	(mat[8] * mat[15] - mat[11] * mat[12]) + 
        (mat[3] * mat[5] - mat[1] * mat[7]) *
	(mat[8] * mat[14] - mat[10] * mat[12]) + 
        (mat[2] * mat[7] - mat[3] * mat[6]) *
	(mat[8] * mat[13] - mat[9] * mat[12]);
}

#define EPSILON .0000001

int matrix4x4f_invert(const matrix4x4f mat, matrix4x4f inv)
{
    int		i, rswap;
    float	det, div, swap;
    matrix4x4f	hold;

    matrix4x4f_copy(hold, mat);
    matrix4x4f_copy(inv, identity_4x4f);
    det = matrix4x4f_determinant(hold);
    if(fabs(det) < EPSILON) /* singular? */
	return -1;

    rswap = 0;
    /* this loop isn't entered unless [0 + 0] > EPSILON and det > EPSILON,
	 so rswap wouldn't be 0, but I initialize so as not to get warned */
    if(fabs(hold[0]) < EPSILON)
    {
        if(fabs(hold[1]) > EPSILON)
            rswap = 1;
        else if(fabs(hold[2]) > EPSILON)
	    rswap = 2;
        else if(fabs(hold[3]) > EPSILON)
	    rswap = 3;

        for(i = 0; i < 4; i++)
	{
            swap = hold[i * 4 + 0];
            hold[i * 4 + 0] = hold[i * 4 + rswap];
            hold[i * 4 + rswap] = swap;

            swap = inv[i * 4 + 0];
            inv[i * 4 + 0] = inv[i * 4 + rswap];
            inv[i * 4 + rswap] = swap;
        }
    }
        
    div = hold[0];
    for(i = 0; i < 4; i++)
    {
        hold[i * 4 + 0] /= div;
        inv[i * 4 + 0] /= div;
    }

    div = hold[1];
    for(i = 0; i < 4; i++)
    {
        hold[i * 4 + 1] -= div * hold[i * 4 + 0];
        inv[i * 4 + 1] -= div * inv[i * 4 + 0];
    }
    div = hold[2];
    for(i = 0; i < 4; i++)
    {
        hold[i * 4 + 2] -= div * hold[i * 4 + 0];
        inv[i * 4 + 2] -= div * inv[i * 4 + 0];
    }
    div = hold[3];
    for(i = 0; i < 4; i++)
    {
        hold[i * 4 + 3] -= div * hold[i * 4 + 0];
        inv[i * 4 + 3] -= div * inv[i * 4 + 0];
    }

    if(fabs(hold[5]) < EPSILON){
        if(fabs(hold[6]) > EPSILON)
	    rswap = 2;
        else if(fabs(hold[7]) > EPSILON)
	    rswap = 3;

        for(i = 0; i < 4; i++)
	{
            swap = hold[i * 4 + 1];
            hold[i * 4 + 1] = hold[i * 4 + rswap];
            hold[i * 4 + rswap] = swap;

            swap = inv[i * 4 + 1];
            inv[i * 4 + 1] = inv[i * 4 + rswap];
            inv[i * 4 + rswap] = swap;
        }
    }

    div = hold[5];
    for(i = 0; i < 4; i++)
    {
        hold[i * 4 + 1] /= div;
        inv[i * 4 + 1] /= div;
    }

    div = hold[4];
    for(i = 0; i < 4; i++)
    {
        hold[i * 4 + 0] -= div * hold[i * 4 + 1];
        inv[i * 4 + 0] -= div * inv[i * 4 + 1];
    }
    div = hold[6];
    for(i = 0; i < 4; i++)
    {
        hold[i * 4 + 2] -= div * hold[i * 4 + 1];
        inv[i * 4 + 2] -= div * inv[i * 4 + 1];
    }
    div = hold[7];
    for(i = 0; i < 4; i++)
    {
        hold[i * 4 + 3] -= div * hold[i * 4 + 1];
        inv[i * 4 + 3] -= div * inv[i * 4 + 1];
    }

    if(fabs(hold[10]) < EPSILON){
        for(i = 0; i < 4; i++)
	{
            swap = hold[i * 4 + 2];
            hold[i * 4 + 2] = hold[i * 4 + 3];
            hold[i * 4 + 3] = swap;

            swap = inv[i * 4 + 2];
            inv[i * 4 + 2] = inv[i * 4 + 3];
            inv[i * 4 + 3] = swap;
        }
    }

    div = hold[10];
    for(i = 0; i < 4; i++)
    {
        hold[i * 4 + 2] /= div;
        inv[i * 4 + 2] /= div;
    }

    div = hold[8];
    for(i = 0; i < 4; i++)
    {
        hold[i * 4 + 0] -= div * hold[i * 4 + 2];
        inv[i * 4 + 0] -= div * inv[i * 4 + 2];
    }
    div = hold[9];
    for(i = 0; i < 4; i++)
    {
        hold[i * 4 + 1] -= div * hold[i * 4 + 2];
        inv[i * 4 + 1] -= div * inv[i * 4 + 2];
    }
    div = hold[11];
    for(i = 0; i < 4; i++)
    {
        hold[i * 4 + 3] -= div * hold[i * 4 + 2];
        inv[i * 4 + 3] -= div * inv[i * 4 + 2];
    }

    div = hold[15];
    for(i = 0; i < 4; i++)
    {
        hold[i * 4 + 3] /= div;
        inv[i * 4 + 3] /= div;
    }

    div = hold[12];
    for(i = 0; i < 4; i++)
    {
        hold[i * 4 + 0] -= div * hold[i * 4 + 3];
        inv[i * 4 + 0] -= div * inv[i * 4 + 3];
    }
    div = hold[13];
    for(i = 0; i < 4; i++)
    {
        hold[i * 4 + 1] -= div * hold[i * 4 + 3];
        inv[i * 4 + 1] -= div * inv[i * 4 + 3];
    }
    div = hold[14];
    for(i = 0; i < 4; i++)
    {
        hold[i * 4 + 2] -= div * hold[i * 4 + 3];
        inv[i * 4 + 2] -= div * inv[i * 4 + 3];
    }
    
    return 0;
}

void vec4f_print(char *label, const vec4f v)
{
    printf("%s: ", label);
    for (int i = 0; i < 4; i++) {
        printf("%6.2f ", v[i]);
    }
    printf("\n");
}

float *matrix4x4f_stack_get_inverse(matrix4x4f_stack *stack)
{
    if(stack->inverse_needs_calculation) {
        matrix4x4f_invert(stack->s[stack->top], stack->inverse);
        stack->inverse_needs_calculation = 0;
    }
    return stack->inverse;
}


//----------------------------------------------------------------------------
// Vector math; vector operations, matrix operations, matrix stack operations

void vec3ub_set(vec3ub v, uint8_t x, uint8_t y, uint8_t z)
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

void vec3f_set(vec3f v, float x, float y, float z)
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

void vec4f_set(vec4f v, float x, float y, float z, float w)
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = w;
}

void vec3f_copy(vec3f d, const vec3f s)
{
    memcpy(d, s, sizeof(vec3f));
}

void vec4f_copy(vec4f d, const vec4f s)
{
    memcpy(d, s, sizeof(vec4f));
}

void vec4f_subtract(vec4f i1, vec4f i2, vec4f out)
{
    for(int i = 0; i < 4; i++)
        out[i] = i1[i] - i2[i];
}

void vec3f_scale(vec3f i1, float v, vec3f out)
{
    for(int i = 0; i < 3; i++)
        out[i] = i1[i] * v;
}

void vec4f_scale(vec4f i1, float v, vec4f out)
{
    for(int i = 0; i < 4; i++)
        out[i] = i1[i] * v;
}

void vec3f_mult(vec3f i1, vec3f i2, vec3f out)
{
    for(int i = 0; i < 3; i++)
        out[i] = i1[i] * i2[i];
}

void vec4f_mult(vec4f i1, vec4f i2, vec4f out)
{
    for(int i = 0; i < 4; i++)
        out[i] = i1[i] * i2[i];
}

void vec3f_blend(vec3f i1, vec3f i2, float t, vec3f out)
{
    for(int i = 0; i < 3; i++)
        out[i] = i1[i] * (1 - t) + i2[i] * t;
}

void vec4f_blend(vec4f i1, vec4f i2, float t, vec4f out)
{
    for(int i = 0; i < 4; i++)
        out[i] = i1[i] * (1 - t) + i2[i] * t;
}

void vec4f_add(vec4f i1, vec4f i2, vec4f out)
{
    for(int i = 0; i < 4; i++)
        out[i] = i1[i] + i2[i];
}

void vec3f_add(vec3f i1, vec3f i2, vec3f out)
{
    for(int i = 0; i < 3; i++)
        out[i] = i1[i] + i2[i];
}

float vec3f_dot(vec3f i1, vec3f i2)
{
    float dot = 0;
    for(int i = 0; i < 3; i++)
        dot += i1[i] * i2[i];
    return dot;
}

float vec4f_dot(vec4f i1, vec4f i2)
{
    float dot = 0;
    for(int i = 0; i < 4; i++)
        dot += i1[i] * i2[i];
    return dot;
}

float vec3f_length(vec3f i1)
{
    return sqrtf(i1[0] * i1[0] + i1[1] * i1[1] + i1[2] * i1[2]);
}

void vec3f_normalize(vec3f i1, vec3f out)
{
    float d = 1.0f / vec3f_length(i1);
    for(int i = 0; i < 3; i++)
        out[i] = i1[i] * d;
}

float vec4f_length(vec4f i1)
{
    return sqrtf(i1[0] * i1[0] + i1[1] * i1[1] + i1[2] * i1[2] + i1[3] * i1[3]);
}

void vec4f_normalize(vec4f i1, vec4f out)
{
    float d = 1.0f / vec4f_length(i1);
    for(int i = 0; i < 4; i++)
        out[i] = i1[i] * d;
}

void vec3f_cross(vec3f v0, vec3f v1, vec3f result)
{
    result[0] = v0[1] * v1[2] - v0[2] * v1[1];
    result[1] = v0[2] * v1[0] - v0[0] * v1[2];
    result[2] = v0[0] * v1[1] - v0[1] * v1[0];
}

void matrix4x4f_copy(matrix4x4f d, const matrix4x4f s)
{
    memcpy(d, s, sizeof(matrix4x4f));
}

void matrix4x4f_translate(float x, float y, float z, float matrix[16])
{
    matrix4x4f_copy(matrix, identity_4x4f);
    matrix[12] = x;
    matrix[13] = y;
    matrix[14] = z;
}

void matrix4x4f_scale(float x, float y, float z, float matrix[16])
{
    matrix4x4f_copy(matrix, identity_4x4f);
    matrix[0] = x;
    matrix[5] = y;
    matrix[10] = z;
}

void matrix4x4f_rotate(float a, float x, float y, float z, float matrix[16])
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

void matrix4x4f_mult_matrix4x4f(const matrix4x4f m1, const matrix4x4f m2, matrix4x4f r)
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

void matrix4x4f_mult_vec4f_(const matrix4x4f m, const vec4f in, vec4f out)
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

void matrix4x4f_mult_vec4f(const matrix4x4f m, const vec4f in, vec4f out)
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

void vec3f_mult_matrix4x4f(const vec3f in, const matrix4x4f m, vec3f out)
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

void vec4f_mult_matrix4x4f(const vec4f in, const matrix4x4f m, vec4f out)
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



float *matrix4x4f_stack_top(matrix4x4f_stack *m)
{
    return m->s[m->top];
}

void matrix4x4f_stack_init(matrix4x4f_stack *m)
{
    m->top = 0;
    m->inverse_needs_calculation = 1;
}

float *matrix4x4f_stack_get_inverse(matrix4x4f_stack *stack);

int matrix4x4f_stack_push(matrix4x4f_stack *stack)
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

int matrix4x4f_stack_pop(matrix4x4f_stack *stack)
{
    if(stack->top == 0) {
        return 0;
    } else {
        stack->top--;
        stack->inverse_needs_calculation = 1;
        return 1;
    }
}

void matrix4x4f_stack_load(matrix4x4f_stack *stack, const matrix4x4f m)
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

void matrix4x4f_stack_mult(matrix4x4f_stack *stack, const matrix4x4f m)
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

void viewport_copy(viewport_t d, const viewport_t s)
{
    memcpy(d, s, sizeof(viewport_t));
}

int viewport_stack_push(viewport_stack_t *stack)
{
    if (stack->top == STACK_MAX - 1) {
        return 0;
    } else {
        viewport_copy(stack->s[stack->top + 1], stack->s[stack->top]);
        stack->top++;
        return 1;
    }
}

int viewport_stack_pop(viewport_stack_t *stack)
{
    if (stack->top == 0) {
        return 0;
    } else {
        stack->top--;
        return 1;
    }
}

float *viewport_stack_top(viewport_stack_t *stack)
{
    return stack->s[stack->top];
}

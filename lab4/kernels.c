/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following student struct 
 */
student_t student = {
  "Rob Johansen",           /* Student full name */
  "johansen",               /* Student CADE login */
  "rob.johansen@gmail.com", /* Student email address */
};

/* This lab was absolutely awful. Easily the worst lab of the semester, and beneath the otheriwse high quality of this class. */

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/* 
 * naive_rotate - The naive baseline version of rotate 
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) 
{
  int i, j;
  
  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      dst[RIDX(j, dim-1-i, dim)] = src[RIDX(i, j, dim)];
}

/*
 * rotate_ptr - Rotate using pointers for array access
 */

// WYLO .... Figure out how to use pointers to access the src and dst variables.
//           Remember what Saurav said:
//               1. You'll be incrementing by 4 because each pixel is 4 integers.
//               2. You still have to use i, j, and dim in your calculations

char rotate_ptr_descr[] = "rotate_ptr: Use pointers for array access";
void rotate_ptr(int dim, pixel *src, pixel *dst)
{
    int i, j;
    
    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
            *(dst + (j * dim + (dim-1-i))) = *(src + (i * dim + j));
}

/*
 * rotate_u2
 */
char rotate_2_descr[] = "rotate_2: Unroll inner by 2";
void rotate_2(int dim, pixel *src, pixel *dst)
{
    int i, j;
    int limit = dim - 1;
    
    for (i = 0; i < dim; i++) {
        for (j = 0; j < limit; j+=2) {
            dst[RIDX(j,   dim-1-i, dim)] = src[RIDX(i, j,   dim)];
            dst[RIDX(j+1, dim-1-i, dim)] = src[RIDX(i, j+1, dim)];
        }
    }
}

/*
 * rotate_2x2
 */
char rotate_2x2_descr[] = "rotate_2x2: Unroll both by 2";
void rotate_2x2(int dim, pixel *src, pixel *dst)
{
    int i, j;
    int outer_limit = dim - 1;
    int inner_limit = dim - 1;
    
    for (i = 0; i < outer_limit; i += 2) {
        for (j = 0; j < inner_limit; j += 2) {
            dst[RIDX(j,   dim-1-i,     dim)] = src[RIDX(i,   j,   dim)];
            dst[RIDX(j+1, dim-1-i,     dim)] = src[RIDX(i,   j+1, dim)];
            dst[RIDX(j,   dim-1-(i+1), dim)] = src[RIDX(i+1, j,   dim)];
            dst[RIDX(j+1, dim-1-(i+1), dim)] = src[RIDX(i+1, j+1, dim)];
        }
    }
}

/*
 * rotate_2x2_ptr
 */
char rotate_2x2_ptr_descr[] = "rotate_2x2_ptr: Unroll both loops by 2 with pointers";
void rotate_2x2_ptr(int dim, pixel *src, pixel *dst)
{
    int i, j = 0;
    int outer_limit = dim - 1;
    int inner_limit = dim - 1;
    
    for (i = 0; i < outer_limit; i += 2) {
        for (j = 0; j < inner_limit; j += 2) {
            *(dst + (j     * dim + (dim-1-i)))     = *(src + (i * dim + j));
            *(dst + ((j+1) * dim + (dim-1-i)))     = *(src + (i * dim + j + 1));
            *(dst + (j     * dim + (dim-1-(i+1)))) = *(src + ((i+1) * dim + j));
            *(dst + ((j+1) * dim + (dim-1-(i+1)))) = *(src + ((i+1) * dim + j+1));
        }
    }
    
    for (; i < dim; i++)
        for (; j < dim; j++)
            *(dst + (j * dim + (dim-1-i))) = *(src++);
}

/*
 * rotate_4
 */
char rotate_4_descr[] = "rotate_4: Unroll inner by 4";
void rotate_4(int dim, pixel *src, pixel *dst)
{
    int i, j;
    int limit = dim - 3;
    
    for (i = 0; i < dim; i++) {
        for (j = 0; j < limit; j+=4) {
            dst[RIDX(j,   dim-1-i, dim)] = src[RIDX(i, j,   dim)];
            dst[RIDX(j+1, dim-1-i, dim)] = src[RIDX(i, j+1, dim)];
            dst[RIDX(j+2, dim-1-i, dim)] = src[RIDX(i, j+2, dim)];
            dst[RIDX(j+3, dim-1-i, dim)] = src[RIDX(i, j+3, dim)];
        }
    }
}

/*
 * rotate_4x4
 */
char rotate_4x4_descr[] = "rotate_4x4: Unroll both by 4";
void rotate_4x4(int dim, pixel *src, pixel *dst)
{
    int i, j;
    int outer_limit = dim - 3;
    int inner_limit = dim - 3;
    int i_dim_0, i_dim_1, i_dim_2, i_dim_3;
    int i_1, i_2, i_3;
    int j_1, j_2, j_3;
    
    for (i = 0; i < outer_limit; i += 4) {
        i_dim_0 = dim-1-i;
        i_dim_1 = dim-1-(i+1);
        i_dim_2 = dim-1-(i+2);
        i_dim_3 = dim-1-(i+3);
        i_1 = i+1;
        i_2 = i+2;
        i_3 = i+3;
        for (j = 0; j < inner_limit; j += 4) {
            j_1 = j+1;
            j_2 = j+2;
            j_3 = j+3;
            dst[RIDX(j,   i_dim_0, dim)] = src[RIDX(i, j,   dim)];
            dst[RIDX(j_1, i_dim_0, dim)] = src[RIDX(i, j_1, dim)];
            dst[RIDX(j_2, i_dim_0, dim)] = src[RIDX(i, j_2, dim)];
            dst[RIDX(j_3, i_dim_0, dim)] = src[RIDX(i, j_3, dim)];

            dst[RIDX(j,   i_dim_1, dim)] = src[RIDX(i_1, j,   dim)];
            dst[RIDX(j_1, i_dim_1, dim)] = src[RIDX(i_1, j_1, dim)];
            dst[RIDX(j_2, i_dim_1, dim)] = src[RIDX(i_1, j_2, dim)];
            dst[RIDX(j_3, i_dim_1, dim)] = src[RIDX(i_1, j_3, dim)];

            dst[RIDX(j,   i_dim_2, dim)] = src[RIDX(i_2, j,   dim)];
            dst[RIDX(j_1, i_dim_2, dim)] = src[RIDX(i_2, j_1, dim)];
            dst[RIDX(j_2, i_dim_2, dim)] = src[RIDX(i_2, j_2, dim)];
            dst[RIDX(j_3, i_dim_2, dim)] = src[RIDX(i_2, j_3, dim)];

            dst[RIDX(j,   i_dim_3, dim)] = src[RIDX(i_3, j,   dim)];
            dst[RIDX(j_1, i_dim_3, dim)] = src[RIDX(i_3, j_1, dim)];
            dst[RIDX(j_2, i_dim_3, dim)] = src[RIDX(i_3, j_2, dim)];
            dst[RIDX(j_3, i_dim_3, dim)] = src[RIDX(i_3, j_3, dim)];
        }
    }
}

/*
 * rotate_8x8
 */
char rotate_8x8_descr[] = "rotate_8x8: Unroll both loops by 8";
void rotate_8x8(int dim, pixel *src, pixel *dst)
{
    int i, j;
    int outer_limit = dim - 7;
    int inner_limit = dim - 7;
    
    for (i = 0; i < outer_limit; i += 8) {
        for (j = 0; j < inner_limit; j += 8) {
            dst[RIDX(j,   dim-1-i, dim)] = src[RIDX(i, j,   dim)];
            dst[RIDX(j+1, dim-1-i, dim)] = src[RIDX(i, j+1, dim)];
            dst[RIDX(j+2, dim-1-i, dim)] = src[RIDX(i, j+2, dim)];
            dst[RIDX(j+3, dim-1-i, dim)] = src[RIDX(i, j+3, dim)];
            dst[RIDX(j+4, dim-1-i, dim)] = src[RIDX(i, j+4, dim)];
            dst[RIDX(j+5, dim-1-i, dim)] = src[RIDX(i, j+5, dim)];
            dst[RIDX(j+6, dim-1-i, dim)] = src[RIDX(i, j+6, dim)];
            dst[RIDX(j+7, dim-1-i, dim)] = src[RIDX(i, j+7, dim)];

            dst[RIDX(j,   dim-1-(i+1), dim)] = src[RIDX(i+1, j,   dim)];
            dst[RIDX(j+1, dim-1-(i+1), dim)] = src[RIDX(i+1, j+1, dim)];
            dst[RIDX(j+2, dim-1-(i+1), dim)] = src[RIDX(i+1, j+2, dim)];
            dst[RIDX(j+3, dim-1-(i+1), dim)] = src[RIDX(i+1, j+3, dim)];
            dst[RIDX(j+4, dim-1-(i+1), dim)] = src[RIDX(i+1, j+4, dim)];
            dst[RIDX(j+5, dim-1-(i+1), dim)] = src[RIDX(i+1, j+5, dim)];
            dst[RIDX(j+6, dim-1-(i+1), dim)] = src[RIDX(i+1, j+6, dim)];
            dst[RIDX(j+7, dim-1-(i+1), dim)] = src[RIDX(i+1, j+7, dim)];

            dst[RIDX(j,   dim-1-(i+2), dim)] = src[RIDX(i+2, j,   dim)];
            dst[RIDX(j+1, dim-1-(i+2), dim)] = src[RIDX(i+2, j+1, dim)];
            dst[RIDX(j+2, dim-1-(i+2), dim)] = src[RIDX(i+2, j+2, dim)];
            dst[RIDX(j+3, dim-1-(i+2), dim)] = src[RIDX(i+2, j+3, dim)];
            dst[RIDX(j+4, dim-1-(i+2), dim)] = src[RIDX(i+2, j+4, dim)];
            dst[RIDX(j+5, dim-1-(i+2), dim)] = src[RIDX(i+2, j+5, dim)];
            dst[RIDX(j+6, dim-1-(i+2), dim)] = src[RIDX(i+2, j+6, dim)];
            dst[RIDX(j+7, dim-1-(i+2), dim)] = src[RIDX(i+2, j+7, dim)];

            dst[RIDX(j,   dim-1-(i+3), dim)] = src[RIDX(i+3, j,   dim)];
            dst[RIDX(j+1, dim-1-(i+3), dim)] = src[RIDX(i+3, j+1, dim)];
            dst[RIDX(j+2, dim-1-(i+3), dim)] = src[RIDX(i+3, j+2, dim)];
            dst[RIDX(j+3, dim-1-(i+3), dim)] = src[RIDX(i+3, j+3, dim)];
            dst[RIDX(j+4, dim-1-(i+3), dim)] = src[RIDX(i+3, j+4, dim)];
            dst[RIDX(j+5, dim-1-(i+3), dim)] = src[RIDX(i+3, j+5, dim)];
            dst[RIDX(j+6, dim-1-(i+3), dim)] = src[RIDX(i+3, j+6, dim)];
            dst[RIDX(j+7, dim-1-(i+3), dim)] = src[RIDX(i+3, j+7, dim)];

            dst[RIDX(j,   dim-1-(i+4), dim)] = src[RIDX(i+4, j,   dim)];
            dst[RIDX(j+1, dim-1-(i+4), dim)] = src[RIDX(i+4, j+1, dim)];
            dst[RIDX(j+2, dim-1-(i+4), dim)] = src[RIDX(i+4, j+2, dim)];
            dst[RIDX(j+3, dim-1-(i+4), dim)] = src[RIDX(i+4, j+3, dim)];
            dst[RIDX(j+4, dim-1-(i+4), dim)] = src[RIDX(i+4, j+4, dim)];
            dst[RIDX(j+5, dim-1-(i+4), dim)] = src[RIDX(i+4, j+5, dim)];
            dst[RIDX(j+6, dim-1-(i+4), dim)] = src[RIDX(i+4, j+6, dim)];
            dst[RIDX(j+7, dim-1-(i+4), dim)] = src[RIDX(i+4, j+7, dim)];

            dst[RIDX(j,   dim-1-(i+5), dim)] = src[RIDX(i+5, j,   dim)];
            dst[RIDX(j+1, dim-1-(i+5), dim)] = src[RIDX(i+5, j+1, dim)];
            dst[RIDX(j+2, dim-1-(i+5), dim)] = src[RIDX(i+5, j+2, dim)];
            dst[RIDX(j+3, dim-1-(i+5), dim)] = src[RIDX(i+5, j+3, dim)];
            dst[RIDX(j+4, dim-1-(i+5), dim)] = src[RIDX(i+5, j+4, dim)];
            dst[RIDX(j+5, dim-1-(i+5), dim)] = src[RIDX(i+5, j+5, dim)];
            dst[RIDX(j+6, dim-1-(i+5), dim)] = src[RIDX(i+5, j+6, dim)];
            dst[RIDX(j+7, dim-1-(i+5), dim)] = src[RIDX(i+5, j+7, dim)];

            dst[RIDX(j,   dim-1-(i+6), dim)] = src[RIDX(i+6, j,   dim)];
            dst[RIDX(j+1, dim-1-(i+6), dim)] = src[RIDX(i+6, j+1, dim)];
            dst[RIDX(j+2, dim-1-(i+6), dim)] = src[RIDX(i+6, j+2, dim)];
            dst[RIDX(j+3, dim-1-(i+6), dim)] = src[RIDX(i+6, j+3, dim)];
            dst[RIDX(j+4, dim-1-(i+6), dim)] = src[RIDX(i+6, j+4, dim)];
            dst[RIDX(j+5, dim-1-(i+6), dim)] = src[RIDX(i+6, j+5, dim)];
            dst[RIDX(j+6, dim-1-(i+6), dim)] = src[RIDX(i+6, j+6, dim)];
            dst[RIDX(j+7, dim-1-(i+6), dim)] = src[RIDX(i+6, j+7, dim)];

            dst[RIDX(j,   dim-1-(i+7), dim)] = src[RIDX(i+7, j,   dim)];
            dst[RIDX(j+1, dim-1-(i+7), dim)] = src[RIDX(i+7, j+1, dim)];
            dst[RIDX(j+2, dim-1-(i+7), dim)] = src[RIDX(i+7, j+2, dim)];
            dst[RIDX(j+3, dim-1-(i+7), dim)] = src[RIDX(i+7, j+3, dim)];
            dst[RIDX(j+4, dim-1-(i+7), dim)] = src[RIDX(i+7, j+4, dim)];
            dst[RIDX(j+5, dim-1-(i+7), dim)] = src[RIDX(i+7, j+5, dim)];
            dst[RIDX(j+6, dim-1-(i+7), dim)] = src[RIDX(i+7, j+6, dim)];
            dst[RIDX(j+7, dim-1-(i+7), dim)] = src[RIDX(i+7, j+7, dim)];
        }
    }
}

/*
 * rotate_16x16
 */
char rotate_16x16_descr[] = "rotate_16x16: Unroll both loops by 16";
void rotate_16x16(int dim, pixel *src, pixel *dst)
{
    int i, j;
    int outer_limit = dim - 15;
    int inner_limit = dim - 15;

    for (i = 0; i < outer_limit; i += 16) {
        for (j = 0; j < inner_limit; j += 16) {
            dst[RIDX(j,    dim-1-i, dim)] = src[RIDX(i, j,    dim)];
            dst[RIDX(j+1,  dim-1-i, dim)] = src[RIDX(i, j+1,  dim)];
            dst[RIDX(j+2,  dim-1-i, dim)] = src[RIDX(i, j+2,  dim)];
            dst[RIDX(j+3,  dim-1-i, dim)] = src[RIDX(i, j+3,  dim)];
            dst[RIDX(j+4,  dim-1-i, dim)] = src[RIDX(i, j+4,  dim)];
            dst[RIDX(j+5,  dim-1-i, dim)] = src[RIDX(i, j+5,  dim)];
            dst[RIDX(j+6,  dim-1-i, dim)] = src[RIDX(i, j+6,  dim)];
            dst[RIDX(j+7,  dim-1-i, dim)] = src[RIDX(i, j+7,  dim)];
            dst[RIDX(j+8,  dim-1-i, dim)] = src[RIDX(i, j+8,  dim)];
            dst[RIDX(j+9,  dim-1-i, dim)] = src[RIDX(i, j+9,  dim)];
            dst[RIDX(j+10, dim-1-i, dim)] = src[RIDX(i, j+10, dim)];
            dst[RIDX(j+11, dim-1-i, dim)] = src[RIDX(i, j+11, dim)];
            dst[RIDX(j+12, dim-1-i, dim)] = src[RIDX(i, j+12, dim)];
            dst[RIDX(j+13, dim-1-i, dim)] = src[RIDX(i, j+13, dim)];
            dst[RIDX(j+14, dim-1-i, dim)] = src[RIDX(i, j+14, dim)];
            dst[RIDX(j+15, dim-1-i, dim)] = src[RIDX(i, j+15, dim)];

            dst[RIDX(j,    dim-1-(i+1), dim)] = src[RIDX(i+1, j,   dim)];
            dst[RIDX(j+1,  dim-1-(i+1), dim)] = src[RIDX(i+1, j+1, dim)];
            dst[RIDX(j+2,  dim-1-(i+1), dim)] = src[RIDX(i+1, j+2, dim)];
            dst[RIDX(j+3,  dim-1-(i+1), dim)] = src[RIDX(i+1, j+3, dim)];
            dst[RIDX(j+4,  dim-1-(i+1), dim)] = src[RIDX(i+1, j+4, dim)];
            dst[RIDX(j+5,  dim-1-(i+1), dim)] = src[RIDX(i+1, j+5, dim)];
            dst[RIDX(j+6,  dim-1-(i+1), dim)] = src[RIDX(i+1, j+6, dim)];
            dst[RIDX(j+7,  dim-1-(i+1), dim)] = src[RIDX(i+1, j+7, dim)];
            dst[RIDX(j+8,  dim-1-(i+1), dim)] = src[RIDX(i+1, j+8, dim)];
            dst[RIDX(j+9,  dim-1-(i+1), dim)] = src[RIDX(i+1, j+9, dim)];
            dst[RIDX(j+10, dim-1-(i+1), dim)] = src[RIDX(i+1, j+10, dim)];
            dst[RIDX(j+11, dim-1-(i+1), dim)] = src[RIDX(i+1, j+11, dim)];
            dst[RIDX(j+12, dim-1-(i+1), dim)] = src[RIDX(i+1, j+12, dim)];
            dst[RIDX(j+13, dim-1-(i+1), dim)] = src[RIDX(i+1, j+13, dim)];
            dst[RIDX(j+14, dim-1-(i+1), dim)] = src[RIDX(i+1, j+14, dim)];
            dst[RIDX(j+15, dim-1-(i+1), dim)] = src[RIDX(i+1, j+15, dim)];

            dst[RIDX(j,    dim-1-(i+2), dim)] = src[RIDX(i+2, j,   dim)];
			dst[RIDX(j+1,  dim-1-(i+2), dim)] = src[RIDX(i+2, j+1, dim)];
			dst[RIDX(j+2,  dim-1-(i+2), dim)] = src[RIDX(i+2, j+2, dim)];
			dst[RIDX(j+3,  dim-1-(i+2), dim)] = src[RIDX(i+2, j+3, dim)];
			dst[RIDX(j+4,  dim-1-(i+2), dim)] = src[RIDX(i+2, j+4, dim)];
			dst[RIDX(j+5,  dim-1-(i+2), dim)] = src[RIDX(i+2, j+5, dim)];
			dst[RIDX(j+6,  dim-1-(i+2), dim)] = src[RIDX(i+2, j+6, dim)];
			dst[RIDX(j+7,  dim-1-(i+2), dim)] = src[RIDX(i+2, j+7, dim)];
			dst[RIDX(j+8,  dim-1-(i+2), dim)] = src[RIDX(i+2, j+8, dim)];
			dst[RIDX(j+9,  dim-1-(i+2), dim)] = src[RIDX(i+2, j+9, dim)];
			dst[RIDX(j+10, dim-1-(i+2), dim)] = src[RIDX(i+2, j+10, dim)];
			dst[RIDX(j+11, dim-1-(i+2), dim)] = src[RIDX(i+2, j+11, dim)];
			dst[RIDX(j+12, dim-1-(i+2), dim)] = src[RIDX(i+2, j+12, dim)];
			dst[RIDX(j+13, dim-1-(i+2), dim)] = src[RIDX(i+2, j+13, dim)];
			dst[RIDX(j+14, dim-1-(i+2), dim)] = src[RIDX(i+2, j+14, dim)];
			dst[RIDX(j+15, dim-1-(i+2), dim)] = src[RIDX(i+2, j+15, dim)];

			dst[RIDX(j,    dim-1-(i+3), dim)] = src[RIDX(i+3, j,   dim)];
			dst[RIDX(j+1,  dim-1-(i+3), dim)] = src[RIDX(i+3, j+1, dim)];
			dst[RIDX(j+2,  dim-1-(i+3), dim)] = src[RIDX(i+3, j+2, dim)];
			dst[RIDX(j+3,  dim-1-(i+3), dim)] = src[RIDX(i+3, j+3, dim)];
			dst[RIDX(j+4,  dim-1-(i+3), dim)] = src[RIDX(i+3, j+4, dim)];
			dst[RIDX(j+5,  dim-1-(i+3), dim)] = src[RIDX(i+3, j+5, dim)];
			dst[RIDX(j+6,  dim-1-(i+3), dim)] = src[RIDX(i+3, j+6, dim)];
			dst[RIDX(j+7,  dim-1-(i+3), dim)] = src[RIDX(i+3, j+7, dim)];
			dst[RIDX(j+8,  dim-1-(i+3), dim)] = src[RIDX(i+3, j+8, dim)];
			dst[RIDX(j+9,  dim-1-(i+3), dim)] = src[RIDX(i+3, j+9, dim)];
			dst[RIDX(j+10, dim-1-(i+3), dim)] = src[RIDX(i+3, j+10, dim)];
			dst[RIDX(j+11, dim-1-(i+3), dim)] = src[RIDX(i+3, j+11, dim)];
			dst[RIDX(j+12, dim-1-(i+3), dim)] = src[RIDX(i+3, j+12, dim)];
			dst[RIDX(j+13, dim-1-(i+3), dim)] = src[RIDX(i+3, j+13, dim)];
			dst[RIDX(j+14, dim-1-(i+3), dim)] = src[RIDX(i+3, j+14, dim)];
			dst[RIDX(j+15, dim-1-(i+3), dim)] = src[RIDX(i+3, j+15, dim)];

			dst[RIDX(j,    dim-1-(i+4), dim)] = src[RIDX(i+4, j,   dim)];
			dst[RIDX(j+1,  dim-1-(i+4), dim)] = src[RIDX(i+4, j+1, dim)];
			dst[RIDX(j+2,  dim-1-(i+4), dim)] = src[RIDX(i+4, j+2, dim)];
			dst[RIDX(j+3,  dim-1-(i+4), dim)] = src[RIDX(i+4, j+3, dim)];
			dst[RIDX(j+4,  dim-1-(i+4), dim)] = src[RIDX(i+4, j+4, dim)];
			dst[RIDX(j+5,  dim-1-(i+4), dim)] = src[RIDX(i+4, j+5, dim)];
			dst[RIDX(j+6,  dim-1-(i+4), dim)] = src[RIDX(i+4, j+6, dim)];
			dst[RIDX(j+7,  dim-1-(i+4), dim)] = src[RIDX(i+4, j+7, dim)];
			dst[RIDX(j+8,  dim-1-(i+4), dim)] = src[RIDX(i+4, j+8, dim)];
			dst[RIDX(j+9,  dim-1-(i+4), dim)] = src[RIDX(i+4, j+9, dim)];
			dst[RIDX(j+10, dim-1-(i+4), dim)] = src[RIDX(i+4, j+10, dim)];
			dst[RIDX(j+11, dim-1-(i+4), dim)] = src[RIDX(i+4, j+11, dim)];
			dst[RIDX(j+12, dim-1-(i+4), dim)] = src[RIDX(i+4, j+12, dim)];
			dst[RIDX(j+13, dim-1-(i+4), dim)] = src[RIDX(i+4, j+13, dim)];
			dst[RIDX(j+14, dim-1-(i+4), dim)] = src[RIDX(i+4, j+14, dim)];
			dst[RIDX(j+15, dim-1-(i+4), dim)] = src[RIDX(i+4, j+15, dim)];

			dst[RIDX(j,    dim-1-(i+5), dim)] = src[RIDX(i+5, j,   dim)];
			dst[RIDX(j+1,  dim-1-(i+5), dim)] = src[RIDX(i+5, j+1, dim)];
			dst[RIDX(j+2,  dim-1-(i+5), dim)] = src[RIDX(i+5, j+2, dim)];
			dst[RIDX(j+3,  dim-1-(i+5), dim)] = src[RIDX(i+5, j+3, dim)];
			dst[RIDX(j+4,  dim-1-(i+5), dim)] = src[RIDX(i+5, j+4, dim)];
			dst[RIDX(j+5,  dim-1-(i+5), dim)] = src[RIDX(i+5, j+5, dim)];
			dst[RIDX(j+6,  dim-1-(i+5), dim)] = src[RIDX(i+5, j+6, dim)];
			dst[RIDX(j+7,  dim-1-(i+5), dim)] = src[RIDX(i+5, j+7, dim)];
			dst[RIDX(j+8,  dim-1-(i+5), dim)] = src[RIDX(i+5, j+8, dim)];
			dst[RIDX(j+9,  dim-1-(i+5), dim)] = src[RIDX(i+5, j+9, dim)];
			dst[RIDX(j+10, dim-1-(i+5), dim)] = src[RIDX(i+5, j+10, dim)];
			dst[RIDX(j+11, dim-1-(i+5), dim)] = src[RIDX(i+5, j+11, dim)];
			dst[RIDX(j+12, dim-1-(i+5), dim)] = src[RIDX(i+5, j+12, dim)];
			dst[RIDX(j+13, dim-1-(i+5), dim)] = src[RIDX(i+5, j+13, dim)];
			dst[RIDX(j+14, dim-1-(i+5), dim)] = src[RIDX(i+5, j+14, dim)];
			dst[RIDX(j+15, dim-1-(i+5), dim)] = src[RIDX(i+5, j+15, dim)];

			dst[RIDX(j,    dim-1-(i+6), dim)] = src[RIDX(i+6, j,   dim)];
			dst[RIDX(j+1,  dim-1-(i+6), dim)] = src[RIDX(i+6, j+1, dim)];
			dst[RIDX(j+2,  dim-1-(i+6), dim)] = src[RIDX(i+6, j+2, dim)];
			dst[RIDX(j+3,  dim-1-(i+6), dim)] = src[RIDX(i+6, j+3, dim)];
			dst[RIDX(j+4,  dim-1-(i+6), dim)] = src[RIDX(i+6, j+4, dim)];
			dst[RIDX(j+5,  dim-1-(i+6), dim)] = src[RIDX(i+6, j+5, dim)];
			dst[RIDX(j+6,  dim-1-(i+6), dim)] = src[RIDX(i+6, j+6, dim)];
			dst[RIDX(j+7,  dim-1-(i+6), dim)] = src[RIDX(i+6, j+7, dim)];
			dst[RIDX(j+8,  dim-1-(i+6), dim)] = src[RIDX(i+6, j+8, dim)];
			dst[RIDX(j+9,  dim-1-(i+6), dim)] = src[RIDX(i+6, j+9, dim)];
			dst[RIDX(j+10, dim-1-(i+6), dim)] = src[RIDX(i+6, j+10, dim)];
			dst[RIDX(j+11, dim-1-(i+6), dim)] = src[RIDX(i+6, j+11, dim)];
			dst[RIDX(j+12, dim-1-(i+6), dim)] = src[RIDX(i+6, j+12, dim)];
			dst[RIDX(j+13, dim-1-(i+6), dim)] = src[RIDX(i+6, j+13, dim)];
			dst[RIDX(j+14, dim-1-(i+6), dim)] = src[RIDX(i+6, j+14, dim)];
			dst[RIDX(j+15, dim-1-(i+6), dim)] = src[RIDX(i+6, j+15, dim)];

			dst[RIDX(j,    dim-1-(i+7), dim)] = src[RIDX(i+7, j,   dim)];
			dst[RIDX(j+1,  dim-1-(i+7), dim)] = src[RIDX(i+7, j+1, dim)];
			dst[RIDX(j+2,  dim-1-(i+7), dim)] = src[RIDX(i+7, j+2, dim)];
			dst[RIDX(j+3,  dim-1-(i+7), dim)] = src[RIDX(i+7, j+3, dim)];
			dst[RIDX(j+4,  dim-1-(i+7), dim)] = src[RIDX(i+7, j+4, dim)];
			dst[RIDX(j+5,  dim-1-(i+7), dim)] = src[RIDX(i+7, j+5, dim)];
			dst[RIDX(j+6,  dim-1-(i+7), dim)] = src[RIDX(i+7, j+6, dim)];
			dst[RIDX(j+7,  dim-1-(i+7), dim)] = src[RIDX(i+7, j+7, dim)];
			dst[RIDX(j+8,  dim-1-(i+7), dim)] = src[RIDX(i+7, j+8, dim)];
			dst[RIDX(j+9,  dim-1-(i+7), dim)] = src[RIDX(i+7, j+9, dim)];
			dst[RIDX(j+10, dim-1-(i+7), dim)] = src[RIDX(i+7, j+10, dim)];
			dst[RIDX(j+11, dim-1-(i+7), dim)] = src[RIDX(i+7, j+11, dim)];
			dst[RIDX(j+12, dim-1-(i+7), dim)] = src[RIDX(i+7, j+12, dim)];
			dst[RIDX(j+13, dim-1-(i+7), dim)] = src[RIDX(i+7, j+13, dim)];
			dst[RIDX(j+14, dim-1-(i+7), dim)] = src[RIDX(i+7, j+14, dim)];
			dst[RIDX(j+15, dim-1-(i+7), dim)] = src[RIDX(i+7, j+15, dim)];

			dst[RIDX(j,    dim-1-(i+8), dim)] = src[RIDX(i+8, j,   dim)];
			dst[RIDX(j+1,  dim-1-(i+8), dim)] = src[RIDX(i+8, j+1, dim)];
			dst[RIDX(j+2,  dim-1-(i+8), dim)] = src[RIDX(i+8, j+2, dim)];
			dst[RIDX(j+3,  dim-1-(i+8), dim)] = src[RIDX(i+8, j+3, dim)];
			dst[RIDX(j+4,  dim-1-(i+8), dim)] = src[RIDX(i+8, j+4, dim)];
			dst[RIDX(j+5,  dim-1-(i+8), dim)] = src[RIDX(i+8, j+5, dim)];
			dst[RIDX(j+6,  dim-1-(i+8), dim)] = src[RIDX(i+8, j+6, dim)];
			dst[RIDX(j+7,  dim-1-(i+8), dim)] = src[RIDX(i+8, j+7, dim)];
			dst[RIDX(j+8,  dim-1-(i+8), dim)] = src[RIDX(i+8, j+8, dim)];
			dst[RIDX(j+9,  dim-1-(i+8), dim)] = src[RIDX(i+8, j+9, dim)];
			dst[RIDX(j+10, dim-1-(i+8), dim)] = src[RIDX(i+8, j+10, dim)];
			dst[RIDX(j+11, dim-1-(i+8), dim)] = src[RIDX(i+8, j+11, dim)];
			dst[RIDX(j+12, dim-1-(i+8), dim)] = src[RIDX(i+8, j+12, dim)];
			dst[RIDX(j+13, dim-1-(i+8), dim)] = src[RIDX(i+8, j+13, dim)];
			dst[RIDX(j+14, dim-1-(i+8), dim)] = src[RIDX(i+8, j+14, dim)];
			dst[RIDX(j+15, dim-1-(i+8), dim)] = src[RIDX(i+8, j+15, dim)];

			dst[RIDX(j,    dim-1-(i+9), dim)] = src[RIDX(i+9, j,   dim)];
			dst[RIDX(j+1,  dim-1-(i+9), dim)] = src[RIDX(i+9, j+1, dim)];
			dst[RIDX(j+2,  dim-1-(i+9), dim)] = src[RIDX(i+9, j+2, dim)];
			dst[RIDX(j+3,  dim-1-(i+9), dim)] = src[RIDX(i+9, j+3, dim)];
			dst[RIDX(j+4,  dim-1-(i+9), dim)] = src[RIDX(i+9, j+4, dim)];
			dst[RIDX(j+5,  dim-1-(i+9), dim)] = src[RIDX(i+9, j+5, dim)];
			dst[RIDX(j+6,  dim-1-(i+9), dim)] = src[RIDX(i+9, j+6, dim)];
			dst[RIDX(j+7,  dim-1-(i+9), dim)] = src[RIDX(i+9, j+7, dim)];
			dst[RIDX(j+8,  dim-1-(i+9), dim)] = src[RIDX(i+9, j+8, dim)];
			dst[RIDX(j+9,  dim-1-(i+9), dim)] = src[RIDX(i+9, j+9, dim)];
			dst[RIDX(j+10, dim-1-(i+9), dim)] = src[RIDX(i+9, j+10, dim)];
			dst[RIDX(j+11, dim-1-(i+9), dim)] = src[RIDX(i+9, j+11, dim)];
			dst[RIDX(j+12, dim-1-(i+9), dim)] = src[RIDX(i+9, j+12, dim)];
			dst[RIDX(j+13, dim-1-(i+9), dim)] = src[RIDX(i+9, j+13, dim)];
			dst[RIDX(j+14, dim-1-(i+9), dim)] = src[RIDX(i+9, j+14, dim)];
			dst[RIDX(j+15, dim-1-(i+9), dim)] = src[RIDX(i+9, j+15, dim)];

			dst[RIDX(j,    dim-1-(i+10), dim)] = src[RIDX(i+10, j,   dim)];
			dst[RIDX(j+1,  dim-1-(i+10), dim)] = src[RIDX(i+10, j+1, dim)];
			dst[RIDX(j+2,  dim-1-(i+10), dim)] = src[RIDX(i+10, j+2, dim)];
			dst[RIDX(j+3,  dim-1-(i+10), dim)] = src[RIDX(i+10, j+3, dim)];
			dst[RIDX(j+4,  dim-1-(i+10), dim)] = src[RIDX(i+10, j+4, dim)];
			dst[RIDX(j+5,  dim-1-(i+10), dim)] = src[RIDX(i+10, j+5, dim)];
			dst[RIDX(j+6,  dim-1-(i+10), dim)] = src[RIDX(i+10, j+6, dim)];
			dst[RIDX(j+7,  dim-1-(i+10), dim)] = src[RIDX(i+10, j+7, dim)];
			dst[RIDX(j+8,  dim-1-(i+10), dim)] = src[RIDX(i+10, j+8, dim)];
			dst[RIDX(j+9,  dim-1-(i+10), dim)] = src[RIDX(i+10, j+9, dim)];
			dst[RIDX(j+10, dim-1-(i+10), dim)] = src[RIDX(i+10, j+10, dim)];
			dst[RIDX(j+11, dim-1-(i+10), dim)] = src[RIDX(i+10, j+11, dim)];
			dst[RIDX(j+12, dim-1-(i+10), dim)] = src[RIDX(i+10, j+12, dim)];
			dst[RIDX(j+13, dim-1-(i+10), dim)] = src[RIDX(i+10, j+13, dim)];
			dst[RIDX(j+14, dim-1-(i+10), dim)] = src[RIDX(i+10, j+14, dim)];
			dst[RIDX(j+15, dim-1-(i+10), dim)] = src[RIDX(i+10, j+15, dim)];

			dst[RIDX(j,    dim-1-(i+11), dim)] = src[RIDX(i+11, j,   dim)];
			dst[RIDX(j+1,  dim-1-(i+11), dim)] = src[RIDX(i+11, j+1, dim)];
			dst[RIDX(j+2,  dim-1-(i+11), dim)] = src[RIDX(i+11, j+2, dim)];
			dst[RIDX(j+3,  dim-1-(i+11), dim)] = src[RIDX(i+11, j+3, dim)];
			dst[RIDX(j+4,  dim-1-(i+11), dim)] = src[RIDX(i+11, j+4, dim)];
			dst[RIDX(j+5,  dim-1-(i+11), dim)] = src[RIDX(i+11, j+5, dim)];
			dst[RIDX(j+6,  dim-1-(i+11), dim)] = src[RIDX(i+11, j+6, dim)];
			dst[RIDX(j+7,  dim-1-(i+11), dim)] = src[RIDX(i+11, j+7, dim)];
			dst[RIDX(j+8,  dim-1-(i+11), dim)] = src[RIDX(i+11, j+8, dim)];
			dst[RIDX(j+9,  dim-1-(i+11), dim)] = src[RIDX(i+11, j+9, dim)];
			dst[RIDX(j+10, dim-1-(i+11), dim)] = src[RIDX(i+11, j+10, dim)];
			dst[RIDX(j+11, dim-1-(i+11), dim)] = src[RIDX(i+11, j+11, dim)];
			dst[RIDX(j+12, dim-1-(i+11), dim)] = src[RIDX(i+11, j+12, dim)];
			dst[RIDX(j+13, dim-1-(i+11), dim)] = src[RIDX(i+11, j+13, dim)];
			dst[RIDX(j+14, dim-1-(i+11), dim)] = src[RIDX(i+11, j+14, dim)];
			dst[RIDX(j+15, dim-1-(i+11), dim)] = src[RIDX(i+11, j+15, dim)];

			dst[RIDX(j,    dim-1-(i+12), dim)] = src[RIDX(i+12, j,   dim)];
			dst[RIDX(j+1,  dim-1-(i+12), dim)] = src[RIDX(i+12, j+1, dim)];
			dst[RIDX(j+2,  dim-1-(i+12), dim)] = src[RIDX(i+12, j+2, dim)];
			dst[RIDX(j+3,  dim-1-(i+12), dim)] = src[RIDX(i+12, j+3, dim)];
			dst[RIDX(j+4,  dim-1-(i+12), dim)] = src[RIDX(i+12, j+4, dim)];
			dst[RIDX(j+5,  dim-1-(i+12), dim)] = src[RIDX(i+12, j+5, dim)];
			dst[RIDX(j+6,  dim-1-(i+12), dim)] = src[RIDX(i+12, j+6, dim)];
			dst[RIDX(j+7,  dim-1-(i+12), dim)] = src[RIDX(i+12, j+7, dim)];
			dst[RIDX(j+8,  dim-1-(i+12), dim)] = src[RIDX(i+12, j+8, dim)];
			dst[RIDX(j+9,  dim-1-(i+12), dim)] = src[RIDX(i+12, j+9, dim)];
			dst[RIDX(j+10, dim-1-(i+12), dim)] = src[RIDX(i+12, j+10, dim)];
			dst[RIDX(j+11, dim-1-(i+12), dim)] = src[RIDX(i+12, j+11, dim)];
			dst[RIDX(j+12, dim-1-(i+12), dim)] = src[RIDX(i+12, j+12, dim)];
			dst[RIDX(j+13, dim-1-(i+12), dim)] = src[RIDX(i+12, j+13, dim)];
			dst[RIDX(j+14, dim-1-(i+12), dim)] = src[RIDX(i+12, j+14, dim)];
			dst[RIDX(j+15, dim-1-(i+12), dim)] = src[RIDX(i+12, j+15, dim)];

			dst[RIDX(j,    dim-1-(i+13), dim)] = src[RIDX(i+13, j,   dim)];
			dst[RIDX(j+1,  dim-1-(i+13), dim)] = src[RIDX(i+13, j+1, dim)];
			dst[RIDX(j+2,  dim-1-(i+13), dim)] = src[RIDX(i+13, j+2, dim)];
			dst[RIDX(j+3,  dim-1-(i+13), dim)] = src[RIDX(i+13, j+3, dim)];
			dst[RIDX(j+4,  dim-1-(i+13), dim)] = src[RIDX(i+13, j+4, dim)];
			dst[RIDX(j+5,  dim-1-(i+13), dim)] = src[RIDX(i+13, j+5, dim)];
			dst[RIDX(j+6,  dim-1-(i+13), dim)] = src[RIDX(i+13, j+6, dim)];
			dst[RIDX(j+7,  dim-1-(i+13), dim)] = src[RIDX(i+13, j+7, dim)];
			dst[RIDX(j+8,  dim-1-(i+13), dim)] = src[RIDX(i+13, j+8, dim)];
			dst[RIDX(j+9,  dim-1-(i+13), dim)] = src[RIDX(i+13, j+9, dim)];
			dst[RIDX(j+10, dim-1-(i+13), dim)] = src[RIDX(i+13, j+10, dim)];
			dst[RIDX(j+11, dim-1-(i+13), dim)] = src[RIDX(i+13, j+11, dim)];
			dst[RIDX(j+12, dim-1-(i+13), dim)] = src[RIDX(i+13, j+12, dim)];
			dst[RIDX(j+13, dim-1-(i+13), dim)] = src[RIDX(i+13, j+13, dim)];
			dst[RIDX(j+14, dim-1-(i+13), dim)] = src[RIDX(i+13, j+14, dim)];
			dst[RIDX(j+15, dim-1-(i+13), dim)] = src[RIDX(i+13, j+15, dim)];

			dst[RIDX(j,    dim-1-(i+14), dim)] = src[RIDX(i+14, j,   dim)];
			dst[RIDX(j+1,  dim-1-(i+14), dim)] = src[RIDX(i+14, j+1, dim)];
			dst[RIDX(j+2,  dim-1-(i+14), dim)] = src[RIDX(i+14, j+2, dim)];
			dst[RIDX(j+3,  dim-1-(i+14), dim)] = src[RIDX(i+14, j+3, dim)];
			dst[RIDX(j+4,  dim-1-(i+14), dim)] = src[RIDX(i+14, j+4, dim)];
			dst[RIDX(j+5,  dim-1-(i+14), dim)] = src[RIDX(i+14, j+5, dim)];
			dst[RIDX(j+6,  dim-1-(i+14), dim)] = src[RIDX(i+14, j+6, dim)];
			dst[RIDX(j+7,  dim-1-(i+14), dim)] = src[RIDX(i+14, j+7, dim)];
			dst[RIDX(j+8,  dim-1-(i+14), dim)] = src[RIDX(i+14, j+8, dim)];
			dst[RIDX(j+9,  dim-1-(i+14), dim)] = src[RIDX(i+14, j+9, dim)];
			dst[RIDX(j+10, dim-1-(i+14), dim)] = src[RIDX(i+14, j+10, dim)];
			dst[RIDX(j+11, dim-1-(i+14), dim)] = src[RIDX(i+14, j+11, dim)];
			dst[RIDX(j+12, dim-1-(i+14), dim)] = src[RIDX(i+14, j+12, dim)];
			dst[RIDX(j+13, dim-1-(i+14), dim)] = src[RIDX(i+14, j+13, dim)];
			dst[RIDX(j+14, dim-1-(i+14), dim)] = src[RIDX(i+14, j+14, dim)];
			dst[RIDX(j+15, dim-1-(i+14), dim)] = src[RIDX(i+14, j+15, dim)];

			dst[RIDX(j,    dim-1-(i+15), dim)] = src[RIDX(i+15, j,   dim)];
			dst[RIDX(j+1,  dim-1-(i+15), dim)] = src[RIDX(i+15, j+1, dim)];
			dst[RIDX(j+2,  dim-1-(i+15), dim)] = src[RIDX(i+15, j+2, dim)];
			dst[RIDX(j+3,  dim-1-(i+15), dim)] = src[RIDX(i+15, j+3, dim)];
			dst[RIDX(j+4,  dim-1-(i+15), dim)] = src[RIDX(i+15, j+4, dim)];
			dst[RIDX(j+5,  dim-1-(i+15), dim)] = src[RIDX(i+15, j+5, dim)];
			dst[RIDX(j+6,  dim-1-(i+15), dim)] = src[RIDX(i+15, j+6, dim)];
			dst[RIDX(j+7,  dim-1-(i+15), dim)] = src[RIDX(i+15, j+7, dim)];
			dst[RIDX(j+8,  dim-1-(i+15), dim)] = src[RIDX(i+15, j+8, dim)];
			dst[RIDX(j+9,  dim-1-(i+15), dim)] = src[RIDX(i+15, j+9, dim)];
			dst[RIDX(j+10, dim-1-(i+15), dim)] = src[RIDX(i+15, j+10, dim)];
			dst[RIDX(j+11, dim-1-(i+15), dim)] = src[RIDX(i+15, j+11, dim)];
			dst[RIDX(j+12, dim-1-(i+15), dim)] = src[RIDX(i+15, j+12, dim)];
			dst[RIDX(j+13, dim-1-(i+15), dim)] = src[RIDX(i+15, j+13, dim)];
			dst[RIDX(j+14, dim-1-(i+15), dim)] = src[RIDX(i+15, j+14, dim)];
			dst[RIDX(j+15, dim-1-(i+15), dim)] = src[RIDX(i+15, j+15, dim)];
        }
    }
}

/*
 * rotate_block32_4x4
 */
char rotate_block32_4x4_descr[] = "rotate_block32_4x4: Block by 32 and unroll both loops by 4";
void rotate_block32_4x4(int dim, pixel *src, pixel *dst)
{
    int i_0, j_0, i, j;
    int outer_limit = dim - 3;
    int block_limit = 32;

    for (i_0 = 0; i_0 < outer_limit; i_0 += block_limit) {
    	for (j_0 = 0; j_0 < outer_limit; j_0 += block_limit) {
			for (i = i_0; i < i_0 + block_limit; i += 4) {
				for (j = j_0; j < j_0 + block_limit; j += 4) {

					dst[RIDX(j,   dim-1-i, dim)] = src[RIDX(i, j,   dim)];
					dst[RIDX(j+1, dim-1-i, dim)] = src[RIDX(i, j+1, dim)];
					dst[RIDX(j+2, dim-1-i, dim)] = src[RIDX(i, j+2, dim)];
					dst[RIDX(j+3, dim-1-i, dim)] = src[RIDX(i, j+3, dim)];

					dst[RIDX(j,   dim-1-(i+1), dim)] = src[RIDX(i+1, j,   dim)];
					dst[RIDX(j+1, dim-1-(i+1), dim)] = src[RIDX(i+1, j+1, dim)];
					dst[RIDX(j+2, dim-1-(i+1), dim)] = src[RIDX(i+1, j+2, dim)];
					dst[RIDX(j+3, dim-1-(i+1), dim)] = src[RIDX(i+1, j+3, dim)];

					dst[RIDX(j,   dim-1-(i+2), dim)] = src[RIDX(i+2, j,   dim)];
					dst[RIDX(j+1, dim-1-(i+2), dim)] = src[RIDX(i+2, j+1, dim)];
					dst[RIDX(j+2, dim-1-(i+2), dim)] = src[RIDX(i+2, j+2, dim)];
					dst[RIDX(j+3, dim-1-(i+2), dim)] = src[RIDX(i+2, j+3, dim)];

					dst[RIDX(j,   dim-1-(i+3), dim)] = src[RIDX(i+3, j,   dim)];
					dst[RIDX(j+1, dim-1-(i+3), dim)] = src[RIDX(i+3, j+1, dim)];
					dst[RIDX(j+2, dim-1-(i+3), dim)] = src[RIDX(i+3, j+2, dim)];
					dst[RIDX(j+3, dim-1-(i+3), dim)] = src[RIDX(i+3, j+3, dim)];
				}
			}
    	}
    }
}

/*
 * rotate_block32_8x8
 */
char rotate_block32_8x8_descr[] = "rotate_block32_8x8: Block by 32 and unroll both loops by 8";
void rotate_block32_8x8(int dim, pixel *src, pixel *dst)
{
    int i_0, j_0, i, j;
    int outer_limit = dim - 7;
    int block_limit = 32;

    for (i_0 = 0; i_0 < outer_limit; i_0 += block_limit) {
    	for (j_0 = 0; j_0 < outer_limit; j_0 += block_limit) {
			for (i = i_0; i < i_0 + block_limit; i += 8) {
				for (j = j_0; j < j_0 + block_limit; j += 8) {
					dst[RIDX(j,   dim-1-i, dim)] = src[RIDX(i, j,   dim)];
					dst[RIDX(j+1, dim-1-i, dim)] = src[RIDX(i, j+1, dim)];
					dst[RIDX(j+2, dim-1-i, dim)] = src[RIDX(i, j+2, dim)];
					dst[RIDX(j+3, dim-1-i, dim)] = src[RIDX(i, j+3, dim)];
					dst[RIDX(j+4, dim-1-i, dim)] = src[RIDX(i, j+4, dim)];
					dst[RIDX(j+5, dim-1-i, dim)] = src[RIDX(i, j+5, dim)];
					dst[RIDX(j+6, dim-1-i, dim)] = src[RIDX(i, j+6, dim)];
					dst[RIDX(j+7, dim-1-i, dim)] = src[RIDX(i, j+7, dim)];

					dst[RIDX(j,   dim-1-(i+1), dim)] = src[RIDX(i+1, j,   dim)];
					dst[RIDX(j+1, dim-1-(i+1), dim)] = src[RIDX(i+1, j+1, dim)];
					dst[RIDX(j+2, dim-1-(i+1), dim)] = src[RIDX(i+1, j+2, dim)];
					dst[RIDX(j+3, dim-1-(i+1), dim)] = src[RIDX(i+1, j+3, dim)];
					dst[RIDX(j+4, dim-1-(i+1), dim)] = src[RIDX(i+1, j+4, dim)];
					dst[RIDX(j+5, dim-1-(i+1), dim)] = src[RIDX(i+1, j+5, dim)];
					dst[RIDX(j+6, dim-1-(i+1), dim)] = src[RIDX(i+1, j+6, dim)];
					dst[RIDX(j+7, dim-1-(i+1), dim)] = src[RIDX(i+1, j+7, dim)];

					dst[RIDX(j,   dim-1-(i+2), dim)] = src[RIDX(i+2, j,   dim)];
					dst[RIDX(j+1, dim-1-(i+2), dim)] = src[RIDX(i+2, j+1, dim)];
					dst[RIDX(j+2, dim-1-(i+2), dim)] = src[RIDX(i+2, j+2, dim)];
					dst[RIDX(j+3, dim-1-(i+2), dim)] = src[RIDX(i+2, j+3, dim)];
					dst[RIDX(j+4, dim-1-(i+2), dim)] = src[RIDX(i+2, j+4, dim)];
					dst[RIDX(j+5, dim-1-(i+2), dim)] = src[RIDX(i+2, j+5, dim)];
					dst[RIDX(j+6, dim-1-(i+2), dim)] = src[RIDX(i+2, j+6, dim)];
					dst[RIDX(j+7, dim-1-(i+2), dim)] = src[RIDX(i+2, j+7, dim)];

					dst[RIDX(j,   dim-1-(i+3), dim)] = src[RIDX(i+3, j,   dim)];
					dst[RIDX(j+1, dim-1-(i+3), dim)] = src[RIDX(i+3, j+1, dim)];
					dst[RIDX(j+2, dim-1-(i+3), dim)] = src[RIDX(i+3, j+2, dim)];
					dst[RIDX(j+3, dim-1-(i+3), dim)] = src[RIDX(i+3, j+3, dim)];
					dst[RIDX(j+4, dim-1-(i+3), dim)] = src[RIDX(i+3, j+4, dim)];
					dst[RIDX(j+5, dim-1-(i+3), dim)] = src[RIDX(i+3, j+5, dim)];
					dst[RIDX(j+6, dim-1-(i+3), dim)] = src[RIDX(i+3, j+6, dim)];
					dst[RIDX(j+7, dim-1-(i+3), dim)] = src[RIDX(i+3, j+7, dim)];

					dst[RIDX(j,   dim-1-(i+4), dim)] = src[RIDX(i+4, j,   dim)];
					dst[RIDX(j+1, dim-1-(i+4), dim)] = src[RIDX(i+4, j+1, dim)];
					dst[RIDX(j+2, dim-1-(i+4), dim)] = src[RIDX(i+4, j+2, dim)];
					dst[RIDX(j+3, dim-1-(i+4), dim)] = src[RIDX(i+4, j+3, dim)];
					dst[RIDX(j+4, dim-1-(i+4), dim)] = src[RIDX(i+4, j+4, dim)];
					dst[RIDX(j+5, dim-1-(i+4), dim)] = src[RIDX(i+4, j+5, dim)];
					dst[RIDX(j+6, dim-1-(i+4), dim)] = src[RIDX(i+4, j+6, dim)];
					dst[RIDX(j+7, dim-1-(i+4), dim)] = src[RIDX(i+4, j+7, dim)];

					dst[RIDX(j,   dim-1-(i+5), dim)] = src[RIDX(i+5, j,   dim)];
					dst[RIDX(j+1, dim-1-(i+5), dim)] = src[RIDX(i+5, j+1, dim)];
					dst[RIDX(j+2, dim-1-(i+5), dim)] = src[RIDX(i+5, j+2, dim)];
					dst[RIDX(j+3, dim-1-(i+5), dim)] = src[RIDX(i+5, j+3, dim)];
					dst[RIDX(j+4, dim-1-(i+5), dim)] = src[RIDX(i+5, j+4, dim)];
					dst[RIDX(j+5, dim-1-(i+5), dim)] = src[RIDX(i+5, j+5, dim)];
					dst[RIDX(j+6, dim-1-(i+5), dim)] = src[RIDX(i+5, j+6, dim)];
					dst[RIDX(j+7, dim-1-(i+5), dim)] = src[RIDX(i+5, j+7, dim)];

					dst[RIDX(j,   dim-1-(i+6), dim)] = src[RIDX(i+6, j,   dim)];
					dst[RIDX(j+1, dim-1-(i+6), dim)] = src[RIDX(i+6, j+1, dim)];
					dst[RIDX(j+2, dim-1-(i+6), dim)] = src[RIDX(i+6, j+2, dim)];
					dst[RIDX(j+3, dim-1-(i+6), dim)] = src[RIDX(i+6, j+3, dim)];
					dst[RIDX(j+4, dim-1-(i+6), dim)] = src[RIDX(i+6, j+4, dim)];
					dst[RIDX(j+5, dim-1-(i+6), dim)] = src[RIDX(i+6, j+5, dim)];
					dst[RIDX(j+6, dim-1-(i+6), dim)] = src[RIDX(i+6, j+6, dim)];
					dst[RIDX(j+7, dim-1-(i+6), dim)] = src[RIDX(i+6, j+7, dim)];

					dst[RIDX(j,   dim-1-(i+7), dim)] = src[RIDX(i+7, j,   dim)];
					dst[RIDX(j+1, dim-1-(i+7), dim)] = src[RIDX(i+7, j+1, dim)];
					dst[RIDX(j+2, dim-1-(i+7), dim)] = src[RIDX(i+7, j+2, dim)];
					dst[RIDX(j+3, dim-1-(i+7), dim)] = src[RIDX(i+7, j+3, dim)];
					dst[RIDX(j+4, dim-1-(i+7), dim)] = src[RIDX(i+7, j+4, dim)];
					dst[RIDX(j+5, dim-1-(i+7), dim)] = src[RIDX(i+7, j+5, dim)];
					dst[RIDX(j+6, dim-1-(i+7), dim)] = src[RIDX(i+7, j+6, dim)];
					dst[RIDX(j+7, dim-1-(i+7), dim)] = src[RIDX(i+7, j+7, dim)];
				}
			}
    	}
    }
}

/*
 * rotate_block32_16x16
 */
char rotate_block32_16x16_descr[] = "rotate_block32_16x16: Block by 32 and unroll both loops by 16";
void rotate_block32_16x16(int dim, pixel *src, pixel *dst)
{
    int i_0, j_0, i, j;
    int outer_limit = dim - 15;
    int block_limit = 32;

    for (i_0 = 0; i_0 < outer_limit; i_0 += block_limit) {
    	for (j_0 = 0; j_0 < outer_limit; j_0 += block_limit) {
			for (i = i_0; i < i_0 + block_limit; i += 16) {
				for (j = j_0; j < j_0 + block_limit; j += 16) {
					dst[RIDX(j,    dim-1-i, dim)] = src[RIDX(i, j,    dim)];
					dst[RIDX(j+1,  dim-1-i, dim)] = src[RIDX(i, j+1,  dim)];
					dst[RIDX(j+2,  dim-1-i, dim)] = src[RIDX(i, j+2,  dim)];
					dst[RIDX(j+3,  dim-1-i, dim)] = src[RIDX(i, j+3,  dim)];
					dst[RIDX(j+4,  dim-1-i, dim)] = src[RIDX(i, j+4,  dim)];
					dst[RIDX(j+5,  dim-1-i, dim)] = src[RIDX(i, j+5,  dim)];
					dst[RIDX(j+6,  dim-1-i, dim)] = src[RIDX(i, j+6,  dim)];
					dst[RIDX(j+7,  dim-1-i, dim)] = src[RIDX(i, j+7,  dim)];
					dst[RIDX(j+8,  dim-1-i, dim)] = src[RIDX(i, j+8,  dim)];
					dst[RIDX(j+9,  dim-1-i, dim)] = src[RIDX(i, j+9,  dim)];
					dst[RIDX(j+10, dim-1-i, dim)] = src[RIDX(i, j+10, dim)];
					dst[RIDX(j+11, dim-1-i, dim)] = src[RIDX(i, j+11, dim)];
					dst[RIDX(j+12, dim-1-i, dim)] = src[RIDX(i, j+12, dim)];
					dst[RIDX(j+13, dim-1-i, dim)] = src[RIDX(i, j+13, dim)];
					dst[RIDX(j+14, dim-1-i, dim)] = src[RIDX(i, j+14, dim)];
					dst[RIDX(j+15, dim-1-i, dim)] = src[RIDX(i, j+15, dim)];

					dst[RIDX(j,    dim-1-(i+1), dim)] = src[RIDX(i+1, j,   dim)];
					dst[RIDX(j+1,  dim-1-(i+1), dim)] = src[RIDX(i+1, j+1, dim)];
					dst[RIDX(j+2,  dim-1-(i+1), dim)] = src[RIDX(i+1, j+2, dim)];
					dst[RIDX(j+3,  dim-1-(i+1), dim)] = src[RIDX(i+1, j+3, dim)];
					dst[RIDX(j+4,  dim-1-(i+1), dim)] = src[RIDX(i+1, j+4, dim)];
					dst[RIDX(j+5,  dim-1-(i+1), dim)] = src[RIDX(i+1, j+5, dim)];
					dst[RIDX(j+6,  dim-1-(i+1), dim)] = src[RIDX(i+1, j+6, dim)];
					dst[RIDX(j+7,  dim-1-(i+1), dim)] = src[RIDX(i+1, j+7, dim)];
					dst[RIDX(j+8,  dim-1-(i+1), dim)] = src[RIDX(i+1, j+8, dim)];
					dst[RIDX(j+9,  dim-1-(i+1), dim)] = src[RIDX(i+1, j+9, dim)];
					dst[RIDX(j+10, dim-1-(i+1), dim)] = src[RIDX(i+1, j+10, dim)];
					dst[RIDX(j+11, dim-1-(i+1), dim)] = src[RIDX(i+1, j+11, dim)];
					dst[RIDX(j+12, dim-1-(i+1), dim)] = src[RIDX(i+1, j+12, dim)];
					dst[RIDX(j+13, dim-1-(i+1), dim)] = src[RIDX(i+1, j+13, dim)];
					dst[RIDX(j+14, dim-1-(i+1), dim)] = src[RIDX(i+1, j+14, dim)];
					dst[RIDX(j+15, dim-1-(i+1), dim)] = src[RIDX(i+1, j+15, dim)];

					dst[RIDX(j,    dim-1-(i+2), dim)] = src[RIDX(i+2, j,   dim)];
					dst[RIDX(j+1,  dim-1-(i+2), dim)] = src[RIDX(i+2, j+1, dim)];
					dst[RIDX(j+2,  dim-1-(i+2), dim)] = src[RIDX(i+2, j+2, dim)];
					dst[RIDX(j+3,  dim-1-(i+2), dim)] = src[RIDX(i+2, j+3, dim)];
					dst[RIDX(j+4,  dim-1-(i+2), dim)] = src[RIDX(i+2, j+4, dim)];
					dst[RIDX(j+5,  dim-1-(i+2), dim)] = src[RIDX(i+2, j+5, dim)];
					dst[RIDX(j+6,  dim-1-(i+2), dim)] = src[RIDX(i+2, j+6, dim)];
					dst[RIDX(j+7,  dim-1-(i+2), dim)] = src[RIDX(i+2, j+7, dim)];
					dst[RIDX(j+8,  dim-1-(i+2), dim)] = src[RIDX(i+2, j+8, dim)];
					dst[RIDX(j+9,  dim-1-(i+2), dim)] = src[RIDX(i+2, j+9, dim)];
					dst[RIDX(j+10, dim-1-(i+2), dim)] = src[RIDX(i+2, j+10, dim)];
					dst[RIDX(j+11, dim-1-(i+2), dim)] = src[RIDX(i+2, j+11, dim)];
					dst[RIDX(j+12, dim-1-(i+2), dim)] = src[RIDX(i+2, j+12, dim)];
					dst[RIDX(j+13, dim-1-(i+2), dim)] = src[RIDX(i+2, j+13, dim)];
					dst[RIDX(j+14, dim-1-(i+2), dim)] = src[RIDX(i+2, j+14, dim)];
					dst[RIDX(j+15, dim-1-(i+2), dim)] = src[RIDX(i+2, j+15, dim)];

					dst[RIDX(j,    dim-1-(i+3), dim)] = src[RIDX(i+3, j,   dim)];
					dst[RIDX(j+1,  dim-1-(i+3), dim)] = src[RIDX(i+3, j+1, dim)];
					dst[RIDX(j+2,  dim-1-(i+3), dim)] = src[RIDX(i+3, j+2, dim)];
					dst[RIDX(j+3,  dim-1-(i+3), dim)] = src[RIDX(i+3, j+3, dim)];
					dst[RIDX(j+4,  dim-1-(i+3), dim)] = src[RIDX(i+3, j+4, dim)];
					dst[RIDX(j+5,  dim-1-(i+3), dim)] = src[RIDX(i+3, j+5, dim)];
					dst[RIDX(j+6,  dim-1-(i+3), dim)] = src[RIDX(i+3, j+6, dim)];
					dst[RIDX(j+7,  dim-1-(i+3), dim)] = src[RIDX(i+3, j+7, dim)];
					dst[RIDX(j+8,  dim-1-(i+3), dim)] = src[RIDX(i+3, j+8, dim)];
					dst[RIDX(j+9,  dim-1-(i+3), dim)] = src[RIDX(i+3, j+9, dim)];
					dst[RIDX(j+10, dim-1-(i+3), dim)] = src[RIDX(i+3, j+10, dim)];
					dst[RIDX(j+11, dim-1-(i+3), dim)] = src[RIDX(i+3, j+11, dim)];
					dst[RIDX(j+12, dim-1-(i+3), dim)] = src[RIDX(i+3, j+12, dim)];
					dst[RIDX(j+13, dim-1-(i+3), dim)] = src[RIDX(i+3, j+13, dim)];
					dst[RIDX(j+14, dim-1-(i+3), dim)] = src[RIDX(i+3, j+14, dim)];
					dst[RIDX(j+15, dim-1-(i+3), dim)] = src[RIDX(i+3, j+15, dim)];

					dst[RIDX(j,    dim-1-(i+4), dim)] = src[RIDX(i+4, j,   dim)];
					dst[RIDX(j+1,  dim-1-(i+4), dim)] = src[RIDX(i+4, j+1, dim)];
					dst[RIDX(j+2,  dim-1-(i+4), dim)] = src[RIDX(i+4, j+2, dim)];
					dst[RIDX(j+3,  dim-1-(i+4), dim)] = src[RIDX(i+4, j+3, dim)];
					dst[RIDX(j+4,  dim-1-(i+4), dim)] = src[RIDX(i+4, j+4, dim)];
					dst[RIDX(j+5,  dim-1-(i+4), dim)] = src[RIDX(i+4, j+5, dim)];
					dst[RIDX(j+6,  dim-1-(i+4), dim)] = src[RIDX(i+4, j+6, dim)];
					dst[RIDX(j+7,  dim-1-(i+4), dim)] = src[RIDX(i+4, j+7, dim)];
					dst[RIDX(j+8,  dim-1-(i+4), dim)] = src[RIDX(i+4, j+8, dim)];
					dst[RIDX(j+9,  dim-1-(i+4), dim)] = src[RIDX(i+4, j+9, dim)];
					dst[RIDX(j+10, dim-1-(i+4), dim)] = src[RIDX(i+4, j+10, dim)];
					dst[RIDX(j+11, dim-1-(i+4), dim)] = src[RIDX(i+4, j+11, dim)];
					dst[RIDX(j+12, dim-1-(i+4), dim)] = src[RIDX(i+4, j+12, dim)];
					dst[RIDX(j+13, dim-1-(i+4), dim)] = src[RIDX(i+4, j+13, dim)];
					dst[RIDX(j+14, dim-1-(i+4), dim)] = src[RIDX(i+4, j+14, dim)];
					dst[RIDX(j+15, dim-1-(i+4), dim)] = src[RIDX(i+4, j+15, dim)];

					dst[RIDX(j,    dim-1-(i+5), dim)] = src[RIDX(i+5, j,   dim)];
					dst[RIDX(j+1,  dim-1-(i+5), dim)] = src[RIDX(i+5, j+1, dim)];
					dst[RIDX(j+2,  dim-1-(i+5), dim)] = src[RIDX(i+5, j+2, dim)];
					dst[RIDX(j+3,  dim-1-(i+5), dim)] = src[RIDX(i+5, j+3, dim)];
					dst[RIDX(j+4,  dim-1-(i+5), dim)] = src[RIDX(i+5, j+4, dim)];
					dst[RIDX(j+5,  dim-1-(i+5), dim)] = src[RIDX(i+5, j+5, dim)];
					dst[RIDX(j+6,  dim-1-(i+5), dim)] = src[RIDX(i+5, j+6, dim)];
					dst[RIDX(j+7,  dim-1-(i+5), dim)] = src[RIDX(i+5, j+7, dim)];
					dst[RIDX(j+8,  dim-1-(i+5), dim)] = src[RIDX(i+5, j+8, dim)];
					dst[RIDX(j+9,  dim-1-(i+5), dim)] = src[RIDX(i+5, j+9, dim)];
					dst[RIDX(j+10, dim-1-(i+5), dim)] = src[RIDX(i+5, j+10, dim)];
					dst[RIDX(j+11, dim-1-(i+5), dim)] = src[RIDX(i+5, j+11, dim)];
					dst[RIDX(j+12, dim-1-(i+5), dim)] = src[RIDX(i+5, j+12, dim)];
					dst[RIDX(j+13, dim-1-(i+5), dim)] = src[RIDX(i+5, j+13, dim)];
					dst[RIDX(j+14, dim-1-(i+5), dim)] = src[RIDX(i+5, j+14, dim)];
					dst[RIDX(j+15, dim-1-(i+5), dim)] = src[RIDX(i+5, j+15, dim)];

					dst[RIDX(j,    dim-1-(i+6), dim)] = src[RIDX(i+6, j,   dim)];
					dst[RIDX(j+1,  dim-1-(i+6), dim)] = src[RIDX(i+6, j+1, dim)];
					dst[RIDX(j+2,  dim-1-(i+6), dim)] = src[RIDX(i+6, j+2, dim)];
					dst[RIDX(j+3,  dim-1-(i+6), dim)] = src[RIDX(i+6, j+3, dim)];
					dst[RIDX(j+4,  dim-1-(i+6), dim)] = src[RIDX(i+6, j+4, dim)];
					dst[RIDX(j+5,  dim-1-(i+6), dim)] = src[RIDX(i+6, j+5, dim)];
					dst[RIDX(j+6,  dim-1-(i+6), dim)] = src[RIDX(i+6, j+6, dim)];
					dst[RIDX(j+7,  dim-1-(i+6), dim)] = src[RIDX(i+6, j+7, dim)];
					dst[RIDX(j+8,  dim-1-(i+6), dim)] = src[RIDX(i+6, j+8, dim)];
					dst[RIDX(j+9,  dim-1-(i+6), dim)] = src[RIDX(i+6, j+9, dim)];
					dst[RIDX(j+10, dim-1-(i+6), dim)] = src[RIDX(i+6, j+10, dim)];
					dst[RIDX(j+11, dim-1-(i+6), dim)] = src[RIDX(i+6, j+11, dim)];
					dst[RIDX(j+12, dim-1-(i+6), dim)] = src[RIDX(i+6, j+12, dim)];
					dst[RIDX(j+13, dim-1-(i+6), dim)] = src[RIDX(i+6, j+13, dim)];
					dst[RIDX(j+14, dim-1-(i+6), dim)] = src[RIDX(i+6, j+14, dim)];
					dst[RIDX(j+15, dim-1-(i+6), dim)] = src[RIDX(i+6, j+15, dim)];

					dst[RIDX(j,    dim-1-(i+7), dim)] = src[RIDX(i+7, j,   dim)];
					dst[RIDX(j+1,  dim-1-(i+7), dim)] = src[RIDX(i+7, j+1, dim)];
					dst[RIDX(j+2,  dim-1-(i+7), dim)] = src[RIDX(i+7, j+2, dim)];
					dst[RIDX(j+3,  dim-1-(i+7), dim)] = src[RIDX(i+7, j+3, dim)];
					dst[RIDX(j+4,  dim-1-(i+7), dim)] = src[RIDX(i+7, j+4, dim)];
					dst[RIDX(j+5,  dim-1-(i+7), dim)] = src[RIDX(i+7, j+5, dim)];
					dst[RIDX(j+6,  dim-1-(i+7), dim)] = src[RIDX(i+7, j+6, dim)];
					dst[RIDX(j+7,  dim-1-(i+7), dim)] = src[RIDX(i+7, j+7, dim)];
					dst[RIDX(j+8,  dim-1-(i+7), dim)] = src[RIDX(i+7, j+8, dim)];
					dst[RIDX(j+9,  dim-1-(i+7), dim)] = src[RIDX(i+7, j+9, dim)];
					dst[RIDX(j+10, dim-1-(i+7), dim)] = src[RIDX(i+7, j+10, dim)];
					dst[RIDX(j+11, dim-1-(i+7), dim)] = src[RIDX(i+7, j+11, dim)];
					dst[RIDX(j+12, dim-1-(i+7), dim)] = src[RIDX(i+7, j+12, dim)];
					dst[RIDX(j+13, dim-1-(i+7), dim)] = src[RIDX(i+7, j+13, dim)];
					dst[RIDX(j+14, dim-1-(i+7), dim)] = src[RIDX(i+7, j+14, dim)];
					dst[RIDX(j+15, dim-1-(i+7), dim)] = src[RIDX(i+7, j+15, dim)];

					dst[RIDX(j,    dim-1-(i+8), dim)] = src[RIDX(i+8, j,   dim)];
					dst[RIDX(j+1,  dim-1-(i+8), dim)] = src[RIDX(i+8, j+1, dim)];
					dst[RIDX(j+2,  dim-1-(i+8), dim)] = src[RIDX(i+8, j+2, dim)];
					dst[RIDX(j+3,  dim-1-(i+8), dim)] = src[RIDX(i+8, j+3, dim)];
					dst[RIDX(j+4,  dim-1-(i+8), dim)] = src[RIDX(i+8, j+4, dim)];
					dst[RIDX(j+5,  dim-1-(i+8), dim)] = src[RIDX(i+8, j+5, dim)];
					dst[RIDX(j+6,  dim-1-(i+8), dim)] = src[RIDX(i+8, j+6, dim)];
					dst[RIDX(j+7,  dim-1-(i+8), dim)] = src[RIDX(i+8, j+7, dim)];
					dst[RIDX(j+8,  dim-1-(i+8), dim)] = src[RIDX(i+8, j+8, dim)];
					dst[RIDX(j+9,  dim-1-(i+8), dim)] = src[RIDX(i+8, j+9, dim)];
					dst[RIDX(j+10, dim-1-(i+8), dim)] = src[RIDX(i+8, j+10, dim)];
					dst[RIDX(j+11, dim-1-(i+8), dim)] = src[RIDX(i+8, j+11, dim)];
					dst[RIDX(j+12, dim-1-(i+8), dim)] = src[RIDX(i+8, j+12, dim)];
					dst[RIDX(j+13, dim-1-(i+8), dim)] = src[RIDX(i+8, j+13, dim)];
					dst[RIDX(j+14, dim-1-(i+8), dim)] = src[RIDX(i+8, j+14, dim)];
					dst[RIDX(j+15, dim-1-(i+8), dim)] = src[RIDX(i+8, j+15, dim)];

					dst[RIDX(j,    dim-1-(i+9), dim)] = src[RIDX(i+9, j,   dim)];
					dst[RIDX(j+1,  dim-1-(i+9), dim)] = src[RIDX(i+9, j+1, dim)];
					dst[RIDX(j+2,  dim-1-(i+9), dim)] = src[RIDX(i+9, j+2, dim)];
					dst[RIDX(j+3,  dim-1-(i+9), dim)] = src[RIDX(i+9, j+3, dim)];
					dst[RIDX(j+4,  dim-1-(i+9), dim)] = src[RIDX(i+9, j+4, dim)];
					dst[RIDX(j+5,  dim-1-(i+9), dim)] = src[RIDX(i+9, j+5, dim)];
					dst[RIDX(j+6,  dim-1-(i+9), dim)] = src[RIDX(i+9, j+6, dim)];
					dst[RIDX(j+7,  dim-1-(i+9), dim)] = src[RIDX(i+9, j+7, dim)];
					dst[RIDX(j+8,  dim-1-(i+9), dim)] = src[RIDX(i+9, j+8, dim)];
					dst[RIDX(j+9,  dim-1-(i+9), dim)] = src[RIDX(i+9, j+9, dim)];
					dst[RIDX(j+10, dim-1-(i+9), dim)] = src[RIDX(i+9, j+10, dim)];
					dst[RIDX(j+11, dim-1-(i+9), dim)] = src[RIDX(i+9, j+11, dim)];
					dst[RIDX(j+12, dim-1-(i+9), dim)] = src[RIDX(i+9, j+12, dim)];
					dst[RIDX(j+13, dim-1-(i+9), dim)] = src[RIDX(i+9, j+13, dim)];
					dst[RIDX(j+14, dim-1-(i+9), dim)] = src[RIDX(i+9, j+14, dim)];
					dst[RIDX(j+15, dim-1-(i+9), dim)] = src[RIDX(i+9, j+15, dim)];

					dst[RIDX(j,    dim-1-(i+10), dim)] = src[RIDX(i+10, j,   dim)];
					dst[RIDX(j+1,  dim-1-(i+10), dim)] = src[RIDX(i+10, j+1, dim)];
					dst[RIDX(j+2,  dim-1-(i+10), dim)] = src[RIDX(i+10, j+2, dim)];
					dst[RIDX(j+3,  dim-1-(i+10), dim)] = src[RIDX(i+10, j+3, dim)];
					dst[RIDX(j+4,  dim-1-(i+10), dim)] = src[RIDX(i+10, j+4, dim)];
					dst[RIDX(j+5,  dim-1-(i+10), dim)] = src[RIDX(i+10, j+5, dim)];
					dst[RIDX(j+6,  dim-1-(i+10), dim)] = src[RIDX(i+10, j+6, dim)];
					dst[RIDX(j+7,  dim-1-(i+10), dim)] = src[RIDX(i+10, j+7, dim)];
					dst[RIDX(j+8,  dim-1-(i+10), dim)] = src[RIDX(i+10, j+8, dim)];
					dst[RIDX(j+9,  dim-1-(i+10), dim)] = src[RIDX(i+10, j+9, dim)];
					dst[RIDX(j+10, dim-1-(i+10), dim)] = src[RIDX(i+10, j+10, dim)];
					dst[RIDX(j+11, dim-1-(i+10), dim)] = src[RIDX(i+10, j+11, dim)];
					dst[RIDX(j+12, dim-1-(i+10), dim)] = src[RIDX(i+10, j+12, dim)];
					dst[RIDX(j+13, dim-1-(i+10), dim)] = src[RIDX(i+10, j+13, dim)];
					dst[RIDX(j+14, dim-1-(i+10), dim)] = src[RIDX(i+10, j+14, dim)];
					dst[RIDX(j+15, dim-1-(i+10), dim)] = src[RIDX(i+10, j+15, dim)];

					dst[RIDX(j,    dim-1-(i+11), dim)] = src[RIDX(i+11, j,   dim)];
					dst[RIDX(j+1,  dim-1-(i+11), dim)] = src[RIDX(i+11, j+1, dim)];
					dst[RIDX(j+2,  dim-1-(i+11), dim)] = src[RIDX(i+11, j+2, dim)];
					dst[RIDX(j+3,  dim-1-(i+11), dim)] = src[RIDX(i+11, j+3, dim)];
					dst[RIDX(j+4,  dim-1-(i+11), dim)] = src[RIDX(i+11, j+4, dim)];
					dst[RIDX(j+5,  dim-1-(i+11), dim)] = src[RIDX(i+11, j+5, dim)];
					dst[RIDX(j+6,  dim-1-(i+11), dim)] = src[RIDX(i+11, j+6, dim)];
					dst[RIDX(j+7,  dim-1-(i+11), dim)] = src[RIDX(i+11, j+7, dim)];
					dst[RIDX(j+8,  dim-1-(i+11), dim)] = src[RIDX(i+11, j+8, dim)];
					dst[RIDX(j+9,  dim-1-(i+11), dim)] = src[RIDX(i+11, j+9, dim)];
					dst[RIDX(j+10, dim-1-(i+11), dim)] = src[RIDX(i+11, j+10, dim)];
					dst[RIDX(j+11, dim-1-(i+11), dim)] = src[RIDX(i+11, j+11, dim)];
					dst[RIDX(j+12, dim-1-(i+11), dim)] = src[RIDX(i+11, j+12, dim)];
					dst[RIDX(j+13, dim-1-(i+11), dim)] = src[RIDX(i+11, j+13, dim)];
					dst[RIDX(j+14, dim-1-(i+11), dim)] = src[RIDX(i+11, j+14, dim)];
					dst[RIDX(j+15, dim-1-(i+11), dim)] = src[RIDX(i+11, j+15, dim)];

					dst[RIDX(j,    dim-1-(i+12), dim)] = src[RIDX(i+12, j,   dim)];
					dst[RIDX(j+1,  dim-1-(i+12), dim)] = src[RIDX(i+12, j+1, dim)];
					dst[RIDX(j+2,  dim-1-(i+12), dim)] = src[RIDX(i+12, j+2, dim)];
					dst[RIDX(j+3,  dim-1-(i+12), dim)] = src[RIDX(i+12, j+3, dim)];
					dst[RIDX(j+4,  dim-1-(i+12), dim)] = src[RIDX(i+12, j+4, dim)];
					dst[RIDX(j+5,  dim-1-(i+12), dim)] = src[RIDX(i+12, j+5, dim)];
					dst[RIDX(j+6,  dim-1-(i+12), dim)] = src[RIDX(i+12, j+6, dim)];
					dst[RIDX(j+7,  dim-1-(i+12), dim)] = src[RIDX(i+12, j+7, dim)];
					dst[RIDX(j+8,  dim-1-(i+12), dim)] = src[RIDX(i+12, j+8, dim)];
					dst[RIDX(j+9,  dim-1-(i+12), dim)] = src[RIDX(i+12, j+9, dim)];
					dst[RIDX(j+10, dim-1-(i+12), dim)] = src[RIDX(i+12, j+10, dim)];
					dst[RIDX(j+11, dim-1-(i+12), dim)] = src[RIDX(i+12, j+11, dim)];
					dst[RIDX(j+12, dim-1-(i+12), dim)] = src[RIDX(i+12, j+12, dim)];
					dst[RIDX(j+13, dim-1-(i+12), dim)] = src[RIDX(i+12, j+13, dim)];
					dst[RIDX(j+14, dim-1-(i+12), dim)] = src[RIDX(i+12, j+14, dim)];
					dst[RIDX(j+15, dim-1-(i+12), dim)] = src[RIDX(i+12, j+15, dim)];

					dst[RIDX(j,    dim-1-(i+13), dim)] = src[RIDX(i+13, j,   dim)];
					dst[RIDX(j+1,  dim-1-(i+13), dim)] = src[RIDX(i+13, j+1, dim)];
					dst[RIDX(j+2,  dim-1-(i+13), dim)] = src[RIDX(i+13, j+2, dim)];
					dst[RIDX(j+3,  dim-1-(i+13), dim)] = src[RIDX(i+13, j+3, dim)];
					dst[RIDX(j+4,  dim-1-(i+13), dim)] = src[RIDX(i+13, j+4, dim)];
					dst[RIDX(j+5,  dim-1-(i+13), dim)] = src[RIDX(i+13, j+5, dim)];
					dst[RIDX(j+6,  dim-1-(i+13), dim)] = src[RIDX(i+13, j+6, dim)];
					dst[RIDX(j+7,  dim-1-(i+13), dim)] = src[RIDX(i+13, j+7, dim)];
					dst[RIDX(j+8,  dim-1-(i+13), dim)] = src[RIDX(i+13, j+8, dim)];
					dst[RIDX(j+9,  dim-1-(i+13), dim)] = src[RIDX(i+13, j+9, dim)];
					dst[RIDX(j+10, dim-1-(i+13), dim)] = src[RIDX(i+13, j+10, dim)];
					dst[RIDX(j+11, dim-1-(i+13), dim)] = src[RIDX(i+13, j+11, dim)];
					dst[RIDX(j+12, dim-1-(i+13), dim)] = src[RIDX(i+13, j+12, dim)];
					dst[RIDX(j+13, dim-1-(i+13), dim)] = src[RIDX(i+13, j+13, dim)];
					dst[RIDX(j+14, dim-1-(i+13), dim)] = src[RIDX(i+13, j+14, dim)];
					dst[RIDX(j+15, dim-1-(i+13), dim)] = src[RIDX(i+13, j+15, dim)];

					dst[RIDX(j,    dim-1-(i+14), dim)] = src[RIDX(i+14, j,   dim)];
					dst[RIDX(j+1,  dim-1-(i+14), dim)] = src[RIDX(i+14, j+1, dim)];
					dst[RIDX(j+2,  dim-1-(i+14), dim)] = src[RIDX(i+14, j+2, dim)];
					dst[RIDX(j+3,  dim-1-(i+14), dim)] = src[RIDX(i+14, j+3, dim)];
					dst[RIDX(j+4,  dim-1-(i+14), dim)] = src[RIDX(i+14, j+4, dim)];
					dst[RIDX(j+5,  dim-1-(i+14), dim)] = src[RIDX(i+14, j+5, dim)];
					dst[RIDX(j+6,  dim-1-(i+14), dim)] = src[RIDX(i+14, j+6, dim)];
					dst[RIDX(j+7,  dim-1-(i+14), dim)] = src[RIDX(i+14, j+7, dim)];
					dst[RIDX(j+8,  dim-1-(i+14), dim)] = src[RIDX(i+14, j+8, dim)];
					dst[RIDX(j+9,  dim-1-(i+14), dim)] = src[RIDX(i+14, j+9, dim)];
					dst[RIDX(j+10, dim-1-(i+14), dim)] = src[RIDX(i+14, j+10, dim)];
					dst[RIDX(j+11, dim-1-(i+14), dim)] = src[RIDX(i+14, j+11, dim)];
					dst[RIDX(j+12, dim-1-(i+14), dim)] = src[RIDX(i+14, j+12, dim)];
					dst[RIDX(j+13, dim-1-(i+14), dim)] = src[RIDX(i+14, j+13, dim)];
					dst[RIDX(j+14, dim-1-(i+14), dim)] = src[RIDX(i+14, j+14, dim)];
					dst[RIDX(j+15, dim-1-(i+14), dim)] = src[RIDX(i+14, j+15, dim)];

					dst[RIDX(j,    dim-1-(i+15), dim)] = src[RIDX(i+15, j,   dim)];
					dst[RIDX(j+1,  dim-1-(i+15), dim)] = src[RIDX(i+15, j+1, dim)];
					dst[RIDX(j+2,  dim-1-(i+15), dim)] = src[RIDX(i+15, j+2, dim)];
					dst[RIDX(j+3,  dim-1-(i+15), dim)] = src[RIDX(i+15, j+3, dim)];
					dst[RIDX(j+4,  dim-1-(i+15), dim)] = src[RIDX(i+15, j+4, dim)];
					dst[RIDX(j+5,  dim-1-(i+15), dim)] = src[RIDX(i+15, j+5, dim)];
					dst[RIDX(j+6,  dim-1-(i+15), dim)] = src[RIDX(i+15, j+6, dim)];
					dst[RIDX(j+7,  dim-1-(i+15), dim)] = src[RIDX(i+15, j+7, dim)];
					dst[RIDX(j+8,  dim-1-(i+15), dim)] = src[RIDX(i+15, j+8, dim)];
					dst[RIDX(j+9,  dim-1-(i+15), dim)] = src[RIDX(i+15, j+9, dim)];
					dst[RIDX(j+10, dim-1-(i+15), dim)] = src[RIDX(i+15, j+10, dim)];
					dst[RIDX(j+11, dim-1-(i+15), dim)] = src[RIDX(i+15, j+11, dim)];
					dst[RIDX(j+12, dim-1-(i+15), dim)] = src[RIDX(i+15, j+12, dim)];
					dst[RIDX(j+13, dim-1-(i+15), dim)] = src[RIDX(i+15, j+13, dim)];
					dst[RIDX(j+14, dim-1-(i+15), dim)] = src[RIDX(i+15, j+14, dim)];
					dst[RIDX(j+15, dim-1-(i+15), dim)] = src[RIDX(i+15, j+15, dim)];
				}
			}
    	}
    }
}

/*
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *src, pixel *dst) 
{
	rotate_block32_8x8(dim, src, dst);
}

/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_rotate_functions() 
{
//    add_rotate_function(&naive_rotate, naive_rotate_descr);
//    add_rotate_function(&rotate_ptr, rotate_ptr_descr);
//    add_rotate_function(&rotate_2, rotate_2_descr);
//    add_rotate_function(&rotate_2x2, rotate_2x2_descr);
//    add_rotate_function(&rotate_2x2_ptr, rotate_2x2_ptr_descr);
//    add_rotate_function(&rotate_4, rotate_4_descr);
//    add_rotate_function(&rotate_4x4, rotate_4x4_descr);
//    add_rotate_function(&rotate_8x8, rotate_8x8_descr);
//    add_rotate_function(&rotate_16x16, rotate_16x16_descr);
//    add_rotate_function(&rotate_block32_4x4, rotate_block32_4x4_descr);
//    add_rotate_function(&rotate_block32_8x8, rotate_block32_8x8_descr);
//    add_rotate_function(&rotate_block32_16x16, rotate_block32_16x16_descr);
}


/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
  int red;
  int green;
  int blue;
  int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum) 
{
  sum->red = sum->green = sum->blue = 0;
  sum->num = 0;
  return;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_sum(pixel_sum *sum, pixel p) 
{
  sum->red   += (int) p.red;
  sum->green += (int) p.green;
  sum->blue  += (int) p.blue;
  sum->num++;
  return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
  current_pixel->red   = (unsigned char) (sum.red/sum.num);
  current_pixel->green = (unsigned char) (sum.green/sum.num);
  current_pixel->blue  = (unsigned char) (sum.blue/sum.num);
  return;
}

/* 
 * avg - Returns averaged pixel value at (i,j) 
 */
static pixel avg(int dim, int i, int j, pixel *src) 
{
    int ii, jj;
    pixel_sum sum;
    pixel current_pixel;
    
    initialize_pixel_sum(&sum);
    for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) {
        for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) {
            accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);
            // "weighted" averge: add (i,j) pixel to sum twice
            if(ii == i && jj == j) {
                accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);
            }
        }
    }
    
    assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}

/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth 
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst) 
{
  int i, j;
  
  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
}

/*
 * smooth_2x2
 */
char smooth_2x2_descr[] = "smooth_2x2: Unroll both by 2";
void smooth_2x2(int dim, pixel *src, pixel *dst)
{
    int i, j;
    int outer_limit = dim - 1;
    int inner_limit = dim - 1;
    
    for (i = 0; i < outer_limit; i += 2) {
        for (j = 0; j < inner_limit; j += 2) {
            dst[RIDX(i, j,   dim)] = avg(dim, i, j,   src);
            dst[RIDX(i, j+1, dim)] = avg(dim, i, j+1, src);
            
            dst[RIDX(i+1, j,   dim)] = avg(dim, i+1, j,   src);
            dst[RIDX(i+1, j+1, dim)] = avg(dim, i+1, j+1, src);
        }
    }
}

/*
 * smooth_4x4
 */
char smooth_4x4_descr[] = "smooth_4x4: Unroll both by 4";
void smooth_4x4(int dim, pixel *src, pixel *dst)
{
    int i, j;
    int outer_limit = dim - 3;
    int inner_limit = dim - 3;
    
    for (i = 0; i < outer_limit; i += 4) {
        for (j = 0; j < inner_limit; j += 4) {
            dst[RIDX(i, j,   dim)] = avg(dim, i, j,   src);
            dst[RIDX(i, j+1, dim)] = avg(dim, i, j+1, src);
            dst[RIDX(i, j+2, dim)] = avg(dim, i, j+2, src);
            dst[RIDX(i, j+3, dim)] = avg(dim, i, j+3, src);
            
            dst[RIDX(i+1, j,   dim)] = avg(dim, i+1, j,   src);
            dst[RIDX(i+1, j+1, dim)] = avg(dim, i+1, j+1, src);
            dst[RIDX(i+1, j+2, dim)] = avg(dim, i+1, j+2, src);
            dst[RIDX(i+1, j+3, dim)] = avg(dim, i+1, j+3, src);
            
            dst[RIDX(i+2, j,   dim)] = avg(dim, i+2, j,   src);
            dst[RIDX(i+2, j+1, dim)] = avg(dim, i+2, j+1, src);
            dst[RIDX(i+2, j+2, dim)] = avg(dim, i+2, j+2, src);
            dst[RIDX(i+2, j+3, dim)] = avg(dim, i+2, j+3, src);
            
            dst[RIDX(i+3, j,   dim)] = avg(dim, i+3, j,   src);
            dst[RIDX(i+3, j+1, dim)] = avg(dim, i+3, j+1, src);
            dst[RIDX(i+3, j+2, dim)] = avg(dim, i+3, j+2, src);
            dst[RIDX(i+3, j+3, dim)] = avg(dim, i+3, j+3, src);
        }
    }
}

/*
 * smooth_block32_2x2
 */
char smooth_block32_2x2_descr[] = "smooth_block32_2x2: Block by 32 and unroll both by 2";
void smooth_block32_2x2(int dim, pixel *src, pixel *dst)
{
    int i_0, j_0, i, j;
    int outer_limit = dim - 1;
    int block_limit = 32;
    
    for (i_0 = 0; i_0 < outer_limit; i_0 += block_limit) {
        for (j_0 = 0; j_0 < outer_limit; j_0 += block_limit) {
            for (i = i_0; i < i_0 + block_limit; i += 2) {
                for (j = j_0; j < j_0 + block_limit; j += 2) {
                    dst[RIDX(i, j,   dim)] = avg(dim, i, j,   src);
                    dst[RIDX(i, j+1, dim)] = avg(dim, i, j+1, src);
            
                    dst[RIDX(i+1, j,   dim)] = avg(dim, i+1, j,   src);
                    dst[RIDX(i+1, j+1, dim)] = avg(dim, i+1, j+1, src);
                }
            }
        }
    }
}

/*
 * smooth - Your current working version of smooth. 
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "smooth: Current working version";
void smooth(int dim, pixel *src, pixel *dst) 
{
    smooth_block32_2x2(dim, src, dst);
}


/********************************************************************* 
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_smooth_functions() {
//    add_smooth_function(&naive_smooth, naive_smooth_descr);
//    add_smooth_function(&smooth_2x2, smooth_2x2_descr);
//    add_smooth_function(&smooth_4x4, smooth_4x4_descr);
//    add_smooth_function(&smooth_block32_2x2, smooth_block32_2x2_descr);
}

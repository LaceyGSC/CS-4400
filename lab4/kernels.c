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
 * ...
 */
char no_multiply_rotate_descr[] = "no_multiply_rotate: ...";
void no_multiply_rotate(int dim, pixel *src, pixel *dst)
{
	unsigned int src_length = dim * dim;
	int src_index = 0;
	int dst_index = dim - 1;
	int dst_start = dst_index;
	pixel src_value;

	if (src_length > dim) {
		for (; src_index < src_length; src_index++) {
			src_value = src[src_index];
			dst[dst_index] = src_value;
			dst_index += dim;
			if (dst_index >= src_length) {
				dst_start -= 1;
				dst_index = dst_start;
			}
		}
	} else {
		printf("%s", "overflow...");
	}
}

/* 
 * ...
 */
char no_multiply_rotate_unroll2_descr[] = "no_multiply_rotate_unroll2: ...";
void no_multiply_rotate_unroll2(int dim, pixel *src, pixel *dst)
{
	unsigned int src_length = dim * dim;
	unsigned int src_index = 0;
	unsigned int dst_index = dim - 1;
	unsigned int dst_start = dst_index;
	
	unsigned int limit = src_length - 1;
	pixel src_value0;
	pixel src_value1;

	if (src_length > dim) {
		for (; src_index < limit; src_index += 2) {
			src_value0 = src[src_index];
			src_value1 = src[src_index + 1];
			dst[dst_index]       = src_value0;
			dst[dst_index + dim] = src_value1;
			dst_index += dim + dim;
			if (dst_index >= src_length) {
				dst_start -= 1;
				dst_index = dst_start;
			}
		}
	} else {
		printf("%s", "overflow...");
	}
	
	if (src_length > dim) {
		for (; src_index < src_length; src_index++) {
			src_value0 = src[src_index];
			dst[dst_index] = src_value0;
			dst_index += dim;
			if (dst_index >= src_length) {
				dst_start -= 1;
				dst_index = dst_start;
			}
		}
	} else {
		printf("%s", "overflow...");
	}
}

/*
 * ...
 */
char no_multiply_rotate_unroll3_descr[] = "no_multiply_rotate_unroll3: ...";
void no_multiply_rotate_unroll3(int dim, pixel *src, pixel *dst)
{
    unsigned int src_length = dim * dim;
    unsigned int src_index = 0;
    unsigned int dst_index = dim - 1;
    unsigned int dst_start = dst_index;
    
    unsigned int limit = src_length - 2;
    pixel src_value0;
    pixel src_value1;
    pixel src_value2;
    
    if (src_length > dim) {
        for (; src_index < limit; src_index += 3) {
            src_value0 = src[src_index];
            src_value1 = src[src_index + 1];
            src_value2 = src[src_index + 2];
            dst[dst_index]             = src_value0;
            dst[dst_index + dim]       = src_value1; // WYLO .... This line has the bug. After one loop, dst_index + dim is past src_length. How to solve this?
            dst[dst_index + dim + dim] = src_value2;
            dst_index += dim + dim + dim;
            if (dst_index >= src_length) {
                dst_start -= 1;
                dst_index = dst_start;
            }
        }
    } else {
        printf("%s", "overflow...");
    }
    
    if (src_length > dim) {
        for (; src_index < src_length; src_index++) {
            src_value0 = src[src_index];
            dst[dst_index] = src_value0;
            dst_index += dim;
            if (dst_index >= src_length) {
                dst_start -= 1;
                dst_index = dst_start;
            }
        }
    } else {
        printf("%s", "overflow...");
    }
}

/*
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *src, pixel *dst) 
{
	no_multiply_rotate(dim, src, dst);
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
  add_rotate_function(&naive_rotate,               naive_rotate_descr);
  add_rotate_function(&no_multiply_rotate,         no_multiply_rotate_descr);
  add_rotate_function(&no_multiply_rotate_unroll2, no_multiply_rotate_unroll2_descr);
  add_rotate_function(&no_multiply_rotate_unroll3, no_multiply_rotate_unroll3_descr);
  /* ... Register additional test functions here */
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
  sum->red += (int) p.red;
  sum->green += (int) p.green;
  sum->blue += (int) p.blue;
  sum->num++;
  return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
  current_pixel->red = (unsigned char) (sum.red/sum.num);
  current_pixel->green = (unsigned char) (sum.green/sum.num);
  current_pixel->blue = (unsigned char) (sum.blue/sum.num);
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
  for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) 
    for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) {
      accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);
      // "weighted" averge: add (i,j) pixel to sum twice
      if(ii == i && jj == j)
	accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);
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
 * smooth - Your current working version of smooth. 
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "smooth: Current working version";
void smooth(int dim, pixel *src, pixel *dst) 
{
  naive_smooth(dim, src, dst);
}


/********************************************************************* 
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_smooth_functions() {
//  add_smooth_function(&smooth, smooth_descr);
//  add_smooth_function(&naive_smooth, naive_smooth_descr);
  /* ... Register additional test functions here */
}

#include <stdio.h>

typedef enum {MODE_A, MODE_B, MODE_C, MODE_D, MODE_E} mode_t;

int add(int x, int y)
{
	printf("Adding numbers %d and %d\n", x, y);
	return x + y;
}

int switch3(int *p1, int *p2, mode_t action)
{
	int result = 0;
	switch (action) {
	case MODE_A:
		result = *p1;
		*p1 = *p2;
		break;
	case MODE_B:
		result  = *p2;
		result += *p1;
		*p2 = result;
		break;
	case MODE_C:
		*p2 = 15;
		result = *p1;
		break;
	case MODE_D:
		*p2 = *p1;
	case MODE_E:
		result = 17;
	}
	return result;
}

int loop(int x, int n)
{
	int z = add(3, 5);

	int result = -1;
	int mask;
	for (mask = 1; mask != 0; mask = mask << n) {
		result ^= mask & x;
	}
	return result;
}

#define M 13
typedef int Marray_t[M][M];

void transpose(Marray_t A)
{
	int j;
	int *col = &A[0][0];
	int *row = &A[1][0];
	for (j = 1; j < M; j++) {
		int t = *row;
		*row = col[j];
		col[j] = t;
		row += M;
	}
}

void psum2way(float a[], float p[], long int n)
{
	long int i;
	int limit = n - 1;
	float last_val, val;
	int i_1 = 1;
	last_val = p[0] = a[0];
	for (i = 1; i < limit; i += 2) {
		i_1 = i + 1;
		int a_i   = a[i];
		int a_i_1 = a[i_1];
		p[i] = last_val + a_i;
		val = last_val + (a_i + a_i_1);
		p[i_1] = val;
		last_val = val;
	}

	for (; i < n; i++) {
		val  = last_val + a[i];
		p[i] = val;
		last_val = val;
	}
}

void psum3way(float a[], float p[], long int n)
{
	long int i;
	int limit = n - 2;
	float last_val, val;
	int i_1 = 1;
	int i_2 = 2;
	last_val = p[0] = a[0];
	for (i = 1; i < limit; i += 3) {
		i_1 = i + 1;
		i_2 = i + 2;
		int a_i   = a[i];
		int a_i_1 = a[i_1];
		int a_i_2 = a[i_2];
		p[i] = last_val + a_i;
		val = last_val + (a_i + a_i_1);
		p[i_1] = val;
		val = last_val + (a_i + (a_i_1 + a_i_2));
		p[i_2] = val;
		last_val = val;
	}

	for (; i < n; i++) {
		val  = last_val + a[i];
		p[i] = val;
		last_val = val;
	}
}

int main()
{
	char a = (char) 0x40;
	char b = (char) 0x23;
	char c = (char) 0xa8;
	printf("a is: %c\n", a);
	printf("b is: %c\n", b);
	printf("c is: %c\n", c);
	return 0;
}

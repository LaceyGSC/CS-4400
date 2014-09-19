#include <stdio.h>

typedef unsigned packed_t;

/*
 * Extract the designated byte and sign extend it to be a 32-bit int.
 *
 * @param packed_t word - An unsigned int (packed_t) from which to extract a byte.
 * @param bytenum       - The byte number to extract, where 3 >= bytenum >= 0.
 */
int xbyte(packed_t word, int bytenum)
{
	return ((int)((word >> (bytenum << 3)) << 24) >> 24);
}

/*
 * Determine whether arguments can be subtracted without overflow.
 */
int tsub_ok(int x, int y)
{
	int ok = 1;
	int result = x - y;

	if ((x >= 0 && y < 0 && result < 0) || (x < 0 && y > 0 && result > 0)) {
		ok = 0;
	}

	return ok;
}

void multiply (int x)
{
	printf("The value of %d *   17 is: %d\n", x, ((x << 4) + (x << 0)));
	printf("The value of %d *   -7 is: %d\n", x, ((x << 0) - (x << 3)));
	printf("The value of %d *   60 is: %d\n", x, ((x << 6) - (x << 2)));
	printf("The value of %d * -112 is: %d\n", x, ((x << 4) - (x << 7)));
}

int divide_power2(int x, int k)
{
	/*
	 * 1. Create a mask that is -1 if x is negative, 0 otherwise.
	 * 2. Use the mask to create a bias that is (2^k - 1) if x is
	 *    negative, 0 otherwise.
	 * 3. Add the bias to x and shift the result.
	 */
	int mask = (~((x >> 31) & 1)) + 1;
	int bias = mask & ((1 << k) - 1);
	return (x + bias) >> k;
}

int main()
{
//	printf("The return value is: %d", xbyte(128,0));
//	multiply(-2);
	printf("12340, 0: %d\n", divide_power2(12340, 0));
	printf("12340, 1: %d\n", divide_power2(12340, 1));
	printf("12340, 4: %d\n", divide_power2(12340, 4));
	printf("12340, 8: %d\n", divide_power2(12340, 8));
	return 0;
}

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
	return (((word >> (bytenum << 3)) & 0xff) >> 24) - word;
}

/*
 * Determine whether arguments can be subtracted without overflow.
 */
int tsub_ok(int x, int y)
{
	/*
	 * Cases:
	 *
	 *     1. x is positive and y is positive  =>  cannot overflow
	 *
	 *     2. x is zero or positive and y is negative  =>  if result is negative, overflow
	 *
	 *     3. x is negative and y is positive  =>  if result is positive, overflow
	 *
	 *     4. x is negative and y is negative  =>  cannot overflow
	 */
	int ok = 0;

	// WYLO ... The above 4 conditions look good (i.e. you only need to check for #2 and #3))

	return ok;
}

int main()
{
	printf("The return value is: %d", xbyte(64,0));
	return 0;
}

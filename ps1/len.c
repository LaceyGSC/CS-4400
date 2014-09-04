#include <stdio.h>
#include <stddef.h>
#include <limits.h>

int string_length(char *string)
{
	int length = 0;

	for (; *string != '\0'; string++) {
		length++;
	}

	return length;
}

int int_shifts_are_arithmetic()
{
	int test = -1;
	test >>= 1;
	return test == -1;
}

int what()
{
	return !-1;
}

int main()
{
//	printf("The length of \"Hello, world!\" is %d\n", string_length("Hello, world!"));
//	printf("The length of \"5\" is %d\n", string_length("5"));
//	printf("The length of \"\" is %d\n", string_length(""));
//	printf("The length of \"CS 4400 Student\" is %d\n", string_length("CS 4400 Student"));
//	printf("The length of \"Go Utes!\" is %d\n", string_length("Go Utes!"));

	// Any bit of x equals 1
	int x = 0;
	int result = x && 1;
//	printf("The result is %d\n", result);

	// Any bit of x equals 0
	x = INT_MAX - 1;
	result = (x ^ INT_MAX) && 1;
//	printf("The result is %d\n", result);

	// Any bit in the least significant byte of x equals 1:
	x = 570564672;
	result = (x & 0xff) && 1;
//	printf("The result is %d\n", result);

	// Any bit in the most significant byte of x equals 0:
//	x = INT_MAX;
	x = -16777216;
//	result = ((x & 0xff000000) ^ 0xff000000) && 1;
	result = (((x >> ((sizeof(int) - 1) << 3)) & 0xff) ^ 0xff) && 1;
//	printf("The result is %d\n", result);

	if (int_shifts_are_arithmetic()) {
//		printf("int shifts on this machine are arithmetic");
	} else {
//		printf("int shifts on this machine are *NOT* arithmetic");
	}

	printf("The result is %d\n", what());

	return 0;
}

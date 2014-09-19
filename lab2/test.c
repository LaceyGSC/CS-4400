#include <stdio.h>

int add(int x, int y)
{
	printf("Adding numbers %d and %d\n", x, y);
	return x + y;
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

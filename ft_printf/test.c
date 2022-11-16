#include <stdio.h>

int main()
{
	int num;
	num = 1;
	printf("%c %d %x %p %s", '\0', -13, 0, &num, 0);
	return (0);
}
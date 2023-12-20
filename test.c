#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
// test behavior if I use read 2 times
void test (int fd)
{
	char *test;
	static char *test2;

	test = malloc(5000);
	read(fd, test, 5000);
	test2 = test;
	printf("111 %s\n", test);
}

int main(void) 
{
	int fd;
	fd = open("test.txt", O_RDONLY);
	test(fd);
	test(fd);
	return (0);
}

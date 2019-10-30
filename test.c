
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(int ac, char **av)
{
	printf("Bonjour !\n");
	(void) ac;
	(void) av;
	printf("BUFFER_SIZE = %d\n", BUFFER_SIZE);	
	int fd = open("testfile", O_RDONLY);
	int fd1 = open("testfile1", O_RDONLY);
	printf("FILE FD : %d\n\n", fd);
	int returned;
	char *str;
	(void) returned;

	int i = 10;

	while (i--)
	{
		returned = get_next_line(fd, &str);
		printf("returned : %d  line : \"%s\"\n", returned, str);
	}
	i = 20;
	while (i--)
	{
		returned = get_next_line(fd1, &str);
		printf("returned : %d  line : \"%s\"\n", returned, str);
	}
	i = 30;
	while (i--)
	{
		returned = get_next_line(fd, &str);
		printf("returned : %d  line : \"%s\"\n", returned, str);
	}

}
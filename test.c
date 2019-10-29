
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(int ac, char **av)
{
	printf("Bonjour !\n");
	(void) ac;
	printf("BUFFER_SIZE = %d\n", BUFFER_SIZE);	
	int fd = open(av[1], O_RDONLY);
	printf("FILE FD : %d\n\n", fd);
	int returned;
	char *str;
	(void) returned;
	returned = get_next_line(fd, &str);
	printf("1rst line : \"%s\"	returned : %d\n",str, returned);

	returned = get_next_line(fd, &str);
	printf("2nd line : \"%s\"	returned : %d\n",str, returned);
	returned = get_next_line(fd, &str);
	printf("3rd line : \"%s\"	returned : %d\n",str, returned);
	returned = get_next_line(fd, &str);
	printf("4th line : \"%s\"	returned : %d\n",str, returned);
	returned = get_next_line(fd, &str);
	printf("5th line : \"%s\"	returned : %d\n",str, returned);
	returned = get_next_line(fd, &str);
	printf("6th line : \"%s\"	returned : %d\n",str, returned);
}
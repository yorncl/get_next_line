
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"

int main()
{
	printf("Bonjour !\n");

	printf("BUFFER_SIZE = %d\n", BUFFER_SIZE);	
	int fd1 = open("testfile", O_RDONLY);
//	int fd2 = open("testfile", O_RDONLY);
	int returned;
	char *str;
	returned = get_next_line(fd1, &str);
	//returned = get_next_line(fd2, &str);
	//returned = get_next_line(fd1, &str);
	(void) returned;
	// printf("1rst line : \"%s\"	returned : %d\n",str, returned);
	// returned = get_next_line(fd, &str);
	// printf("2nd line : \"%s\"	returned : %d\n",str, returned);
	// returned = get_next_line(fd, &str);
	// printf("3rd line : \"%s\"	returned : %d\n",str, returned);
	// returned = get_next_line(fd, &str);
	// printf("4th line : \"%s\"	returned : %d\n",str, returned);
	// returned = get_next_line(fd, &str);
	// printf("5th line : \"%s\"	returned : %d\n",str, returned);
	// returned = get_next_line(fd, &str);
	// printf("6th line : \"%s\"	returned : %d\n",str, returned);
}
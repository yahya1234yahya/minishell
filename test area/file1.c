#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


int	main(void)
{
	int	fd2;
	int fd;
	
	fd = open("file1.c", O_RDONLY);
	fd2 = open("file2", O_RDONLY);
	printf("file 1fd = %d\n", fd);
	printf("file 2fd = %d\n", fd2);
	printf("\n\ndup2\n\n");
	dup2(fd, fd2);
	printf("file 1fd = %d\n", fd);
	printf("file 2fd = %d\n", fd2);

	return (0);
}
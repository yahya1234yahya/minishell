#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


int	main(void)
{
	int	fd2;
	int fd;

	fd = open("file1.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	fd2 = open("file2.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	

	dup2(fd, fd2);

	write(fd, "fd", 2);
	write(fd2, "fd2", 3);

	return (0);
}
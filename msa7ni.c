#include <libc.h>


int	main(void)
{
	int fd = open("HELLO", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	int holder = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	write(1, "in file", 7);
	dup2(holder, STDOUT_FILENO);
	write(1, "in stdout", 9);
	close(holder);
	return (0);
}
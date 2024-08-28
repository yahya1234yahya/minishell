#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int	main(void)
{
	char **s;
	s = malloc(sizeof(char *) * 2);
	s[0] = "/bin/ls";
	s[1] = NULL;
	execve(s[0], s, NULL);

	return (0);
}
#include <stdio.h>
#include <unistd.h>
#include <libc.h>
#include <stdlib.h>


int	main(int ac, char **av, char **env)
{
	char *path = "/bin/ls";
    char *arguments[] = { "ls", "/", NULL};
	int pid = fork();
	if(pid == 0)
	{
		printf("---> %d<---\n", execve(path, arguments, env));

	}
}
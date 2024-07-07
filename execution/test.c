#include <unistd.h>
#include <stdio.h>
#include <libc.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	char *str[] = {"ls", "-l", NULL};
	int pid = fork();

	if (pid != 0)
	{
		int status;
		wait(&status);
		sleep(1);
	}
	else
	{
		execvp(str[0],str);

	}
	return 0;
}

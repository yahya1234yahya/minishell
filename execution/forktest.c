#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	pid_t pid;

	//fork creates a child process of a process the parent has it's unique pid
	//and the child has pid 0 if fork return -1 than fork failled

	pid = fork();
	if (pid == -1)
	{
		//error
	}
	printf("Hello World\n");
	if (pid == 0)
	{
		printf("TEST\n");
	}
	
	return 0;
}

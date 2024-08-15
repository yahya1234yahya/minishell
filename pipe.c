#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char* strjoin(const char* str1, const char* str2)
{
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	char* result = malloc(len1 + len2 + 1); // +1 for the null terminator
	if (result == NULL) {
		perror("malloc");
		exit(1);
	}
	strcpy(result, str1);
	strcat(result, str2);
	return result;
};

void child_process(int pipefd[2], char* command)
{
	close(pipefd[1]); // Close the write end of the pipe

	// Redirect the input from the pipe
	dup2(pipefd[0], STDIN_FILENO);
	// Execute the command using exec
	execlp(command, command, NULL);

	// If exec fails, print an error message
	perror("exec");
	exit(1);
}

void parent_process(int pipefd[2], char* command)
{
	close(pipefd[0]); // Close the read end of the pipe

	// Redirect the output to the command
	dup2(pipefd[1], STDOUT_FILENO);

	// Execute the command using exec
	execlp(command, command, NULL);

	// If exec fails, print an error message
	perror("exec");
	exit(1);
}


int main(int argc, char* argv[])
{
	pid_t pid;
	int pipefd[2];

	if (argc < 3)
	{
		printf("Usage: %s <command1>  <command2>\n", argv[0]);
		return -1;
	}
	pipe(pipefd);
	pid = fork();
	char *cmd1 = strjoin("/bin/", argv[1]);
	char *cmd2 = strjoin("/bin/", argv[2]);
	if (pid == 0)
		child_process(pipefd, cmd2);
	else
		parent_process(pipefd, cmd1);

	return 0;
}

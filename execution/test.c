// #include <unistd.h>
// #include <stdio.h>
// #include <libc.h>
// #include <sys/wait.h>



// int main(int argc, char const *argv[], char **envp)
// {
	
// 	int i = 0;

// 	while (envp[i])
// 	{
// 		if (ft_strstr(envp[i], "PWD"))
// 			break ;
// 		i++;
// 	}
// 	char *str;
// 	str = ft_strstr(envp[i], "PWD");
// 	i = 4;
// 	while (str[i])
// 	{
// 		write(1, &str[i], 1);
// 		i++;
// 	}
// 	write(1, "\n", 1);
	
// 	// char *str[] = {"ls", "-l", NULL};
// 	// int pid = fork();

// 	// if (pid != 0)
// 	// {
// 	// 	wait(NULL);
// 	// }
// 	// else
// 	// {
// 	// 	if (execvp(str[0],str) == -1)
// 	// 	{
// 	// 		printf("Command doesn't exists or error happened in execvp\n");
// 	// 		exit(1);
// 	// 	}

// 	// }
// 	return 0;
// }

#include "../minishell.h"

int	calculateargs(t_cmd *cmd)
{
	char **args;
	int i;
	int j;
	
	args = ft_split(cmd->args, ' ');
	i = 1;
	while (args[i])
		i++;
	j = i;
	while (j != 0)
	{
		free(args[j]);
		j--;
	}
	free(args);
	return (i);
};


static char **prepend_array(char **original, char *new_element)
{
    int i;
    int original_size = 0;

    while (original[original_size] != NULL) {
        original_size++;
    }
    char **new_array = (char **)malloc(sizeof(char *) * (original_size + 2));
    new_array[0] = (char *)malloc(strlen(new_element) + 1);
    strcpy(new_array[0], new_element);
    for (i = 0; i < original_size; i++) {
        new_array[i + 1] = original[i];
    }
    new_array[original_size + 1] = NULL;

    return (new_array);
};

void notbuilt(t_cmd *cmd)
{
	int i;
	int pid;
	char **fixed;
	char **splited;



	if (cmd->args != NULL)
	{
		i = calculateargs(cmd);
		fixed = (char **)malloc(sizeof(char *) * (i + 2));
		splited = ft_split(cmd->args, ' ');
		fixed = prepend_array(splited, ft_strjoin("/bin/", cmd->cmd));
		if (access(fixed[0], X_OK) == 0)
		{
			pid = fork();
			if (pid == 0)
				execve(fixed[0], fixed, NULL);
			else
			{
				int status;
				wait(&status);
			}
		}
	}
	else
	{
		fixed = (char **)malloc(sizeof(char *) * 2);
		fixed[0] = ft_strjoin("/bin/", cmd->cmd);
		fixed[1] = NULL;
		if (access(fixed[0], X_OK) == 0)
		{
			pid = fork();
			if (pid == 0)
				execve(fixed[0], fixed, NULL);
			else
			{
				int status;
				wait(&status);
			}
		}
	}
}

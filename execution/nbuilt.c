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

char	**convert(t_cmd *cmd)
{
	t_env *tmp;
	char **ret;
	int i;
	int j;

	i = 0;
	tmp = cmd->env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	};
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	j = 0;
	tmp = cmd->env;
	while (j < i)
	{
		ret[j] = tmp->name;
		j++;
		tmp = tmp->next;
	};
	ret[j] = NULL;
	return (ret);
};


char **prepend_array(char **original, char *new_element)
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
}

void	notbuilt(t_cmd *cmd, char **envp)
{
	int i;
	char **fixed;
	char **splited;

	if (cmd->args)
		args(cmd, envp, i, fixed, splited);
	else
		noargs(cmd, envp, fixed, splited);
};





















// void notbuilt(t_cmd *cmd, char **envp)
// {
// 	int i;
// 	int pid;
// 	char **fixed;
// 	char **splited;
// 	char **envvv = convert(cmd);

// 	if (cmd->args != NULL)
// 	{
// 		i = calculateargs(cmd);
// 		fixed = (char **)malloc(sizeof(char *) * (i + 2));
// 		splited = ft_split(cmd->args, ' ');
// 		fixed = prepend_array(splited, cmd->path);
// 		if (access(fixed[0], X_OK) == 0)
// 		{
// 			pid = fork();
// 			if (pid == 0)
// 			{
// 				if (cmd->redirection == 2)
//                 {
//                     dup2(cmd->fd_redirect, STDOUT_FILENO);
//                     close(cmd->fd_redirect);
//                 }
// 				execve(fixed[0], fixed, envvv);
// 			}
// 			else
// 			{
// 				int status;
// 				wait(&status);
// 			}
// 		}
// 	}
// 	else
// 	{
// 		fixed = (char **)malloc(sizeof(char *) * 2);
// 		fixed[0] = cmd->path;
// 		fixed[1] = NULL;
// 		if (access(fixed[0],F_OK | X_OK) == 0)
// 		{
// 			pid = fork();
// 			if (pid == 0)
// 			{
// 				if (cmd->redirection == 2)
//                 {
//                     dup2(cmd->fd_redirect, 1);
//                     close(cmd->fd_redirect);
//                 }
// 				execve(fixed[0], fixed, envvv);
// 				if (execve(fixed[0], fixed, envvv) == -1)
// 					perror("execve");
// 			}
// 			else
// 			{
// 				int status;
// 				wait(&status);
// 			}
// 		}
// 	}
// };

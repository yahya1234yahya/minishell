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

void notbuilt(t_cmd *cmd)
{
	int i;
	int j;
	char *fixed;

	i = calculateargs(cmd);
	fixed = (char *)malloc(sizeof(char *) * (i + 2));
	fixed[0] = cmd->cmd;
	j = 1;
	while (j < i + 1)
	{
		strcpy(fixed[j], cmd->args[j + 1]);
	}
	
}
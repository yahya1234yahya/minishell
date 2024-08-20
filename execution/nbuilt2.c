/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbuilt2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 03:18:44 by mboughra          #+#    #+#             */
/*   Updated: 2024/08/01 03:27:06 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void helperfunction(t_cmd **cmd, char ***fixed,char ***splited)
{
	int		i;
	char	*command;

	if ((*cmd)->args)
	{
		command = ft_strjoin((*cmd)->cmd, " ");
		command = ft_strjoin(command, (*cmd)->args);
		(*splited) = ft_split(command, ' ');
		int r = 0;
		while (splited[r])
		{
			printf("splited[%d] = %s\n", r, (*splited)[r]);
			r++;
		}
		exit(1);
		// *splited = ft_split((*cmd)->args, ' ');
		// i = 0;

		// while (splited[i])
		// 	printf("splited[%d] = %s\n", i, (*splited)[i++]);
		
		// exit(1);
		// while (splited[i])
		// 	i++;
		// *fixed = (char **)malloc(sizeof(char *) * (i + 2));
		// *fixed = prepend_array(*splited, (*cmd)->path);
		// // for (size_t r = 0; r < i; r++)
		// {
		// 	printf("fixed[%d] = %s\n", r, (*fixed)[r]);
		// }
	}else
	{
		*fixed = (char **)malloc(sizeof(char *) * 2);
		(*fixed)[0] = (*cmd)->path;
		(*fixed)[1] = NULL;
	};
}
void execfromsystem(t_cmd *cmd, char **envp)
{
	int pid;
	char **splited;
	char *command;

	if (cmd->args)
	{	
		command = ft_strjoin(cmd->path, " ");
		command = ft_strjoin(command, cmd->args);
		splited = ft_split(command, ' ');
	}else
	{
		splited = (char **)malloc(sizeof(char *) * 2);
		splited[0] = cmd->path;
		splited[1] = NULL;
	}
	// helperfunction(&cmd, &fixed, &splited);
	if (access(splited[0], X_OK | F_OK) == 0)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		if (pid == 0)
		{
			if (execve(splited[0], splited, envp) == -1)
				perror("execve");
		}
		else
			waitpid(pid, NULL, 0);
	}
}

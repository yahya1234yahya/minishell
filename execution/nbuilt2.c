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

void args(t_cmd *cmd, char **envp, int i, char **fixed, char **splited)
{
	int pid;
	char **env;
	int status;

	i = calculateargs(cmd);
	fixed = (char **)malloc(sizeof(char *) * (i + 2));
	splited = ft_split(cmd->args, ' ');
	fixed = prepend_array(splited, cmd->path);
	if (access(fixed[0], X_OK | F_OK) == 0)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return ;
		}
		if (pid == 0)
		{
			if (execve(fixed[0], fixed, envp) == -1)
				perror("execve");
		}
		else
			wait(&status);
	}
};

void noargs(t_cmd *cmd, char **envp, char **fixed, char **splited)
{
	int status;
	int pid;
	char **env;
	
	fixed = (char **)malloc(sizeof(char *) * 2);
	if (cmd->redirection == 4)
		fixed[1] = cmd->hdoc;					//might come handy LATER
	else
		fixed[1] = NULL;
	fixed[0] = cmd->path;
	if (access(fixed[0],F_OK | X_OK) == 0)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return ;
		}
		if (pid == 0)
		{
			if (execve(fixed[0], fixed, envp) == -1)
				perror("execve");
		}
		else
			wait(&status);
	}
}

static void helperfunction(t_cmd **cmd, char ***fixed,char ***splited)
{
	int i;

	if ((*cmd)->args)
	{
		*splited = ft_split((*cmd)->args, ' ');
		i = 0;
		while (splited[i])
			i++;
		*fixed = (char **)malloc(sizeof(char *) * (i + 2));
		*fixed = prepend_array(*splited, (*cmd)->path);
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
	char **fixed;
	char **splited;

	helperfunction(&cmd, &fixed, &splited);
	if (access(fixed[0], X_OK | F_OK) == 0)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		if (pid == 0)
		{
			if (execve(fixed[0], fixed, envp) == -1)
				perror("execve");
		}
		else
			waitpid(pid, NULL, 0);
	}
}

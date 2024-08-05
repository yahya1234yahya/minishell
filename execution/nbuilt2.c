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

	env = convert(cmd);
	i = calculateargs(cmd);
	fixed = (char **)malloc(sizeof(char *) * (i + 2));
	splited = ft_split(cmd->args, ' ');
	fixed = prepend_array(splited, cmd->path);
	if (access(fixed[0], X_OK) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			if (cmd->redirection == 2 || cmd->redirection == 3)
			{
				dup2(cmd->fd_redirect, STDOUT_FILENO);
				close(cmd->fd_redirect);
			}
			else if (cmd->redirection == 1)
			{
				dup2(cmd->fd_redirect, STDIN_FILENO);
    			close(cmd->fd_redirect);	
			}
			if (execve(fixed[0], fixed, env) == -1)
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
	
	env = convert(cmd);
	fixed = (char **)malloc(sizeof(char *) * 2);
	fixed[0] = cmd->path;
	fixed[1] = NULL;
	if (access(fixed[0],F_OK | X_OK) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			if (cmd->redirection == 2 || cmd->redirection == 3)
			{
				dup2(cmd->fd_redirect, STDOUT_FILENO);
				close(cmd->fd_redirect);
            }
			else if (cmd->redirection == 1)
			{
				dup2(cmd->fd_redirect, STDIN_FILENO);
				close(cmd->fd_redirect);	
			}
			if (execve(fixed[0], fixed, env) == -1)
				perror("execve");
		}
		else
			wait(&status);
	}
};
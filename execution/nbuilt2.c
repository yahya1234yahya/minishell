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

t_cmd *preparecmd(t_cmd *cmd)
{
	char *tmp;

	if (!cmd->path)
		cmd->path = ft_strdup(cmd->cmd);
	if (cmd->args)
	{	
		tmp = ft_strjoin(cmd->path, " ");
		tmp = ft_strjoin(tmp, cmd->args);
		cmd->splited = ft_split(tmp, ' ');
	}else
	{
		cmd->splited = (char **)malloc(sizeof(char *) * 2);
		cmd->splited[0] = cmd->path;
		cmd->splited[1] = NULL;
	};
	return (cmd);
}

void ft_errorwrite(t_cmd *cmd)
{
	if (access(cmd->splited[0], F_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->splited[0], 2);
		ft_putstr_fd(" :command or file not found\n", 2);
		cmd->exs = 127;
	}
	else if (access(cmd->splited[0], X_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->splited[0], 2);
		ft_putstr_fd(" : Permission denied\n", 2);
		cmd->exs = 126;
	}
}


void execfromsystem(t_cmd *cmd, char **envp)
{
	int pid;
	
	cmd = preparecmd(cmd);
	if (access(cmd->splited[0], X_OK | F_OK) == 0)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			cmd->exs = 1;
			exit(1);
		}
		if (pid == 0)
		{
			g_signal = 1;
			if (execve(cmd->splited[0], cmd->splited, envp) == -1)
			{
				perror("execve");
				cmd->exs = 126;
			}
		}
		else
			waitpid(pid, NULL, 0);
	}
	else
		ft_errorwrite(cmd);
}

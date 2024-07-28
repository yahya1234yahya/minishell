/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decider.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:44:19 by mboughra          #+#    #+#             */
/*   Updated: 2024/07/28 06:04:18 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

void decider(t_cmd *cmd, char **envp)
{
	if (cmd->redirection == 1)
	{
		cmd = redirectchange(cmd);
	}
	
	if (!ft_strcmp("echo", cmd->cmd))
	{
		if (cmd->args == NULL)
		{
			write(cmd->fd_redirect,"\n",1);
			return ; //TODO HANDLE THE CASE OF -n and empty
		}
		ft_echo(cmd);
	}
	else if (!ft_strcmp("cd", cmd->cmd))
		changedir(cmd);
	else if (!ft_strcmp("export", cmd->cmd))
		ft_export(cmd);
	else if (!ft_strcmp("env", cmd->cmd))
		printenv(cmd->env);
	else if (!ft_strcmp("exit", cmd->cmd))
		exit(0);
	else if (!ft_strcmp("pwd", cmd->cmd))
		ft_pwd(cmd->env);
	else if (!ft_strcmp("unset", cmd->cmd))
		ft_unset(&cmd->env, cmd);
	else
		notbuilt(cmd, envp);
}
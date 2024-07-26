/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decider.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:44:19 by mboughra          #+#    #+#             */
/*   Updated: 2024/07/26 21:09:40 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

void decider(t_cmd *cmd, char **envp)
{
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
	else if (!ft_strcmp("pwd", cmd->cmd))   //wa9ela fiha mochkill
		ft_pwd(cmd->env);
	else
		notbuilt(cmd, envp);

	// if (!ft_strcmp("exit", cmd->cmd))
	// 	exit(0);
}
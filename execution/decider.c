/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decider.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:44:19 by mboughra          #+#    #+#             */
/*   Updated: 2024/07/25 02:19:42 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void decider(t_cmd *cmd, char **envp)
{
	if (!ft_strcmp("echo", cmd->cmd))
	{
		if (cmd->args == NULL)
		{
			write(1,"\n",1);
			return ; //TODO HANDLE THE CASE OF -n and empty
		}
		ft_echo(cmd);
	}
	else if (!ft_strcmp("cd", cmd->cmd))  // hadi ghi test
		changedir(cmd->args, envp);
	else if (!ft_strcmp("env", cmd->cmd))
		printenv(envp);
	else if (!ft_strcmp("exit", cmd->cmd))
		exit(0);
	// if (!ft_strcmp("clear", cmd->cmd))
	// 	system("clear");
	else
		notbuilt(cmd, envp);
	// else if(!ft_strcmp("exit", cmd->cmd))
	// 	exit(0);
	// if (!ft_strcmp("pwd", cmd->cmd))   //wa9ela fiha mochkill
	// 	ft_pwd(envp);
	// if (!ft_strcmp("exit", cmd->cmd))
	// 	exit(0);
}
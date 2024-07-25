/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decider.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:44:19 by mboughra          #+#    #+#             */
/*   Updated: 2024/07/25 21:53:57 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void decider(t_cmd *cmd, char **envp, t_env *env)
{
	printf("HELLO FROM DECIDER\n");
	if (!ft_strcmp("echo", cmd->cmd))
	{
		if (cmd->args == NULL)
		{
			write(1,"\n",1);
			return ; //TODO HANDLE THE CASE OF -n and empty
		}
		ft_echo(cmd);
	}
	else if (!ft_strcmp("cd", cmd->cmd))
		changedir(cmd->args, env);
	else if (!ft_strcmp("env", cmd->cmd))
		printenv(env);
	else if (!ft_strcmp("exit", cmd->cmd))
		exit(0);
	else
		notbuilt(cmd, envp);
	// if (!ft_strcmp("clear", cmd->cmd))
	// 	system("clear");
	// else if(!ft_strcmp("exit", cmd->cmd))
	// 	exit(0);
	// if (!ft_strcmp("pwd", cmd->cmd))   //wa9ela fiha mochkill
	// 	ft_pwd(envp);
	// if (!ft_strcmp("exit", cmd->cmd))
	// 	exit(0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decider.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:44:19 by mboughra          #+#    #+#             */
/*   Updated: 2024/07/18 01:19:51 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void decider(t_cmd *cmd, char **envp)
{
	// if (!ft_strcmp("echo", cmd->cmd))
	// 	ft_echo(cmd);
	// if (!ft_strcmp("pwd", cmd->cmd))   //wa9ela fiha mochkill
	// 	ft_pwd(envp);
	// if (!ft_strcmp("exit", cmd->cmd))
	// 	exit(0);
	// if (!ft_strcmp("cd", cmd->cmd))  // hadi ghi test
	// {
	// 	chdir(cmd->args);
	// }
	notbuilt(cmd);
}
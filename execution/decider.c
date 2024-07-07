/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decider.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:44:19 by mboughra          #+#    #+#             */
/*   Updated: 2024/07/07 19:27:45 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void decider(t_cmd *cmd, char **envp)
{
	if (!ft_strcmp("echo", cmd->cmd))
		ft_echo(cmd);
	if (!ft_strcmp("pwd", cmd->cmd))
		ft_pwd(envp);
	if (!ft_strcmp("exit", cmd->cmd))
		exit(0);
}
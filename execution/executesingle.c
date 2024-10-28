/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executesingle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:34:40 by mboughra          #+#    #+#             */
/*   Updated: 2024/10/28 01:30:29 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	executesingle(t_cmd *cmd, char **envp)
{
	int	input;
	int	output;
	int	retv;
	int	value;

	// if (cmd->skip == 1)
	// 	return (-42);
	if (cmd->redout != 0 || cmd->redin != 0)
	{
		input = dup(STDIN_FILENO);
		output = dup(STDOUT_FILENO);
		if (input == -1 || output == -1 || redirectchange(cmd) == -1)
			return (write(2, "dup or dup2 failed\n", 20), -1);
	}
	value = helper(cmd);
	if (value == 1337)
	{
		retv = execfromsystem(cmd, envp);
		return (filedreset(input, output), retv);
	}
	else
		retv = isbuiltin(cmd, value, 1);
	return (filedreset(input, output), retv);
}

int	redirectchange(t_cmd *cmd)
{
	if (dup2(cmd->ft_in, STDIN_FILENO) == -1)
		return (-1);
	if (dup2(cmd->ft_out, STDOUT_FILENO) == -1)
		return (-1);
	return (0);
}

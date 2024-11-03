/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 21:04:58 by mboughra          #+#    #+#             */
/*   Updated: 2024/11/03 21:15:58 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	waiter(int *status)
{
	if (WIFSIGNALED(*status))
		return (setandget(NULL)->exs = 128 + WTERMSIG(*status));
	else if (WIFEXITED(*status))
		return (setandget(NULL)->exs = WEXITSTATUS(*status));
	return (0);
}

void	reset(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->ft_in != STDIN_FILENO)
			close(cmd->ft_in);
		if (cmd->ft_out != STDOUT_FILENO)
			close(cmd->ft_out);
		cmd = cmd->next;
	}
}

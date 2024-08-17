/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initargs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 03:31:51 by mboughra          #+#    #+#             */
/*   Updated: 2024/08/08 03:31:51 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
	{
		perror("malloc");
		exit(1);
	}
	new_cmd->cmd = NULL;
	new_cmd->args = NULL;
	new_cmd->pipe = 0;
	new_cmd->redirection = 0;
	new_cmd->ft_in = 1;
	new_cmd->path = NULL;
	new_cmd->next = NULL;
	new_cmd->hdoc = NULL;
	return (new_cmd);
};

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:51:29 by ymouigui          #+#    #+#             */
/*   Updated: 2024/11/05 00:41:51 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	split_pipe(t_cmd *cmd, char *input, t_env *envp)
{
	char	*token;
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(input);
	token = ft_strtok(tmp, "|");
	while (token != NULL)
	{
		cmd->input = ft_strdup(token);
		token = ft_strtok(NULL, "|");
		if (token != NULL)
		{
			cmd->next = init_cmd();
			cmd = cmd->next;
			cmd->env = envp;
		}
	}
}

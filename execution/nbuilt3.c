/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbuilt3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 19:40:34 by mboughra          #+#    #+#             */
/*   Updated: 2024/10/27 19:40:58 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	perrornb(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	argsprepare(t_cmd *cmd)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strjoin(ft_strjoin(cmd->path, " "), cmd->args);
	cmd->splited = ft_strtok_all(tmp, " ");
	while (cmd->splited[i])
	{
		cmd->splited[i] = remove_quotes(cmd->splited[i]);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:42:32 by mboughra          #+#    #+#             */
/*   Updated: 2024/07/07 17:18:19 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_echo(t_cmd *cmd)
{
	char **av;
	int i;
	// int fd;

	// if (cmd->redirection == 0)
	// 	fd = 1;
	// else
	// 	fd = fd diyal text
	
	if (cmd->args == NULL)
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
	av = ft_split(cmd->args, ' ');
	if (ft_strcmp(av[0], "-n") == 0)
	{
		i = 1;
		while (av[i])
		{
			ft_putstr_fd(av[i++], 1);
			if (av[i] != NULL)
				ft_putstr_fd(" ", 1);
		}
	}
	else if (ft_strcmp(av[0], "-n") != 0)
	{
		i = 0;
		while (av[i])
		{
			ft_putstr_fd(av[i++], 1);
			if (av[i] != NULL)
				ft_putstr_fd(" ", 1);
		}
		ft_putstr_fd("\n", 1);
	}
	//free av;
}
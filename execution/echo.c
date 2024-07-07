/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:42:32 by mboughra          #+#    #+#             */
/*   Updated: 2024/07/07 18:18:41 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int echohelper(t_cmd *cmd)
{
	if (cmd->args[0] == '-' && cmd->args[1] == 'n' && cmd->args[2] == ' ')
		return (3);
	return (0);
}

void ft_echo(t_cmd *cmd)
{
	char **av;
	int i;
	int	option;
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
	if (cmd->args[0] == '-' && cmd->args[1] == 'n' && cmd->args[2] == ' ')
	{
		i = 3;
		option = 0;
	}
	else
	{
		i = 0;
		option = 1;
	}
	while (cmd->args[i])
		write(1,&cmd->args[i++],1);
	if (option)
		write(1, "\n", 1);
	

	
	// av = ft_split(cmd->args, ' ');
	// if (ft_strcmp(av[0], "-n") == 0)
	// {
	// 	i = 1;
	// 	while (av[i])
	// 	{
	// 		ft_putstr_fd(av[i++], 1);
	// 		if (av[i] != NULL)
	// 			ft_putstr_fd(" ", 1);
	// 	}
	// }
	// else if (ft_strcmp(av[0], "-n") != 0)
	// {
	// 	i = 0;
	// 	while (av[i])
	// 	{
	// 		ft_putstr_fd(av[i++], 1);
	// 		if (av[i] != NULL)
	// 			ft_putstr_fd(" ", 1);
	// 	}
	// 	ft_putstr_fd("\n", 1);
	// }
}

	// free av;
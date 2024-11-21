/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 00:18:59 by mboughra          #+#    #+#             */
/*   Updated: 2024/11/21 19:54:18 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	no_args(char *data)
{
	int	i;

	i = setandget(NULL)->exs;
	if (!data)
	{
		ft_putstr_fd("exit\n", 1);
		safe_malloc(0, 'f');
		exit(i);
	}
}

void	ft_exit(char *data, int flag)
{
	unsigned long long	num;
	int					i;
	char				**str;
	int					j;

	no_args(data);
	str = preparexit(data);
	i = 0;
	if (str[0][i] == '-' || str[0][i] == '+')
		i++;
	while (str[0][i])
	{
		if (!ft_isdigit(str[0][i]))
			print_numeric_error(str[0]);
		i++;
	}
	if (too_many_args(str, flag))
		return ;
	num = ft_atoil(str[0]);
	if (flag)
		ft_putstr_fd("exit\n", 1);
	j = convertexit(num);
	safe_malloc(0, 'f');
	exit(j);
}

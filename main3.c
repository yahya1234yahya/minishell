/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 22:50:42 by mboughra          #+#    #+#             */
/*   Updated: 2024/11/03 22:50:43 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	updateshlvl(t_env *env)
{
	int		shelllevel;
	char	*shlvlchar;

	shlvlchar = envsearch2(env, "SHLVL");
	if (!shlvlchar)
	{
		envset2(env, "SHLVL", "1");
		return ;
	}
	shelllevel = ft_atoi(shlvlchar);
	if (shelllevel < 0)
		envset2(env, "SHLVL", "0");
	else if (shelllevel > 999)
	{
		ft_putstr_fd("minishell: warning: shell level (", 2);
		ft_putstr_fd(envsearch2(env, "SHLVL"), 2);
		ft_putstr_fd(") too high, resetting to 1\n", 2);
		envset2(env, "SHLVL", "1");
	}
	else if (shelllevel == 999)
		envset2(env, "SHLVL", " ");
	else
		envset2(env, "SHLVL", ft_itoa(shelllevel + 1));
}

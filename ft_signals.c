/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 21:04:20 by mboughra          #+#    #+#             */
/*   Updated: 2024/11/12 22:34:25 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	funcsign(int signum)
{
	char	*holder;

	(void)signum;
	holder = setandget(NULL)->cmd;
	if (waitpid(-1, NULL, WNOHANG) != -1)
	{
		reset(setandget(NULL));
		ft_unlink(setandget(NULL));
		if (strrstr(holder, "minishell"))
			return ;
		write(1, "\n", 1);
		return ;
	}
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	setandget(NULL)->exs = 1;
}

void	funcsign2(int signum)
{
	char	*holder;

	(void)signum;
	holder = setandget(NULL)->cmd;
	if (waitpid(-1, NULL, WNOHANG) != -1)
	{
		if (strrstr(holder, "minishell"))
			return ;
		else
			write(1, "Quit: 3\n", 9);
	}
}

void	ft_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, funcsign);
	signal(SIGQUIT, funcsign2);
}

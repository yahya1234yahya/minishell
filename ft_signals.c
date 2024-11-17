/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 21:04:20 by mboughra          #+#    #+#             */
/*   Updated: 2024/11/17 14:18:07 by ymouigui         ###   ########.fr       */
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

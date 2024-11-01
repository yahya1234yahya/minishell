/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_complete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:57:57 by ymouigui          #+#    #+#             */
/*   Updated: 2024/10/25 22:57:57 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//DONE
#include "../minishell.h"

void	print_exit_s(char *str, int i)
{
	ft_putstr_fd(str, 2);
	setandget(NULL)->exs = i;
}

void	set_zero(int	*i, int	*j)
{
	*i = 0;
	*j = 0;
}

int	check_redirect(char	*str)
{
	t_check_r	var;

	(1) && (var.i = 0, var.d_q = 0, var.s_q = 0, var.in = 0, var.out = 0);
	while (str[var.i])
	{
		check_quots(str[var.i], &var.s_q, &var.d_q);
		if (str[var.i] == '<' && !var.s_q && !var.d_q)
		{
			var.in++;
			if (var.out || var.in > 2)
				return (print_exit_s("minishell: syntax error\n", 2), 0);
		}
		else if (str[var.i] == '>' && !var.s_q && !var.d_q)
		{
			var.out++;
			if (var.in || var.out > 2)
				return (print_exit_s("minishell: syntax error\n", 2), 0);
		}
		else if (str[var.i] != ' ' && str[var.i] != '\t' )
			set_zero(&var.in, &var.out);
		var.i++;
	}
	return (1);
}

int	check_complete_2(char *input, int len)
{
	t_check_c	c;

	c.i = 0;
	while (c.i < len)
	{
		if (input[c.i] == '"' || input[c.i] == '\'')
		{
			c.quote_char = input[c.i++];
			c.found = 0;
			while (c.i < len)
			{
				if (input[c.i] == c.quote_char)
				{
					c.found = 1;
					break ;
				}
				c.i++;
			}
			if (!c.found)
				return (print_exit_s("minishell: syntax error\n", 2), 0);
		}
		c.i++;
	}
	return (1);
}

int	check_complete(char *input)
{
	int		len;

	input = ft_strtrim(input, " \t");
	len = ft_strlen(input);
	if (!len || input[len - 1] == '|' || input[len - 1] == '<'
		|| input[len - 1] == '>' || input[len - 1] == '\\')
		return (print_exit_s("minishell: syntax error\n", 2), 0);
	if (check_redirect(input) == 0)
		return (0);
	if (check_complete_2(input, len) == 0)
		return (0);
	return (1);
}

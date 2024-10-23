/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:17:38 by mboughra          #+#    #+#             */
/*   Updated: 2024/10/23 21:41:49 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_numeric_error(char *str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	setandget(NULL)->exs = 255;
	exit(255);
}
static char convertexit(int num)
{
	if (num < 0)
		return (256 + num);
	else
	num = (unsigned char )num;
	return (num);
}

static long long	ft_atoil(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	rest;

	i = 0;
	rest = 0;
	sign = 1;
	while (str[i] != '\0' && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		rest = rest * 10 + (str[i] - '0');

		if (sign == -1 && rest > 9223372036854775808ULL)
			return (LLONG_MAX);
		if (sign == 1 && rest > 9223372036854775807ULL)
			return (LLONG_MAX);
		i++;
	}
	if (sign == -1 && rest == 9223372036854775808ULL)
		return (LLONG_MIN);
	return (rest * sign);
}

static char **preparexit(char *data)
{
	char	**str;
	int		i;

	str = ft_strtok_all(data, " ");
	i = 0;
	while (str[i])
	{
		str[i] = remove_quotes(str[i]);
		i++;
	}
	i = 0;
	while (str[i])
	{
		str[i] = ft_strtrim(str[i], " ");
		i++;
	}
	return (str);
}

static int too_many_args(char **str, int flag)
{
	if (str[1])
	{
		if (flag)
			ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		setandget(NULL)->exs = 1;
		return (1);
	}
	return (0);
}

static void no_args(char *data)
{
	if (!data)
	{
		ft_putstr_fd("exit\n", 1);
		exit(setandget(NULL)->exs);
	}
}


void	ft_exit(char *data, int flag)
{
	long long	num;
	int			i;
	char		**str;

	int r = 0;
	while (data[r])
	{
		if (data[r] == ' ' || data[r] == '\t' || data[r] == '\'' || data[r] == '\"')
			r++;
	}
	if (r == ft_strlen(data))
	{
		ft_putstr_fd("exit\n", 1);
		setandget(NULL)->exs = 255;
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		exit(setandget(NULL)->exs);
	}
	
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
	if (num == LLONG_MAX )
		print_numeric_error(str[0]);
	if (flag)
		ft_putstr_fd("exit\n", 1);
	exit(convertexit(num));
}

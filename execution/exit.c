/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:17:38 by mboughra          #+#    #+#             */
/*   Updated: 2024/11/03 19:42:06 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_numeric_error(char *str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	setandget(NULL)->exs = 255;
	safe_malloc(0, 'f');
	exit(255);
}

char	convertexit(int num)
{
	if (num < 0)
		return (256 + num);
	num = (unsigned char )num;
	return (num);
}

long long	ft_atoil(const char *str)
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

char	**preparexit(char *data)
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

int	too_many_args(char **str, int flag)
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

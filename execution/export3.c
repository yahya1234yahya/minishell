/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 02:19:16 by mboughra          #+#    #+#             */
/*   Updated: 2024/10/27 17:35:34 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parsename(char *name)
{
	int	i;
	int	ret;

	i = 0;
	if (ft_strcmp(name, "\0") == 0)
		return (0);
	if (name[i] && (name[i] != '_' && !ft_isalpha(name[i])))
		return (0);
	while (name[i])
	{
		if (name[i] != '_' && !ft_isalpha(name[i]) && !ft_isdigit(name[i]))
			return (0);
		i++;
	}
	return (1);
}

char	**preparetokens(char *str)
{
	int		i;
	char	**ret;

	i = 0;
	ret = ft_strtok_all(str, " ");
	while (ret[i])
	{
		ret[i] = remove_quotes(ret[i]);
		i++;
	}
	return (ret);
}

int	checkplus(char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (0);
	i = ft_strlen(str) - 1;
	if (str[i] == '+')
		return (1);
	return (0);
}

void	printerrorexport(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	onechar(char *str, char c)
{
	int	i;

	i = 0;
	while ((str[i]) && (str[i] == c || str[i] == '\'' || str[i] == '\"'))
		i++;
	if (ft_strlen(str) == i)
		return (1);
	return (0);
}

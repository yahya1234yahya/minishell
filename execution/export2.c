/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 02:05:38 by mboughra          #+#    #+#             */
/*   Updated: 2024/10/27 02:54:47 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	plusaddpack(t_env **env, char *key, char *value)
{
	t_env	*tmp;
	t_env	*tmp2;
	char	*newvalue;

	tmp = *env;
	while (tmp)
	{
		if (!strncmp(tmp->key, value, ft_strlen(key)))
		{
			newvalue = ft_strjoin(tmp->value, key);
			free(tmp->value);
			tmp->value = newvalue;
			return (1);
		}
		tmp = tmp->next;
	}
	return (-1);
}

int	exportsignal(int sig, t_cmd *cmd)
{
	char	*str;
	t_exp	*exp;

	str = ft_itoa(sig);
	exp = (t_exp *)malloc(sizeof(t_exp));
	exp->key = ft_strdup("?");
	exp->v = ft_strdup(str);
	if (plusaddpack(&cmd->env, exp->key, exp->v) == -1)
	{
		str = ft_strjoin(exp->key, "=");
		addback(&cmd->env, ft_lstnew(ft_strjoin(str, exp->v)));
	}
	return (0);
}

int	exportwithouthvalue(t_exp exp, t_cmd *cmd)
{
	char	*str;
	t_env	*tmp;

	if (parskey(exp.key))
	{
		if (exp.equal == 0)
		{
			tmp = ft_lstnew(exp.key);
			tmp->value = NULL;
			addback(&cmd->env, tmp);
		}
		else if (exp.equal == 1)
		{
			if (exp.plus == 1)
			{
				exp.key = ft_substr(exp.key, 0, ft_strlen(exp.key) - 1);
				if (plusaddpack(&cmd->env, exp.v, exp.key) == -1)
				{
					str = ft_strjoin(exp.key, "=");
					addback(&cmd->env, ft_lstnew(ft_strjoin(str, exp.v)));
				}
			}
			else
			{
				str = ft_strjoin(exp.key, "=");
				str = ft_strjoin(str, exp.v);
				addback(&cmd->env, ft_lstnew(str));
			}
		}
	}
	else
	{
		printerrorexport(ft_strjoin(ft_strjoin(exp.key, "="), exp.v));
		setandget(NULL)->exs = 1;
		return (1);
	}
	return (0);
}

int	parskey(char *str)
{
	int	i;

	i = 0;
	if (str[i] && (str[i] != '_' && !ft_isalpha(str[i])))
		return (0);
	i++;
	if (str[i] == '\0')
	{
		if (ft_isdigit(str[i - 1]))
			return (0);
		return (1);
	}
	while (str[i])
	{
		if (str[i] == '+')
		{
			if (str[i + 1] == '\0')
				return (1);
			return (0);
		}
		if (str[i] != '_' && !ft_isalpha(str[i]) && !ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
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

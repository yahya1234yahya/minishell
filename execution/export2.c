/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 02:05:38 by mboughra          #+#    #+#             */
/*   Updated: 2024/11/03 17:08:04 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	plusaddpack(t_env **env, char *key, char *value)
{
	t_env	*tmp;
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
	exp = (t_exp *)safe_malloc(sizeof(t_exp), 'a');
	exp->key = ft_strdup("?");
	exp->v = ft_strdup(str);
	if (plusaddpack(&cmd->env, exp->key, exp->v) == -1)
	{
		str = ft_strjoin(exp->key, "=");
		addback(&cmd->env, ft_lstnew(ft_strjoin(str, exp->v)));
	}
	return (0);
}

void	equalfound(t_exp *exp, t_cmd *cmd)
{
	char	*str;

	if (exp->plus == 1)
	{
		exp->key = ft_substr(exp->key, 0, ft_strlen(exp->key) - 1);
		if (plusaddpack(&cmd->env, exp->v, exp->key) == -1)
		{
			str = ft_strjoin(exp->key, "=");
			addback(&cmd->env, ft_lstnew(ft_strjoin(str, exp->v)));
		}
	}
	else
	{
		str = ft_strjoin(exp->key, "=");
		str = ft_strjoin(str, exp->v);
		addback(&cmd->env, ft_lstnew(str));
	}
}

int	exportwithouthvalue(t_exp exp, t_cmd *cmd)
{
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
			equalfound(&exp, cmd);
		}
	}
	else
	{
		printerrorexport(ft_strjoin(ft_strjoin(exp.key, "="), exp.v));
		return (setandget(NULL)->exs = 1, 1);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 03:31:15 by mboughra          #+#    #+#             */
/*   Updated: 2024/08/08 03:31:15 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_exp	*collect(char *str, t_exp *exp)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			exp->equal = 1;
			exp->key = ft_strdup(ft_substr(str, 0, i));
			exp->v = ft_strdup(ft_substr(str, i + 1, ft_strlen(str) - i - 1));
			exp->plus = checkplus(exp->key);
			break ;
		}
		i++;
	}
	if (exp->equal == 0)
	{
		exp->key = ft_strdup(str);
		exp->v = NULL;
		exp->plus = 0;
	}
	return (exp);
}

t_exp	*initexp(t_exp *exp)
{
	exp->key = NULL;
	exp->v = NULL;
	exp->plus = 0;
	exp->equal = 0;
	return (exp);
}

char	**prepareforexport(char *str, t_exp *exp)
{
	char	**token;

	exp = (t_exp *)safe_malloc(sizeof(t_exp), 'a');
	exp = initexp(exp);
	token = preparetokens(str);
	return (token);
}

int	preexport(t_cmd *cmd)
{
	if (!cmd->args)
		return (printenv(cmd->env, 0));
	return (ft_export(cmd));
}

int	ft_export(t_cmd *cmd)
{
	char	**token;
	t_exp	*exp;
	int		ret;

	ret = 0;
	if (onechar(cmd->args, ' '))
		return (printerrorexport(cmd->args), setandget(NULL)->exs = 1, 1);
	exp = (t_exp *)malloc(sizeof(t_exp));
	exp = initexp(exp);
	token = preparetokens(cmd->args);
	while (*token)
	{
		exp = collect(*token, exp);
		if (exp->key[0] == '\0')
		{
			ret = 1;
			printerrorexport(*token++);
			continue ;
		}
		if (exportwithouthvalue(*exp, cmd) == 1)
			ret = 1;
		exp = initexp(exp);
		token++;
	}
	return (setandget(NULL)->exs = ret, ret);
}

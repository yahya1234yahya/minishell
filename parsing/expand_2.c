/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:15:25 by ymouigui          #+#    #+#             */
/*   Updated: 2024/10/27 22:27:57 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_quots(char c, int *single_q, int *double_q)
{
	if (c == '\'' && *double_q == 0)
		*single_q = !(*single_q);
	else if (c == '\'' && *double_q == 1)
		return ;
	else if (c == '"' && *single_q == 0)
		*double_q = !(*double_q);
	else if (c == '"' && *single_q == 1)
		return ;
}

int	ft_isalpha(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123))
		return (1);
	else
		return (0);
}

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	else
		return (0);
}

int	count_word(char *input)
{
	int	i;

	i = 0;
	while (input[i] && (ft_isdigit(input[i]) || ft_isalpha(input[i])
			|| input[i] == '_'))
	{
		i++;
	}
	return (i);
}

char	*count_one(t_count *co, char *input, t_env *env, int herdoc)
{
	input++;
	co->name = ft_strdup("?");
	co->env_value = envsearch3(env, co->name);
	if (co->env_value && herdoc == 0)
		co->count += ft_strlen(add_d_quot(co->env_value));
	if (co->env_value && herdoc == 1)
		co->count += ft_strlen(co->env_value);
	return (input);
}

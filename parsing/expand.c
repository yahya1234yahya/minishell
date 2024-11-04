/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:17:25 by ymouigui          #+#    #+#             */
/*   Updated: 2024/10/27 13:17:25 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*count_two(t_count *co, char *input, t_env *env, int herdoc)
{
	input++;
	co->name = safe_malloc(count_word(input) + 1, 'a');
	co->i = 0;
	while (*input && (ft_isdigit(*input) || ft_isalpha(*input)
			|| *input == '_'))
	{
		co->name[co->i++] = *input;
		input++;
	}
	co->name[co->i] = '\0';
	co->env_value = envsearch3(env, co->name);
	if (co->env_value && herdoc == 0)
		co->count += ft_strlen(add_d_quot(co->env_value));
	if (co->env_value && herdoc == 1)
		co->count += ft_strlen(co->env_value);
	return (input);
}

static char	*expand_one(t_expa *expa, char *input, t_env *env, int herdoc)
{
	input++;
	expa->name = ft_strdup("?");
	expa->env_value = envsearch3(env, expa->name);
	if (expa->env_value)
	{
		if (herdoc == 0)
			expa->env_value = add_d_quot(expa->env_value);
		while (*expa->env_value)
		{
			expa->new_input[expa->j++] = *expa->env_value;
			expa->env_value++;
		}
	}
	input++;
	return (input);
}

static char	*expand_two(t_expa *expa, char *input, t_env *env, int herdoc)
{
	input++;
	expa->name = safe_malloc(count_word(input) + 1, 'a');
	expa->i = 0;
	while (*input && (ft_isdigit(*input) || ft_isalpha(*input)
			|| *input == '_' ))
	{
		expa->name[expa->i++] = *input;
		input++;
	}
	expa->name[expa->i] = '\0';
	expa->env_value = envsearch3(env, expa->name);
	if (expa->env_value)
	{
		if (herdoc == 0)
			expa->env_value = add_d_quot(expa->env_value);
		while (*expa->env_value)
		{
			expa->new_input[expa->j++] = *expa->env_value;
			expa->env_value++;
		}
	}
	return (input);
}

int	count_new_input(t_env *env, char *input, int herdoc)
{
	t_count	co;

	(1) && (co.count = 0, co.count_name = 0, co.single_q = 0, co.double_q = 0);
	while (*input)
	{
		co.i = 0;
		check_quots(*input, &co.single_q, &co.double_q);
		if (*input == '$' && *(input + 1) == '?' && co.single_q == 0)
			input = count_one(&co, input, env, herdoc);
		else if (*input == '$' && (ft_isalpha(*(input + 1))
				|| *(input + 1) == '_' ) && co.single_q == 0)
			input = count_two(&co, input, env, herdoc);
		else if (*input == '$' && (*(input + 1) == '*'
				|| *(input + 1) == '@' || ft_isdigit(*input + 1)))
			input = input + 2;
		else if (*input == '$' && co.single_q == 0 && co.double_q == 0
			&& (*(input + 1) == '\'' || *(input + 1) == '\"'))
			input++;
		else
		{
			co.count++;
			input++;
		}
	}
	return (co.count);
}

char	*expand_variables(t_env *env, char *input, int herdoc)
{
	t_expa	expa;

	init_struct(&expa, input, env, herdoc);
	while (*input)
	{
		expa.i = 0;
		check_quots(*input, &expa.single_q, &expa.double_q);
		if (*input == '$' && *(input + 1) == '?' && expa.single_q == 0)
			input = expand_one(&expa, input, env, herdoc);
		else if (*input == '$' && (ft_isalpha(*(input + 1))
				|| *(input + 1) == '_') && expa.single_q == 0)
			input = expand_two(&expa, input, env, herdoc);
		else if (*input == '$' && (*(input + 1) == '*'
				|| *(input + 1) == '@' || ft_isdigit(*(input + 1))))
			input = input + 2;
		else if (*input == '$' && expa.single_q == 0 && expa.double_q == 0
			&& (*(input + 1) == '\'' || *(input + 1) == '\"'))
			input++;
		else
		{
			expa.new_input[expa.j++] = *input;
			input++;
		}
	}
	return (expa.new_input[expa.j] = '\0', expa.new_input);
}

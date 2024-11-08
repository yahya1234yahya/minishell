/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 22:30:25 by mboughra          #+#    #+#             */
/*   Updated: 2024/11/08 21:04:56 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*setandget(t_cmd *cmd)
{
	static t_cmd	*cmd2;

	if (cmd)
		cmd2 = cmd;
	return (cmd2);
}

t_env	*noenv(void)
{
	t_env	*env;
	char	*currenntwd;
	t_env	*tmp;

	currenntwd = getcwd(NULL, 0);
	env = (t_env *)safe_malloc(sizeof(t_env), 'a');
	if (!env)
	{
		perror("malloc");
		safe_malloc(0, 'f');
		exit(1);
	}
	tmp = env;
	tmp->value = currenntwd;
	tmp->key = ft_strdup("PWD");
	tmp->next = (t_env *)safe_malloc(sizeof(t_env), 'a');
	tmp = tmp->next;
	tmp->key = ft_strdup("SHLVL");
	tmp->value = ft_strdup("1");
	tmp->next = (t_env *)safe_malloc(sizeof(t_env), 'a');
	tmp = tmp->next;
	tmp->key = ft_strdup("PATH");
	tmp->value = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:");
	tmp->next = NULL;
	return (env);
}

int	check_pipe(char	*input)
{
	int	i;
	int	s_quote;
	int	d_quote;

	d_quote = 0;
	s_quote = 0;
	input = ft_strtrim(input, " \t");
	if (input[ft_strlen(input) - 1] == '|' || input[0] == '|')
		return (0);
	i = 0;
	while (input[i])
	{
		check_quots(input[i], &d_quote, &s_quote);
		if (input[i] == '|' && d_quote == 0 && s_quote == 0)
		{
			i++;
			while (input[i] == ' ' || input[i] == '\t')
				i++;
			if (input[i] == '|' || input[i] == '\0')
				return (0);
		}
		i++;
	}
	return (1);
}

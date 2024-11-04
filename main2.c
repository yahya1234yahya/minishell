/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 22:30:25 by mboughra          #+#    #+#             */
/*   Updated: 2024/11/04 23:43:03 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	funcsign(int signum)
{
	if (signum == SIGINT)
	{
		if (waitpid(-1, NULL, WNOHANG) != -1)
		{
			reset(setandget(NULL));
			ft_unlink(setandget(NULL));
			if (ft_strcmp(setandget(NULL)->cmd, "./minishell") == 0)
				return ;
			write(1, "\n", 1);
			return ;
		}
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		setandget(NULL)->exs = 1;
	}
	else if (signum == SIGQUIT)
	{
		if (waitpid(-1, NULL, WNOHANG) != -1)
			write(1, "Quit: 3\n", 8);
	}
}

void	ft_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, funcsign);
	signal(SIGQUIT, funcsign);
}

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

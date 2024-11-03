/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:26:42 by mboughra          #+#    #+#             */
/*   Updated: 2024/08/24 15:26:42 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	eof(void)
{
	ft_putstr_fd("exit\n", 1);
	safe_malloc(0, 'f');
	exit(setandget(NULL)->exs);
}

static t_env	*thirdmain(t_cmd *cmd, char *input)
{
	t_env	*env;

	decider(cmd);
	env = cmd->env;
	free(input);
	return (env);
}

static void	postreadline(char *input)
{
	if (input == NULL)
		eof();
	if (input != NULL && *input != '\0')
		add_history(input);
}

static void	secondmain(t_cmd *cmd, struct termios ts, t_env *env, char *input)
{
	while (1)
	{
		set_cmd(cmd, env);
		input = readline("minishell > ");
		postreadline(input);
		if (!(*input))
		{
			free(input);
			continue ;
		}
		split_pipe(cmd, input, cmd->env);
		if (check_pipe(input) == 0)
		{
			ft_putstr_fd("minishell: syntax error\n", 2);
			setandget(NULL)->exs = 2;
			continue ;
		}
		exportsignal(cmd->exs, cmd);
		if (parse(cmd) == 0)
			continue ;
		env = thirdmain(cmd, input);
		tcsetattr(0, TCSANOW, &ts);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd					*cmd;
	char					*input;
	t_env					*env;
	static struct termios	ts;

	ft_signals();
	(void)argv;
	(void)argc;
	input = NULL;
	cmd = (t_cmd *)safe_malloc(sizeof(t_cmd), 'a');
	tcgetattr(0, &ts);
	if (*envp)
	{
		env = initenv(envp);
		updateshlvl(env);
	}
	else
		env = noenv();
	cmd->first_run = 1;
	setandget(cmd);
	setandget(NULL)->exs = 0;
	secondmain(cmd, ts, env, input);
	return (0);
}

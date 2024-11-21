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
	int i;

	i = setandget(NULL)->exs;
	ft_putstr_fd("exit\n", 1);
	safe_malloc(0, 'f');
	exit(i);
}

static t_env	*thirdmain(t_cmd *cmd)
{
	t_env	*env;

	if (cmd->next)
		exportlastcommand(cmd, 1);
	signal(SIGINT, funcsign);
	signal(SIGQUIT, funcsign2);
	decider(cmd);
	env = cmd->env;
	return (env);
}

static char	*postreadline(char *input)
{
	char	*tmp;

	if (input == NULL)
		eof();
	if (input != NULL && *input != '\0')
		add_history(input);
	tmp = ft_strdup(input);
	free(input);
	return (tmp);
}

static void	secondmain(t_cmd *cmd, struct termios ts, t_env *env, char *input)
{
	while (1)
	{
		set_cmd(cmd, env);
		input = readline("minishell > ");
		input = postreadline(input);
		input = remove_tab(input);
		if (!(*input))
			continue ;
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
		env = thirdmain(cmd);
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

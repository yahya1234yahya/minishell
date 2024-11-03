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

void print_commands(t_cmd *head)
{
    t_cmd *current = head;
	while(current)
	{
		// printf("input: %s\n", current->input);
		printf("Command: %s\n", current->cmd);
		printf("Arguments: [%s]\n", current->args);
		printf("Pipe: %d\n", current->pipe ? current->pipe : 0);
		printf("redout: %d\n", current->redout ? current->redout : 0);
		printf("redin: %d\n", current->redin ? current->redin : 0);
		printf("ft_in: %d\n", current->ft_in ? current->ft_in : 0);
		printf("ft_out: %d\n", current->ft_out ? current->ft_out : 0);
		printf("path: %s\n", current->path);
		printf("----------------\n");
		current = current->next;
	}
} 

void funcsign(int signum)
{
	if (signum == SIGINT)
	{
		if (waitpid(-1, NULL, WNOHANG) != -1)
		{
			if (ft_strcmp(setandget(NULL)->cmd, "./minishell") == 0)
				return ;
			write(1, "\n", 1);
			return;
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

void ft_signals()
{
	rl_catch_signals = 0;
	signal(SIGINT, funcsign);
	signal(SIGQUIT, funcsign);
}


t_cmd	*setandget(t_cmd *cmd)
{
	static t_cmd *cmd2;

	if (cmd)
		cmd2 = cmd;
	return (cmd2);
}

t_env	*noenv()
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
	int i = 0;
	int d_quote = 0;
	int s_quote = 0;
	
	input = ft_strtrim(input, " \t");
	i = ft_strlen(input) - 1;
	// when the input is empty strlen == -1 and segfault occurs here
	if (input[i] == '|' || input[0] == '|')
      return (0);
	i = 0;
	while(input[i])
	{
		check_quots(input[i], &d_quote, &s_quote);
		if (input[i] == '|' && d_quote == 0 && s_quote == 0)
		{
			i++;
			while(input[i] == ' ' || input[i] == '\t')
				i++;
			if (input[i] == '|' || input[i] == '\0')
				return (0);
		}
		i++;
	}
	return (1);

}

void	updateshlvl(t_env *env)
{
	int		shelllevel;
	char	*shlvlchar;
	shlvlchar = envsearch2(env, "SHLVL");
	if (!shlvlchar)
	{
		envset2(env, "SHLVL", "1");	
		return ;
	}
	shelllevel = ft_atoi(shlvlchar);
	if (shelllevel < 0)
		envset2(env, "SHLVL", "0");
	else if (shelllevel > 999)
	{
		ft_putstr_fd("minishell: warning: shell level (", 2);
		ft_putstr_fd(envsearch2(env, "SHLVL"), 2);
		ft_putstr_fd(") too high, resetting to 1\n", 2);
		envset2(env, "SHLVL", "1");
	}
	else if (shelllevel == 999)
		envset2(env, "SHLVL", " ");
	else
		envset2(env, "SHLVL", ft_itoa(shelllevel + 1));
}


int main(int argc, char **argv, char **envp)
{  
	t_cmd	*cmd;
	char	*input;
	t_env 	*env;
	char	*input_res;
	static struct termios	termstate;

	(void)argv;
	(void)argc;

	input = NULL;
	cmd = (t_cmd *)safe_malloc(sizeof(t_cmd), 'a');
	tcgetattr(0, &termstate);
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
	while (1)
	{
		set_cmd(cmd);
		setandget(cmd);
		ft_signals();
		cmd->env = env;
		input = readline("minishell > ");
		if (input == NULL)
		{
			write(1, "exit\n", 5);
			safe_malloc(0, 'f');
			exit(setandget(NULL)->exs);
		}
		if (input != NULL && *input != '\0')
			add_history(input);
		if (!(*input))
		{
			free(input);
			continue ;
		}
         if(!input[0])
		 {
            continue ;
		 }
		input_res = ft_strdup(input);
		split_pipe(cmd, input, cmd->env);	
		if(check_pipe(input_res) == 0)
    	{
			ft_putstr_fd("minishell: syntax error\n", 2);
			setandget(NULL)->exs = 2;
			continue ;
    	}
		int check = parse(cmd);
        if(check == 0)   
			continue ;
		exportsignal(cmd->exs, cmd);
		// print_commands(cmd);
		ft_unlink(cmd);
		decider(cmd);
		if (cmd->ft_in != STDIN_FILENO)
			close(cmd->ft_in);
		if (cmd->ft_out != STDOUT_FILENO)
			close(cmd->ft_out);
		env = cmd->env;
		tcsetattr(0, TCSANOW, &termstate);
		if (input)
		{
			free(input);
			input = NULL;
		}
    }
    return (0);
}

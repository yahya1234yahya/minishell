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
	int i = 0;
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

// void funcsign(int signum)
// {
//     if (signum == SIGINT)
//     {
// 		if (waitpid(-1, NULL, WNOHANG) != -1)
// 		{
// 			write(1, "\n", 1);
// 			return;
// 		}
// 		write(1, "\n", 1);
//         rl_on_new_line();
//         rl_replace_line("", 0);
//         rl_redisplay();
// 		setandget(NULL)->exs = 1;
//     }
//     else if (signum == SIGQUIT)
//     {
//         if (waitpid(-1, NULL, WNOHANG) != -1)
//             write(1, "Quit: 3\n", 8);
// 	}
void funcsign(int signum)
{
	if (signum == SIGINT)
	{
		if (waitpid(-1, NULL, WNOHANG) != -1)
		{
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


// |ls hadi makhashach douz

t_cmd	*setandget(t_cmd *cmd)
{
	static t_cmd *cmd2;

	if (cmd)
		cmd2 = cmd;
	return (cmd2);
}

// free_cmd(t_cmd *cmd)
// {
// 	t_cmd *tmp;

// 	while (cmd)
// 	{
// 		tmp = cmd;
// 		cmd = cmd->next;
// 		free(tmp->input);
// 		free(tmp->cmd);
// 		free(tmp->args);
// 		free(tmp->path);
// 		free(tmp->splited);
// 		free(tmp);
// 	}
// }

t_env	*noenv()
{
	t_env	*env;
	char	*vallue;
	char	*currenntwd;
	char arr[PATH_MAX];

	getcwd(arr, PATH_MAX);
	env = (t_env *)safe_malloc(sizeof(t_env), 'a');
	if (!env)
	{
		perror("malloc");
		exit(1);
	}
	env->name = ft_strdup("PWD");
	env->value = strdup(arr);
	env->next = (t_env *)safe_malloc(sizeof(t_env), 'a');
	env->next->name = ft_strdup("SHLVL");
	env->next->value = ft_strdup("1");
	env->next->next = NULL;
	//TODO $_

	return (env);
}

void	updateshlvl(t_env *env)
{
	int shelllevel;

	shelllevel = ft_atoi(envsearch2(env, "SHLVL"));
	if (shelllevel == 999)
		envset(env, "SHLVL", " ");
	else
		envset(env, "SHLVL", ft_itoa(shelllevel + 1));
}

void f(){system("leaks minishell");}


int main(int argc, char **argv, char **envp)
{  
	t_cmd	*cmd;
	char	*input;
	t_env 	*env;
	static struct termios	termstate;

	cmd = (t_cmd *)safe_malloc(sizeof(t_cmd), 'a');
	tcgetattr(0, &termstate);
	if (!*envp)
	{
		env = noenv();
	}
	else
		env = initenv(envp);
	updateshlvl(env);

	cmd->first_run = 1;
	while (1)
	{
		set_cmd(cmd);
		setandget(cmd);
		ft_signals();
		cmd->env = env;
		exportsignal(cmd->exs, cmd);
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
        input = expand_variables(env, input);
         if(!input[0])
		 {
            continue ;
		 }
		 if(check_complete(input) == 0)
    	{
			ft_putstr_fd("minishell: syntax error\n", 2);
			continue ;
    	}
		// printf("input: %s\n", input);
		split_pipe(cmd, input, envp);
		int check = parse(cmd, input, envp, 0);
		// printf("check: %d\n", check);
        if(check == 0)   
			continue ;
		// print_commands(cmd);
		decider(cmd);
		env = cmd->env;
		tcsetattr(0, TCSANOW, &termstate);
    }
    return (0);
}

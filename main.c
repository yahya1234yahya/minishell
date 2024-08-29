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
		printf("path: %s\n", current->path);
		printf("----------------\n");
		current = current->next;
	}
} 


int g_signal = 0;



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
    }
    else if (signum == SIGQUIT)
    {
        if (waitpid(-1, NULL, WNOHANG) != -1)
		{
			// printf("Quit: 3\n");
            write(1, "Quit: 3\n", 8);
            // exit(0);
		}
	}
}


void ft_signals()
{
	rl_catch_signals = 0;
	signal(SIGINT, funcsign);
	signal(SIGQUIT, funcsign);
}


// |ls hadi makhashach douz

int main(int argc, char **argv, char **envp)
{  
	t_cmd	*cmd;
	t_cmd	head;
	char	*input;
	t_env 	*env;
	static struct termios	termstate;
	
	tcgetattr(0, &termstate);
	ft_signals();
	env = initenv(envp);//TODO we cange here
	while (1)
	{
		cmd = init_cmd();
		cmd->env = env;
		input = readline("minishell > ");
		if (input == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		if (input != NULL && *input != '\0')
			add_history(input);
        input = expand_variables(input);
        if(!input[0])
            continue ;
		 if(check_complete(input) == 0)
    	{
			printf("error: incomplete command\n");
			continue ;
    	}
		if (input == NULL)
    	{
          printf("\033[33merror:  command not found\033[0m\n");
          return (0);
    	}
		split_pipe(cmd, input, envp);
		int check = parse(cmd, input, envp, 0);
        if(check == 0)
			continue ;
		// while (check == 5)
		// {
        //     cmd->next = init_cmd();
		// 	cmd->next->env = initenv(envp);
		// 	check = parse(cmd->next, ft_strtok(NULL, " "), envp, 1);
		// }
		// print_commands(cmd);
		decider(cmd);
		// while(head)
		// {
		// 	t_cmd *tmp = head;
		// 	head = head->next;
		// 	free(tmp);
		// }
		// my_free(cmd);
		// cmd->redout = 0;
		env = cmd->env;
		tcsetattr(0, TCSANOW, &termstate);
    }
    return (0);
}

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
		printf("Command: %s\n", current->cmd);
		printf("input: %s\n", current->input);
		printf("Arguments: [%s]\n", current->args);
		printf("Pipe: %d\n", current->pipe ? current->pipe : 0);
		printf("redout: %d\n", current->redout ? current->redout : 0);
		printf("redin: %d\n", current->redin ? current->redin : 0);
		printf("path: %s\n", current->path);
		printf("----------------\n");
		current = current->next;
	}
}

int main(int argc, char **argv, char **envp)
{  
	while (1)
	{
		t_cmd	*cmd;
		t_cmd	*head = cmd; 
		char	*input;
		
		cmd = init_cmd();
		// cmd->next = init_cmd;
		cmd->env = initenv(envp);//TODO we cange here
		input = readline("minishell > ");
		if (input != NULL && *input != '\0')
			add_history(input);
        input = expand_variables(input);
        if(!input[0])
            continue ;
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
		// decider(cmd);
		// while(head)
		// {
		// 	t_cmd *tmp = head;
		// 	head = head->next;
		// 	free(tmp);
		// }
		// my_free(cmd);
		// cmd->redout = 0;
    }
    return (0);
}

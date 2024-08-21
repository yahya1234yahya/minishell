#include "minishell.h"

void print_commands(t_cmd *head)
{
    t_cmd *current = head;
	int i = 0;
    while (current != NULL)
	{
		
		if (current->cmd)
			printf("Command: %s\n", current->cmd);
		if (current->args)
			printf("Arguments: %s\n", current->args);
		printf("Pipe: %d\n", current->pipe ? current->pipe : 0);
		printf("redout: %d\n", current->redout ? current->redout : 0);
		printf("redin: %d\n", current->redin ? current->redin : 0);
		if (current->path)
		printf("path: %s\n", current->path);
		printf("----------------\n");
		i++;
		current = current->next;
	}
}

int main(int argc, char **argv, char **envp)
{
	while (1)
	{
    t_cmd	*cmd;
    t_cmd	head;
    char	*input;

    cmd = init_cmd();
	// cmd->next = init_cmd;
	cmd->env = initenv(envp);
	
		input = readline("minishell > ");
		if (input != NULL && *input != '\0')
			add_history(input);
		
        input = expand_variables(input);
        if(!input[0])
            continue ;
        if(check_complete(input) == 0)
        {
            printf("error: incomplete command\n");
            continue;
        }
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
		
		my_free(cmd);
		// cmd->redout = 0;
    }
    return (0);
}

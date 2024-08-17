#include "minishell.h"

void print_commands(t_cmd *head)
{
    t_cmd *current = head;
	int i = 0;
    while (current != NULL)
	{
		printf("Command: %s\n", current->cmd ? current->cmd : "(none)");
		printf("Arguments: %s\n", current->args ? current->args : "(none)");
		printf("Pipe: %d\n", current->pipe ? current->pipe : 0);
		printf("redout: %d\n", current->redout ? current->redout : 0);
		printf("redin: %d\n", current->redin ? current->redin : 0);
		printf("path: %s\n", current->path ? current->path : "(none)");
		printf("----------------\n");
		i++;
		current = current->next;
	}
}

int main(int argc, char **argv, char **envp)
{
    t_cmd	*cmd;
    t_cmd	head;
    char	*input;

    cmd = init_cmd();
	cmd->env = initenv(envp);
	while (1)
	{
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
        if(parse(cmd, input, envp, 0) == 0)
			continue ;
		print_commands(cmd);
		// decider(cmd);
		// free(cmd->args);
        // cmd->args = NULL;
		// cmd->redout = 0;
    }
    return (0);
}

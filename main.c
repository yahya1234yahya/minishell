#include "minishell.h"

void print_commands(t_cmd *head)
{
    t_cmd *current = head;
    while (current != NULL) {
        printf("Command: %s\n", current->cmd);
        printf("Arguments: %s\n", current->args ? current->args : "(none)");
        printf("Pipe: %d\n", current->pipe);
        printf("Redirection: %d\n", current->redirection);
        printf("path: %s\n", current->path);
        printf("----------------\n");
        current = current->next;
    }
}

int main(int argc, char **argv, char **envp)
{
    t_cmd	*cmd;
    t_cmd	head;
    char	*input;
    char	*word;
	char	*herdoc;

    cmd = init_cmd();
	cmd->env = initenv(envp);
	while (1)
	{
		input = readline("\033[32mminishell\033[0m \033[34m>\033[0m ");
		if (input != NULL)
			add_history(input);
        input = expand_variables(input);
        if(!input[0])
            continue ;
        if(check_complete(input) == 0)
        {
            printf("\033[33merror: incomplete command\033[0m\n");
            continue;
        }
        if(parse(cmd, input, envp, 0) == 0)
			continue ;
		// print_commands(cmd);
        // printf("cmd->redirection : %d\n", cmd->redirection);
		decider(cmd);
		free(cmd->args);
        cmd->args = NULL;
		cmd->redirection = 0;
    }
    return (0);
}

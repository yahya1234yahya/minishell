
#include "minishell.h"

void print_commands(t_cmd *head) {
    t_cmd *current = head;
    while (current != NULL) {
        printf("Command: %s\n", current->cmd);
        printf("Arguments: %s\n", current->args ? current->args : "(none)");
        printf("Pipe: %d\n", current->pipe);
        printf("Redirection: %d\n", current->redirection);
        printf("----------------\n");
        current = current->next;
    }
}

int main() {
    t_cmd cmd;
    t_cmd head;
    while (1) {
        char *input = readline("\033[32mminishell\033[0m \033[34m>\033[0m ");
        add_history(input);
        if(!input[0])
            continue;
        while(check_complete(input) == 0)
        {
            input = ft_strjoin(input, " ");
            input = ft_strjoin(input, readline("\033[31mcontinue\033[0m \033[34m>\033[0m "));
        }
        parse(&cmd, input, 0);
        print_commands(&cmd);
        add_history(input);
		decider(&cmd);
    }
    return 0;
}
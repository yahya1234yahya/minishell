
#include "minishell.h"

char *expand_variables(char *input)
{
    char *expanded = malloc(strlen(input) + 1);
    if (!expanded)
	{
        perror("malloc");
        exit(1);
    }
    strcpy(expanded, input);

    char *pos = expanded;
    while ((pos = strchr(pos, '$')) != NULL)
	{
        char *start = pos;
        pos++;
        char varname[256];
        int i = 0;
        while (*pos && (isalnum(*pos) || *pos == '_'))
            varname[i++] = *pos++;
        varname[i] = '\0';

        char *value = getenv(varname);
        if (!value)
            value = "";

        int new_len = strlen(expanded) - strlen(varname) - 1 + strlen(value);
        char *new_expanded = malloc(new_len + 1);
        if (!new_expanded) {
            exit(1);
        }

        strncpy(new_expanded, expanded, start - expanded);
        new_expanded[start - expanded] = '\0';
        strcat(new_expanded, value);
        strcat(new_expanded, pos);

        free(expanded);
        expanded = new_expanded;
        pos = expanded + (start - expanded) + strlen(value);
    }
    free(input);
    return expanded;
}


void print_commands(t_cmd *head) {
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
    t_cmd cmd;
    t_cmd head;
    while (1) {
        char *input = readline("\033[32mminishell\033[0m \033[34m>\033[0m ");
        add_history(input);
        input = expand_variables(input);
        if(!input[0])
            continue;
        while(check_complete(input) == 0)
        {
            input = ft_strjoin(input, " ");
            input = ft_strjoin(input, readline("\033[31mcontinue\033[0m \033[34m>\033[0m "));
        }
        parse(&cmd, input, 0);
        // print_commands(&cmd);
		decider(&cmd, envp);
    }
    return 0;
}
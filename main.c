
#include "minishell.h"

char *expand_variables(char *input)
{
    char	*expanded;
    char	*pos;
    char	*start;
    int		i;
    char	varname[256];
    char	*value;
    int		new_len;
    char	*new_expanded;
	
	expanded = malloc(strlen(input) + 1);
    if (!expanded)
	{
        perror("malloc");
        exit(1);
    }
    strcpy(expanded, input);
	pos = expanded;
    while ((pos = strchr(pos, '$')) != NULL)
	{
		start = pos;
        pos++;
		i = 0;
        while (*pos && (isalnum(*pos) || *pos == '_'))
            varname[i++] = *pos++;
        varname[i] = '\0';

		value = getenv(varname);
        if (!value)
            value = "";
		new_len = strlen(expanded) - strlen(varname) - 1 + strlen(value);
		new_expanded = malloc(new_len + 1);
        if (!new_expanded) 
            exit(1);
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

    cmd = init_cmd();
	cmd->env = initenv(envp);
	while (1)
	{
		input = readline("\033[32mminishell\033[0m \033[34m>\033[0m ");
        add_history(input);
        input = expand_variables(input);
        if(!input[0])
            continue ;
        while(check_complete(input) == 0)
        {
            input = ft_strjoin(input, " ");
            input = ft_strjoin(input, readline("\033[31mcontinue\033[0m \033[34m>\033[0m "));
        }
        if(parse(cmd, input, 0) == 0)
			continue ;
        print_commands(cmd);
		decider(cmd, envp, cmd->env);
        free(cmd->args);
        cmd->args = NULL;
    }
    return 0;
}
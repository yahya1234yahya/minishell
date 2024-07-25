#include "minishell.h"
#include <string.h>

char *skip_whitespace(char *str)
{
    while (isspace(*str)) str++;
    return (str);
}

int is_valid_command(t_cmd *cmd, char *word)
{
    char *path_env = getenv("PATH");
    if (!path_env) {
        return 0;
    }
    char *path_dup = strdup(path_env);
    if (!path_dup) {
        perror("strdup");
        exit(1);
    }
    char *dir = strtok(path_dup, ":");
    while (dir)
    {
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, word);
        if (access(full_path, X_OK) == 0) {
            cmd->path = strdup(full_path); 
            free(path_dup);
            return 1;
        }
        dir = strtok(NULL, ":");
    }

    free(path_dup);
    return 0;
}

int parse(t_cmd *cmd, char *input, int rec)
{
   
    char *next_word;
    int flags;
    
	cmd->cmd = NULL;
    cmd->args = NULL;
    cmd->pipe = 0;
    cmd->redirection = 0;
    cmd->next = NULL;
	next_word = NULL;
    input = skip_whitespace(input);
    if (rec == 0)
        next_word = ft_strtok(input, " ");
    else    
        next_word = input;
    if (!next_word) return (0);

    if (!is_valid_command(cmd, next_word) && strcmp("exit", next_word))
	{
        printf("\033[33merror: %s is not a command\033[0m\n\n", next_word);
        return (0);
    }
    cmd->cmd = strdup(next_word);
    cmd->fd_redirect = 1;
    while ((next_word = ft_strtok(NULL, " ")) != NULL)
	{
		if (strcmp(next_word, "|") == 0)
		{
            cmd->pipe = 1;
            cmd->next = (t_cmd *)malloc(sizeof(t_cmd));
            next_word = ft_strtok(NULL, " ");
            parse(cmd->next, next_word, 1);
            break;

        } else if (strcmp(next_word, "<") == 0 || strcmp(next_word, ">") == 0 || strcmp(next_word, "<<") == 0 || strcmp(next_word, ">>") == 0) {
            cmd->redirection = 1;
            next_word = ft_strtok(NULL, " ");
            if (next_word == NULL)
			{
                printf("\033[33merror: expected filename after redirection \033[0m\n\n");
                return (0);
            }
			flags = O_WRONLY | O_CREAT | O_APPEND;
            cmd->fd_redirect = open(next_word, flags, 0644);
            if (cmd->fd_redirect == -1)
			{
                printf("\033[33merror: can't open file \033[0m\n\n");
                return (0);
            }
            write(cmd->fd_redirect, cmd->args, strlen(cmd->args));

        } else
        {
            if (cmd->args == NULL) 
                cmd->args = strdup(next_word);
            else
            {
                cmd->args = ft_strjoin(cmd->args, " ");
                cmd->args = ft_strjoin(cmd->args, next_word);
            }
        }
    }
	return (1);
}

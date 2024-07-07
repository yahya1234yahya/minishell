#include "minishell.h"

char *skip_whitespace(char *str) {
    while (isspace(*str)) str++;
    return str;
}

int is_valid_command(const char *cmd) {
    char *valid_commands[] = {
        "echo", "cd", "pwd", "export", "unset", "env", "exit", "ls", "clear", NULL
    };
    int i = 0;
    while (valid_commands[i] != NULL) {
        if (strcmp(cmd, valid_commands[i]) == 0) {
            return 1;
        }
        i++;
    }
    return 0;
}

void parse(t_cmd *cmd, char *input, int rec) {
   
    cmd->cmd = NULL;
    cmd->args = NULL;
    cmd->pipe = 0;
    cmd->redirection = 0;
    cmd->next = NULL;
    char *next_word = NULL;

    input = skip_whitespace(input);
    if (rec == 0)
        next_word = ft_strtok(input, " ");
    else    
        next_word = input;
    if (!next_word) return;

    if (!is_valid_command(next_word)) {
        printf("\033[33merror: %s is not a command\033[0m\n\n", next_word);
        return;
    }

    cmd->cmd = strdup(next_word);
    cmd->fd_redirect = 1;
    while ((next_word = ft_strtok(NULL, " ")) != NULL) {
        if (strcmp(next_word, "|") == 0) {
            cmd->pipe = 1;
            cmd->next = (t_cmd *)malloc(sizeof(t_cmd));
            next_word = ft_strtok(NULL, " ");
            parse(cmd->next, next_word, 1);
            break;

        } else if (strcmp(next_word, "<") == 0 || strcmp(next_word, ">") == 0 || strcmp(next_word, "<<") == 0 || strcmp(next_word, ">>") == 0) {
            cmd->redirection = 1;
            next_word = ft_strtok(NULL, " ");
            if (next_word == NULL) {
                printf("\033[33merror: expected filename after redirection \033[0m\n\n");
                return;
            }
            int flags = 0;
                flags = O_WRONLY | O_CREAT | O_APPEND;
            cmd->fd_redirect = open(next_word, flags, 0644);
            if (cmd->fd_redirect == -1) {
                printf("\033[33merror: can't open file \033[0m\n\n");
                return;
            }
            write(cmd->fd_redirect, cmd->args, strlen(cmd->args));

        } else {
            if (cmd->args == NULL) 
                cmd->args = strdup(next_word);
            else
            {
                cmd->args = ft_strjoin(cmd->args, " ");
                cmd->args = ft_strjoin(cmd->args, next_word);
            }
        }
    }
}

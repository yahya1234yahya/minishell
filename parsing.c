#include "minishell.h"

char *skip_whitespace(char *str) {
    while (isspace(*str)) str++;
    return str;
}

int is_valid_command(const char *cmd) {
    char *valid_commands[] = {
        "echo", "cd", "pwd", "export", "unset", "env", "exit", "ls", NULL
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

void parse(t_cmd *cmd, char *input) {
    cmd->cmd = NULL;
    cmd->args = NULL;
    cmd->pipe = 0;
    cmd->redirection = 0;
    cmd->next = NULL;

    input = skip_whitespace(input);
    char *next_word = ft_strtok(input, " ");
    if (!next_word) return;

    if (!is_valid_command(next_word)) {
        printf("error: %s is not a command\n", next_word);
        return;
    }

    cmd->cmd = strdup(next_word);
    while ((next_word = ft_strtok(NULL, " ")) != NULL) {
        if (strcmp(next_word, "|") == 0) {
            cmd->pipe = 1;
            cmd->next = (t_cmd *)malloc(sizeof(t_cmd));
            parse(cmd->next, ft_strtok(NULL, ""));
            break;
        } else if (strcmp(next_word, "<") == 0 || strcmp(next_word, ">") == 0 || strcmp(next_word, "<<") == 0 || strcmp(next_word, ">>") == 0) {
            cmd->redirection = 1;
        } else {
            if (cmd->args == NULL) {
                cmd->args = strdup(next_word);
        }
    }
}
}
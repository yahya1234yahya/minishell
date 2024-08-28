#include "../minishell.h"

static int redouthelper(t_cmd *cmd)
{
	if (cmd->redout == 1)
		return (O_RDONLY);
	else if (cmd->redout == 2)
		return (O_RDWR | O_CREAT | O_TRUNC);
	else if (cmd->redout == 3)
		return (O_RDWR | O_CREAT | O_APPEND);
	else if (cmd->redout == 4)
		return (O_RDWR | O_CREAT | O_APPEND);
	return (0);
};

char *skip_whitespace(char *str)
{
    while (isspace(*str)) str++;
    return (str);
}

int is_valid_command(t_cmd *cmd, char *word)
{
    char *path_env = envsearch(cmd->env, "PATH")->name; //TODO WE HAVE TO CHANGE HERE
    if (!path_env) {
        exit (0);
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

int parse(t_cmd *cmd, char *input, char **envp, int rec)
{
    char *next_word;
    int flags;
    next_word = NULL;

   
    while(cmd)
    {

        next_word = ft_strtok(cmd->input, "<>\"' \t\n");
        if (!next_word) return (0);

        // printf("\n\nnext_word : %s\n\n", next_word);

        // if (!is_valid_command(cmd, next_word) && strcmp("exit", next_word) && strcmp("unset", next_word) && strcmp("export", next_word) && strcmp("set", next_word))
        // {
        //     printf("\033[33merror: not a command\033[0m\n");
        //     return (0);
        // }
        if (strcmp(next_word, ">")  || strcmp(next_word, ">>") || strcmp(next_word, "<") || strcmp(next_word, "<<"))
        {
                is_valid_command(cmd, next_word);
                cmd->cmd = strdup(next_word); 
                next_word = ft_strtok(NULL, "<>\"' \t\n");
        }
        cmd->ft_in = 1;
        while (next_word)
        {
            if (strcmp(next_word, "|") == 0)
            {
                cmd->pipe = 1;
                break;
            } else if (strcmp(next_word, ">") == 0 || strcmp(next_word, ">>") == 0)
            {
                cmd->redout = index_char(next_word);
                next_word = ft_strtok(NULL, "<>\"' \t\n");
                if (next_word == NULL)
                {
                    printf("\033[33merror: expected filename after redout \033[0m\n");
                    return (0);
                }
                flags = redouthelper(cmd);
                cmd->ft_out = open(next_word, flags, 0644);
                if (cmd->ft_out == -1)
                {
                    printf("\033[33merror: can't open file \033[0m\n");
                    return (0);
                }
            
            }
            else if (strcmp(next_word, "<") == 0)
            {
                cmd->redin = index_char(next_word);
                next_word = ft_strtok(NULL, "<>\"' \t\n");
                if (next_word == NULL)
                {
                    printf("\033[33merror: expected filename after redout \033[0m\n");
                    return (0);
                }
                flags = redouthelper(cmd);
                cmd->ft_in = open(next_word, flags, 0644);
                if (cmd->ft_in == -1)
                {
                    printf("\033[33merror: can't open file \033[0m\n");
                    return (0);
                }   
            }
            else if (strcmp(next_word, "<<") == 0 )
            {
                cmd->args = handle_heredoc(ft_strtok(NULL, "<>\"' \t\n"));
                
            }
            else
            {
                next_word = remove_quotes(next_word);
                if (cmd->args == NULL) 
                    cmd->args = strdup(next_word);
                else
                {
                    cmd->args = ft_strjoin(cmd->args, " ");
                    cmd->args = ft_strjoin(cmd->args, next_word);
                }
            }
        next_word = ft_strtok(NULL, "<>\"' \t\n");
        }
        cmd = cmd->next;
    }
	return (1);
}

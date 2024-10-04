#include "../minishell.h"

static int redouthelper(t_cmd *cmd)
{
	if (cmd->redin == 1)
		return (O_RDONLY);
	else if (cmd->redout == 2)
		return (O_RDWR | O_CREAT | O_TRUNC);
	else if (cmd->redout == 3)
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
    t_env *tmp = envsearch(cmd->env, "PATH");
    char *path_env;
    if (!tmp)
    {
        return 0;
    }
    path_env = tmp->name; //TODO WE HAVE TO CHANGE HERE
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

// char    *add_space(char *input)
// {
//     int i = 0;
//     int count = 0;
//     int j = 0;
//     while(input && input[i])
//     {
//         if (input[i] == '<' || input[i] == '>')
//         {
//             if (i > 0 && input[i - 1] != '<' && input[i - 1] != '>')
//                 count += 2;
//             count++;
//             i++;
//             continue ;
//         }
//         i++;
//         count++;
//     }
//     char *new_input = malloc(count + 1);
//     i = 0;
//     while(input && input[i])
//     {
//         if (input[i] == '<' || input[i] == '>')
//         {
//             if (i > 0 && input[i - 1] != '<' && input[i - 1] != '>')
//                 new_input[j++] = ' ';
//             new_input[j++] = input[i++];
//             if (input[i] != '<' && input[i] != '>')
//                 new_input[j++] = ' ';
//             continue;
//         }
//         new_input[j++] = input[i++];
//     }
//     new_input[j] = '\0';
//     return (new_input);

// }

char    *add_space(char *input)
{
    int i = 0;
    int count = 0;
    int s_quote = 0;
    int d_quote = 0;
    int j = 0;

    while(input && input[i])
    {
        check_quots(input[i], &s_quote, &d_quote);
        if ((input[i] == '<' || input[i] == '>') && !s_quote && !d_quote)
        {
            if (i > 0 && input[i - 1] != '<' && input[i - 1] != '>')
                count += 2;
            count++;
            i++;
            continue ;
        }
        i++;
        count++;
    }
    char *new_input = malloc(count + 1);
    i = 0;
    while(input && input[i])
    {
       check_quots(input[i], &s_quote, &d_quote);
        if ((input[i] == '<' || input[i] == '>') && !s_quote && !d_quote)
        {
            if (i > 0 && input[i - 1] != '<' && input[i - 1] != '>')
                new_input[j++] = ' ';
            new_input[j++] = input[i++];
            if (input[i] != '<' && input[i] != '>')
                new_input[j++] = ' ';
            continue;
        }
        new_input[j++] = input[i++];
    }
    new_input[j] = '\0';
    return (new_input);

}


int parse(t_cmd *cmd, char *input, char **envp, int rec)
{
    char *next_word;
    int flags;
    next_word = NULL;
    char    *delimiter;
    char    *tmp_args;

   
    while(cmd)
    {
        cmd->input = add_space(cmd->input);
		cmd->tokens = ft_strtok_all(cmd->input, " ");
        // printf("next_word : %s\n", next_word);
        if (!*(cmd->tokens)) return (0);

        // printf("\n\nnext_word : %s\n\n", next_word);

        // if (!is_valid_command(cmd, next_word) && strcmp("exit", next_word) && strcmp("unset", next_word) && strcmp("export", next_word) && strcmp("set", next_word))
        // {
        //     printf("\033[33merror: not a command\033[0m\n");
        //     return (0);
        // }
        if (strcmp(*(cmd->tokens), ">")  && strcmp(*(cmd->tokens), ">>") && strcmp(*(cmd->tokens), "<") && strcmp(*(cmd->tokens), "<<"))
        {
                *(cmd->tokens) = remove_quotes(*(cmd->tokens));
                is_valid_command(cmd, *(cmd->tokens));
                cmd->cmd = ft_strdup(*(cmd->tokens)); 
                cmd->tokens++;
        }
        cmd->ft_in = 1;
        while (cmd->tokens && *(cmd->tokens))
        {
            if (strcmp(*(cmd->tokens), "|") == 0)
            {
                cmd->pipe = 1;
                break;
            }
            else if (strcmp(*(cmd->tokens), ">") == 0 || strcmp(*(cmd->tokens), ">>") == 0)
            {
                cmd->redout = index_char(*(cmd->tokens));
                cmd->tokens++;
                if (*(cmd->tokens) == NULL)
                {
                    ft_putstr_fd("minishell: ", 2);
                    ft_putstr_fd("error: expected filename after redout\n", 2);
                    return (0);
                }
                flags = redouthelper(cmd);
                cmd->ft_out = open(*(cmd->tokens), flags, 0644);
                if (cmd->ft_out == -1)
                {
                    ft_putstr_fd("minishell: ", 2);
                    // ft_putstr_fd("error: can't open file\n", 2);
					ft_putstr_fd("No such file or directory\n", 2);
					setandget(NULL)->exs = 1;
                    cmd->skip = 1;
                    if (cmd->next)
                        break ;
                    else
                        return (0);
                }
            
            }
            else if (strcmp(*(cmd->tokens), "<") == 0)
            {
                cmd->redin = index_char(*(cmd->tokens));
                cmd->tokens++;
                if (*(cmd->tokens) == NULL)
                {
                    ft_putstr_fd("minishell: ", 2);
                    ft_putstr_fd("error: expected filename after redin\n", 2);
                    return (0);
                }
                flags = redouthelper(cmd);
                cmd->ft_in = open(*(cmd->tokens), flags, 0644);
                if (cmd->ft_in == -1)
                {
                    ft_putstr_fd("minishell: ", 2);
                    // ft_putstr_fd("error: can't open file\n", 2);
					ft_putstr_fd("No such file or directory\n", 2);
					setandget(NULL)->exs = 1;
                     cmd->skip = 1;
                    if (cmd->next)
                        break ;
                    else
                        return (0);
                }   
            }
            else if (strcmp(*(cmd->tokens), "<<") == 0 )
            {
                cmd->tokens++;
                cmd->redin = 1;
                if (cmd->ft_in == 1)
                {
                    cmd->ft_in = open("tmp_hdoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
                }
                cmd->hdoc_delimiter = ft_strdup(*(cmd->tokens));
                handle_heredoc(*(cmd->tokens), cmd);
				cmd->ft_in = open("tmp_hdoc", O_RDWR , 0644);
            }
            else
            {
               
                // prinft("cmd->tokens : %s\n", *(cmd->tokens));
                if (cmd->args == NULL) 
                    cmd->args = ft_strdup(*(cmd->tokens));
                else
                {
                    cmd->args = ft_strjoin(cmd->args, " ");
                    cmd->args = ft_strjoin(cmd->args, *(cmd->tokens));
                }
            }
            // printf("cmd->args : %s\n", cmd->args);
            cmd->tokens++;
        }
      
        if (ft_strcmp(cmd->cmd, "export") == 0 && !cmd->args )
        {
            t_cmd *tmp;
            
            if (cmd->next)
                tmp = cmd->next;
            
            cmd->next = init_cmd();
            if (cmd->redout == 2 || cmd->redout == 3)
            {
                cmd->next->redout = cmd->ft_out;
                cmd->next->ft_out = cmd->ft_out;
                cmd->ft_out = 1;
                cmd->redout = 0;
            }
            cmd = cmd->next;
            cmd->env = initenv(envp);
            cmd->input = ft_strdup("sort");
            if (tmp)
                cmd->next = tmp;
        }
        else
            cmd = cmd->next;
    }
	return (1);
}

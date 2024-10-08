#include "../minishell.h"

void my_free(t_cmd *t)
{
    // t_cmd *head = t;
    // while(head)
    // {
    //     free(head->args);
    //     free(head->cmd);
    //     free(head->cmd);
    //     head = head->next;
    // }
//     t_cmd *tmp;
//     while (t)
//     {
    free(t);

}
void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (fd < 0)
		return ;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write (fd, &s[i], 1);
		i++;
	}
	write (fd, "\n", 1);
}


char* add_quotes(char* str)
{
    int len ;
    int i = 0;
    int j = 0;

    len = ft_strlen(str);
    char* quoted_str = safe_malloc(len + 3, 'a');
    if (quoted_str == NULL)
        return (NULL);
    quoted_str[i] = '\'';
    while(j < len)
    {
        quoted_str[i + 1] = str[j];
        i++;
        j++;
    }
    quoted_str[++i] = '\'';
    quoted_str[++i] = '\0';
    return (quoted_str);
}

void    handle_heredoc(char *input,t_cmd *cmd)
{
    char *line;
    int is_quoted = 0;
    int i = 0;


    if (cmd->hdoc_delimiter[ft_strlen(cmd->hdoc_delimiter) - 1] == '\'' || cmd->hdoc_delimiter[ft_strlen(cmd->hdoc_delimiter) - 1] == '"')
        is_quoted = 1;
    cmd->hdoc_delimiter = remove_quotes(cmd->hdoc_delimiter);
    while (1) {
        line = readline("> ");
        if (is_quoted)
            line = add_quotes(line);
        line = expand_variables(cmd->env, line);
         if (is_quoted)
            line = remove_quotes(line);
        if (ft_strcmp(line, cmd->hdoc_delimiter) == 0)
        {
			close(cmd->ft_in);
            break;
        }
        ft_putendl_fd(line, cmd->ft_in);
        free(line);
        line = NULL;
    }
}
int is_all_space(char *input)
{
    int i = 0;
    while(input[i])
    {
        if (input[i] != ' ')
            return 0;
        i++;
    }
    return 1;
}
int index_char(char *str)
{
    if (strcmp(str, "<") == 0)
        return (1);
    else if (strcmp(str, ">") == 0)
        return (2);
    else if (strcmp(str, ">>") == 0)
        return (3);
    else if (strcmp(str, "<<") == 0)
        return (4);
    else 
        return (2);
}

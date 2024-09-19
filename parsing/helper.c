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
void    handle_heredoc(char *input,t_cmd *cmd)
{
    char *line;

    while (1) {
        line = readline("> ");
        if (strcmp(line, cmd->hdoc_delimiter) == 0)
        {
			close(cmd->ft_in);
            return ;
        }
        line = expand_variables(cmd->env, line);
        ft_putendl_fd(line, cmd->ft_in);
        free(line);
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

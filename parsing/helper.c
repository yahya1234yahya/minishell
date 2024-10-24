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

char    chose_quotes(char   *str)
{
    int i = 0;
    int d_q = 0;
    int s_q = 0;

    while(str[i])
    {
        check_quots(str[i], &s_q, &d_q);
        i++;
    }
    if (s_q && !d_q)
        return ('"');
    if (!s_q && d_q)
        return ('\'');
    return ('"');
}

char* add_d_quot(char* str)
{
    int len ;
    int i = 0;
    int j = 0;

    len = ft_strlen(str);
    char* quoted_str = safe_malloc(len + 3, 'a');
    if (quoted_str == NULL)
        return (NULL);
    quoted_str[i] = chose_quotes(str);
    while(j < len)
    {
        quoted_str[i + 1] = str[j];
        i++;
        j++;
    }
    quoted_str[++i] = chose_quotes(str);
    quoted_str[++i] = '\0';
    return (quoted_str);
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

void signalhandlerherdoc(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = 1;
		close(STDIN_FILENO); 
	}
}

void    handle_heredoc(char *input,t_cmd *cmd)
{
    char *line;
    int is_quoted = 0;
    int i = 0;
	int tmp_fd;
    char *tmp;

	tmp_fd = dup(STDIN_FILENO); // i added this to remmember the fd of STDIN
	signal(SIGINT, signalhandlerherdoc); // i added this to modify the signal behaviour in the heredoc
    if (cmd->hdoc_delimiter[ft_strlen(cmd->hdoc_delimiter) - 1] == '\'' || cmd->hdoc_delimiter[ft_strlen(cmd->hdoc_delimiter) - 1] == '"')
            is_quoted = 1;
    cmd->hdoc_delimiter = remove_quotes(cmd->hdoc_delimiter);
    while (1)
	{
        line = readline("> ");
		if (line == NULL)
		{
			close(cmd->ft_in);		//i added this to close the file descriptor when ctrl + D is pressed
			break;
		}
        tmp = ft_strdup(line);
        if (ft_strcmp(tmp, cmd->hdoc_delimiter) == 0)
        {
			setandget(NULL)->exs = 0;
			free(line);
			close(cmd->ft_in);
            break;
        }
        if (is_quoted)

            line = add_quotes(line);

        line = expand_variables(cmd->env, line);
         if (is_quoted)
        {
            line = remove_quotes(line);
        }
        ft_putendl_fd(line, cmd->ft_in);
        free(line);
        line = NULL;
    }
	dup2(tmp_fd, STDIN_FILENO); //i added this  to reset the stdin
	signal(SIGINT, funcsign); //i added this to return the normal behaviour of signal
	g_signal = 0;
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
    if (ft_strcmp(str, "<") == 0)
        return (1);
    else if (ft_strcmp(str, ">") == 0)
        return (2);
    else if (ft_strcmp(str, ">>") == 0)
        return (3);
    else if (ft_strcmp(str, "<<") == 0)
        return (4);
    else 
        return (2);
}

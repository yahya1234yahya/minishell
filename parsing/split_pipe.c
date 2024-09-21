#include "../minishell.h"

void    split_pipe(t_cmd *cmd, char *input, char **envp)
{
    char *token;
    int i = 0;
    token = ft_strtok(input, "|");
    while (token != NULL)
    {
        cmd->input = ft_strdup(token);
        if ((token = ft_strtok(NULL, "|")) != NULL)
        {
            cmd->next = init_cmd();
            cmd = cmd->next;
            cmd->env = initenv(envp);//TODO we cange here
        }
    }
}
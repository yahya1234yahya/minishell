#include "../minishell.h"

char    *exit_status_case(char  *token)
{
    int     i;
    int     j;
    int     s_q;
    int     d_q;
    char    *new_token;

    new_token = safe_malloc(ft_strlen(token), 'a');
    i = 0;
    j = 0;
    s_q = 0;
    d_q = 0;
    while(token[i])
    {
        check_quots(token[i], &s_q, &d_q);
        if (token[i] == '$' && token[i + 1] == '?' && !s_q)
        {
            i++;
            new_token[j] = '0';
        }
        else
            new_token[j] = token[i];
        i++;
        j++;
    }
    new_token[j] = '\0';
    return (new_token);
}
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
            // token = exit_status_case(token);
            cmd->next = init_cmd();
            cmd = cmd->next;
            cmd->env = initenv(envp);
        }
        i++;
            
    }
    
        
}
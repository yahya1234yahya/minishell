#include "../minishell.h"

int check_complete(t_cmd *cmd)
{
	int		len;
    int		i;
    int		found;
	char	quote_char;
    char    *input;
    t_cmd	*tmp;

    tmp = cmd;
    while(tmp)
    {
        input = ft_strtrim(tmp->input, " \t");
        // printf("input: %s\n", input);
        len = ft_strlen(input);
        if (!len)
            return (0);
        if (input[len - 1] == '|' || input[len - 1] == '<' || input[len - 1] == '>' || input[len - 1] == '\\')
            return (0);
        i = 0;
        while (i < len)
        {
            if (input[i] == '"' || input[i] == '\'')
            {
                quote_char = input[i++];
                found = 0;
                while (i < len)
                {
                    if (input[i] == quote_char)
                    {
                        found = 1;
                        break;
                    }
                    i++;
                }
                if (!found)
                    return (0);
            }
            i++;
        }
        tmp = tmp->next;
    }
    return (1);
}


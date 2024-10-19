#include "../minishell.h"

int check_complete(char *input)
{
	int		len;
    int		i;
    int		found;
	char	quote_char;


        // printf("input: %s\n", input);
        input = ft_strtrim(input, " \t");
        len = ft_strlen(input);
        if (!len || input[len - 1] == '|' || input[len - 1] == '<' || input[len - 1] == '>' || input[len - 1] == '\\')
        {
            ft_putstr_fd("minishell: syntax error\n", 2);
			setandget(NULL)->exs = 2;
            return (0);
        }
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
                {
                    ft_putstr_fd("minishell: syntax error\n", 2);
			        setandget(NULL)->exs = 2;
                    return (0);
                }
            }
            i++;
        }
    return (1);
}


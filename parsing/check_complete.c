#include "../minishell.h"

int check_redirect(char *str)
{
    int i;
    int d_q;
    int s_q;
    int out;
    int in;

    out = 0;
    in = 0;
    d_q = 0;
    s_q = 0;
    i = 0;

    while(str[i])
    {
        check_quots(str[i], &s_q, &d_q);
        if (str[i] == '<' && !s_q && !d_q)
        {
            in++;
            if (out || in > 2)
            {
                ft_putstr_fd("minishell: syntax error\n", 2);
			    setandget(NULL)->exs = 2;
                return (0);
            }
        }
        else if (str[i] == '>' && !s_q && !d_q)
        {
            out++;
            if (in || out > 2)
            {
                printf("here str is : %s\n",str);
                ft_putstr_fd("minishell: syntax error\n", 2);
			    setandget(NULL)->exs = 2;
                return (0);
            }
        }
        else if (str[i] != ' ' && str[i] != '\t')
        {
            in = 0;
            out = 0;
        }
        i++;
    }
    return (1);
}
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
        if (check_redirect(input) == 0)
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


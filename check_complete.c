#include "minishell.h"

int check_complete(const char *input)
{
	int		len;
    int		i;
    int		found;
	char	quote_char;

	len = strlen(input);
    if (!len)
		return (0);
    while (len > 0 && isspace(input[len - 1]))
		len--;
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
    return (1); 
}

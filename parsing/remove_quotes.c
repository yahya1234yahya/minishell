#include "../minishell.h"

char *remove_quotes(char *input)
{
    if (!input)
        return (NULL);
    int length = strlen(input);
    char quote;
    char *new_input = (char *)safe_malloc(length + 1, 'a');
    int i = 0;
    int j = 0;
    while (i <= length)
    {
        if (input[i] == '"' || input[i] == '\'') {
            quote = input[i];
            i++;
            while (i <= length && input[i] != quote)
                new_input[j++] = input[i++];
            if (i <= length && input[i] == quote)
                i++;
        }
        else
        {
            new_input[j++] = input[i++];
        }
    }
    new_input[j] = '\0';
    if (i != j && j == 0)
        return (NULL);
    if (is_all_space(new_input))
    {
        new_input[0] = '\0';
        return (new_input);
    }
    return new_input;
}

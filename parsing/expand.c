#include "../minishell.h"

char *expand_variables(char *input)
{
    int length = 0;
    int i = 0;
    int j = 0;
    int z = 0;
    char *name;
    char *env_value;
    char *new_input;
    while (input[i])
    {
        if (input[i] == '$' && input[i + 1] && input[i + 1] != ' ')
        {
            i++;
            j = i;
            while (input[j] && input[j] != ' ')
                j++;
            name = malloc(j - i + 1);
            z = 0;
            while (i < j)
            {
                name[z] = input[i];
                z++;
                i++;
            }
            name[z] = '\0';
            env_value = getenv(name);
            if (env_value)
                length += ft_strlen(env_value);
            else
                length += 0;
            free(name);
        }
        else
        {
            length++;
            i++;
        }
    }
    i = 0;
    j = 0;
    new_input = malloc(length + 1);
    while (input[i])
    {
        if (input[i] == '$' && input[i + 1] && input[i + 1] != ' ')
        {
            i++;
            int start = i;
            while (input[i] && input[i] != ' ')
                i++;
            name = malloc(i - start + 1);
            strncpy(name, &input[start], i - start);
            name[i - start] = '\0';
            env_value = getenv(name);
            if (env_value)
            {
                strcpy(&new_input[j], env_value);
                j += ft_strlen(env_value);
            }
            free(name);
        }
        else
        {
            new_input[j++] = input[i++];
        }
    }
    new_input[j] = '\0';
    return (new_input);
}



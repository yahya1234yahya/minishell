#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdlib.h>
#include <string.h>

char **ft_strtok_all(char *str, char *delim)
{
    int dquote = 0, squote = 0, token_count = 0;
    char **tokens = malloc(10 * sizeof(char *));
    char *current_token;

    if (!tokens)
        return NULL;

    while (*str) {
        while (*str && strchr(delim, *str) != NULL)
            str++;
        if (!(*str))
            break;

        current_token = str;

        while (*str) {
            if (*str == '"' && squote == 0)
                dquote = !dquote;
            else if (*str == '\'' && dquote == 0)
                squote = !squote;
            else if (strchr(delim, *str) != NULL && dquote == 0 && squote == 0)
                break;
            str++;
        }

        int token_len = str - current_token;
        tokens[token_count] = malloc((token_len + 1) * sizeof(char));
        strncpy(tokens[token_count], current_token, token_len);
        tokens[token_count][token_len] = '\0';
        token_count++;

        if (token_count == 10)
            break;

        if (*str)
            str++;
    }

    tokens[token_count] = NULL;
    return tokens;
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
char *remove_quotes(char *input)
{
    if (!input)
        return (NULL);
    int length = strlen(input);
    char quote;
    char *new_input = (char *)malloc(length + 1);
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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char str[] = "ls | grep \"\"";
    char delim[] = " ";

    char **tokens = ft_strtok_all(str, delim);
    while(*tokens)
    {
        *tokens = remove_quotes(*tokens);
        printf("token %s\n", *tokens);
        tokens++;
    }
   
    return 0;
}

#include "../minishell.h"

char *ft_strtok(char *str, char *delim)
{
    static char *next_token;
    char *current_token;
    int dquote = 0, squote = 0;

    if (str != NULL)
        next_token = str;
    if (next_token == NULL)
        return NULL;
    while (*next_token && strchr(delim, *next_token) != NULL)
        next_token++;
    if (!(*next_token))
        return NULL;
    current_token = next_token;
    while (*next_token) {
        if (*next_token == '"' && squote == 0)
            dquote = !dquote;
        else if (*next_token == '\'' && dquote == 0)
            squote = !squote;
        else if (strchr(delim, *next_token) != NULL && dquote == 0 && squote == 0)
            break;
        next_token++;
    }
    if (*next_token) {
        *next_token = '\0';
        next_token++;
    }
    return (current_token);
}

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

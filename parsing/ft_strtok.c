#include "../minishell.h"

// char *ft_strtok(char *str, char *delim)
// {
//     static char *next_token = NULL;
//     if (str != NULL) {
//         next_token = str;
//     }

//     if (next_token == NULL || *next_token == '\0') {
//         return NULL;
//     }

//     while (*next_token != '\0' && strchr(delim, *next_token) != NULL) {
//         next_token++;
//     }

//     if (*next_token == '\0') {
//         return NULL;
//     }

//     char *current_token = next_token;

//     while (*next_token != '\0' && strchr(delim, *next_token) == NULL) {
//         next_token++;
//     }

//     if (*next_token != '\0') {
//         *next_token = '\0';
//         next_token++;
//     }

//     return current_token;
// }
// char *ft_strtok(char *str, char *delim)
// {
//     static char *next_token ;
// 	int dquote = 0;
//     if (str != NULL) {
//         next_token = str;
//     }

//     if (next_token == NULL || *next_token == '\0') {
//         return NULL;
//     }

//     while (*next_token != '\0' && strchr(delim, *next_token) != NULL) {
// 		if (*next_token == '"')
// 			dquote = 1;
// 		else if (*next_token == '\'' && dquote == 0)
// 			dquote = 2;

//         next_token++;
//     }
//     if (*next_token == '\0') {
//         return NULL;
//     }
//     char *current_token = next_token;
// 	if (dquote == 1)
// 	{
// 		while (*next_token != '\0' && *next_token != '"') {
// 			next_token++;
// 		}
// 	}
// 	else if (dquote == 2)
// 	{
// 		while (*next_token != '\0' && *next_token != '\'') {
// 			next_token++;
// 		}
// 	}
// 	else
// 	{
//     while (*next_token != '\0' && strchr(delim, *next_token) == NULL) {
//         next_token++;
//     }
// 	}

//     if (*next_token != '\0') {
//         *next_token = '\0';
//         next_token++;
//     }

//     return current_token;
// }



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


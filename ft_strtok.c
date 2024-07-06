#include "minishell.h"

char *ft_strtok(char *str, const char *delim) {
    static char *next_token = NULL;
    if (str != NULL) {
        next_token = str;
    }

    if (next_token == NULL || *next_token == '\0') {
        return NULL;
    }

    while (*next_token != '\0' && strchr(delim, *next_token) != NULL) {
        next_token++;
    }

    if (*next_token == '\0') {
        return NULL;
    }

    char *current_token = next_token;

    while (*next_token != '\0' && strchr(delim, *next_token) == NULL) {
        next_token++;
    }

    if (*next_token != '\0') {
        *next_token = '\0';
        next_token++;
    }

    return current_token;
}

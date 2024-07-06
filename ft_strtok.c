#include "minishell.h"


// gerated by CHATGPT HHHHHHHHHH NO TIME HHHHHHHHHHH


char *ft_strtok(char *str, const char *delim) {
    static char *next_token = NULL;  // pointer to the next token in the string
    if (str != NULL) {
        next_token = str;  // start tokenizing from the beginning of str
    }

    if (next_token == NULL || *next_token == '\0') {
        return NULL;  // no more tokens to parse
    }

    // Skip leading delimiters
    while (*next_token != '\0' && strchr(delim, *next_token) != NULL) {
        next_token++;
    }

    if (*next_token == '\0') {
        return NULL;  // reached end of string
    }

    // Start of the next token is here
    char *current_token = next_token;

    // Find end of token
    while (*next_token != '\0' && strchr(delim, *next_token) == NULL) {
        next_token++;
    }

    if (*next_token != '\0') {
        *next_token = '\0';  // replace delimiter with null terminator
        next_token++;        // move to next character after the delimiter
    }

    return current_token;  // return the current token
}

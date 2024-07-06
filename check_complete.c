#include "minishell.h"

int check_complete(const char *input) {
    int len = strlen(input);
    if (len == 0) return 0;  
    while (isspace(input[len - 1])) len--;
    if (input[len - 1] == '|' || input[len - 1] == '<' || input[len - 1] == '>') {
        return 0; 
    }
    int quote_count = 0;
    for (int i = 0; i < len; i++) {
        if (input[i] == '"') {
            quote_count++;
        }
    }
    if (quote_count % 2 != 0) {
        return 0; 
    }

    return 1; 
}
#include "minishell.h"

int check_complete(const char *input) {
    int len = strlen(input);
    if (len == 0) return 0;  
    
    while (len > 0 && isspace(input[len - 1])) len--;
    
    if (input[len - 1] == '|' || input[len - 1] == '<' || input[len - 1] == '>' || input[len - 1] == '\\') {
        return 0; 
    }
    
    int i = 0;
    while (i < len) {
        if (input[i] == '"' || input[i] == '\'') {
            char quote_char = input[i++];
            int found = 0;
            while (i < len) {
                if (input[i] == quote_char) {
                    found = 1;
                    break;
                }
                i++;
            }
            if (!found) return 0;
        }
        i++;
    }

    return 1; 
}

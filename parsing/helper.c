#include "../minishell.h"


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
int index_char(char *str)
{
    if (strcmp(str, "<") == 0)
        return (1);
    else if (strcmp(str, ">") == 0)
        return (2);
    else if (strcmp(str, ">>") == 0)
        return (3);
    else if (strcmp(str, "<<") == 0)
        return (4);
    else 
        return (2);
}
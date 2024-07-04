
#include "minishell.h"


int main()
{
    while(1)
    {
        char *input = readline("\033[32mminishell\033[0m \033[34m>\033[0m ");
        printf("command works : %s\n", input);
		free(input);
    }
}
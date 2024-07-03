#include <stdio.h>

#include <readline/readline.h>
#include <readline/history.h>

int main()
{
    while(1)
    {

        char *input = readline("mini-shell>  ");
        printf("command works : %s\n", input);
    }
}
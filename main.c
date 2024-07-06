
#include "minishell.h"


int main() {
    t_cmd cmd;
    while (1) {
        char *input = readline("\033[32mminishell\033[0m \033[34m>\033[0m ");
        parse(&cmd, input, 0);
        if (cmd.redirection)
            printf("there is a redariction\n");
        if (cmd.pipe)
            printf("there is a pipe\n");
        free(input);
    }
    return 0;
}
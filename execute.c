#include "minishell.h"



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int execute(t_cmd *cmd)
{
    int pid;
    char **full;

    full = ft_split(cmd->args, ' ');
        
    pid = fork();
    // if (pid == -1)
        //
    
    if (pid == 0)
    {
        execvp(cmd->cmd, full);
        //if
    }
    else
        waitpid(pid, NULL, 0);

    // free(full[0]);
    // free(full[1]);
    // free(full);
    return 0;
}


#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdio.h>


int main(void)
{
    char *args[] = {"ls", "-la", NULL};
    int pid = fork();

    if (pid != 0)
    {
        execvp(args[0], args);
    }
    

    return (0);
}
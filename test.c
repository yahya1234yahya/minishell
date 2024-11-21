#include <libc.h>

void f()
{
    system("leaks a.out");
}

int main()
{
    atexit(f);
    char *s = malloc(20);

    int pid = fork();

    if (pid == 0)
    {
        // free(s);
    }
    else
    {
        wait(NULL);
        free(s);
    }
        
}
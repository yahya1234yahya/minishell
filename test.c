#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int is_single_quote(char *input, int i)
{
    int j = 0;
    int found = 0;
    while(j < i)
    {
        if (input[j] = '\'')
            found += 1; 
        j++;
    }
    if (found % 2 != 0)
        return (1);
    return (0);
}

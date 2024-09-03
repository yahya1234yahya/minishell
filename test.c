#include <stdio.h>
#include <stdlib.h>

char    *add_space(char *input)
{
    int i = 0;
    int count = 0;
    int j = 0;
    while(input && input[i])
    {
        if (input[i] == '<' || input[i] == '>')
        {
            if (i > 0 && input[i - 1] != '<' && input[i - 1] != '>')
                count += 2;
            count++;
            i++;
            continue ;
        }
        i++;
        count++;
    }
    char *new_input = malloc(count + 1);
    i = 0;
    while(input && input[i])
    {
        if (input[i] == '<' || input[i] == '>')
        {
            if (i > 0 && input[i - 1] != '<' && input[i - 1] != '>')
                new_input[j++] = ' ';
            new_input[j++] = input[i++];
            if (input[i] != '<' && input[i] != '>')
                new_input[j++] = ' ';
            continue;
        }
        new_input[j++] = input[i++];
    }
    new_input[j] = '\0';
    return (new_input);

}

int main()
{
    char    *input = "cd<1>2<<1>>1";
    printf("str : %s", add_space(input));
    return 0;
}
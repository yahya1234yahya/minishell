#include <stdio.h>
#include <stdlib.h>

int check_redi(char	*input)
{
	int i = 0;
	int red = 0;

	while (input[i])
	{
		if (input[i] == '<' || input[i] == '>')
		{
			red++;
			if (red > 2)
				return (0);
		}
		else if (input[i] != ' ' && input[i] != '|')
			red = 0;
		i++;
	}
	return (1);
}

int main()
{
    char    *input = "cd<1>2>>1>>1";
    printf("str : %d", check_redi(input));
    return 0;
}
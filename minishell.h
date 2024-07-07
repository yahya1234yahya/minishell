#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
#include <stdbool.h> 
#include <fcntl.h>
#include <unistd.h>

typedef struct s_cmd
{
	char	*cmd;
	char	*args;
	int		pipe;
	int		redirection;
	int		fd_redirect;
	struct 	s_cmd *next;
} t_cmd;

char *ft_strtok(char *str, const char *delim);
void parse(t_cmd *cmd, char *input, int rec);
int check_complete(const char *input);
char	*ft_strjoin(char const *s1, char const *s2);



// echo with -n option
// cd with relative or absolute path
// pwd with no options
// export with no options
// unset with no options
// env with no options or arguments
// exit with no options
#endif
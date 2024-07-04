#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_cmd
{
	char	*cmd;
	char	*args;
	int		pipe;
	int		redirection;  //we give each element a token
	struct 	s_cmd *next;
} t_cmd;

// echo with -n option
// cd with relative or absolute path
// pwd with no options
// export with no options
// unset with no options
// env with no options or arguments
// exit with no options
#endif
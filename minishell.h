#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
<<<<<<< HEAD
#include <stdbool.h> 
#include <fcntl.h>
#include <unistd.h>
=======
# include <stdbool.h> 
# include <unistd.h>
# include <sys/types.h>
// # include <sys/wait.h>
>>>>>>> 410220e6b00f5d3a617daeefdad397de3cabc8e0

typedef struct s_cmd
{
	char	*cmd;
	char	*args;
	int		pipe;
	int		redirection;
	int		fd_redirect;
	struct 	s_cmd *next;
} t_cmd;

char	*ft_strtok(char *str, const char *delim);
void	parse(t_cmd *cmd, char *input, int rec);
int		check_complete(const char *input);
char	*ft_strjoin(char const *s1, char const *s2);
int		execute(t_cmd *cmd);
char	**ft_split(char *s, char c);



// echo with -n option
// cd with relative or absolute path
// pwd with no options
// export with no options
// unset with no options
// env with no options or arguments
// exit with no options
#endif
#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
#include <stdbool.h> 
#include <fcntl.h>
#include <unistd.h>
# include <stdbool.h> 
# include <unistd.h>
# include <sys/types.h>
// #include <libc.h>
#include <ctype.h>
// # include <sys/wait.h>

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

//execution
int		execute(t_cmd *cmd);
void	ft_echo(t_cmd *cmd);
void	decider(t_cmd *cmd, char **envp);
void	ft_pwd(char **envp);
void	notbuilt(t_cmd *cmd);

//tools
char	**ft_split(char *s, char c);
int		ft_strcmp(const char	*s1, const char	*s2);
void	ft_putstr_fd(char *s, int fd);

// echo with -n option
// cd with relative or absolute path
// pwd with no options
// export with no options
// unset with no options
// env with no options or arguments
// exit with no options
#endif
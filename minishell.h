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
#include <libc.h>
#include <ctype.h>
// # include <sys/wait.h>

typedef struct s_env
{
	char			*name;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char	*cmd;
	char	*args;
	int		pipe;
	int		redirection;
	int		fd_redirect;
	char 	*path;
	t_env	*env;
	struct 	s_cmd *next;
} t_cmd;



char	*ft_strtok(char *str, const char *delim);
int		parse(t_cmd *cmd, char *input, int rec);
int		check_complete(const char *input);
char	*ft_strjoin(char const *s1, char const *s2);
t_env	*envsearch(t_env *env, char *name);
char    *remove_quotes(char *input);
void 	print_commands(t_cmd *head);

//execution
int		execute(t_cmd *cmd);
void	ft_echo(t_cmd *cmd);
void	decider(t_cmd *cmd, char **envp);
void	ft_pwd(t_env *env);
void	notbuilt(t_cmd *cmd, char **envp);
t_env 	*initenv(char **envp);
void 	changedir(t_cmd *cmd);
t_cmd	*init_cmd(void);
void	printenv(t_env *env);
t_env	*envset(t_env *env, char *name, char *value);

//tools
char	**ft_split(char *s, char c);
int		ft_strcmp(const char	*s1, const char	*s2);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strnstr(char	*haystack, char	*needle, size_t	len);
size_t ft_strlen(const char *s);
// echo with -n option
// cd with relative or absolute path
// pwd with no options
// export with no options
// unset with no options
// env with no options or arguments
// exit with no options
#endif
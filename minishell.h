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
#include <ctype.h>
#include <string.h>
// # include <sys/wait.h>
#define BUFFER_SIZE 200

typedef struct s_env
{
	char			*name;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	int 	originalfd[2];
	int 	pipedfd[2];
} t_data;

typedef struct s_cmd
{
	char	*cmd;  
	char	*args;
	int		pipe;
	int		redout;
	int		redin;
	int		ft_in;
	int		ft_out;
	char 	*path;
	char	*hdoc;
	t_env	*env;
	t_data	data;
	struct 	s_cmd *next;
} t_cmd;


void 	ft_export(t_cmd *cmd);
char	*ft_strtok(char *str, char *delim);
int		parse(t_cmd *cmd, char *input, char **envp, int rec);
int		check_complete(const char *input);
char	*ft_strjoin(char  *s1, char  *s2);
t_env	*envsearch(t_env *env, char *name);
char    *remove_quotes(char *input);
void 	print_commands(t_cmd *head);
int		is_all_space(char *input);
char 	*expand_variables(char *input);
int index_char(char *str);

//execution
void	ft_echo(t_cmd *cmd);
void	decider(t_cmd *cmd);
void	ft_pwd(t_env *env);
void	notbuilt(t_cmd *cmd, char **envp);
t_env 	*initenv(char **envp);
void 	changedir(t_cmd *cmd);
t_cmd	*init_cmd(void);
void	printenv(t_env *env);
t_env	*envset(t_env *env, char *name, char *value);
t_env	*ft_lstnew(void *content);
void	ft_lstadd_back(t_env **lst, t_env *newnode);
void	ft_unset(t_env **env, t_cmd *cmd);
char	*get_next_line2(char **line, char **rem, char **buf, int fd);
int		newcheck(char *str);
char	*ft_strdup(char *s1);
size_t	ft_strlcpy(char	*dst, char	*src, size_t	dstsize);
char	*get_next_line(int fd);
char	*ft_cutfront(char *line);
char	*ft_cutback(char *line);
void	redirectchange(t_cmd *cmd);
char	**convert(t_cmd *cmd);
void	args(t_cmd *cmd, char **envp, int i, char **fixed, char **splited);
void	noargs(t_cmd *cmd, char **envp, char **fixed, char **splited);
char	**prepend_array(char **original, char *new_element);
int		calculateargs(t_cmd *cmd);
t_cmd 	*hdoc(char *delimiter, t_cmd *cmd);
int		filedreset(int input, int output);
void	execfromsystem(t_cmd *cmd, char **envp);

//
// void execute_pipeline(t_cmd *cmds, int num_cmds, char **envp);
int nodeslen(t_cmd *cmd);

//tools
char	**ft_split(char *s, char c);
int		ft_strcmp(const char	*s1, const char	*s2);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strnstr(char	*haystack, char	*needle, size_t	len);
size_t	ft_strlen( char *s);
// echo with -n option
// cd with relative or absolute path
// pwd with no options
// export with no options
// unset with no options
// env with no options or arguments
// exit with no options
#endif
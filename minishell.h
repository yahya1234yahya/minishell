#ifndef MINISHELL_H
# define MINISHELL_H


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
#include <signal.h>
#include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
// # include <sys/wait.h>
#define BUFFER_SIZE 200


typedef struct s_garbage
{
    void                *adr;
    bool                is_free;
    struct s_garbage    *next;
}    t_garbage;

typedef struct s_env
{
	char			*name;
	char			*key;
	char 			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	int 	originalfd[2];
	int 	pipedfd[2];
} t_data;

typedef struct s_cmd
{
	char	*input;
	char	**tokens;
	char	*cmd;  
	char	*args;
	int		pipe;
	int		redout;
	int		redin;
	int		ft_in;
	int		ft_out;
	char 	*path;
	char	*hdoc_delimiter;
	t_env	*env;
	t_data	data;
	char	**splited;
	int		exs;
	int 	first_run;
	int		fd_hdoc;
	int		signal_exs_flag;
	int		skip;
	struct 	s_cmd *next;
} t_cmd;

typedef struct s_exp
{
	char *key;
	char *value;
	char plus;
	char equal;
} t_exp;

int g_signal;

int 	ft_export(t_cmd *cmd);
char	*ft_strtok(char *str, char *delim);
int		parse(t_cmd *cmd, char *input, char **envp, int rec);
char	*ft_strjoin(char  *s1, char  *s2);
t_env	*envsearch(t_env *env, char *key);
char    *remove_quotes(char *input);
void 	print_commands(t_cmd *head);
int		is_all_space(char *input);
char 	*expand_variables(t_env *env, char *input);
int		index_char(char *str);
void	my_free(t_cmd *t);
void	handle_heredoc(char *input, t_cmd *cmd);
void	split_pipe(t_cmd *cmd, char *input, char **envp);
char	**ft_strtok_all(char *str, char *delim);
void	check_quots(char c, int *single_q, int  *double_q);
int		redouthelper(t_cmd *cmd);
void	handle_args(t_cmd *cmd);
int		fd_error(t_cmd *cmd);
void	herdoc(t_cmd *cmd);
void	check_cmd(t_cmd *cmd);
void	check_cases(t_cmd *cmd);
char	*skip_whitespace(char *str);
int		is_valid_command(t_cmd *cmd, char *word);
void	handle_redirection_error(void);
void	handle_export_sort(t_cmd *cmd, char	**envp);
char	**handle_redirection_in(t_cmd *cmd, char **tokens);
char	**handle_redirection_out(t_cmd *cmd, char **tokens);



//execution
t_env 	*initenv(char **envp);
t_cmd	*set_cmd(t_cmd *cmd);
t_cmd	*init_cmd();
t_env	*envset(t_env *env, char *name, char *value);
t_env	*ft_lstnew(void *content);
void	ft_lstadd_back(t_env **lst, t_env *newnode);
void	decider(t_cmd *cmd);
int		ft_echo(t_cmd *cmd);
int		ft_pwd(t_env *env);
int 	changedir(t_cmd *cmd);
int		printenv(t_env *env, int flag);
void	printenv2(t_env *current);
int		ft_unset(t_env **env, t_cmd *cmd);
int		redirectchange(t_cmd *cmd);
char	**convert(t_cmd *cmd);
int		filedreset(int input, int output);
int		execfromsystem(t_cmd *cmd, char **envp);
int		executemultiple(t_cmd *cmd);
int		executesingle(t_cmd *cmd , char **envp);
int		preparecmd(t_cmd *cmd);
int		ft_errorwrite(t_cmd *cmd);
int		exportsignal(int sig, t_cmd *cmd);
t_cmd	*setandget(t_cmd *cmd);
char	*envsearch2(t_env *env, char *name);
int		check_command(char *command);
void	ft_exit(char *data, int flag);
char	*envsearch3(t_env *env, char *name);
t_env 	*envset2(t_env *env, char *key, char *value);
void 	funcsign(int signum);
int 	exportwithouthvalue(t_exp exp, t_cmd *cmd);
int 	isbuiltin(t_cmd *cmd, int value, int flag);
void	parent(int *input, int *pipefd);
int		child(t_cmd *cmd, int input, int *pipefd);
int		executesingle(t_cmd *cmd , char **envp);
// void	exportlastcommand(t_cmd *cmd);
void exportlastcommand(t_cmd *cmd);

//tools
char	**ft_split(char *s, char c);
int		ft_strcmp(const char	*s1, const char	*s2);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strnstr(char	*haystack, char	*needle, size_t	len);
size_t	ft_strlen( char *s);
size_t	ft_strlcpy(char	*dst, char	*src, size_t	dstsize);
char	*ft_strdup(char *s1);
char	*ft_strtrim(char  *s1, char  *set);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_strncmp(const char	*s1, const char	*s2, size_t	n);
int		ft_strcmp2(const char *s1, const char *s2);
int		ft_tolower(int c);
int		helper(t_cmd *cmd);
void    *safe_malloc(size_t size, int flag);
int		check_complete(char *input);
char	*ft_substr(char  *s, unsigned int start, size_t len);
int		check_char(char  *set, char c);
int		ft_tolower(int c);
// int		ft_export_status(t_cmd *cmd);
// char	*ft_strchr(const char *s, int c); //TODO


#endif
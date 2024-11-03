/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 20:12:26 by mboughra          #+#    #+#             */
/*   Updated: 2024/10/27 20:12:26 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define MLL 9223372036854775807ULL
# define MLLOF 9223372036854775808ULL
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h> 
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h> 
# include <unistd.h>
# include <sys/types.h>
# include <ctype.h>
# include <string.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_garbage
{
	void				*adr;
	bool				is_free;
	struct s_garbage	*next;
}	t_garbage;

typedef struct s_env
{
	char			*name;
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_check_r
{
	int	i;
	int	d_q;
	int	s_q;
	int	out;
	int	in;
}	t_check_r;

typedef struct s_parse
{
	char	*next_word;
	int		flags;
	char	*delimiter;
	char	*tmp_args;
	int		i;
}	t_parsing;

typedef struct s_check_c
{
	int		i;
	int		found;
	char	quote_char;
}	t_check_c;

typedef struct s_valid_command
{
	t_env	*tmp;
	char	*path_env;
	char	f_p[1024];
	char	*dir;
	char	*path_dup;
}	t_valid;

typedef struct s_data
{
	int		originalfd[2];
	int		pipedfd[2];
}	t_data;

typedef struct s_parse_it
{
	int		count;
	int		d_quot;
	int		s_quot;
	char	c;
	char	*res;
	int		j;
	int		z;
}	t_parse;

typedef struct s_expand
{
	int		count;
	int		count_name;
	int		single_q;
	int		double_q;
	int		i;
	int		j;
	char	*name;
	char	*env_value;
	char	*new_input;
	char	*tmp;
	char	*tmp2;
}	t_expa;

typedef struct s_count
{
	int		count;
	int		count_name;
	int		single_q;
	int		double_q;
	int		i;
	char	*name;
	char	*env_value;
}	t_count;

typedef struct s_cmd
{
	char			*input;
	char			**tokens;
	char			*cmd;
	char			*args;
	int				pipe;
	int				redout;
	int				redin;
	int				ft_in;
	int				ft_out;
	char			*path;
	char			*hdoc_delimiter;
	t_env			*env;
	t_data			data;
	char			**splited;
	int				exs;
	int				first_run;
	int				fd_hdoc;
	int				found;
	int				signal_exs_flag;
	int				skip;
	char			*herdoc_file;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_exp
{
	char	*key;
	char	*v;
	char	plus;
	char	equal;
}	t_exp;

int	g_signal;

char		*add_d_quot(char *str);
int			ft_export(t_cmd *cmd);
char		*ft_strtok(char *str, char *delim);
int			parse(t_cmd *cmd);
char		*ft_strjoin(char *s1, char *s2);
t_env		*envsearch(t_env *env, char *key);
char		*remove_quotes(char *input);
void		print_commands(t_cmd *head);
int			is_all_space(char *input);
char		*expand_variables(t_env *env, char *input, int herdoc);
int			index_char(char *str);
int			handle_heredoc(t_cmd *cmd);
void		split_pipe(t_cmd *cmd, char *input, t_env *envp);
char		**ft_strtok_all(char *str, char *delim);
void		check_quots(char c, int *single_q, int *double_q);
int			redouthelper(t_cmd *cmd);
void		handle_args(t_cmd *cmd);
int			fd_error(t_cmd *cmd);
int			herdoc(t_cmd *cmd);
void		check_cmd(t_cmd *cmd);
int			check_cases(t_cmd *cmd);
char		*skip_whitespace(char *str);
int			is_valid_command(t_cmd *cmd, char *word);
void		handle_redirection_error(void);
void		handle_export_sort(t_cmd *cmd, char **envp);
char		**handle_redirection_in(t_cmd *cmd);
char		**handle_redirection_out(t_cmd *cmd);
int			check_exit(char *path, char *word);
void		check_quots(char c, int *single_q, int *double_q);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			count_word(char *input);
char		*count_one(t_count *co, char *input, t_env *env, int herdoc);
void		init_struct(t_expa *expa, char *input, t_env *env, int herdoc);
int			count_new_input(t_env *env, char *input, int herdoc);
int			index_char(char *str);
int			is_all_space(char *input);
char		*add_d_quot(char *str);
void		ft_putendl_fd(char *s, int fd);
char		chose_quotes(char *str);
void		print_exit_s(char *str, int i);
int			is_there_space(char *input);
char		*add_space(char *input);
int			calculate_space(char *input);
char    	*ft_random(void);
char		*find_name(void);
void    ft_unlink(t_cmd *cmd);
//execution
t_env		*initenv(char **envp);
t_cmd		*set_cmd(t_cmd *cmd);
t_cmd		*init_cmd(void);
t_env		*ft_lstnew(void *content);
void		addback(t_env **lst, t_env *newnode);
void		decider(t_cmd *cmd);
int			ft_echo(t_cmd *cmd);
int			ft_pwd(t_env *env);
int			changedir(t_cmd *cmd);
int			printenv(t_env *env, int flag);
void		printenv2(t_env *current);
int			ft_unset(t_env **env, t_cmd *cmd);
int			redirectchange(t_cmd *cmd);
char		**convert(t_cmd *cmd);
int			filedreset(int input, int output);
int			execfromsystem(t_cmd *cmd, char **envp);
int			executemultiple(t_cmd *cmd);
int			executesingle(t_cmd *cmd, char **envp);
int			preparecmd(t_cmd *cmd);
int			ft_errorwrite(t_cmd *cmd);
int			exportsignal(int sig, t_cmd *cmd);
t_cmd		*setandget(t_cmd *cmd);
char		*envsearch2(t_env *env, char *name);
int			check_command(char *command);
void		ft_exit(char *data, int flag);
char		*envsearch3(t_env *env, char *name);
t_env		*envset2(t_env *env, char *key, char *value);
void		funcsign(int signum);
int			exportwithouthvalue(t_exp exp, t_cmd *cmd);
int			isbuiltin(t_cmd *cmd, int value, int flag);
void		parent(int *input, int *pipefd);
void		child(t_cmd *cmd, int input, int *pipefd);
int			executesingle(t_cmd *cmd, char **envp);
void		exportlastcommand(t_cmd *cmd, int flag);
void		no_args(char *data);
int			too_many_args(char **str, int flag);
char		**preparexit(char *data);
long long	ft_atoil(const char *str);
char		convertexit(int num);
void		print_numeric_error(char *str);
int			caseofnocp(t_cmd *cmd, char *cp);
int			headhome(t_cmd *cmd, char *current_path);
int			checkiffail(char *destination);
void		printerror(char *path, int error);
char		*preparearcd(t_cmd *cmd);
int			normalcase(t_cmd *cmd, char *current_path);
int			check_string(char *str);
int			plusaddpack(t_env **env, char *key, char *value);
int			preexport(t_cmd *cmd);
int			parskey(char *str);
void		printerrorexport(char *str);
int			checkplus(char *str);
char		**preparetokens(char *str);
int			parsename(char *name);
int			waiter(int *status);
void		perrornb(char *str);
void		argsprepare(t_cmd *cmd);
void		reset(t_cmd *cmd);
//tools
char		**ft_split(char *s, char c);
int			ft_strcmp(const char	*s1, const char	*s2);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strnstr(char	*haystack, char	*needle, size_t	len);
size_t		ft_strlen( char *s);
size_t		ft_strlcpy(char	*dst, char	*src, size_t	dstsize);
char		*ft_strdup(char *s1);
char		*ft_strtrim(char *s1, char *set);
char		*ft_itoa(int n);
int			ft_atoi(const char *str);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_strncmp(const char	*s1, const char	*s2, size_t	n);
int			ft_strcmp2(const char *s1, const char *s2);
int			ft_tolower(int c);
int			helper(t_cmd *cmd);
void		*safe_malloc(size_t size, int flag);
int			check_complete(char *input);
char		*ft_substr(char *s, unsigned int start, size_t len);
int			check_char(char *set, char c);
int			ft_tolower(int c);
int			onechar(char *str, char c);

#endif
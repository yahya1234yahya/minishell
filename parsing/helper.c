/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:44:58 by ymouigui          #+#    #+#             */
/*   Updated: 2024/10/27 13:44:58 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	chose_quotes(char *str)
{
	int	i;
	int	d_q;
	int	s_q;

	i = 0;
	d_q = 0;
	s_q = 0;
	while (str[i])
	{
		check_quots(str[i], &s_q, &d_q);
		i++;
	}
	if (s_q && !d_q)
		return ('"');
	if (!s_q && d_q)
		return ('\'');
	return ('"');
}

void	signalhandlerherdoc(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = 1;
		close(STDIN_FILENO);
		rl_replace_line("", 0);
		setandget(NULL)->exs = 1;
		reset(setandget(NULL));
		ft_unlink(setandget(NULL));
	}
}

static int	helper2(t_cmd	*cmd, char	*line)
{
	if (line == NULL)
	{
		close(cmd->ft_in);
		open(cmd->herdoc_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		return (1);
	}
	if (ft_strcmp(line, cmd->hdoc_delimiter) == 0)
	{
		setandget(NULL)->exs = 0;
		close(cmd->ft_in);
		return (1);
	}
	return (0);
}

int	read_herdoc(t_cmd *cmd, int is_quoted, int tmp_fd, int flag)
{
	char	*line;
	char	*input;

	while (1)
	{
		input = readline("> ");
		line = ft_strdup(input);
		free(input);
		if (g_signal == 1)
		{
			signal(SIGINT, funcsign);
			return (g_signal = 0, dup2(tmp_fd, STDIN_FILENO), -1);
		}
		if (!line && flag)
			return (1);	
		if (helper2(cmd, line))
			break ;
		if (is_quoted)
			line = remove_quotes(expand_variables(cmd->env, add_quotes(line), \
				1));
		else
			line = expand_variables(cmd->env, line, 1);
		ft_putendl_fd(line, cmd->ft_in);
	}
	return (0);
}

int	handle_heredoc(t_cmd *cmd, int flag)
{
	int	is_quoted;
	int	i;
	int	tmp_fd;

	i = 0;
	is_quoted = 0;
	tmp_fd = dup(STDIN_FILENO);
	signal(SIGINT, signalhandlerherdoc);
	if (ft_strchr(cmd->hdoc_delimiter, '\'')
		|| ft_strchr(cmd->hdoc_delimiter, '"'))
		is_quoted = 1;
	cmd->hdoc_delimiter = remove_quotes(cmd->hdoc_delimiter);
	if (read_herdoc(cmd, is_quoted, tmp_fd, flag) == -1)
		return (-1);
	return (0);
}

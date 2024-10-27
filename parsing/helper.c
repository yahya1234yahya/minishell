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

char	*add_quotes(char *str)
{
	int		len;
	int		i;
	int		j;
	char	*quoted_str;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	quoted_str = safe_malloc(len + 3, 'a');
	if (quoted_str == NULL)
		return (NULL);
	quoted_str[i] = '\'';
	while (j < len)
	{
		quoted_str[i + 1] = str[j];
		i++;
		j++;
	}
	quoted_str[++i] = '\'';
	quoted_str[++i] = '\0';
	return (quoted_str);
}

void	signalhandlerherdoc(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = 1;
		close(STDIN_FILENO);
	}
}

void	read_herdoc(t_cmd *cmd, int is_quoted)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			close(cmd->ft_in);
			break ;
		}
		if (ft_strcmp(line, cmd->hdoc_delimiter) == 0)
		{
			setandget(NULL)->exs = 0;
			free(line);
			close(cmd->ft_in);
			break ;
		}
		if (is_quoted)
			line = add_quotes(line);
		line = expand_variables(cmd->env, line);
		line = remove_quotes(line);
		ft_putendl_fd(line, cmd->ft_in);
		free(line);
	}
}

void	handle_heredoc(char *input, t_cmd *cmd)
{
	int	is_quoted;
	int	i;
	int	tmp_fd;

	i = 0;
	is_quoted = 0;
	tmp_fd = dup(STDIN_FILENO);
	signal(SIGINT, signalhandlerherdoc);
	if (cmd->hdoc_delimiter[ft_strlen(cmd->hdoc_delimiter) - 1] == '\''
		|| cmd->hdoc_delimiter[ft_strlen(cmd->hdoc_delimiter) - 1] == '"')
		is_quoted = 1;
	cmd->hdoc_delimiter = remove_quotes(cmd->hdoc_delimiter);
	read_herdoc(cmd, is_quoted);
	dup2(tmp_fd, STDIN_FILENO);
	signal(SIGINT, funcsign);
	g_signal = 0;
}

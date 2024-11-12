/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:27:45 by ymouigui          #+#    #+#             */
/*   Updated: 2024/11/12 21:48:06 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fd_error(t_cmd *cmd)
{
	handle_redirection_error();
	cmd->skip = 1;
	setandget(NULL)->exs = 1;
	return (0);
}

void	increment(int	*i, int	*j)
{
	if (i)
		(*i)++;
	if (j)
		(*j)++;
}

int	calculate_alloc(char	*str)
{
	int	i;
	int	s_quot;
	int	d_quot;
	int	count ;

	i = 0;
	s_quot = 0;
	d_quot = 0;
	count = 0;
	while (str[i])
	{
		check_quots(str[i], &s_quot, &d_quot);
		if (str[i] == '$' && (str[i + 1] == '\'' || str[i + 1] == '"')
			&& !s_quot && !d_quot)
		{
			i++;
			continue ;
		}
		increment(&i, &count);
	}
	return (count);
}

char	*parse_it(char	*str)
{
	t_parse	p;

	(1) && (p.j = 0, p.count = 0, p.d_quot = 0, p.s_quot = 0, p.z = 0);
	p.count = calculate_alloc(str);
	p.res = safe_malloc(p.count + 1, 'a');
	while (str[p.z])
	{
		check_quots(str[p.z], &p.s_quot, &p.d_quot);
		if (str[p.z] == '$' && (str[p.z + 1] == '\'' || str[p.z + 1] == '"')
			&& !p.s_quot && !p.d_quot)
		{
			p.z++;
			continue ;
		}
		p.res[p.j] = str[p.z];
		increment(&p.z, &p.j);
	}
	return (p.res[p.j] = '\0', p.res);
}

int	herdoc(t_cmd *cmd)
{
	// char **new;
	cmd->tokens++;
	cmd->redin = 1;
	if (cmd->ft_in == 0)
	{
		cmd->herdoc_file = find_name();
		cmd->ft_in = open(cmd->herdoc_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	}
	cmd->hdoc_delimiter = parse_it(*(cmd->tokens));
	// new = cmd->tokens;
	// new++;
	// if (*new == NULL && cmd->lasthdoc)
		// return (0);
	// new++;
	if (handle_heredoc(cmd) == -1)
		return (-1);
	cmd->ft_in = open(cmd->herdoc_file, O_RDWR, 0644);
	return (0);
}

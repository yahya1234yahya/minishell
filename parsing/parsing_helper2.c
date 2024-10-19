/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:27:45 by ymouigui          #+#    #+#             */
/*   Updated: 2024/10/19 14:55:44 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_args(t_cmd *cmd)
{
	if (cmd->args)
	{
		cmd->args = ft_strjoin(cmd->args, " ");
		cmd->args = ft_strjoin(cmd->args, *(cmd->tokens));
	}
	else
		cmd->args = ft_strdup(*(cmd->tokens));
}

int	fd_error(t_cmd *cmd)
{
	handle_redirection_error();
	setandget(NULL)->exs = 1;
	cmd->skip = 1;
	return (0);
}

void	herdoc(t_cmd *cmd)
{
	cmd->tokens++;
	cmd->redin = 1;
	if (cmd->ft_in == 0)
		cmd->ft_in = open("tmp_hdoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	cmd->hdoc_delimiter = ft_strdup(*(cmd->tokens));
	handle_heredoc(*(cmd->tokens), cmd);
	cmd->ft_in = open("tmp_hdoc", O_RDWR, 0644);
}

void	check_cmd(t_cmd *cmd)
{
	*(cmd->tokens) = remove_quotes(*(cmd->tokens));
	is_valid_command(cmd, *(cmd->tokens));
	cmd->cmd = ft_strdup(*(cmd->tokens));
}

void	check_cases(t_cmd *cmd)
{
	*(cmd->tokens) = expand_variables(cmd->env, *(cmd->tokens));
	if (ft_strcmp(*(cmd->tokens), ">") == 0 || ft_strcmp(*(cmd->tokens), ">>") == 0
		|| ft_strcmp(*(cmd->tokens), "<") == 0)
	{
		if (ft_strcmp(*(cmd->tokens), "<") == 0)
			cmd->tokens = handle_redirection_in(cmd, cmd->tokens);
		else
			cmd->tokens = handle_redirection_out(cmd, cmd->tokens);
	}
	else if (ft_strcmp(*(cmd->tokens), "<<") == 0)
		herdoc(cmd);
	else
		handle_args(cmd);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:38:47 by ymouigui          #+#    #+#             */
/*   Updated: 2024/11/21 20:09:52 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//DONE
#include "../minishell.h"

int	redouthelper(t_cmd *cmd)
{
	if (cmd->redout == 2)
	{
		return (O_RDWR | O_CREAT | O_TRUNC);
	}
	else if (cmd->redout == 3)
	{
		return (O_RDWR | O_CREAT | O_APPEND);
	}
	return (0);
}

char	*skip_whitespace(char *str)
{
	while (*str == ' ')
		str++;
	return (str);
}

int	check_exit(char *path, char *word)
{
	if (access(word, X_OK) == 0)
	{
		path = ft_strdup(word);
		return (1);
	}
	return (0);
}

int	check_cases(t_cmd *cmd)
{
	*(cmd->tokens) = expand_variables(cmd->env, *(cmd->tokens), 0);
	if (ft_strcmp(*(cmd->tokens), ">") && ft_strcmp(*(cmd->tokens), ">>")
		&& ft_strcmp(*(cmd->tokens), "<") && ft_strcmp(*(cmd->tokens), "<<")
		&& cmd->found == 0)
	{
		cmd->found = 1;
		check_cmd(cmd);
	}
	else if (ft_strcmp(*(cmd->tokens), ">") == 0
		|| ft_strcmp(*(cmd->tokens), ">>") == 0
		|| ft_strcmp(*(cmd->tokens), "<") == 0)
	{
		if (ft_strcmp(*(cmd->tokens), "<") == 0)
			cmd->tokens = handle_redirection_in(cmd);
		else
			cmd->tokens = handle_redirection_out(cmd);
	}
	else if (ft_strcmp(*(cmd->tokens), "<<") == 0)
	{
		if (herdoc(cmd) == -1)
			return (-1);
	}
	else
		handle_args(cmd);
	return (0);
}

void	check_cmd(t_cmd *cmd)
{
	*(cmd->tokens) = remove_quotes(*(cmd->tokens));
	if (ft_strcmp(*(cmd->tokens), ".") == 0
		|| ft_strcmp(*(cmd->tokens), "..") == 0)
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		setandget(NULL)->exs = 127;
		return ;
	}
	is_valid_command(cmd, *(cmd->tokens));
	if (*(cmd->tokens)[0] == '\0')
		cmd->cmd = ft_strdup("/usr/bin/true");
	else
		cmd->cmd = ft_strdup(*(cmd->tokens));
}

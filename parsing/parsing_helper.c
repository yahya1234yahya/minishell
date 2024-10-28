/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:25:59 by ymouigui          #+#    #+#             */
/*   Updated: 2024/10/28 01:35:38 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//DONE
#include "../minishell.h"

int	is_valid_command(t_cmd *cmd, char *word)
{
	t_valid	valid;

	valid.tmp = envsearch(cmd->env, "PATH");
	if (!valid.tmp || valid.tmp->key == NULL)
		return (0);
	if (!word || !*word)
		return (0);
	if (word[0] == '.' || word[0] == '/')
		return (check_exit(cmd->path, word));
	valid.path_env = valid.tmp->value;
	valid.path_dup = ft_strdup(valid.path_env);
	valid.dir = ft_strtok(valid.path_dup, ":");
	while (valid.dir)
	{
		snprintf(valid.f_p, sizeof(valid.f_p), "%s/%s", valid.dir, word);
		if (access(valid.f_p, X_OK) == 0)
		{
			cmd->path = ft_strdup(valid.f_p);
			return (1);
		}
		valid.dir = ft_strtok(NULL, ":");
	}
	return (0);
}

void	handle_redirection_error(void)
{
	if (errno == EACCES)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("error: Permission denied\n", 2);
	}
	else if (errno == EISDIR)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("error: Is a directory\n", 2);
	}
	else if (errno == ENOENT)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("error: No such file or directory\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("error: Can't open file\n", 2);
	}
}

void	handle_export_sort(t_cmd *cmd, char	**envp)
{
	t_cmd	*tmp;

	if (cmd->next)
		tmp = cmd->next;
	cmd->next = init_cmd();
	if (cmd->redout == 2 || cmd->redout == 3)
	{
		cmd->next->redout = cmd->ft_out;
		cmd->next->ft_out = cmd->ft_out;
		cmd->ft_out = 1;
		cmd->redout = 0;
	}
	cmd = cmd->next;
	cmd->env = initenv(envp);
	cmd->input = ft_strdup("sort");
	if (tmp)
		cmd->next = tmp;
}

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:25:59 by ymouigui          #+#    #+#             */
/*   Updated: 2024/10/08 09:27:36 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	is_valid_command(t_cmd *cmd, char *word)
{
	t_env	*tmp;
	char	*path_env;
	char	full_path[1024];
	char	*dir;
	char	*path_dup;

	tmp = envsearch(cmd->env, "PATH");
	if (!tmp)
		return (0);
	path_env = tmp->name;
	if (!path_env)
		exit (0);
	path_dup = ft_strdup(path_env);
	dir = ft_strtok(path_dup, ":");
	while (dir)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, word);
		if (access(full_path, X_OK) == 0)
		{
			cmd->path = ft_strdup(full_path);
			return (1);
		}
		dir = ft_strtok(NULL, ":");
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
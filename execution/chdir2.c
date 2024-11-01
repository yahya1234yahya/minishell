/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 00:27:20 by mboughra          #+#    #+#             */
/*   Updated: 2024/11/01 17:43:51 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	caseofnocp(t_cmd *cmd, char *cp)
{
	char	*dest;

	if (cmd->args == NULL)
	{
		dest = envsearch3(cmd->env, "HOME");
		if (!dest)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (setandget(NULL)->exs = 1, 1);
		}
		chdir(dest);
		envset2(cmd->env, "OLDPWD", cp);
		getcwd(cp, PATH_MAX);
		envset2(cmd->env, "PWD", cp);
		return (setandget(NULL)->exs = 0, 0);
	}
	dest = preparearcd(cmd);
	if (access(dest, F_OK) == 0)
	{
		chdir(dest);
		envset2(cmd->env, "OLDPWD", cp);
		getcwd(cp, PATH_MAX);
		envset2(cmd->env, "PWD", cp);
	}
	return (0);
}

int	normalcase(t_cmd *cmd, char *current_path)
{
	char	*destination;

	destination = preparearcd(cmd);
	if (checkiffail(destination) == -1)
		return (-1);
	envset2(cmd->env, "OLDPWD", current_path);
	getcwd(current_path, PATH_MAX);
	envset2(cmd->env, "PWD", current_path);
	return (0);
}

int	headhome(t_cmd *cmd, char *current_path)
{
	char	*home;

	home = envsearch3(cmd->env, "HOME");
	if (home == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (setandget(NULL)->exs = 1);
	}
	if (chdir(home) == -1)
	{
		printerror(home, errno);
		return (setandget(NULL)->exs = 1);
	}
	envset2(cmd->env, "OLDPWD", current_path);
	getcwd(current_path, PATH_MAX);
	envset2(cmd->env, "PWD", current_path);
	return (0);
}

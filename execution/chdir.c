/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 23:43:45 by mboughra          #+#    #+#             */
/*   Updated: 2024/07/29 17:24:59 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int changedir(t_cmd *cmd)
{
	char *oldpwd;
	t_env *homeenv;
	cmd->args = ft_split(cmd->args, ' ')[0];
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		setandget(NULL)->exs = 1;
		perror("getcwd");
		return -1;
	};
	if (cmd->args == NULL)
	{
		homeenv = envsearch(cmd->env, "HOME");
		if (!homeenv)
		{
			setandget(NULL)->exs = 1;
			ft_putstr_fd("HOME not set\n", 2);
			return -1;
		}
		if (chdir(homeenv->value) == -1)
		{
			perror("chdir");
			setandget(NULL)->exs = 1;
			return -1;
		};
		envset(cmd->env, "OLDPWD", oldpwd);
		envset(cmd->env, "PWD",homeenv->value);
		return -1;
	}
	else if (chdir(cmd->args) == -1)
	{
		setandget(NULL)->exs = 1; //lll
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(cmd->args, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return -1;
	};
	envset(cmd->env, "OLDPWD", oldpwd);
	envset(cmd->env, "PWD", getcwd(NULL, 0));
	//TODO HANDLE THE CASE OF OLDPWD AND PWD NOT SET
	//TODO HANDLE THE CASE OF "../" && "./"
	return (0);
};


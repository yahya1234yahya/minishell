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


void changedir(t_cmd *cmd)
{
	char *oldpwd;
	t_env *homeenv;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		setandget(NULL)->exs = 1;
		perror("getcwd");
		exit(1);
	};
	if (cmd->args == NULL)
	{
		homeenv = envsearch(cmd->env, "HOME");
		if (!homeenv)
		{
			setandget(NULL)->exs = 1;
			ft_putstr_fd("HOME not set\n", 2);
			return ;
		}
		if (chdir(homeenv->value) == -1)
		{
			perror("chdir");
			setandget(NULL)->exs = 1;
			exit(1);
		};
		envset(cmd->env, "OLDPWD", oldpwd);
		envset(cmd->env, "PWD",homeenv->value);
		return ;
	}
	else if (chdir(cmd->args) == -1)
	{
		setandget(NULL)->exs = 1;
		perror("chdir");
		return ;
	};
	envset(cmd->env, "OLDPWD", oldpwd);
	envset(cmd->env, "PWD", getcwd(NULL, 0));
	//TODO HANDLE THE CASE OF OLDPWD AND PWD NOT SET
	//TODO HANDLE THE CASE OF "../" && "./"
};


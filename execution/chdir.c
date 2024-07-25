/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 23:43:45 by mboughra          #+#    #+#             */
/*   Updated: 2024/07/25 23:51:07 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void changedir(t_cmd *cmd)
{
	char *oldpwd;
	char **home;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("getcwd");
		exit(1);
	};
	if (cmd->args == NULL)
	{
		home = ft_split(envsearch(cmd->env, "HOME")->name, '=');
		if (chdir(home[1]) == -1)
		{
			perror("chdir");
			return ;
		};
		envset(cmd->env, "OLDPWD", oldpwd);
		envset(cmd->env, "PWD",home[1]);
		return ;
	}
	else if (chdir(cmd->args) == -1)
	{
		perror("chdir");
		return ;
	};
	envset(cmd->env, "OLDPWD", oldpwd);
	envset(cmd->env, "PWD", getcwd(NULL, 0));
	//TODO HANDLE THE CASE OF OLDPWD AND PWD NOT SET
	//TODO HANDLE THE CASE OF "../" && "./"
};


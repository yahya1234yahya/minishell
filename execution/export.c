/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 03:31:15 by mboughra          #+#    #+#             */
/*   Updated: 2024/08/08 03:31:15 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <string.h>

// void ft_export(t_cmd *cmd)
// {
//     if (!cmd->args)
// 		return;
//     char *arg = cmd->args;
//     char *equal_sign = strchr(arg, '=');
//     if (!equal_sign)
//         return;
//     *equal_sign = '\0';
//     char *var = arg;
//     char *value = equal_sign + 1;
//     setenv(var, value, 1);
// };

// static void	ft_lstdelone(t_env *env, void (*del)(void*))
// {
// 	if (!env || !del)
// 		return ;
// 	del (env->name);
// 	free (env);
// };

void	ft_export(t_cmd *cmd)
{
	char	**arg;

	if (!cmd->args)
		return;
	ft_lstadd_back(&cmd->env, ft_lstnew(cmd->args));
};

void	ft_unset(t_env	**env, t_cmd *cmd)
{
	t_env *tmp;
	t_env *runner;
	char **split;
	
	split = ft_split(cmd->args, '=');
	tmp = *env;
	if (!strncmp(tmp->name,split[0], ft_strlen(split[0]))) 
	{
		*env = tmp->next;
		free(tmp);
		return ;
	}
	while (tmp)
	{
		runner = tmp->next;
		if (runner && !strncmp(runner->name, split[0], ft_strlen(split[0])))
		{
			tmp->next = runner->next;
			free(runner);
			return ;
		}
		else
			tmp = tmp->next;
	}
};

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:44:56 by mboughra          #+#    #+#             */
/*   Updated: 2024/10/27 17:45:06 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*initenv(char **envp)
{
	t_env	*env;
	t_env	*current;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		current = ft_lstnew(envp[i]);
		if (!current)
			return (NULL);
		if (ft_strcmp(current->key, "_"))
			addback(&env, current);
		i++;
	}
	return (env);
}

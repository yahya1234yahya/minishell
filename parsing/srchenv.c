/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srchenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 09:39:38 by ymouigui          #+#    #+#             */
/*   Updated: 2024/10/26 09:39:38 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//DONE
#include "../minishell.h"

t_env	*envsearch(t_env *env, char *name)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strnstr(current->key, name, ft_strlen(name)))
			return (current);
		current = current->next;
	}
	return (NULL);
}

char	*envsearch2(t_env *env, char *name)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strnstr(current->name, name, ft_strlen(name)))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*envsearch3(t_env *env, char *name)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 03:31:05 by mboughra          #+#    #+#             */
/*   Updated: 2024/08/08 03:31:05 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_lstnew(void *content)
{
	t_env	*node;
	char	*typecast;
	int		i;

	typecast = (char *)content;
	node = safe_malloc(sizeof(t_env), 'a');
	if (!node)
		return (NULL);
	i = 0;
	while (typecast[i] && typecast[i] != '=')
		i++;
	node->key = ft_substr(typecast, 0, i);
	if (typecast[i] == '=' && typecast[i + 1] == '\0')
		node->value = ft_strdup("");
	else
		node->value = ft_substr(typecast, i + 1, ft_strlen(typecast) - i - 1);
	node->name = content;
	node->next = NULL;
	return (node);
}

void	addback(t_env **lst, t_env *newnode)
{
	t_env	*last;

	if (!*lst)
	{
		*lst = newnode;
		return ;
	}
	last = *lst;
	while (last)
	{
		if (ft_strcmp(last->key, newnode->key) == 0)
		{
			if (last->value && newnode->value == NULL)
				return ;
			envset2(*lst, newnode->key, newnode->value);
			return ;
		}
		last = last->next;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = newnode;
}

void	printenv2(t_env *current)
{
	while (current)
	{
		if (ft_strcmp(current->key, "?") == 0)
		{
			current = current->next;
			continue ;
		}
		if (ft_strcmp(current->key, "_") == 0)
		{
			current = current->next;
			continue ;
		}
		printf("declare -x %s", current->key);
		if (current->value)
			printf("=\"%s\"\n", current->value);
		else
			printf("\n");
		current = current->next;
	}
}

int	printenv(t_env *env, int flag)
{
	t_env	*current;

	current = env;
	if (!current)
		return (ft_putstr_fd("no env\n", 2), 1);
	if (flag)
	{
		while (current)
		{
			if (ft_strcmp(current->key, "?") == 0)
			{
				current = current->next;
				continue ;
			}
			if (current->value != NULL)
			{
				printf("%s=", current->key);
				printf("%s\n", current->value);
			}
			current = current->next;
		}
	}
	else
		printenv2(current);
	return (0);
}

t_env	*envset2(t_env *env, char *key, char *value)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			temp->value = ft_strdup(value);
			return (env);
		}
		temp = temp->next;
	}
	addback(&env, ft_lstnew(ft_strjoin(ft_strjoin(key, "="), value)));
	return (env);
}

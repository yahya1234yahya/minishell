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
	char	**split;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	split = ft_split((char *)content , '=');
	node->key = split[0];
	node->value = split[1];
	node->name = content;
	node->next = NULL;
	return (node);
};

void	ft_lstadd_back(t_env **lst, t_env *newnode)
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

		if (ft_strcmp(last->key, newnode->key) == 0)  //l9inah
		{
			if (last->value && newnode->value == NULL)
				return ;
			envset(*lst, newnode->key, newnode->value);
			return ;
		}
		last = last->next;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = newnode;
};
 // TODO env and export ls+color plus shlvl 
void	printenv2(t_env *current)
{
	while (current)
	{
		if (ft_strcmp(current->key, "?") == 0)
		{
			current = current->next;
			continue;
		}
		printf("declare -x %s", current->key);
		if(current->value)
			printf("=%s\n", current->value);
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
	{
		ft_putstr_fd("no env\n", 2);
		return (1);
	}
	if (flag)
	{
		while (current)
		{
			if (ft_strcmp(current->key, "?") == 0)
			{
				current = current->next;
				continue;
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
};

t_env	*envset(t_env *env, char *name, char *value)
{
	t_env	*current;
	char	*new;
	int		i;

	i = 0;
	current = env;
	while (current)
	{
		if (ft_strnstr(current->name, name, ft_strlen(name)))
		{
			current->value = value;
			return (env);
		}
		current = current->next;
	}
	return (env);
};

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
		ft_lstadd_back(&env, current);
		i++;
	}
	return (env);
};

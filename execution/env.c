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

size_t ft_min(size_t a, size_t b)
{
	if (a < b)
	{
		return (a);
	}
	else
	{
		return (b);
	}
}
char	*ft_substr(char  *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	substr_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	substr_len = ft_min(len, s_len - start);
	substr = (char *)malloc((substr_len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, substr_len + 1);
	return (substr);
}

t_env	*ft_lstnew(void *content)
{
	t_env	*node;
	char	**split;
	int 	i;
	char	*valuejoined;
	char *typecast;

	typecast = (char *)content;
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	i = 0;
	while (typecast[i] && typecast[i] != '=')
		i++;
	node->key = ft_substr(typecast, 0, i);
	node->value = ft_substr(typecast, i + 1, ft_strlen(typecast) - i - 1);
	node->value[ft_strlen(node->value)] = '\0';
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
			if ( ft_strcmp(name, "_") == 0 && ft_strcmp(current->name, name) == 0)
			{	
			current->value = value;
			return (env);}
			else if (ft_strcmp(name, "_"))
			{
				current->value = value;
				return (env);
			}
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

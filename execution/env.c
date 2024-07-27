#include "../minishell.h"

t_env	*ft_lstnew(void *content)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
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
	while (last->next)
		last = last->next;
	last->next = newnode;
};

void printenv(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		printf("%s\n", current->name);
		current = current->next;
	}
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
			new = ft_strjoin(name, "=");
			new = ft_strjoin(new, value);
			// free(current->name);
			current->name = new;
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

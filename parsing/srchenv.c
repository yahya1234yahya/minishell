#include "../minishell.h"

t_env	*envsearch(t_env *env, char *name)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strnstr(current->name, name, ft_strlen(name)))
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
		// if(current->name == NULL || current->value == NULL || current->key == NULL) 
		// 	return (NULL);
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

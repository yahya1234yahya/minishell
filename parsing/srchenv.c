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
};
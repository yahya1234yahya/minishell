#include "../minishell.h"

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
	
	tmp = *env;
	if (!ft_strcmp(tmp->name,cmd->args)) 
	{
		*env = tmp->next;
		free(tmp);
		return ;
	}
	while (tmp)
	{
		runner = tmp->next;
		if (runner && !ft_strcmp(runner->name, cmd->args))
		{
			tmp->next = runner->next;
			free(runner);
			return ;
		}
		else
			tmp = tmp->next;
	}
};

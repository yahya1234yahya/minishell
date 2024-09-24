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


static int plusaddpack(t_env **env, char *key, char *value)
{
	t_env	*tmp;
	t_env	*tmp2;
	char	*newvalue;

	tmp = *env;
	while (tmp)
	{
		if (!strncmp(tmp->key, value , ft_strlen(key)))
		{
			newvalue = ft_strjoin(tmp->value, key);
			free(tmp->value);
			tmp->value = newvalue;
			return 1;
		}
		tmp = tmp->next;
	}
	return -1;
};

static char *removeFirstChar(const char* str)
{
	if (str == NULL || str[0] == '\0')
		return NULL;
	return strdup(str + 1);
}


int exportsignal(int sig, t_cmd *cmd)
{
	char *str;

	
	str = ft_itoa(sig);
	if (!str)
		return(-1);
	cmd->args = ft_strjoin("?=", str);
	ft_export_status(cmd);
	free(str);
	cmd->args = NULL;
	return (0);
}

int	is_special_alpha(char c)
{
	if (ft_isalpha(c) || c == '_' || c == '+' || ft_isdigit(c) || c == '=' )
		return (0);
	return (1);
}

int parse_export(t_cmd *cmd)
{
	char	**split;
	int		i;
	int		start;
	int 	s_quote = 0;
	int		d_quote = 0;

	start = 1;

	i = 0;
	if (!cmd->args)
		return (0);
	if (cmd->args[0] == '=')
		{
			printf("not a valid identifier\n");
			return (-1);
			
		}
	
	while(cmd->args[i])
	{
		check_quots(cmd->args[i], &s_quote, &d_quote);
		if (start == 0 && cmd->args[i] == ' ')
			start = 1;
		if (start == 1 && isdigit(cmd->args[i]) && !s_quote && !d_quote)
		{
			printf("not a valid identifier\n");
			return (-1);
		}
		if (is_special_alpha(cmd->args[i]) == 1 && !s_quote && !d_quote)
		{
			printf("not a valid identifier\n");
			return (-1);
		}
		if (cmd->args[i] == '=')
		{

			while (cmd->args[i] && cmd->args[i] != ' ')
				i++;
		}
		i++;
	}
	return (0);	
}


int	ft_export(t_cmd *cmd)
{
	char	**arg;
	t_env	*tmp;

	//TODO parse the args before export
	if (!cmd->args)
		printenv(cmd->env, 0);
	if (parse_export(cmd) == -1)
		return (-1);
	else if (ft_strnstr(cmd->args, "+=", ft_strlen(cmd->args)))   //zayd
	{
		arg = ft_split(cmd->args, '+');
		arg[1] = removeFirstChar(arg[1]);
		if (plusaddpack(&cmd->env, arg[1], arg[0]) == -1)
		{
			arg[0] = ft_strjoin(arg[0], "=");
			ft_lstadd_back(&cmd->env, ft_lstnew(ft_strjoin(arg[0], arg[1])));
		}
	}
	else
	{
		arg = ft_split(cmd->args, ' ');
		while(arg && *arg)
		{
			ft_lstadd_back(&cmd->env, ft_lstnew(*arg));
			arg++;
		}
	}
	return (0);
};
int	ft_export_status(t_cmd *cmd)
{
	char	**arg;
	t_env	*tmp;

	//TODO parse the args before export
	if (!cmd->args)
		printenv(cmd->env, 0);
	
	else if (ft_strnstr(cmd->args, "+=", ft_strlen(cmd->args)))   //zayd
	{
		arg = ft_split(cmd->args, '+');
		arg[1] = removeFirstChar(arg[1]);
		if (plusaddpack(&cmd->env, arg[1], arg[0]) == -1)
		{
			arg[0] = ft_strjoin(arg[0], "=");
			ft_lstadd_back(&cmd->env, ft_lstnew(ft_strjoin(arg[0], arg[1])));
		}
	}
	else
		ft_lstadd_back(&cmd->env, ft_lstnew(cmd->args));
	return (0);
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

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
	ft_export(cmd);
	free(str);
	cmd->args = NULL;
	return (0);
}

int	is_special_alpha(char c)
{
	if (ft_isalpha(c) || c == '_' || c == '=' || ft_isdigit(c))
		return (0);
	return (1);
}

int parse_export(t_cmd *cmd)
{
	char	**split;
	int		i;
	int		j;

	split = ft_split(cmd->args, ' ');
	if (!split)
		return (-1);
	i = 0;
	while (split[i])
	{
		if (ft_strncmp(split[i], "?=" , ft_strlen("?=")) == 0)
		{
			i++;
			if (split[i] == NULL)
				break;
		}
		if (split[i][0] == '=' || is_special_alpha(split[i][0]) || ft_isdigit(split[i][0]))
		{
			printf("minishell: export: `%s': not a valid identifier\n", split[i]);
			return (-1);
		}
		j = 0;
		while (split[i][j])
		{
			if (is_special_alpha(split[i][j]) || ft_isdigit(split[i][j]))
			{
				printf("minishell: export: `%s': not a valid identifier\n", split[i]);
				return (-1);
			}
			j++;
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
	if (parse_export(cmd))
		return (-1);
	
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

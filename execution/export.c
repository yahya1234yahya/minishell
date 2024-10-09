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
	return (-1);
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


int parsename(char *name)
{
	int i;
	int ret;

	i = 0;
	if (ft_strcmp(name, "\0") == 0)
		return (0);
	if (name[i] && (name[i] != '_' && !ft_isalpha(name[i])))
		return (0);
	while (name[i])
	{
		if (name[i] != '_' && !ft_isalpha(name[i]) && !ft_isdigit(name[i]))
			return (0);
		i++;
	}
	return (1);
}

int checkvalue(char *value)
{
	if (!value)
		return (1);
	else if (value[0] == '+')
		return (2);
	else
		return (3);
}

static char **preparetokens(char *str)
{
	int i;
	char **ret;

	i = 0;
	ret = ft_strtok_all(str, " ");
	while (ret[i])
	{
		ret[i] = remove_quotes(ret[i]);
		i++;
	}
	i = 0;
	while (ret[i])
	{
		ret[i] = ft_strtrim(ret[i], " ");
		i++;
	}
	return (ret);
}


static int checkplus(char *str)
{
	int i;

	i = ft_strlen(str) - 1;
	if (str[i] == '+')
	{
		return (1);
	}
	return (0);
}

int hardcodecheck(char *str, char *str2)
{
	str = ft_strjoin("=", str);
	if (ft_strcmp(str, str2) == 0)
		return (1);
	return (0);
}

int	ft_export(t_cmd *cmd)
{
	char	**arg;
	char *parsed;
	t_env	*tmp;
	int		i;
	char **token;
	int ret;
	char **split;
	int plus;

	plus = 0;

	ret = 0;

	if (!cmd->args)
	{
		printenv(cmd->env, 0);
		return (0);
	}
	token = preparetokens(cmd->args);
	i = 0;
	while (token[i])
	{
		split = ft_split(token[i], '=');
		if (split[0] == NULL || hardcodecheck(split[0], token[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(token[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			setandget(NULL)->exs = 1;
			ret = 1;
			return (ret);
		}
		
		if (checkplus(split[0]))
			plus = 1;
		if (plus)
		{
			int r = 0;
			while (split[0][r])
				r++;			
			split[0][r-1] = '\0';
		}

		if (!parsename(split[0]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(token[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			setandget(NULL)->exs = 1;
			ret = 1;
		}
		if (split[1] == NULL)
			ft_lstadd_back(&cmd->env, ft_lstnew(token[i]));
		else if(plus == 1)
		{
			if (plusaddpack(&cmd->env, split[1], split[0]) == -1)
			{
				split[0] = ft_strjoin(split[0], "=");
				ft_lstadd_back(&cmd->env, ft_lstnew(ft_strjoin(split[0], split[1])));
			}
		}
		else
		{
			split[0] = ft_strjoin(split[0], "=");
			ft_lstadd_back(&cmd->env, ft_lstnew(ft_strjoin(split[0], split[1])));
		}
		


		i++;
	}
	setandget(NULL)->exs = ret;
return (ret);

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
	{
		t_env *tmp = ft_lstnew(cmd->args);

		ft_lstadd_back(&cmd->env, tmp);
	}
	return (0);
};


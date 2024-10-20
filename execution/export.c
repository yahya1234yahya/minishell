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

void printerrorexport(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}


static int onechar(char *str, char c)
{
	int i;

	i = 0;

	while ((str[i]) && (str[i] == c || str[i] == '\'' || str[i] == '\"'))
		i++;
	if (ft_strlen(str) == i)
		return (1);
	return (0);
}

int parskey(char *str)
{
	int i;

	i = 0;
	if (str[i] && (str[i] != '_' && !ft_isalpha(str[i])))
		return (0);
	i++;
	if (str[i] == '\0')
	{
		if(ft_isdigit(str[i - 1]))
			return (0);
		return (1);
	}
	while (str[i])
	{
		if (str[i] == '+')
		{
			if (str[i + 1] == '\0')
				return (1);
			else
				return (0);
		}
		if (str[i] != '_' && !ft_isalpha(str[i]) && !ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}



int exportwithouthvalue(t_exp exp, t_cmd *cmd)
{
	char *str;

	if (parskey(exp.key))
	{
		if (exp.equal == 0)
		{
			t_env *tmp = ft_lstnew(exp.key);
			// free(tmp->value);
			tmp->value = NULL;
			ft_lstadd_back(&cmd->env, tmp);
		}
		else if (exp.equal == 1)
		{
			if (exp.plus == 1)
			{
				exp.key = ft_substr(exp.key, 0, ft_strlen(exp.key) - 1);
				// printf("exp.key = %s\n", exp.key);
				if (plusaddpack(&cmd->env, exp.value, exp.key) == -1)
				{
					str = ft_strjoin(exp.key, "=");
					ft_lstadd_back(&cmd->env, ft_lstnew(ft_strjoin(str, exp.value)));
				}
			}
			else
			{
				// printf("case of equal without plus\n");
				str = ft_strjoin(exp.key, "=");
				str = ft_strjoin(str, exp.value);
				ft_lstadd_back(&cmd->env, ft_lstnew(str));
			}
		}
	}
	else
	{
		printerrorexport(ft_strjoin(ft_strjoin(exp.key, "="), exp.value));
		setandget(NULL)->exs = 1;
		return (1);
	}
	return (0);
}

t_exp *collect(char *str, t_exp *exp)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			{
				exp->equal = 1;
				exp->key = ft_strdup(ft_substr(str, 0, i));
				exp->value = ft_strdup(ft_substr(str, i + 1, ft_strlen(str) - i - 1));
				exp->plus = checkplus(exp->key);
				break ;
			}
		i++;
	}
	if (exp->equal == 0)
	{
		exp->key = ft_strdup(str);
		exp->value = NULL;
		exp->plus = 0;
	}
	return (exp);
}

int ft_export(t_cmd *cmd)
{
	char	**token;
	t_exp	*exp;
	int ret = 0;
	
	if (!cmd->args)
		return (printenv(cmd->env, 0));
	if (onechar(cmd->args, ' '))
		return (printerrorexport(cmd->args),setandget(NULL)->exs = 1, 1);
	exp = (t_exp *)malloc(sizeof(t_exp));
	exp->key = NULL;
	exp->value = NULL;
	exp->plus = 0;
	exp->equal = 0;
	token = preparetokens(cmd->args);
	while (*token)
	{
		exp = collect(*token, exp);
		// printf("key = %s\n", exp->key);
		// printf("value = %s\n", exp->value);
		// printf("plus = %d\n", exp->plus);
		// printf("equal = %d\n", exp->equal);
		// printf("\n-----------------\n");
		if (exportwithouthvalue(*exp, cmd) == 1)
			ret = 1;
		exp->key = NULL;
		exp->value = NULL;
		exp->plus = 0;
		exp->equal = 0;
		token++;
		//todo 
	}
	setandget(NULL)->exs = ret;
	return (ret);	
}


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


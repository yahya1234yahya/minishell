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

static int parse_export(char *args)
{
	char	**split;
	int		i;
	int		start;
	int 	s_quote = 0;
	int		d_quote = 0;

	start = 1;

	i = 0;
	if (!args)
		return (0);
	if (args[0] == '=')
		{
			// printf("not a valid identifier\n");
			return (-1);
			
		}
	
	while(args[i])
	{
		check_quots(args[i], &s_quote, &d_quote);
		if (start == 0 && args[i] == ' ')
			start = 1;
		if (start == 1 && isdigit(args[i]) && !s_quote && !d_quote)
		{
			// printf("not a valid identifier\n");
			return (-1);
		}
		if (is_special_alpha(args[i]) == 1 && !s_quote && !d_quote)
		{
			// printf("not a valid identifier\n");
			return (-1);
		}
		if (args[i] == '=')
		{
			while (args[i])
			{
				
				// printf("args[%d] = %c\n",i, args[i]);
				// printf("s_quote = %d\n", s_quote);
				// printf("d_quote = %d\n", d_quote);
				if (s_quote || d_quote)
				{
					i++;
					continue;
				}
				if (args[i] == ' ')
					break ;
				check_quots(args[i], &s_quote, &d_quote);
				i++;
			}
		}
		if (args[i] == '\0')		
			return (0);	
		i++;
	}
	return (0);	
}


char *parse_export2(char *args)
{
	char		**splitted;
	char		*ret;
	char		*tmp;
	int			i  = 0;

	int quotes[2];
	quotes[0] = 0;
	quotes[1] = 0;
	ret = ft_strdup("");

	int r = 0;
	while(args[r])
	{
		while (args[r])
		{
			check_quots(args[r], &quotes[0], &quotes[1]);
			if (quotes[0] == 1 || quotes[1] == 1)
			{
					r++;
					continue;
			}
			if (args[r] == ' ')
				break;
			r++;
		}
		r++;
		ft_strlcpy(tmp, args + i, r - i);
		i = r;
		// printf("tmp = %s\n", tmp);
		// printf("parse_export(tmp) = %d\n", parse_export(tmp));
		if(parse_export(tmp) == -1)
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(tmp, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		else
		{
			ret = ft_strjoin(ret, " ");
			ret = ft_strjoin(ret, tmp);
		}
	}
	
	// 

	// splitted = ft_split(args, ' ');

	// exit(0);
	// if (!splitted)
	// 	return (NULL);
	// i = 0;
	// while (splitted[i])
	// {
		
	// 	if(parse_export(splitted[i]) == -1)
	// 	{
	// 		ft_putstr_fd("minishell: export: `", 2);
	// 		ft_putstr_fd(splitted[i], 2);
	// 		ft_putstr_fd("': not a valid identifier\n", 2);
	// 	}
	// 	else
	// 	{
	// 		ret = ft_strjoin(ret, " ");
	// 		ret = ft_strjoin(ret, splitted[i]);
	// 	}
	// 	i++;
	// }
	return (ret);
};

int	ft_export(t_cmd *cmd)
{
	char	**arg;
	t_env	*tmp;

	//TODO parse the args before export
	if (!cmd->args)
		printenv(cmd->env, 0);
	char *fff =  parse_export2(cmd->args);
	cmd->args = fff;
	// cmd->args = arg;
	// printf("cmd->args = %s\n", cmd->args);
	// cmd->args = parse_export2(cmd->args);
	printf("cmd->args = %s\n", cmd->args);
	if (ft_strnstr(cmd->args, "+=", ft_strlen(cmd->args)))   //zayd
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

int	ft_unset(t_env	**env, t_cmd *cmd)
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
		return (0);
	}
	while (tmp)
	{
		runner = tmp->next;
		if (runner && !strncmp(runner->name, split[0], ft_strlen(split[0])))
		{
			tmp->next = runner->next;
			free(runner);
			return (0);
		}
		else
			tmp = tmp->next;
	}
	return (0);
};

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:49:43 by mboughra          #+#    #+#             */
/*   Updated: 2024/10/07 16:07:52 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

static int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

static int is_valid_variable_name(char *str)
{
	int i;
	
	if (str == NULL || *str == '\0')
	{
        return (1);
	}
	if (!isalpha(*str) && *str != '_')
	{
        return (1);
	}

    i = 0;
	while (i < ft_strlen(str))
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			return (1);
		}
		i++;
	}
	return 0;
}


#include "../minishell.h"

int	ft_unset(t_env	**env, t_cmd *cmd)
{
	t_env *tmp;
	t_env *runner;
	char **tokens;
	char **split;
	int i;
	int ret = 0;
	
	if (!cmd->args)
		return (0);
	tokens = ft_strtok_all(cmd->args, " ");
	
	i = 0;
	while (tokens[i])
	{
		tokens[i] = remove_quotes(tokens[i]);
		tokens[i] = ft_strtrim(tokens[i], " ");
		i++;
	}
	i = 0;
	while (tokens[i])
	{
		if (is_valid_variable_name(tokens[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(tokens[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			setandget(NULL)->exs = 1;
			ret = 1;
		}
		else
		{
			split = ft_split(tokens[i], '=');
			tmp = *env;
			if (!strncmp(tmp->name,split[0], ft_strlen(split[0])))
			{
				*env = tmp->next;
				free(tmp);
				if (ret != 1)
					ret = 0;
			}
			while (tmp)
			{
				runner = tmp->next;
				if (runner && !strncmp(runner->name, split[0], ft_strlen(split[0])))
				{
					tmp->next = runner->next;
					free(runner);
					if (ret != 1)
						ret = 0;
				}
				else
					tmp = tmp->next;
			}	
		}
		i++;
	}
	setandget(NULL)->exs = ret;
	return (ret);
}

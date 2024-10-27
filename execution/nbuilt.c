/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbuilt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 03:31:56 by mboughra          #+#    #+#             */
/*   Updated: 2024/08/08 03:31:56 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	**convert(t_cmd *cmd)
// {
// 	t_env	*tmp;
// 	char	**ret;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	tmp = cmd->env;
// 	while (tmp)
// 	{
// 		i++;
// 		tmp = tmp->next;
// 	};
// 	ret = (char **)safe_malloc(sizeof(char *) * (i + 1), 'a');
// 	if (!ret)
// 		return (perror("malloc"), setandget(NULL)->exs = 1, NULL);
// 	ret[i] = NULL;
// 	j = 0;
// 	free(tmp);
// 	tmp = cmd->env;
// 	while (j < i && tmp)
// 	{
// 		ret[j] = ft_strjoin(tmp->key, "=");
// 		ret[j] = ft_strjoin(ret[j], tmp->value);
// 		tmp = tmp->next;
// 		j++;
// 	};
// 	ret[j] = NULL;		
// 	return (ret);
// }

static char	**fill_ret_array(t_cmd *cmd, int count)
{
	t_env	*tmp;
	char	**ret;
	int		j;

	ret = (char **)safe_malloc(sizeof(char *) * (count + 1), 'a');
	if (!ret)
		return (perror("malloc"), setandget(NULL)->exs = 1, NULL);
	ret[count] = NULL;
	tmp = cmd->env;
	j = 0;
	while (j < count && tmp)
	{
		ret[j] = ft_strjoin(tmp->key, "=");
		ret[j] = ft_strjoin(ret[j], tmp->value);
		tmp = tmp->next;
		j++;
	}
	return (ret);
}

char	**convert(t_cmd *cmd)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = cmd->env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	free(tmp);
	return (fill_ret_array(cmd, i));
}

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

char	**convert(t_cmd *cmd)
{
	t_env *tmp;
	char **ret;
	int i;
	int j;

	i = 0;
	tmp = cmd->env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	};
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	if (!ret)
	{
		perror("malloc");
		setandget(NULL)->exs = 1;
		return (NULL);
	}
	ret[i] = NULL;
	j = 0;
	tmp = cmd->env;
	while (j < i && tmp)
	{
		ret[j] = ft_strjoin(tmp->key, "=");
		ret[j] = ft_strjoin(ret[j], tmp->value);
		tmp = tmp->next;
		j++;
	};

	// exit(0);
		

	return (ret);
}


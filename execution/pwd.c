/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 19:14:04 by mboughra          #+#    #+#             */
/*   Updated: 2024/07/25 22:45:55 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_env *env)
{
	t_env	*wd;
	char	*pwd;

	wd = envsearch(env, "PWD");
	if (!wd)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
		{
			perror("getcwd");
			return (1);
		}
		printf("%s\n", pwd);
		free(pwd);
		return (0);
	}
	printf("%s\n", wd->value);
	return (0);
}

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

static char	*ft_strstr(const char	*haystack, const char	*needle)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!haystack && needle != NULL)
		return (NULL);
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && (i + j))
		{
			if (needle[j + 1] == '\0')
				return ((char *)(haystack + i));
			j++;
		}
		i++;
	}
	return (NULL);
};

void	ft_pwd(t_env *env)
{
	t_env	*wd;
	char 	*pwd;

	wd = envsearch(env, "PWD");
	if (!wd)
	{
		pwd = getcwd(NULL, 0);
		printf("%s\n", pwd);
		free(pwd);
		return ;
	}
	printf("%s\n", wd->value);
}


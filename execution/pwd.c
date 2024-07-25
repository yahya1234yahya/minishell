/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 19:14:04 by mboughra          #+#    #+#             */
/*   Updated: 2024/07/25 01:54:28 by mboughra         ###   ########.fr       */
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
}

void ft_pwd(char **env)
{
	int i;
	char *pwd;

	i = 0;
	while(env[i])
	{
		if(ft_strstr(env[i],"PWD"))
			break;
		i++;
	}
	pwd = ft_split(env[i],'=')[1];
	printf("%s\n",pwd);
};


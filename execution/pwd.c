/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 19:14:04 by mboughra          #+#    #+#             */
/*   Updated: 2024/07/07 19:15:39 by mboughra         ###   ########.fr       */
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

void ft_pwd(char **envp)
{
	int i;
	char *str;
	
	i = 0;
	while (envp[i])
	{
		if (ft_strstr(envp[i], "PWD"))
			break ;
		i++;
	}
	str = ft_strstr(envp[i], "PWD");
	i = 4;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibft4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:04:26 by mboughra          #+#    #+#             */
/*   Updated: 2024/11/05 00:13:06 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	char	*s;

	if (dstsize == 0)
		return (ft_strlen(src));
	if (!dst || !src)
		return (0);
	s = (char *)src;
	i = 0;
	while (src[i] && i < (dstsize -1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	size_t	i;
	size_t	lenofs;
	char	*s2;

	i = 0;
	lenofs = ft_strlen(s1)+1;
	if (!s1)
		return (NULL);
	s2 = safe_malloc(lenofs * sizeof(char), 'a');
	if (!s2)
		return (NULL);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

int	ft_strcmp2(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (ft_tolower(*s1) != ft_tolower(*s2))
			return (ft_tolower(*s1) - ft_tolower(*s2));
		s1++;
		s2++;
	}
	return (ft_tolower(*s1) - ft_tolower(*s2));
}

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] && i < n)
	{
		dst[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}

char	*ft_strchr(char *s, int c)
{
	char	*char_s;
	char	char_c;
	size_t	i;

	i = 0;
	char_c = (char)c;
	char_s = (char *)s;
	while (char_s[i])
	{
		if (char_s[i] == char_c)
			return (&char_s[i]);
		i++;
	}
	if (char_c == '\0')
		return (&char_s[i]);
	return (NULL);
}

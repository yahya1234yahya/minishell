/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibft3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:58:18 by mboughra          #+#    #+#             */
/*   Updated: 2024/10/21 20:04:41 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static size_t	ft_min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	substr_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	substr_len = ft_min(len, s_len - start);
	substr = (char *)safe_malloc((substr_len + 1) * sizeof(char), 'a');
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, substr_len + 1);
	return (substr);
}

static int	ft_ofchercker(long max, long re, int s)
{
	if (max > re && s > 0)
		return (-1);
	if (max > re && s < 0)
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		s;
	long	re;
	long	max;

	i = 0;
	s = 1;
	re = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		max = re;
		re = re * 10 +(str[i] - 48);
		if (ft_ofchercker(max, re, s) != 1)
			return (ft_ofchercker(max, re, s));
		i++;
	}
	return (re * s);
}

char	*ft_strjoin(char	*s1, char	*s2)
{
	char	*str;
	size_t	s1len;
	size_t	s2len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	str = (char *)safe_malloc(s1len + s2len + 1, 'a');
	if (!str)
		return (NULL);
	ft_strlcpy (str, s1, s1len + 1);
	ft_strlcpy (str + s1len, s2, s2len + 1);
	return (str);
}

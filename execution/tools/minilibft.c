/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:46:39 by mboughra          #+#    #+#             */
/*   Updated: 2024/07/28 06:01:20 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strnstr(char	*haystack, char	*needle, size_t	len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!haystack && len == 0 && needle != NULL)
		return (NULL);
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && (i + j) < len)
		{
			if (needle[j + 1] == '\0' )
				return ((char *)(haystack + i));
			j++;
		}
		i++;
	}
	return (NULL);
}

size_t	ft_strlen( char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

static char	*filler(char *ret, long count, long n)
{
	long	n2;

	ret[count--] = '\0';
	if (n > 0)
	{
		while (count >= 0)
		{
			n2 = n % 10;
			ret[count--] = n2 + '0';
			n = n / 10;
		}
	}
	if (n < 0)
	{
		n = n * -1;
		while (count >= 1)
		{
			n2 = n % 10;
			ret[count--] = n2 + '0';
			n = n / 10;
		}
		ret[0] = '-';
	}
	return (ret);
}

char	*ft_itoa(int n)
{
	long		count;
	long		n2;
	char		*ret;

	count = 0;
	n2 = n;
	if (n == '\0')
		return (ft_strdup("0"));
	while (n2 != 0)
	{
		n2 = n2 / 10;
		count++;
	}
	if (n < 0)
		count++;
	ret = (char *)safe_malloc(sizeof(char) * count + 1, 'a');
	if (!ret)
		return (NULL);
	ret = filler(ret, count, n);
	return (ret);
}

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

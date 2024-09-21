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

static int	check_char(char  *set, char c)
{
	int	w;

	w = 0;
	while (set[w])
	{
		if (set[w] == c)
			return (1);
		w++;
	}
	return (0);
}

char	*ft_strtrim(char  *s1, char  *set)
{
	int		i;
	int		j;
	int		len;
	char	*ptr;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	len = ft_strlen(s1);
	i = 0;
	while (check_char(set, s1[i]) == 1 && s1[i])
		i++;
	while (i < len && check_char(set, s1[len - 1]) == 1)
		len--;
	ptr = (char *)malloc(len - i + 1);
	if (ptr == NULL)
		return (NULL);
	j = 0;
	while (i < len)
		ptr[j++] = s1[i++];
	ptr[j] = '\0';
	return (ptr);
}

int	ft_strcmp(const char	*s1, const char	*s2)
{
	size_t			i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	i = 0;
	while (ss1[i] && ss2[i] && ss1[i] == ss2[i])
		i++;
	return (ss1[i] - ss2[i]);
}
int	ft_strncmp(const char	*s1, const char	*s2, size_t	n)
{
	size_t			i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	i = 0;
	while ((i < n) && ss1[i] && ss2[i] && ss1[i] == ss2[i])
		i++;
	if (i == n)
		return (0);
	return (ss1[i] - ss2[i]);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (fd < 0)
		return ;
	if (!s)
		return ;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
};

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
			if (needle[j + 1] == '\0')
				return ((char *)(haystack + i));
			j++;
		}
		i++;
	}
	return (NULL);
};

size_t ft_strlen( char *s)
{
	size_t i;

	i = 0;
	if (!s)
		return 0;
	while (s[i])
		i++;
	return (i);
};


char	*ft_strjoin(char	*s1, char	*s2)
{
	char	*str;
	size_t	s1len;
	size_t	s2len;

	if (!s1 && !s2)
		return NULL;
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	str = (char *)malloc(s1len + s2len + 1);
	if (!str)
		return ( NULL);
	ft_strlcpy (str, s1, s1len + 1);
	ft_strlcpy (str + s1len, s2, s2len + 1);
	return (str);
}

size_t	ft_strlcpy(char	*dst, char	*src, size_t	dstsize)
{
	size_t	i;
	char	*s;

	if (dstsize == 0)
		return (ft_strlen(src));
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
	s2 = malloc(lenofs * sizeof(char));
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
	ret = (char *)malloc(sizeof(char) * count + 1);
	if (!ret)
		return (NULL);
	ret = filler(ret, count, n);
	return (ret);
}

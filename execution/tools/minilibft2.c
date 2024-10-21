/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibft2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:54:39 by mboughra          #+#    #+#             */
/*   Updated: 2024/10/21 19:57:29 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_char(char *set, char c)
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

char	*ft_strtrim(char *s1, char *set)
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
	ptr = (char *)safe_malloc(len - i + 1, 'a');
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

	if (!s1 || !s2)
		return (1);
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

	if (!s1 || !s2)
		return (1);
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
}

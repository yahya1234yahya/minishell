/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:45:06 by ymouigui          #+#    #+#             */
/*   Updated: 2024/07/25 21:49:16 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	lenth(int *len1, int *len2, char const *s1, char const *s2)
{
	if (s1)
		*len1 = strlen(s1);
	if (s2)
		*len2 = strlen(s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	int		j;
	int		i;
	char	*str;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	len1 = 0;
	len2 = 0;
	lenth(&len1, &len2, s1, s2);
	str = (char *)malloc(len1 + len2 + 1);
	if (str == NULL)
		return (NULL);
	while (i < len1 && len1 != 0)
	{
		str[i] = s1[i];
		i++;
	}
	j = 0; 
	while (i < (len1 + len2) && len2 != 0)
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

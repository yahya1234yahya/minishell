/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibft5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:29:40 by mboughra          #+#    #+#             */
/*   Updated: 2024/11/21 18:22:51 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strrstr(char *haystack, char *needle)
{
	size_t	needle_len;
	size_t	haystack_len;
	int		i;

	if (!needle || !haystack)
		return (NULL);
	needle_len = ft_strlen(needle);
	haystack_len = ft_strlen(haystack);
	i = haystack_len - needle_len;
	while (i >= 0)
	{
		if (ft_strncmp(haystack + i, needle, needle_len) == 0)
			return ((char *)(haystack + i));
		i--;
	}
	return (NULL);
}

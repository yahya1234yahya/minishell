/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 23:45:57 by ymouigui          #+#    #+#             */
/*   Updated: 2024/11/04 23:46:09 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_quotes(char *str)
{
	int		len;
	int		i;
	int		j;
	char	*quoted_str;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	quoted_str = safe_malloc(len + 3, 'a');
	if (quoted_str == NULL)
		return (NULL);
	quoted_str[i] = '\'';
	while (j < len)
	{
		quoted_str[i + 1] = str[j];
		i++;
		j++;
	}
	quoted_str[++i] = '\'';
	quoted_str[++i] = '\0';
	return (quoted_str);
}

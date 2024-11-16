/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 09:24:53 by ymouigui          #+#    #+#             */
/*   Updated: 2024/11/16 09:41:35 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_tab(char *input)
{
	char	*res;
	int		i;
	int		d_q;
	int		s_q;

	d_q = 0;
	s_q = 0;
	i = 0;
	res = safe_malloc(ft_strlen(input) + 1, 'a');
	while (input[i])
	{
		check_quots(input[i], &s_q, &d_q);
		if (input[i] == '\t' && !s_q && !d_q)
		{
			res[i] = ' ';
			i++;
			continue ;
		}
		res[i] = input[i];
		i++;
	}
	res[i] = '\0';
	return (ft_strtrim(res, " "));
}

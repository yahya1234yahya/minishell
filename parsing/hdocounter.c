/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdocounter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:34:43 by mboughra          #+#    #+#             */
/*   Updated: 2024/11/18 15:34:50 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	herdoc_counter(char *str)
{
	int		i;
	char	**tok;

	i = 0;
	tok = ft_strtok_all(str, "<<");
	while (tok[i])
		i++;
	return (i - 1);
}

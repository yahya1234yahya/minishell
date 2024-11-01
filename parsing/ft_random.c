/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:35:55 by ymouigui          #+#    #+#             */
/*   Updated: 2024/11/01 16:33:39 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *ft_random(void)
{
    static int index;
    char *filename;

    filename = safe_malloc(ft_strlen(ft_itoa(index)), 'a');
    filename = ft_itoa(index);
    index++;
    return (filename);
}

char    *find_name(void)
{
    char    *tmp = ft_random();
    while(access(tmp, F_OK) == 0)
        tmp = ft_random();
    return (tmp);
}
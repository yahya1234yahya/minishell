/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:29:09 by ymouigui          #+#    #+#             */
/*   Updated: 2024/10/27 22:26:03 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_struct(t_expa *expa, char *input, t_env *env, int herdoc)
{
	expa->single_q = 0;
	expa->double_q = 0;
	expa->i = 0;
	expa->j = 0;
	expa->tmp2 = ft_strdup(input);
	expa->tmp = input;
	expa->count = count_new_input(env, input, herdoc);
	expa->new_input = (char *)safe_malloc(expa->count + 1, 'a');
}

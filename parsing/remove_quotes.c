/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 09:44:42 by ymouigui          #+#    #+#             */
/*   Updated: 2024/10/26 09:44:42 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	there_is_another(char *input, char c, int i)
{
	while (input[i])
	{
		i++;
		if (input[i] == c)
			return (1);
	}
	return (0);
}
char	*remove_quotes(char *input)
{
	char	quote;
	char	*new_input;
	int		i;
	int		j;

	(1) && (i = 0, j = 0);
	new_input = safe_malloc((ft_strlen(input) + 1) * sizeof(char *), 'a');
	while (input && input[i])
	{
		if ((input[i] == '"' || input[i] == '\'') && there_is_another(input, input[i], i))
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
				new_input[j++] = input[i++];
			if (input[i] && input[i] == quote)
				i++;
		}
		else
			new_input[j++] = input[i++];
	}
	new_input[j] = '\0';
	if (i != j && j == 0)
		return (ft_strdup(""));
	return (new_input);
}

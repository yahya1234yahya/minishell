/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:17:27 by ymouigui          #+#    #+#             */
/*   Updated: 2024/10/27 15:23:25 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_space(char *input)
{
	int		i;
	int		j;
	int		s_quote;
	int		d_quote;
	char	*new_input;

	(1) && (i = 0, j = 0, s_quote = 0, d_quote = 0);
	new_input = safe_malloc(calculate_space(input) + 1, 'a');
	while (input && input[i])
	{
		check_quots(input[i], &s_quote, &d_quote);
		if ((input[i] == '<' || input[i] == '>') && !s_quote && !d_quote)
		{
			if (i > 0 && input[i - 1] != '<' && input[i - 1] != '>')
				new_input[j++] = ' ';
			new_input[j++] = input[i++];
			if (input[i] != '<' && input[i] != '>')
				new_input[j++] = ' ';
			continue ;
		}
		new_input[j++] = input[i++];
	}
	new_input[j] = '\0';
	return (new_input);
}

char	**handle_redirection_out(t_cmd *cmd, char **tokens)
{
	cmd->redout = index_char(*(cmd->tokens));
	cmd->tokens++;
	if (*(cmd->tokens) == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("error: expected filename after redout\n", 2);
		return (0);
	}
	*(cmd->tokens) = remove_quotes(*(cmd->tokens));
	cmd->ft_out = open(*(cmd->tokens), redouthelper(cmd), 0644);
	return (cmd->tokens);
}

char	**handle_redirection_in(t_cmd *cmd, char **tokens)
{
	cmd->redin = 1;
	cmd->tokens++;
	if (*(cmd->tokens) == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("error: expected filename after redout\n", 2);
		return (0);
	}
	*(cmd->tokens) = remove_quotes(*(cmd->tokens));
	cmd->ft_in = open(*(cmd->tokens), O_RDONLY, 0644);
	return (cmd->tokens);
}

int	is_there_space(char *input)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (input[i])
	{
		check_quots(input[i], &s_quote, &d_quote);
		if (input[i] == ' ' || input[i] == '\t' && !s_quote && !d_quote)
			return (1);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:10:01 by ymouigui          #+#    #+#             */
/*   Updated: 2024/10/08 09:10:01 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	calculate_space(char *input)
{
	int	i;
	int	count;
	int	s_quote;
	int	d_quote;

	i = 0;
	count = 0;
	s_quote = 0;
	d_quote = 0;
	while (input && input[i])
	{
		check_quots(input[i], &s_quote, &d_quote);
		if ((input[i] == '<' || input[i] == '>') && !s_quote && !d_quote)
		{
			if (i > 0 && input[i - 1] != '<' && input[i - 1] != '>')
				count += 2;
			count++;
			i++;
			continue ;
		}
		i++;
		count++;
	}
	return (count);
}

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

int	parse(t_cmd *cmd, char *input, char **envp, int rec)
{
	char	*next_word;
	int		flags;
	char	*delimiter;
	char	*tmp_args;

	while (cmd)
	{
		cmd->input = add_space(cmd->input);
		cmd->tokens = ft_strtok_all(cmd->input, " ");
		int i = 0;
		if (ft_strcmp(*(cmd->tokens), ">") && ft_strcmp(*(cmd->tokens), ">>")
			&& ft_strcmp(*(cmd->tokens), "<") && ft_strcmp(*(cmd->tokens), "<<"))
		{
			check_cmd(cmd);
		}
		while (cmd->tokens && *(cmd->tokens))
		{
			check_cases(cmd);
			if ((cmd->ft_out == -1 || cmd->ft_in == -1) && fd_error(cmd) == 0)
			{
				if (cmd->next)
					break ;
				return (0);
			}
			cmd->tokens++;
		}
		cmd = cmd->next;
	}
	return (1);
}

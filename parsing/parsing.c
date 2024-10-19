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
	if (input[0] == '<' || input[0] == '>')
		count = 1;
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
int is_there_space(char *input)
{
	int i = 0;
	int s_quote = 0;
	int d_quote = 0;
	while(input[i])
	{
		check_quots(input[i], &s_quote, &d_quote);
		if (input[i] == ' ' || input[i] == '\t' && !s_quote && !d_quote)
			return (1);
		i++;
	}
	return (0);
}
char	*expand_main(t_env *env, char *input)
{
	int i = 0;
	char	*tmp;
	char **tokens = ft_strtok_all(input, " \t");

	while(tokens && tokens[i])
	{
		tokens[i] = expand_variables(env, tokens[i]);
		if (ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i], ">>") == 0 || ft_strcmp(tokens[i], "<") == 0)
		{
			i++;
			tmp = ft_strdup(tokens[i]);
			if (tokens && tokens[i])
				tokens[i] = expand_variables(env, tokens[i]);
			else
				break;
			if(!tokens || !tokens[i][0] || (is_there_space(tokens[i]) && ft_strcmp(tmp, tokens[i])))
			{
				ft_putstr_fd("minishell: ambiguous redirect\n", 2);
				setandget(NULL)->exs = 1;
				return (NULL);
			}
		}
		i++;
	}
	i = 0;
	while(tokens && tokens[i])
	{
		if (i == 0)
			input = ft_strdup(tokens[i]);
		else
		{
			input = ft_strjoin(input, " ");
			input = ft_strjoin(input, tokens[i]);
		}
		i++;
	}
	return (input);
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
		if (strstr(cmd->input, "<<") == NULL)
		{
			cmd->input = expand_main(cmd->env, cmd->input);
			if (cmd->input == NULL)
				return (0);
			if(check_complete(cmd->input) == 0)
				return (0);
		}
		else
		{
			if(check_complete(cmd->input) == 0)
				return (0);
		}
		cmd->tokens = ft_strtok_all(cmd->input, " \t");
		int i = 0;
		if (ft_strcmp(*(cmd->tokens), ">") && ft_strcmp(*(cmd->tokens), ">>")
			&& ft_strcmp(*(cmd->tokens), "<") && ft_strcmp(*(cmd->tokens), "<<"))
		{
			*(cmd->tokens) = expand_variables(cmd->env, *(cmd->tokens));
			check_cmd(cmd);
			cmd->tokens++;
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

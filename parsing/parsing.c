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

int	calculate_space(char *input)
{
	int	i;
	int	count;
	int	s_quote;
	int	d_quote;

	(1) && (i = 0, count = 0);
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

int	ambigous(char	**tokens, t_env *env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tokens && tokens[i])
	{
		tokens[i] = expand_variables(env, tokens[i], 0);
		if (ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i], ">>") == 0
			|| ft_strcmp(tokens[i], "<") == 0)
		{
			i++;
			tmp = ft_strdup(tokens[i]);
			if (tokens && tokens[i])
				tokens[i] = expand_variables(env, tokens[i], 0);
			else
				break ;
			if (!tokens || !tokens[i][0] || (is_there_space(tokens[i])
				&& ft_strcmp(tmp, tokens[i])))
				return (print_exit_s("minishell: ambiguous redirect\n", 1), 0);
		}
		i++;
	}
	return (1);
}

char	*expand_main(t_env *env, char *input)
{
	int		i;
	char	**tokens;

	tokens = ft_strtok_all(input, " \t");
	if (ambigous(tokens, env) == 0)
		return (NULL);
	i = 0;
	// while (tokens && tokens[i])
	// {
	// 	if (i == 0)
	// 		input = ft_strdup(tokens[i]);
	// 	else
	// 	{
	// 		input = ft_strjoin(input, " ");
	// 		input = ft_strjoin(input, tokens[i]);
	// 	}
	// 	i++;
	// }
	return (input);
}

int	expand_check(t_cmd *cmd)
{
	cmd->input = expand_main(cmd->env, cmd->input);
	if (cmd->input == NULL)
		return (0);
	if (check_complete(cmd->input) == 0)
		return (0);
	return (1);
}

int	parse(t_cmd *cmd, char *input, char **envp, int rec)
{
	int	i;

	while (cmd)
	{
		cmd->input = add_space(cmd->input);
		if (strstr(cmd->input, "<<") == NULL && expand_check(cmd) == 0)
			return (0);
		else if (strstr(cmd->input, "<<") && check_complete(cmd->input) == 0)
			return (0);
		cmd->tokens = ft_strtok_all(cmd->input, " \t");
		i = 0;
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

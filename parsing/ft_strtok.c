/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:13:54 by ymouigui          #+#    #+#             */
/*   Updated: 2024/10/26 15:13:54 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	char	*strtok_helper(char *next_token, char *delim)
{
	int	dquote;
	int	squote;

	dquote = 0;
	squote = 0;
	while (*next_token)
	{
		if (*next_token == '"' && squote == 0)
			dquote = !dquote;
		else if (*next_token == '\'' && dquote == 0)
			squote = !squote;
		else if (ft_strchr(delim, *next_token) != NULL
			&& dquote == 0 && squote == 0)
			break ;
		next_token++;
	}
	return (next_token);
}

char	*ft_strtok(char *str, char *delim)
{
	static char	*next_token;
	char		*current_token;

	if (str != NULL)
		next_token = str;
	if (next_token == NULL)
		return (NULL);
	while (*next_token && ft_strchr(delim, *next_token) != NULL)
		next_token++;
	if (!(*next_token))
		return (NULL);
	current_token = next_token;
	next_token = strtok_helper(next_token, delim);
	if (*next_token)
	{
		*next_token = '\0';
		next_token++;
	}
	return (current_token);
}

static int	count_tokens(char *str, char *delim)
{
	int	count;
	int	token_count;

	(1) && (count = 0, token_count = 0);
	while (*str)
	{
		while (*str && ft_strchr(delim, *str) != NULL)
			str++;
		if (!(*str))
			break ;
		str = strtok_helper(str, delim);
		count++;
		if (*str)
			str++;
	}
	return (count);
}

char	**ft_strtok_all(char *str, char *delim)
{
	int		token_count;
	char	**tokens;
	char	*current_token;
	int		token_len;

	token_count = 0;
	tokens = safe_malloc((count_tokens(str, delim) + 1) * sizeof(char *), 'a');
	tokens[count_tokens(str, delim)] = NULL;
	while (*str)
	{
		while (*str && ft_strchr(delim, *str) != NULL)
			str++;
		if (!(*str))
			break ;
		current_token = str;
		str = strtok_helper(str, delim);
		token_len = str - current_token;
		tokens[token_count] = safe_malloc((token_len + 1) * sizeof(char), 'a');
		ft_strncpy(tokens[token_count], current_token, token_len);
		tokens[token_count++][token_len] = '\0';
		if (*str)
			str++;
	}
	return (tokens[token_count] = NULL, tokens);
}

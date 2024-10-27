/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:44:57 by ymouigui          #+#    #+#             */
/*   Updated: 2024/10/27 13:50:00 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	index_char(char *str)
{
	if (ft_strcmp(str, "<") == 0)
		return (1);
	else if (ft_strcmp(str, ">") == 0)
		return (2);
	else if (ft_strcmp(str, ">>") == 0)
		return (3);
	else if (ft_strcmp(str, "<<") == 0)
		return (4);
	else
		return (2);
}

int	is_all_space(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

char	*add_d_quot(char *str)
{
	int		len;
	int		i;
	int		j;
	char	*quoted_str;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	quoted_str = safe_malloc(len + 3, 'a');
	if (quoted_str == NULL)
		return (NULL);
	quoted_str[i] = chose_quotes(str);
	while (j < len)
	{
		quoted_str[i + 1] = str[j];
		i++;
		j++;
	}
	quoted_str[++i] = chose_quotes(str);
	quoted_str[++i] = '\0';
	return (quoted_str);
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (fd < 0)
		return ;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write (fd, &s[i], 1);
		i++;
	}
	write (fd, "\n", 1);
}

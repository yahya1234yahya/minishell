/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:42:32 by mboughra          #+#    #+#             */
/*   Updated: 2024/07/29 18:04:48 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**preparetokecho(char *str)
{
	char	**tok;
	int		i;

	i = 0;
	tok = ft_strtok_all(str, " ");
	while (tok[i])
	{
		tok[i] = remove_quotes(tok[i]);
		i++;
	}
	return (tok);
}

static int	allspace(char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
	{
		ft_putstr_fd("\n", 1);
		return (1);
	}
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (i == ft_strlen(str))
	{
		ft_putstr_fd("\n", 1);
		return (1);
	}
	return (0);
}

static int	handle_write_error(void)
{
	if (write(STDOUT_FILENO, "\n", 1) == -1)
	{
		perror("write");
		setandget(NULL)->exs = 1;
		return (-1);
	}
	return (0);
}

static int	handle_flags(char **tok, int *flag)
{
	int	i;

	i = 0;
	while (tok[i])
	{
		if (check_string(tok[i]))
		{
			*flag = 1;
			i++;
		}
		else
			break ;
	}
	return (i);
}

int	ft_echo(t_cmd *cmd)
{
	int		flag;
	int		i;
	char	**tok;
	char	*str;

	flag = 0;
	if (allspace(cmd->args))
		return (0);
	if (cmd->args == NULL || cmd->args[0] == '\0')
		return (handle_write_error());
	tok = preparetokecho(cmd->args);
	i = handle_flags(tok, &flag);
	if (tok[i] == NULL)
		return (0);
	cmd->args = remove_quotes(cmd->args);
	str = ft_strnstr(cmd->args, tok[i], ft_strlen(cmd->args));
	ft_putstr_fd(str, 1);
	if (!flag)
		ft_putstr_fd("\n", 1);
	return (0);
}

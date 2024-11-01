/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 23:43:45 by mboughra          #+#    #+#             */
/*   Updated: 2024/07/29 17:24:59 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*preparearcd(t_cmd *cmd)
{
	char	**tok;
	int		i;

	tok = ft_strtok_all(cmd->args, " ");
	i = 0;
	while (tok[i])
	{
		tok[i] = remove_quotes(tok[i]);
		i++;
	}
	return (tok[0]);
}

void	printerror(char *path, int error)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	if (error == 2)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (error == 13)
		ft_putstr_fd(": Permission denied\n", 2);
	else if (error == 20)
		ft_putstr_fd(": Not a directory\n", 2);
	else if (error == ERANGE)
		ft_putstr_fd(": File name too long\n", 2);
	else
		ft_putstr_fd(": unknown error\n", 2);
}

int	checkiffail(char *destination)
{
	int		i;
	char	cwd[PATH_MAX];

	getcwd(cwd, PATH_MAX);
	i = chdir(destination);
	if (i == -1)
	{
		printerror(destination, errno);
		setandget(NULL)->exs = 1;
		return (setandget(NULL)->exs = 1, -1);
	}
	return (0);
}

char	*ft_strrchr(char	*s, int c)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	c_char;

	i = ft_strlen(s);
	str = (unsigned char *)s;
	c_char = (unsigned char)c;
	if (c_char == '\0')
		return ((char *)&str[i]);
	while (i > 0)
	{
		i--;
		if (str[i] == c_char)
			return ((char *)&str[i]);
	}
	return (NULL);
}

int	changedir(t_cmd *cmd)
{
	char	current_path[PATH_MAX];

	if (getcwd(current_path, PATH_MAX) == NULL)
	{
		if (errno == ERANGE)
			return (printerror("cd", ERANGE), setandget(NULL)->exs = 1, 1);
		return (caseofnocp(cmd, current_path));
	}
	if (cmd->args == NULL || cmd->args[0] == '\0')
		return (headhome(cmd, current_path));
	else if (ft_strcmp(cmd->args, "\"\"") == 0)
		return (setandget(NULL)->exs = 0, 0);
	else
		return (normalcase(cmd, current_path));
}

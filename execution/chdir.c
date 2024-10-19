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


static char *preparearcd(t_cmd *cmd)
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

static void printerror(char *path, int error)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	if (error == 2)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (error == 13)
		ft_putstr_fd(": Permission denied\n", 2);
	else if (error == 20)
		ft_putstr_fd(": Not a directory\n", 2);
	else
		ft_putstr_fd(": unknown error\n", 2);
};


static int checkiffail(t_cmd *cmd, char *destination, char *current_path)
{
	int i;
	char *cwd;

	cwd = getcwd(NULL, 0);
	i = chdir(destination);
	if (i == -1)
	{
		printerror(destination, errno);
		setandget(NULL)->exs = 1;
		return (setandget(NULL)->exs = 1, -1);
	}
	envset2(cmd->env, "OLDPWD", current_path);
	envset2(cmd->env, "PWD", cwd);
	free(cwd);
	return (0);
}


static char	*ft_strrchr(char	*s, int c)
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

static char *get_directory_path(char *path)
{
	char *last_slash;
	
	last_slash = ft_strrchr(path, '/');
	if (last_slash)
	{
		*last_slash = '\0';
		return (path);
	}
	return (NULL);
}

int handledeletedfile(t_cmd *cmd)
{
	char *destination;
	char *current_path;

	ft_putstr_fd("current file is not accesisble\n", 2);
	ft_putstr_fd("trying to go back to the last valid directory\n", 2);
	current_path = envsearch3(cmd->env, "PWD");
	if (!current_path)
	{
		ft_putstr_fd("failed to get the current last directory from env trying to go Home\n", 2);
		if (access(envsearch3(cmd->env, "HOME"), F_OK) == 0)
		{
			chdir(envsearch3(cmd->env, "HOME"));
			envset2(cmd->env, "OLDPWD", envsearch3(cmd->env, "HOME"));
			envset2(cmd->env, "PWD", envsearch3(cmd->env, "HOME"));
			return (setandget(NULL)->exs = 1);
		}
		else
		{
			ft_putstr_fd("HOME not set exiting the program\n", 2);
			exit(1);
			return (setandget(NULL)->exs = 1);
		}
		
		return (setandget(NULL)->exs = 1);
	}
	while (1)
	{
		current_path = get_directory_path(current_path);
		if (access(current_path, F_OK) == 0)
		{
			chdir(current_path);	
			break;
		}
	}
	envset2(cmd->env, "OLDPWD", current_path);
	envset2(cmd->env, "PWD", current_path);
	return (0);
}


int changedir(t_cmd *cmd)
{
	char *home;
	char *destination;
	char *current_path;

	current_path = getcwd(NULL, 0);
	if (!current_path)
	{
		handledeletedfile(cmd);
		return (setandget(NULL)->exs = 1, 1);
	}
	if (cmd->args == NULL)
	{
		if ((home = envsearch2(cmd->env, "HOME")) == NULL)
			return (free(current_path), setandget(NULL)->exs = 1, ft_putstr_fd("HOME not set\n", 2), -1);
		if(chdir(home) == -1)
		{
			printerror(home, errno);
			return (free(current_path), setandget(NULL)->exs = 1, -1);
		}
		envset2(cmd->env, "OLDPWD", current_path);
		envset2(cmd->env, "PWD", getcwd(NULL, 0));
	}
	else if(ft_strcmp(cmd->args, "\"\"") == 0)
	{
		return (free(current_path), setandget(NULL)->exs = 0, 0);
	}
	else
	{
		destination = preparearcd(cmd);
		if (checkiffail(cmd, destination, current_path) == -1)
			return (free(current_path), -1);
		envset2(cmd->env, "OLDPWD", current_path);
		envset2(cmd->env, "PWD", getcwd(NULL, 0));
	}
	free(current_path);
	return (0);
}


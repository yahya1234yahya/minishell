/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbuilt2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 03:18:44 by mboughra          #+#    #+#             */
/*   Updated: 2024/08/01 03:27:06 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void static	perrornb(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	argsprepare(t_cmd *cmd)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strjoin(ft_strjoin(cmd->path, " "), cmd->args);
	cmd->splited = ft_strtok_all(tmp, " ");
	while (cmd->splited[i])
	{
		cmd->splited[i] = remove_quotes(cmd->splited[i]);
		i++;
	}
}

//  


int	preparecmd(t_cmd *cmd)
{
	if (!cmd->path)
	{
		if (cmd->cmd[0] == '.' || cmd->cmd[0] == '/')
			cmd->path = ft_strdup(cmd->cmd);
		else
			return (perrornb(cmd->cmd), setandget(NULL)->exs = 127, 127);
	}
	if (cmd->args)
		argsprepare(cmd);
	else
	{
		cmd->splited = (char **)safe_malloc(sizeof(char *) * 2, 'a');
		(1) && (cmd->splited[0] = cmd->path, cmd->splited[1] = NULL);
	}
	return (0);
}

int	ft_errorwrite2(char *str, int ernum)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(ernum), 2);
	ft_putstr_fd("\n", 2);
	return (1);
}
int	ft_errorwrite(t_cmd *cmd)
{
	struct stat	path_stat;
	
	if (stat(cmd->splited[0], &path_stat) == 0)
	{
		if(errno == ENOTDIR)
		{
			ft_errorwrite2(cmd->splited[0], errno);
			return (setandget(NULL)->exs = 126, 126);
		}
	}
	else
	{
		return (perror("perror"), 1);
	}
	if (access(cmd->splited[0], F_OK) == -1) //NOT FOUND ERROR (FOLDER OR COMMAND)
	{
		ft_errorwrite2(cmd->splited[0], errno);
		return (setandget(NULL)->exs = 127, 127);
	}
	if (access(cmd->splited[0], X_OK) == -1)
	{
		ft_errorwrite2(cmd->splited[0], errno);
		return (setandget(NULL)->exs = 126, 126);
	}	
	return 1;
}

int check_command(char *command)
{
    struct stat sb;

	// printf("command: %s\n", command);

    if (stat(command, &sb) == -1) 
	{
		if (errno == ENOENT)
		{
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(command, 2);
            // ft_putstr_fd(": command not found\n", 2);
            ft_putstr_fd(": No such file or directory\n", 2);
            return (setandget(NULL)->exs = 127, 127);
        }
		else
            return (perror("stat"), setandget(NULL)->exs = 126, 126); //CHECK THIS TODO
    }
    if (S_ISDIR(sb.st_mode))
	{
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(command, 2);
        ft_putstr_fd(": is a directory\n", 2);
        return (setandget(NULL)->exs = 126, 126);
    }
    if (!S_ISREG(sb.st_mode))
	{
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(command, 2);
        ft_putstr_fd(": not a regular file\n", 2);
        return (setandget(NULL)->exs = 126, 126);
    }
    if (access(command, X_OK) == -1)
	{
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(command, 2);
        ft_putstr_fd(": Permission denied\n", 2);
		return (setandget(NULL)->exs = 126, 126);
    }
    return (0);
}

int	execfromsystem(t_cmd *cmd, char **envp)
{
	int	pid;
	int	s;
	int	check;

	if (preparecmd(cmd))
		return (cmd->exs);
	check = check_command(cmd->splited[0]);
	if (check)
		return (check);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		if (execve(cmd->splited[0], cmd->splited, envp) < 0)
			return (perror("execve:"), 1);
	}
	else
	{
		waitpid(pid, &s, 0);
		if (WIFSIGNALED(s))
			return (setandget(NULL)->exs = 128 + WTERMSIG(s), 128 + WTERMSIG(s));
		else if (WIFEXITED(s))
			return (setandget(NULL)->exs = WEXITSTATUS(s), WEXITSTATUS(s));
	}
	return (0);
}

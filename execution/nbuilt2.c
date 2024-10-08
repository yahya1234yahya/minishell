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

int preparecmd(t_cmd *cmd)
{
	char *tmp;
	int i;
	i = 0;
	if (!cmd->path)
	{
		if (cmd->cmd[0] == '.' || cmd->cmd[0] == '/')
		{
			cmd->path = ft_strdup(cmd->cmd);
		}
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
			setandget(NULL)->exs = 127;
			return (127);		
		}
		// cmd->path = ft_strdup(cmd->cmd);
	}
	if (cmd->args)
	{	
		tmp = ft_strjoin(cmd->path, " ");
		tmp = ft_strjoin(tmp, cmd->args);
		cmd->splited = ft_strtok_all(tmp, " ");
		while (cmd->splited[i])
		{
			cmd->splited[i] = remove_quotes(cmd->splited[i]);
			i++;
		}
	}else
	{
		cmd->splited = (char **)safe_malloc(sizeof(char *) * 2, 'a');
		cmd->splited[0] = cmd->path;
		cmd->splited[1] = NULL;
	};
	return (0);
}

int ft_errorwrite(t_cmd *cmd)
{
	struct stat path_stat;
	
	if (stat(cmd->splited[0], &path_stat) == 0)
	{
		if(errno == ENOTDIR)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->splited[0], 2);
			ft_putstr_fd(": is a directory\n", 2);
			setandget(NULL)->exs = 126;
			return (126);
		}
		// if (S_ISDIR(path_stat.st_mode))
		// {
		// 	printf("%s is a directory.\n",cmd->splited[0]);
		// 	return(setandget(NULL)->exs = 126, 126);
		// }
	}




	else
	{
		perror("stat");
		return 1;
	}

	if (access(cmd->splited[0], F_OK) == -1) //NOT FOUND ERROR (FOLDER OR COMMAND)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->splited[0], 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
		setandget(NULL)->exs = 127;
		return 127;
	}

	if (access(cmd->splited[0], X_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->splited[0], 2);
		ft_putstr_fd(" : Permission denied\n", 2);
		setandget(NULL)->exs = 126;
		return 126;
	}	

	return 1;
}



///////////



// #include <sys/stat.h>
// #include <unistd.h>
// #include <stdio.h>

// int ft_errorwrite(t_cmd *cmd)
// {
//     struct stat path_stat;

//     // Attempt to get the file status first
//     if (stat(cmd->splited[0], &path_stat) == -1) // File does not exist
//     {
//         ft_putstr_fd("minishell: ", 2);
//         ft_putstr_fd(cmd->splited[0], 2);
//         ft_putstr_fd(": No such file or directory\n", 2);
//         setandget(NULL)->exs = 127;
//         return (127);
//     }

//     // Check if the path is a directory
//     if (S_ISDIR(path_stat.st_mode))
//     {
//         ft_putstr_fd("minishell: ", 2);
//         ft_putstr_fd(cmd->splited[0], 2);
//         ft_putstr_fd(": is a directory\n", 2);
//         setandget(NULL)->exs = 126;
//         return (126);
//     }

//     // Check for execute permissions
//     if (access(cmd->splited[0], X_OK) == -1)
//     {
//         ft_putstr_fd("minishell: ", 2);
//         ft_putstr_fd(cmd->splited[0], 2);
//         ft_putstr_fd(": Permission denied\n", 2);
//         setandget(NULL)->exs = 126;
//         return (126);
//     }

//     // If no errors occurred, return success
//     return (1);
// }






// int ft_errorwrite(t_cmd *cmd)
// {
//     struct stat path_stat;
    
//     // Use stat() to check if the command exists and get its details
//     if (stat(cmd->splited[0], &path_stat) == -1) // NOT FOUND ERROR
//     {
//         ft_putstr_fd("minishell: ", 2);
//         ft_putstr_fd(cmd->splited[0], 2);
//         ft_putstr_fd(": No such file or directory\n", 2);
//         setandget(NULL)->exs = 127;
//         return (127);
//     }

//     // Check if it is a directory
//     if (S_ISDIR(path_stat.st_mode))
//     {
//         ft_putstr_fd("minishell: ", 2);
//         ft_putstr_fd(cmd->splited[0], 2);
//         ft_putstr_fd(": is a directory\n", 2);
//         setandget(NULL)->exs = 126;
//         return (126);
//     }

//     // Check if it has execute permission
//     if (access(cmd->splited[0], X_OK) == -1)
//     {
//         ft_putstr_fd("minishell: ", 2);
//         ft_putstr_fd(cmd->splited[0], 2);
//         ft_putstr_fd(": Permission denied\n", 2);
//         setandget(NULL)->exs = 126;
//         return (126);
//     }
    
//     return (1); // No error
// }
////////
/*
int check_command(char *command)      //the most correct
{
    struct stat sb;

    if (stat(command, &sb) == -1)
	{
		if (errno == ENOENT)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(command, 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		else
            perror("stat");
        return (setandget(NULL)->exs = 127, 127);
    }
	if (S_ISDIR(sb.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": is a directory\n", 2);
		return(setandget(NULL)->exs = 126, 126);
    }
    if (access(command, X_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": Permission denied\n", 2);
        return(setandget(NULL)->exs = 126, 126);
    }
		return (0);	
}  */


// int checkpath(t_cmd *cmd)  //TODO PATH
// {
// 	t_env	*tmp;
// 	char	*path;
// 	char	**path2;
// 	int		i;


// 	if (access(cmd->cmd, F_OK) == 0)
// 		return (0);
// 	tmp = cmd->env;
// 	while (ft_strcmp(tmp->name, "PATH") != 0)
// 		tmp = tmp->next; //TODO pr
// 	path = ft_strdup(tmp->value);
// 	path2 = ft_strtok_all(path, ":");
// 	i = 0;
// 	while (path2[i])
// 	{
// 		if (access(ft_strjoin(path2[i],cmd->cmd), F_OK))
// 		{
// 			cmd->path = ft_strjoin(path2[i], cmd->cmd);
// 			free(path);
// 			free(path2);
// 			return (0);
// 		}
// 	}
// }

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
		{
            perror("stat");
            return (1);
        }
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



int execfromsystem(t_cmd *cmd, char **envp)
{
	int pid;
	int status;
	int check;

	check = preparecmd(cmd);
	if (check)
	{
		return (check);
	}
	
	check = check_command(cmd->splited[0]);
	if (check)
		return (check);

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (1);
		}
		if (pid == 0)
		{
			if (execve(cmd->splited[0], cmd->splited, envp) < 0)
			{
				perror("execve"); //TODO HERE
				return (1);
			}
		}
		else
		{
			waitpid(pid, &status, 0);
			if (WIFSIGNALED(status))
			{
				setandget(NULL)->exs = 128 + WTERMSIG(status);
				return (128 + WTERMSIG(status));
			}
			else if (WIFEXITED(status))
			{
				setandget(NULL)->exs = WEXITSTATUS(status);
				return WEXITSTATUS(status);
			}
		}
	return 0;
}

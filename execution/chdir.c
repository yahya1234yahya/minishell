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

	i = chdir(destination);
	if (i == -1)
	{
		printerror(destination, errno);
		setandget(NULL)->exs = 1;
		return (setandget(NULL)->exs = 1, -1);
	}
	envset2(cmd->env, "OLDPWD", current_path);
	envset2(cmd->env, "PWD", getcwd(NULL, 0));
	return (0);
}
// Function to manually update PWD when getcwd() fails
// static void update_virtual_pwd(t_cmd *cmd, char *current_path, char *destination)
// {
//     char *last_slash;

//     // Simulate the behavior of `cd ..` by removing the last directory from the path
//     last_slash = strrchr(current_path, '/');
//     if (last_slash)
//         *last_slash = '\0';  // Cut off the last directory in the path
//     else
//         strcpy(current_path, "/");  // Fallback to root if no slash found

//     envset2(cmd->env, "PWD", current_path);
// }

// // Updated checkiffail function
// static int checkiffail(t_cmd *cmd, char *destination, char *current_path)
// {
//     int i;

//     i = chdir(destination);
//     if (i == -1)
//     {
//         printerror(destination, errno);
//         setandget(NULL)->exs = 1;
//         return (-1);
//     }

//     char *new_path = getcwd(NULL, 0);
//     if (!new_path)  // If getcwd fails, manually handle PWD update
//     {
//         ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
//         update_virtual_pwd(cmd, current_path, destination);  // Handle manually
//         free(current_path);
//     }
//     else
//     {
//         envset2(cmd->env, "OLDPWD", current_path);
//         envset2(cmd->env, "PWD", new_path);
//         free(new_path);
//     }
//     return (0);
// }






int changedir(t_cmd *cmd)
{
	char *home;
	char *destination;
	char *current_path;

	current_path = getcwd(NULL, 0);
	if (!current_path)
	{
		setandget(NULL)->exs = 1;
		perror("getcwd");
		return (-1);
	}
	if (cmd->args == NULL)
	{
		if ((home = envsearch2(cmd->env, "HOME")) == NULL)
			return (free(current_path), setandget(NULL)->exs = 1, ft_putstr_fd("HOME not set\n", 2), -1);
		if(chdir(home) == -1)
		{
			printerror(home, errno);
			return (setandget(NULL)->exs = 1, -1);
		}
		envset2(cmd->env, "OLDPWD", current_path);
		envset2(cmd->env, "PWD", getcwd(NULL, 0));
	}
	else
	{
		destination = preparearcd(cmd);
		if (checkiffail(cmd, destination, current_path) == -1)
			return (-1);
	}
	free(current_path);
	return (0);
}
















// int changedir(t_cmd *cmd)
// {
// 	char *oldpwd;
// 	t_env *homeenv;


// 	printf("cmd->args: %s\n", cmd->args);

// 	if (ft_split(cmd->args, ' '))
// 		cmd->args = ft_split(cmd->args, ' ')[0];
// 	oldpwd = getcwd(NULL, 0);
		
// 	if (!oldpwd)
// 	{
// 		setandget(NULL)->exs = 1;
// 		perror("getcwd");
// 		return -1;
// 	};
// 	if (cmd->args == NULL)
// 	{
// 		homeenv = envsearch(cmd->env, "HOME");
// 		if (!homeenv)
// 		{
// 			setandget(NULL)->exs = 1;
// 			ft_putstr_fd("HOME not set\n", 2);
// 			return -1;
// 		}
// 		if (chdir(homeenv->value) == -1)
// 		{
// 			perror("chdir");
// 			setandget(NULL)->exs = 1;
// 			return -1;
// 		};
// 		envset(cmd->env, "OLDPWD", oldpwd);
// 		envset(cmd->env, "PWD",homeenv->value);
// 		return -1;
// 	}
// 	else if (chdir(cmd->args) == -1)
// 	{
// 		printf("errno: %d\n", errno);
// 		setandget(NULL)->exs = 1; //lll
// 		ft_putstr_fd("minishell: cd: ", 2);
// 		ft_putstr_fd(cmd->args, 2);
// 		ft_putstr_fd(": No such file or directory\n", 2);
// 		return -1;
// 	};
// 	envset(cmd->env, "OLDPWD", oldpwd);
// 	envset(cmd->env, "PWD", getcwd(NULL, 0));
// 	//TODO HANDLE THE CASE OF OLDPWD AND PWD NOT SET
// 	//TODO HANDLE THE CASE OF "../" && "./"
// 	return (0);
// }


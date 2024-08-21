/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbuilt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 03:31:56 by mboughra          #+#    #+#             */
/*   Updated: 2024/08/08 03:31:56 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**convert(t_cmd *cmd)
{
	t_env *tmp;
	char **ret;
	int i;
	int j;

	i = 0;
	tmp = cmd->env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	};
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	j = 0;
	tmp = cmd->env;
	while (j < i)
	{
		ret[j] = tmp->name;
		j++;
		tmp = tmp->next;
	};
	ret[j] = NULL;
	return (ret);
};























// void notbuilt(t_cmd *cmd, char **envp)
// {
// 	int i;
// 	int pid;
// 	char **fixed;
// 	char **splited;
// 	char **envvv = convert(cmd);

// 	if (cmd->args != NULL)
// 	{
// 		i = calculateargs(cmd);
// 		fixed = (char **)malloc(sizeof(char *) * (i + 2));
// 		splited = ft_split(cmd->args, ' ');
// 		fixed = prepend_array(splited, cmd->path);
// 		if (access(fixed[0], X_OK) == 0)
// 		{
// 			pid = fork();
// 			if (pid == 0)
// 			{
// 				if (cmd->redout == 2)
//                 {
//                     dup2(cmd->ft_in, STDOUT_FILENO);
//                     close(cmd->ft_in);
//                 }
// 				execve(fixed[0], fixed, envvv);
// 			}
// 			else
// 			{
// 				int status;
// 				wait(&status);
// 			}
// 		}
// 	}
// 	else
// 	{
// 		fixed = (char **)malloc(sizeof(char *) * 2);
// 		fixed[0] = cmd->path;
// 		fixed[1] = NULL;
// 		if (access(fixed[0],F_OK | X_OK) == 0)
// 		{
// 			pid = fork();
// 			if (pid == 0)
// 			{
// 				if (cmd->redout == 2)
//                 {
//                     dup2(cmd->ft_in, 1);
//                     close(cmd->ft_in);
//                 }
// 				execve(fixed[0], fixed, envvv);
// 				if (execve(fixed[0], fixed, envvv) == -1)
// 					perror("execve");
// 			}
// 			else
// 			{
// 				int status;
// 				wait(&status);
// 			}
// 		}
// 	}
// };

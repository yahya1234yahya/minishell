/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:44:46 by mboughra          #+#    #+#             */
/*   Updated: 2024/10/08 10:24:45 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



// void child_process(int pipefd[2], t_cmd *cmd)
// {
// 	char **splited;
// 	char *command;

// 	// helperfunction(&cmd, &fixed2, &splited2);
// 	close(pipefd[1]); // Close the write end of the pipe
// 	dup2(pipefd[0], STDIN_FILENO);
// 	if (cmd->args)
// 	{	
// 		command = ft_strjoin(cmd->path, " ");
// 		command = ft_strjoin(command, cmd->args);
// 		splited = ft_split(command, ' ');
// 	}else
// 	{
// 		splited = (char **)safe_malloc(sizeof(char *) * 2);
// 		splited[0] = cmd->path;
// 		splited[1] = NULL;
// 	}
// 	// helperfunction(&cmd, &fixed, &splited);
// 	if (access(splited[0], X_OK | F_OK) == 0)
// 	{
// 		if (execve(splited[0], splited, convert(cmd)) == -1)
// 			perror("execve");
// 	}
// }

// void parent_process(int pipefd[2], t_cmd *cmd)
// {
// 	char **splited;
// 	char *command;
// 	int pid;
// 	// helperfunction(&cmd, &fixed, &splited);
// 	close(pipefd[0]); // Close the read end of the pipe
// 	// Redirect the output to the command
// 	dup2(pipefd[1], STDOUT_FILENO);
// 	if (cmd->args)
// 	{	
// 		command = ft_strjoin(cmd->path, " ");
// 		command = ft_strjoin(command, cmd->args);
// 		splited = ft_split(command, ' ');
// 	}
// 	else
// 	{
// 		splited = (char **)safe_malloc(sizeof(char *) * 2);
// 		splited[0] = cmd->path;
// 		splited[1] = NULL;
// 	}
// 	// helperfunction(&cmd, &fixed, &splited);
// 	if (access(splited[0], X_OK | F_OK) == 0)
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			if (execve(splited[0], splited, convert(cmd)) == -1)
// 				perror("execve");
// 		}
// 		else
// 			waitpid(pid, NULL, 0);
// 	}
// 	else
// 		exit(0);
// }


// static void executemultiple(t_cmd *cmd , char **envp)
// {
// 	int input;
// 	int output;
// 	int pipefd[2];

// 	input = dup(STDIN_FILENO);
// 	output = dup(STDOUT_FILENO);
// 	pid_t pid;
// 	// 0 is read end, 1 is write end
// 	pipe(pipefd);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		child_process(pipefd, cmd->next);
// 	}
// 	else
// 	{
// 		parent_process(pipefd, cmd);
// 	}
// 	// dup2(input, STDIN_FILENO);
// 	// dup2(output, STDOUT_FILENO);

// }


#include "../minishell.h"


// void child_process(int pipefd[2], t_cmd *cmd)
// {
//     char **splited;
//     char *command;

//     close(pipefd[1]); // Close the write end of the pipe

//     if (cmd->args) {
//         command = ft_strjoin(cmd->path, " ");
//         command = ft_strjoin(command, cmd->args);
//         splited = ft_split(command, ' ');
//     } else {
//         splited = (char **)safe_malloc(sizeof(char *) * 2);
//         splited[0] = cmd->path;
//         splited[1] = NULL;
//     }

//     if (access(splited[0], X_OK | F_OK) == 0)
// 	{
//         if (execve(splited[0], splited, convert(cmd)) == -1)
//             perror("execve");
//     }
// }

// void parent_process(int pipefd[2], t_cmd *cmd)
// {
//     char **splited;
//     char *command;

//     close(pipefd[0]); // Close the read end of the pipe

//     if (cmd->args) {
//         command = ft_strjoin(cmd->path, " ");
//         command = ft_strjoin(command, cmd->args);
//         splited = ft_split(command, ' ');
//     } else {
//         splited = (char **)safe_malloc(sizeof(char *) * 2);
//         splited[0] = cmd->path;
//         splited[1] = NULL;
//     }

//     if (access(splited[0], X_OK | F_OK) == 0) {
//         if (execve(splited[0], splited, convert(cmd)) == -1)
//             perror("execve");
//     } else {
//         exit(0);
//     }
// }

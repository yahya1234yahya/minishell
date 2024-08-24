/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decider.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:44:19 by mboughra          #+#    #+#             */
/*   Updated: 2024/07/31 21:30:27 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void redirectchange(t_cmd *cmd)
{
	dup2(cmd->ft_in, STDIN_FILENO);
	dup2(cmd->ft_out, STDOUT_FILENO);
	// write(STDIN_FILENO, "hsssssere\n", 11);
	// close(cmd->ft_in);
	// close(cmd->ft_out);
};

static int isbuiltin(t_cmd *cmd)
{
	if (!ft_strcmp("echo", cmd->cmd))
		ft_echo(cmd);
	else if (!ft_strcmp("cd", cmd->cmd))
		changedir(cmd);
	else if (!ft_strcmp("export", cmd->cmd))
		ft_export(cmd);
	else if (!ft_strcmp("env", cmd->cmd))
		printenv(cmd->env);
	else if (!ft_strcmp("exit", cmd->cmd))
		exit(0);
	else if (!ft_strcmp("pwd", cmd->cmd))
		ft_pwd(cmd->env);
	else if (!ft_strcmp("unset", cmd->cmd))
		ft_unset(&cmd->env, cmd);
	else
		return (-1);
	return (0);
}
static 	void	executesingle(t_cmd *cmd , char **envp)
{
	int input;
	int output;

	if (cmd->redout != 0 || cmd->redin != 0)
	{
		input = dup(STDIN_FILENO);
		output = dup(STDOUT_FILENO);
		redirectchange(cmd);
	}
	if (isbuiltin(cmd) == -1)
		execfromsystem(cmd, envp);
	if (cmd->ft_in != input)
	{
		filedreset(input, output);
	}
}

static int helper(t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd, "echo") == 0 || ft_strcmp(cmd->cmd, "pwd") == 0
		|| ft_strcmp(cmd->cmd, "env") == 0 || ft_strcmp(cmd->cmd, "exit") == 0 
			|| ft_strcmp(cmd->cmd, "cd") == 0 
				|| ft_strcmp(cmd->cmd, "export") == 0 
					|| ft_strcmp(cmd->cmd, "unset") == 0)
		return (0);

	else
		return (-1);

}

int child(t_cmd *cmd, int input , int *pipefd)
{
	close(pipefd[0]);
	dup2(input, STDIN_FILENO);
	if (cmd->next != NULL) // If not the last command, redirect output to pipe
		dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	if (helper(cmd) == 0)
	{
		if (cmd->redin != 0 || cmd->redout != 0)
			redirectchange(cmd);
		isbuiltin(cmd);
		exit(0);
	}
	else
	{
		cmd = preparecmd(cmd);
		if (access(cmd->splited[0], X_OK | F_OK) == 0)
		{
			if (execve(cmd->splited[0], cmd->splited,convert(cmd)) == -1)
			{ 
				perror("execve");
				return (-1);
			}
		}
		else
		{
			perror("access");
			return (-1);
		}
	}
	return (0);
}


void executemultiple(t_cmd *cmd)
{
	int		input;
	int		output;
	int		pipefd[2];
	pid_t	pid;

	while (cmd)
	{
		if (cmd->cmd == NULL)
			break;
		pipe(pipefd);
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{		
			child(cmd, input, pipefd);
		}
		else
		{
			close(pipefd[1]);
			waitpid(pid, NULL, 0);
			input = dup(pipefd[0]);
			close(pipefd[0]);
		}
		cmd = cmd->next;
	}
}

// 0 is read end, 1 is write end

// static void executemultiple(t_cmd *cmd , char **envp)
// {
//     int		input;
// 	int		output;
// 	int		pipefd[2];
//     pid_t	pid;

// 	output = dup(STDOUT_FILENO);
// 	while (cmd->next)
// 	{
// 		if (exeqtonebyone(pipefd, cmd) == -1)
// 			exit(1);
// 	}
	

// };

// static int exeqtonebyone(int pipefd[2], t_cmd *cmd)
// {
// 	int pid;

// 	pipe(pipefd);
// 	close(pipefd[0]); 				// Close the read end of the pipe
// 	dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to the write end of the pipe
// 	close(pipefd[1]); 				// Close the write end of the pipe
// 	cmd = preparecmd(cmd);
// 	if (access(cmd->splited[0], X_OK | F_OK) == 0)
// 	{
// 		pid = fork();
// 		if(pid == 0)
// 			if (execve(cmd->splited[0], cmd->splited, convert(cmd)) == -1)
// 			{
// 				perror("execve");
// 				exit(1);
// 			}
// 		else
// 			waitpid(pid, NULL, 0);
// 	}
// 	else
// 	{
// 		perror("access\n");
// 		exit(1);
// 	}
// 	return (0);
// }

// void parent_process(int pipefd[2], t_cmd *cmd)
// {
//     char **splited;
//     char *command;
// 	int pid;

//     close(pipefd[0]); // Close the read end of the pipe

//     if (cmd->args)
// 	{
//         command = ft_strjoin(cmd->path, " ");
//         command = ft_strjoin(command, cmd->args);
//         splited = ft_split(command, ' ');
//     }
// 	else 
// 	{
//         splited = (char **)malloc(sizeof(char *) * 2);
//         splited[0] = cmd->path;
//         splited[1] = NULL;
//     }

//     if (access(splited[0], X_OK | F_OK) == 0)
// 	{	
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			if (execve(splited[0], splited, convert(cmd)) == -1)
// 				perror("execve");
// 		}
// 		else
// 		{
// 			waitpid(pid, NULL, 0);
// 		}
//     }
// 	else
// 	{
//         exit(0);
//     }
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
/*
	int input;
	int output;
	
	if (cmd->redout != 0)
	{
		input = dup(STDIN_FILENO);
		output = dup(STDOUT_FILENO);
		redirectchange(cmd);
	}*/


int filedreset(int input, int output)
{
	dup2(input, STDIN_FILENO);
	dup2(output, STDOUT_FILENO);
	close(input);
	close(output);
	return (0);
};

void decider(t_cmd *cmd)
{
	char **env;

	env = convert(cmd);
	if (cmd->next == NULL)
	{
		// ft_export(cmd);
		executesingle(cmd, env);
	}
	else
	{
		executemultiple(cmd);
	}
}


// void execute_pipeline(t_cmd *cmds, int num_cmds, char **envp)  //deleteme or change me
// {
// 	int pipefd[2];
// 	int prev_pipe;
// 	int i;
	
// 	i = 0;
// 	prev_pipe = 0;

// 	while (i < num_cmds)
// 	{
// 		if (i < num_cmds - 1) //if not last command
// 		{
// 			if (pipe(pipefd) == -1) //create pipe
// 			{
// 				perror("pipe");
// 				exit(1);
// 			}
// 		}
// 		pid_t pid = fork(); //create child process
// 		if (pid == -1)
// 		{
// 			perror("fork");
// 			exit(1);
// 		}
// 		else if (pid == 0)
// 		{
// 			if (i > 0) //if not first command
// 			{
// 				dup2(prev_pipe, STDIN_FILENO);
// 				close(prev_pipe);
// 			}

// 			if (i < num_cmds - 1)
// 			{
// 				dup2(pipefd[1], STDOUT_FILENO);
// 				close(pipefd[0]);
// 				close(pipefd[1]);
// 			}

// 			redirectchange(&cmds[i]);
// 			// execute_command(&cmds[i], envp);
// 		}
// 		else
// 		{
// 			if (i > 0)
// 				close(prev_pipe);

// 			if (i < num_cmds - 1)
// 			{
// 				prev_pipe = pipefd[0];
// 				close(pipefd[1]);
// 			}
// 			wait(NULL);
// 		}
// 		i++;
// 	}
// }


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

int nodeslen(t_cmd *cmd)
{
	int i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

void redirectchange(t_cmd *cmd)
{
	if (cmd->redirection == 2 || cmd->redirection == 3)
	{
		dup2(cmd->fd_redirect, STDOUT_FILENO);
		close(cmd->fd_redirect);
	}
	else if (cmd->redirection == 1 || cmd->redirection == 4)
	{
		dup2(cmd->fd_redirect, STDIN_FILENO);
		close(cmd->fd_redirect);
	}
}

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

	if (cmd->redirection != 0)
	{
		printf("--------------------\n--->%d<---\n--->%d<---\n", STDIN_FILENO, STDOUT_FILENO);
		input = dup(STDIN_FILENO);
		output = dup(STDOUT_FILENO);
		redirectchange(cmd);
	}
	if (isbuiltin(cmd) == -1)
		notbuilt(cmd, envp);

	//reset file descriptors
	filedreset(input, output);	
}

static void executemultiple(t_cmd *cmd , char **envp)
{

}
/*
	int input;
	int output;
	
	if (cmd->redirection != 0)
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

void decider(t_cmd *cmd, char **envp)
{

	if (cmd->next == NULL)
	{
		// ft_export(cmd);
		executesingle(cmd, envp);
	}
	else
	{
		executemultiple(cmd, envp);
	}
	// printf("--------------------\n--->%d<---\n--->%d<---\n", cmd->data.originalfd[0], cmd->data.originalfd[1]);
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


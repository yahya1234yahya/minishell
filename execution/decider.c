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
		printenv(cmd->env, 1);
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

int child(t_cmd *cmd, int input, int *pipefd)
{
    close(pipefd[0]);
    if (cmd->redin != 0)
        dup2(cmd->ft_in, STDIN_FILENO);
	else
        dup2(input, STDIN_FILENO);
    if (cmd->redout != 0)
        dup2(cmd->ft_out, STDOUT_FILENO);
	else if (cmd->next != NULL)
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
    exit(EXIT_SUCCESS);
}

static void parent(int *input, int *pipefd)
{
	close(pipefd[1]);
	if (*input != STDIN_FILENO)
		close(*input);
	*input = pipefd[0];
}

void executemultiple(t_cmd *cmd)
{
	pid_t	pid;
	int		input;
	int		pipefd[2];
	
	input = STDIN_FILENO;
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
            child(cmd, input, pipefd);
        else
			parent(&input, pipefd);
        cmd = cmd->next;
	}
	while (wait(NULL) > 0)
        ;
}

// void executemultiple(t_cmd *cmd) 							//mine//
// {
//     int input;
	
//     int pipefd[2];
//     pid_t pid;

// 	input = STDIN_FILENO;
//     while (cmd)
// 	{
//         if (cmd->cmd == NULL)
//             break;
//         pipe(pipefd);
//         pid = fork();
//         if (pid == -1)
// 		{
//             perror("fork");
//             exit(EXIT_FAILURE);
//         }
//         if (pid == 0)
// 		{ 
// 			child(cmd, input, pipefd);
//         }
// 		else
// 		{
// 			close(pipefd[1]);
// 			// waitpid(pid, NULL, 0);
//             input = dup(pipefd[0]);
//             close(pipefd[0]);
//         }
//         cmd = cmd->next; // Move to the next command
//     }
// 	while (wait(NULL) > 0)
// 		;
	
// }


int filedreset(int input, int output)
{
	dup2(input, STDIN_FILENO);
	dup2(output, STDOUT_FILENO);
	close(input);
	close(output);
	return (0);
}

void decider(t_cmd *cmd)
{
	char **env;

	if (cmd->next == NULL)
	{
		//TODO export last argument
		env = convert(cmd);
		executesingle(cmd, env);
	}
	else
	{
		executemultiple(cmd);
	}
}

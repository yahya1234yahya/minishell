/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executemulti.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:31:17 by mboughra          #+#    #+#             */
/*   Updated: 2024/11/01 15:37:33 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parent(int *input, int *pipefd)
{
	close(pipefd[1]);
	if (*input != STDIN_FILENO)
		close(*input);
	*input = pipefd[0];
}

void	prechildredirection(t_cmd *cmd, int input, int *pipefd)
{
	close(pipefd[0]);
	if (cmd->skip == 1)
		exit(1);
	if (cmd->redin != 0)
		dup2(cmd->ft_in, STDIN_FILENO);
	else
		dup2(input, STDIN_FILENO);
	if (cmd->redout != 0)
		dup2(cmd->ft_out, STDOUT_FILENO);
	else if (cmd->next != NULL)
		dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
}

void	child(t_cmd *cmd, int input, int *pipefd)
{
	int	check;

	prechildredirection(cmd, input, pipefd);
	if (helper(cmd) != 1337)
	{
		isbuiltin(cmd, helper(cmd), 0);
		exit(0);
	}
	else
	{
		check = preparecmd(cmd);
		if (check)
			exit(check);
		check = check_command(cmd->splited[0]);
		if (check)
			exit(check);
		if (execve(cmd->splited[0], cmd->splited, convert(cmd)) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
	exit(EXIT_SUCCESS);
}

int	executemultiple(t_cmd *cmd)
{
	int	input;
	int	pipefd[2];
	int	status;
	int	pid;

	input = STDIN_FILENO;
	while (cmd)
	{
		if (cmd->cmd == NULL)
			cmd->cmd = ft_strdup("/usr/bin/true");
		pipe(pipefd);
		pid = fork();
		if (pid == -1)
			return ((perror("fork"), setandget(NULL)->exs = 1), 1);
		if (pid == 0)
			child(cmd, input, pipefd);
		else
			parent(&input, pipefd);
		cmd = cmd->next;
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		setandget(NULL)->exs = 128 + WTERMSIG(status);
	else if (WIFEXITED(status))
		setandget(NULL)->exs = WEXITSTATUS(status);
	// waiter(pid, &status);
	while (wait(NULL) > 0)
		;
	close(pipefd[0]);
	return (0);
}

int	waiter(int pid, int *status)
{
	waitpid(pid, status, 0);
	if (WIFSIGNALED(*status))
		return (setandget(NULL)->exs = 128 + WTERMSIG(*status));
	else if (WIFEXITED(*status))
		return (setandget(NULL)->exs = WEXITSTATUS(*status));
	return (0);
}

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

int redirectchange(t_cmd *cmd)
{
	if (dup2(cmd->ft_in, STDIN_FILENO) == -1)
	{
		perror("dup2");
		cmd->exs = 1;
		return (-1);
	}
	
	if (dup2(cmd->ft_out, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		cmd->exs = 1;
		return (-1);
	}
	
	return (0);
};
int ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

int ft_strcmp2(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (ft_tolower(*s1) != ft_tolower(*s2))
			return (ft_tolower(*s1) - ft_tolower(*s2));
		s1++;
		s2++;
	}
	return (ft_tolower(*s1) - ft_tolower(*s2));
}
static int isbuiltin(t_cmd *cmd)
{
	if (!ft_strcmp2("echo", cmd->cmd))
		ft_echo(cmd);
	else if (!ft_strcmp2("cd", cmd->cmd))
		{
			if (changedir(cmd) == -1)
			return (-1);
		}
	else if (!ft_strcmp("export", cmd->cmd))
		ft_export(cmd);
	else if (!ft_strcmp2("env", cmd->cmd))
		printenv(cmd->env, 1);
	else if (!ft_strcmp("exit", cmd->cmd))
	{
		printf("exit\n");
		exit(0);
	}
	else if (!ft_strcmp2("pwd", cmd->cmd))
		ft_pwd(cmd->env);
	else if (!ft_strcmp("unset", cmd->cmd))
		ft_unset(&cmd->env, cmd);
	else
		return (1337);
	return (0);
}

int	executesingle(t_cmd *cmd , char **envp)
{
	int input;
	int output;
	int retv;

	if (cmd->redout != 0 || cmd->redin != 0)
	{
		input = dup(STDIN_FILENO);
		output = dup(STDOUT_FILENO);
		if (input == -1 || output == -1 || redirectchange(cmd) == -1)
		{
			perror("dup");
			return (-1);
		}
		// char buffer[6];
		// lseek(STDIN_FILENO, 0, SEEK_SET);
		// read(STDIN_FILENO, buffer, 5);
		// write(STDOUT_FILENO, buffer, 5);
	
	}
	retv = isbuiltin(cmd);
	if (retv == 1337)
	{
		if (execfromsystem(cmd, envp) == -1)
			return (-1);
	}
	else if (retv == -1)
		return (-1);
	if (cmd->ft_in != input || cmd->ft_out != output)
		if (filedreset(input, output) == -1)
			return (-1);
	return (0);
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

// int child(t_cmd *cmd, int input, int *pipefd)
// {
//     close(pipefd[0]);
//     if (cmd->redin != 0)
//         dup2(cmd->ft_in, STDIN_FILENO);
// 	else
//         dup2(input, STDIN_FILENO);
//     if (cmd->redout != 0)
//         dup2(cmd->ft_out, STDOUT_FILENO);
// 	else if (cmd->next != NULL)
//         dup2(pipefd[1], STDOUT_FILENO);
//     close(pipefd[1]);
//  	if (helper(cmd) == 0)
// 	{
// 		if (cmd->redin != 0 || cmd->redout != 0)
// 			redirectchange(cmd);
// 		isbuiltin(cmd);
// 		exit(0);
// 	}
// 	else
// 	{
// 		cmd = preparecmd(cmd);
// 		if (access(cmd->splited[0], X_OK | F_OK) == 0)
// 		{
// 			if (execve(cmd->splited[0], cmd->splited,convert(cmd)) == -1)
// 			{ 
// 				perror("execve");
// 				return (-1);
// 			}
// 		}
// 		else
// 		{
// 			ft_errorwrite(cmd);
// 			return (-1);
// 		}
// 	}
//     exit(EXIT_SUCCESS);
// }


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
			ft_errorwrite(cmd);
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

// static void parent(int *input, int *pipefd)
// {
// 	close(pipefd[1]);
// 	if (*input != STDIN_FILENO)
// 		close(*input);
// 	*input = pipefd[0];
// }

// void executemultiple(t_cmd *cmd)  //this
// {
// 	pid_t	pid;
// 	int		input;
// 	int		pipefd[2];
	
// 	input = STDIN_FILENO;
// 	while (cmd)
// 	{
// 		if (cmd->cmd == NULL)
// 			break;
// 		pipe(pipefd);
// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			perror("fork");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (pid == 0)
// 		{
//             if(child(cmd, input, pipefd) == -1)
// 				exit(1);
// 		}
//         else
// 			parent(&input, pipefd);
//         cmd = cmd->next;
// 	}
// 	while (wait(NULL) > 0)
// 		;
// }
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
		{
            if(child(cmd, input, pipefd) == -1)
				exit(1);
		}
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
	char	**env;
	char	**last_argument;
	int		i;


	if (cmd->next == NULL)
	{
		env = convert(cmd);
		if (executesingle(cmd, env) == 0)
			setandget(NULL)->exs = 0;
		if (cmd->args == NULL)
			cmd->args = ft_strjoin("_=", cmd->cmd);
		else
		{
			i = 0;
			last_argument = ft_split(cmd->args, ' ');
			while (last_argument[i])
				i++;
			cmd->args = ft_strjoin("_=",	last_argument[i - 1]);
		}
		ft_export(cmd);
	}
	else
		executemultiple(cmd);
}

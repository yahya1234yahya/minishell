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
		return (-1);
	if (dup2(cmd->ft_out, STDOUT_FILENO) == -1)
		return (-1);
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


static int isbuiltin(t_cmd *cmd, int value, int flag)
{
	int	retv;

	retv = 1337;
	if (value == 1)
		retv = ft_echo(cmd);
	if (value == 2)
		retv = ft_pwd(cmd->env);
	if (value == 3)
		retv = printenv(cmd->env, 1);
	if (value == 4)
		ft_exit(cmd->args, flag);
	if (value == 5)
		retv = changedir(cmd);
	if (value == 6)
		retv = ft_export(cmd);
	if (value == 7)
		retv = ft_unset(&cmd->env, cmd);
	return (retv);
}

int	executesingle(t_cmd *cmd , char **envp)
{
	int input;
	int output;
	int retv;
	int	value;

	if (cmd->skip == 1)
		return (-42);
	if (cmd->redout != 0 || cmd->redin != 0)
	{
		input = dup(STDIN_FILENO);
		output = dup(STDOUT_FILENO);
		if (input == -1 || output == -1 || redirectchange(cmd) == -1)
		{
			write(2, "dup or dup2 failed\n", 21);
			return (-1);
		}
	}
	value = helper(cmd);
	if (value == 1337)
	{
		retv = execfromsystem(cmd, envp);
			return (filedreset(input, output), retv);
	}
	else
		retv = isbuiltin(cmd, value, 1);
	return (filedreset(input, output), retv);
}

int helper(t_cmd *cmd)
{
	int i;
	
	i = 0;
	if (ft_strcmp2(cmd->cmd, "echo") == 0) //don't remove the quotes
		i = 1;
	else if (ft_strcmp2(cmd->cmd, "pwd") == 0)
		i = 2;
	else if (ft_strcmp2(cmd->cmd, "env") == 0)
		i = 3;
	else if (ft_strcmp2(cmd->cmd, "exit") == 0) //don't remove the quotes
		i = 4; 
	else if (ft_strcmp2(cmd->cmd, "cd") == 0)
		i = 5; 
	else if (ft_strcmp(cmd->cmd, "export") == 0) //don't remove the quotes
		i = 6;
	else if (ft_strcmp(cmd->cmd, "unset") == 0) //don't remove the quotes
		i = 7;
	else
		return (1337);
	if (i && i != 6 && i != 7 && i != 4 && i != 1)
	{
		cmd->args = remove_quotes(cmd->args);
	}
	return (i);
}


int child(t_cmd *cmd, int input, int *pipefd)
{
	int check;

    close(pipefd[0]);
	if (cmd->skip == 1)
			exit(1) ;
    if (cmd->redin != 0)
        dup2(cmd->ft_in, STDIN_FILENO);
	else
        dup2(input, STDIN_FILENO);
    if (cmd->redout != 0)
        dup2(cmd->ft_out, STDOUT_FILENO);
	else if (cmd->next != NULL)
        dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);
	if(helper(cmd)!= 1337)
		{
			isbuiltin(cmd, helper(cmd), 0);
			exit(0);
		}
	else
	{
		check =  preparecmd(cmd);
		if (check)
			return (check);
		check = check_command(cmd->splited[0]);
		if (check)
			return (check);
		if (execve(cmd->splited[0], cmd->splited,convert(cmd)) == -1)
		{ 
			perror("execve");
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

int	executemultiple(t_cmd *cmd)
{
	pid_t	pid;
	int		input;
	int		pipefd[2];
	int		status;
	
	input = STDIN_FILENO;
	while (cmd)
	{
		//TODO make updates of the old env for the new usage in case changed :'(
		if (cmd->cmd == NULL)
		{
			cmd = cmd->next;
			continue;
		}
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
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			setandget(NULL)->exs = 128 + WTERMSIG(status);
		}
		else if (WIFEXITED(status))
		{
			setandget(NULL)->exs = WEXITSTATUS(status);
		}
	while (wait(NULL) > 0)
        ;
	return (0);
}

int filedreset(int input, int output)
{
	dup2(input, STDIN_FILENO);
	dup2(output, STDOUT_FILENO);
	close(input);
	close(output);
	return (0);
}

void	decider(t_cmd *cmd)
{
	char	**env;
	char	**last_argument;
	int		i;
	int		exs;

	if (cmd->next == NULL)
	{
		if (cmd->cmd == NULL)
			return ;
		
		env = convert(cmd);
		exs = executesingle(cmd, env);
		if (exs == 0)
			setandget(NULL)->exs = 0;
		else if (exs == -1 || exs == 1)
			setandget(NULL)->exs = 1;
		if (cmd->args == NULL)
			envset2(cmd->env, "_", cmd->cmd);
		else
		{
			last_argument = ft_split(cmd->args, ' ');
			i = 0;
			while (last_argument[i])
				i++;
			envset2(cmd->env, "_", last_argument[i - 1]);
		}
	}
	else
		executemultiple(cmd);
		
}
















	// if (data)
	// {

	// 	num = 1;
	// 	i = 0;
	// 	if ((data[0] == '-' || data[0] == '+' || isdigit(data[0])) && ft_strlen(data) != 1)
	// 		i++;
	// 	while (num)
	// 	{	
	// 		if (data[i] == ' ')
    //         {
    //             if (data[i+1] != 0)
	// 			{
	// 				write(2, "exit\n", 5);
    //                 write(2, "minishell: exit", 16);
    //                 write(2, ": too many arguments\n", 22);
    //                 exit(1);
    //             }
    //         }
	// 		if (isdigit(data[i]) == 0)
	// 		{
	// 			if (data[i] == '\0')
	// 				break;
	// 			num = 0;
	// 			write(2, "exit\n", 5);
	// 			write(2, "minishell: exit", 16);
	// 			write(2, ": numeric argument required\n", 29);
	// 			exit(255);
	// 		}
	// 		else
	// 			i++;
	// 	}
	// 	ft_putstr_fd("exit\n", 1);
	// 	exit(ft_atoi(data));
	// }
	// else
	// {
	// 	ft_putstr_fd("exit\n", 1);
	// 	exit(setandget(NULL)->exs);
	// }
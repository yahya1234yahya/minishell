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

int	isbuiltin(t_cmd *cmd, int value, int flag)
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
		retv = preexport(cmd);
	if (value == 7)
		retv = ft_unset(&cmd->env, cmd);
	return (retv);
}

int	helper(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (ft_strcmp2(cmd->cmd, "echo") == 0)
		i = 1;
	else if (ft_strcmp2(cmd->cmd, "pwd") == 0)
		i = 2;
	else if (ft_strcmp2(cmd->cmd, "env") == 0)
		i = 3;
	else if (ft_strcmp2(cmd->cmd, "exit") == 0)
		i = 4;
	else if (ft_strcmp2(cmd->cmd, "cd") == 0)
		i = 5;
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		i = 6;
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		i = 7;
	else
		return (1337);
	if (i == 2 || i == 3)
		cmd->args = remove_quotes(cmd->args);
	return (i);
}

int	filedreset(int input, int output)
{
	dup2(input, STDIN_FILENO);
	dup2(output, STDOUT_FILENO);
	return (0);
}

void	exportlastcommand(t_cmd *cmd, int flag)
{
	char	**last_argument;
	int		i;

	if (flag == 1)
	{
		envset2(cmd->env, "_", NULL);
		return ;
	}
	else if (flag == 0)
	{
		if (cmd->args == NULL || cmd->args[0] == '\0')
			envset2(cmd->env, "_", cmd->path);
		else
		{
			last_argument = ft_split(cmd->args, ' ');
			i = 0;
			while (last_argument[i])
				i++;
			envset2(cmd->env, "_", last_argument[i - 1]);
		}
	}
}

void	decider(t_cmd *cmd)
{
	char	**env;
	int		exs;

	ft_unlink(cmd);
	if (cmd->next == NULL)
	{
		exportlastcommand(cmd, 0);
		if (cmd->cmd == NULL)
			return ;
		env = convert(cmd);
		exs = executesingle(cmd, env);
		if (exs == 0)
			setandget(NULL)->exs = 0;
		else if (exs == -1 || exs == 1)
			setandget(NULL)->exs = 1;
	}
	else
	{
		executemultiple(cmd);
	}
	reset(cmd);
}

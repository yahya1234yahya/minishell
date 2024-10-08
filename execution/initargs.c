/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initargs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 03:31:51 by mboughra          #+#    #+#             */
/*   Updated: 2024/08/08 03:31:51 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*set_cmd(t_cmd *cmd)
{
	if (cmd->first_run == 1)
	{
		cmd->first_run = 0;
		cmd->exs = 0;
	}
	cmd->input = NULL;
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->skip = 0;
	cmd->pipe = 0;
	cmd->redout = 0;
	cmd->redin = 0;
	cmd->ft_in = STDIN_FILENO;
	cmd->ft_out = STDOUT_FILENO;
	cmd->path = NULL;
	cmd->next = NULL;
	cmd->hdoc_delimiter = NULL;
	cmd->signal_exs_flag = 0;
	return (cmd);
};
t_cmd	*init_cmd()
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)safe_malloc(sizeof(t_cmd), 'a');
	if (!new_cmd)
	{
		perror("malloc");
		exit(1);
	}
	new_cmd->input = NULL;
	new_cmd->cmd = NULL;
	new_cmd->skip = 0;
	new_cmd->args = NULL;
	new_cmd->pipe = 0;
	new_cmd->redout = 0;
	new_cmd->redin = 0;
	new_cmd->ft_in = STDIN_FILENO;
	new_cmd->ft_out = STDOUT_FILENO;
	new_cmd->path = NULL;
	new_cmd->next = NULL;
	new_cmd->hdoc_delimiter = NULL;
	new_cmd->exs = 0;
	return (new_cmd);
};

// typedef struct s_cmd
// {
// 	char	*input;
// 	char	*cmd;  
// 	char	*args;
// 	int		pipe;
// 	int		redout;
// 	int		redin;
// 	int		ft_in;
// 	int		ft_out;
// 	char 	*path;
// 	char	*hdoc;
// 	t_env	*env;
// 	t_data	data;
// 	char	**splited;
// 	int		exs;
// 	struct 	s_cmd *next;
// } 
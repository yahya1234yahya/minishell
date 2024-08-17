/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 03:30:51 by mboughra          #+#    #+#             */
/*   Updated: 2024/08/17 10:19:38 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


t_cmd *hdoc(char *delimiter, t_cmd *cmd)
{
	char *line;
	char *tmp;
	int		fd;
	
	tmp = NULL;
	line = ft_strdup("");
	while (1)
	{
		tmp = readline("> ");
		if (ft_strcmp(tmp, delimiter) == 0)
			break;
		line = ft_strjoin(line, tmp);
		line = ft_strjoin(line, "\n");
	}
	fd = open("tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	write(fd, line, ft_strlen(line));
	cmd->hdoc = line;
	cmd->ft_in = fd;
	return (cmd);
};

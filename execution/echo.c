/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:42:32 by mboughra          #+#    #+#             */
/*   Updated: 2024/07/29 18:04:48 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int echohelper(t_cmd *cmd)
{
	if (cmd->args[0] == '-' && cmd->args[1] == 'n' && cmd->args[2] == ' ')
		return (3);
	return (0);
}

int	ft_echo(t_cmd *cmd)
{
    int option;
    int i;
	int	j;
	
	i = 0;
	option = 0;
	if (cmd->args == NULL)
	{
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			return(perror("write"), -1);
		return (1);
	}
    while (cmd->args[i] == '-' && cmd->args[i + 1] == 'n')
    {
        j = i + 2;
        while (cmd->args[j] == 'n')
            j++;
        if (cmd->args[j] == ' ' || cmd->args[j] == '\0')
        {
            option = 1;
            i = j;
            while (cmd->args[i] == ' ')
                i++;
        }
        else
            break;
    }
    if(write(STDOUT_FILENO, &cmd->args[i], strlen(&cmd->args[i])) == -1)
		return (perror("write"),-1);
	if (!option)
        if (write(1, "\n", 1) == -1)
			return(perror("write"),-1);
		return (1);
}

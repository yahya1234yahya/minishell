/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 19:02:33 by mboughra          #+#    #+#             */
/*   Updated: 2024/10/20 19:58:00 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void printerrorexport(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static int onechar(char *str, char c)  //checks if the string is only made of one character
{
	int i;

	i = 0;

	while ((str[i]) && (str[i] == c || str[i] == '\'' || str[i] == '\"'))
		i++;
	if (ft_strlen(str) == i)
		return (1);
	return (0);
}


// int ft_export(t_cmd *cmd)
// {
// 	char			**token;
// 	int i;
	
// 	i = 0;
// 	if (cmd->args == NULL)
// 		return (printenv(cmd->env, 0));
// 	if (onechar(cmd->args, ' '))
// 		return (printerrorexport(cmd->args), 1);
// 	token = ft_strtok_all(cmd->args, " ");
	
	
	
	
	

// 	return 0;
// }
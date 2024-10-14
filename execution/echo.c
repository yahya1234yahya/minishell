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

// static int echohelper(t_cmd *cmd)
// {
// 	if (cmd->args[0] == '-' && cmd->args[1] == 'n' && cmd->args[2] == ' ')
// 		return (3);
// 	return (0);
// }

// int	ft_echo(t_cmd *cmd)
// {
//     int option;
//     int i;
// 	int	j;
	
// 	i = 0;
// 	option = 0;
// 	if (cmd->args == NULL || cmd->args[0] == '\0')
// 	{
// 		if (write(STDOUT_FILENO, "\n", 1) == -1)
// 			return(perror("write"), -1);
// 		return (0);
// 	}
//     while (cmd->args[i] == '-' && cmd->args[i + 1] == 'n')
//     {
//         j = i + 2;
//         while (cmd->args[j] == 'n')
//             j++;
//         if (cmd->args[j] == ' ' || cmd->args[j] == '\0')
//         {
//             option = 1;
//             i = j;
//             while (cmd->args[i] == ' ')
//                 i++;
//         }
//         else
//             break;
//     }
//     if(write(STDOUT_FILENO, &cmd->args[i], strlen(&cmd->args[i])) == -1)
// 		return (perror("write"),-1);
// 	if (!option)
//         if (write(1, "\n", 1) == -1)
// 			return(perror("write"),-1);
// 		return (0);
// }


static int check_string(char *str)
{
    int i = 0;

    if (strlen(str) < 2)
        return 0;

    if (str[0] == '-' && str[1] == 'n')
	{
        i = 2;
        while (str[i] == 'n')
            i++;
        if (str[i] == '\0')
            return 1;
    }
    return (0);
}

static char **preparetokecho(char *str)
{
	char	**tok;
	int		i;

	i = 0;
	tok = ft_strtok_all(str, " ");
	while (tok[i])
	{
		tok[i] = remove_quotes(tok[i]);
		i++;
	}
	return (tok);
}

static int allspace(char *str)
{
	int i;

	i = 0;
	if (str == NULL)
	{
		ft_putstr_fd("\n", 1);
		return (1);
	}
	
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\'' || str[i] == '\"')
		i++;
	if (i == ft_strlen(str))
	{
		ft_putstr_fd("\n", 1);
		return (1);
	}
	return (0);
}
	
// int	ft_echo(t_cmd *cmd)
// {
// 	int		flag;
// 	int		i;
// 	char	**tok;
// 	char	*str;

// 	flag = 0;
// 	if (cmd->args == NULL || cmd->args[0] == '\0' )
// 		if (write(STDOUT_FILENO, "\n", 1) == -1)
// 			return (perror("write"), setandget(NULL)->exs = 1,  -1);
// 		else
// 			return (0);
// 	tok = preparetokecho(cmd->args);
// 	i = 0;
// 	while (tok[i])
// 	{
// 		if (check_string(tok[i]))
// 		{
// 			flag = 1;
// 			i++;
// 		}else
// 			break;
// 	}
// 	if (tok[i] == NULL)
// 		return (0);
// 	cmd->args = remove_quotes(cmd->args);
// 	str = ft_strnstr(cmd->args, tok[i], ft_strlen(cmd->args));
// 	ft_putstr_fd(str, 1);
// 	if (!flag)
// 		ft_putstr_fd("\n", 1);
// 	return (0);
// }


int	handle_write_error(void)
{
	if (write(STDOUT_FILENO, "\n", 1) == -1)
	{
		perror("write");
		setandget(NULL)->exs = 1;
		return (-1);
	}
	return (0);
}

int	handle_flags(char **tok, int *flag)
{
	int	i;

	i = 0;
	while (tok[i])
	{
		if (check_string(tok[i]))
		{
			*flag = 1;
			i++;
		}
		else
			break;
	}
	return (i);
}

int	ft_echo(t_cmd *cmd)
{
	int		flag;
	int		i;
	char	**tok;
	char	*str;

	flag = 0;
	if (allspace(cmd->args))
		return (0);
	if (cmd->args == NULL || cmd->args[0] == '\0')
		return (handle_write_error());
	tok = preparetokecho(cmd->args);
	i = handle_flags(tok, &flag);
	if (tok[i] == NULL)
		return (0);
	cmd->args = remove_quotes(cmd->args);
	str = ft_strnstr(cmd->args, tok[i], ft_strlen(cmd->args));
	ft_putstr_fd(str, 1);
	if (!flag)
		ft_putstr_fd("\n", 1);
	return (0);
}


//TODO protect write
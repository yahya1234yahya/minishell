#include "../minishell.h"

t_cmd	*redirectchange(t_cmd *cmd)
{
	char *reader = NULL;
	char *joined;

	joined = NULL;
	
	while (1)
	{
		reader = get_next_line(cmd->fd_redirect);
		if (!reader)
			break ;
		joined = ft_strjoin(joined, reader);
		free(reader);
		reader = NULL;
	};
	cmd->args = joined;
	return (cmd);
};

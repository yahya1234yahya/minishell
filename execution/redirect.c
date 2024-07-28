#include "../minishell.h"

t_cmd	*redirectchange(t_cmd *cmd)
{
	char *reader;
	char *joined = NULL;
	
	while (1)
	{
		reader = get_next_line(cmd->fd_redirect);
		printf("reader : %s\n", reader);
		if (!reader)
			break ;
		joined = ft_strjoin(joined, reader);
		free(reader);
		reader = NULL;
	};
	printf("joined : %s\n", joined);
	cmd->args = joined;
	exit(1);
	return (cmd);
};

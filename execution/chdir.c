#include "../minishell.h"

void changedir(char *path, char **env)
{
	char **oldpwd;
	int i;

	i = 0;
	while(env[i])
	{
		if(strnstr(env[i],"PWD",3))
			break;
		i++;
	}
	oldpwd = ft_split(env[i],'=');
	envset(env,"OLDPWD",oldpwd[1]);
	chdir(path);
	envset(env,"PWD",path);

};


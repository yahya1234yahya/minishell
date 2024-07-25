#include "../minishell.h"
#include <unistd.h>

void changedir(char *path, t_env *env)
{
	char *oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("getcwd");
		exit(1);
	};
	if (chdir(path) == -1)
	{
		perror("chdir");
		return ;
	};
	envset(env, "OLDPWD", oldpwd);
	envset(env, "PWD", path);
};


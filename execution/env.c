#include "../minishell.h"

void	printenv(char **env)
{
	int i;

	i = 0;
	while(env[i])
		printf("%s\n",env[i++]);
}

char **initenv(char **envp)
{
	char	**newenv;
	int		i;

	i = 0;
	while(envp[i])
		i++;
	newenv = (char **)malloc((i + 1) * sizeof(char *));
	if(!newenv)
	{
		perror("malloc");
		exit(1);
	}
	i = 0;
	while(envp[i])
	{
		newenv[i] = strdup(envp[i]);
		i++;
	}
	newenv[i] = NULL;
	return (newenv);
};

int envset(char **env, char *var, char *value)
{
	int i;
	char *newvar;

	i = 0;
	while(env[i])
	{
		if(strnstr(env[i],var,strlen(var)))
		{
			newvar = malloc(strlen(var) + strlen(value) + 2);
			if(!newvar)
			{
				perror("malloc");
				exit(1);
			}
			strcpy(newvar,var);
			strcat(newvar,"=");
			strcat(newvar,value);
			free(env[i]);
			env[i] = newvar;
			return (0);
		}
		i++;
	}
	return (1);
}

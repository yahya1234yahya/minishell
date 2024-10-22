 #include "../minishell.h"

void    check_quots(char c, int *single_q, int  *double_q)
{
    if (c == '\'' && *double_q == 0)
        *single_q = !(*single_q);
    else if (c == '\'' && *double_q == 1)
        return ;
    else if (c == '"' && *single_q == 0)
        *double_q = !(*double_q);
    else if (c == '"' && *single_q == 1)
        return ;
}
int	ft_isalpha(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123))
		return (1);
	else 
		return (0);
}

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	else
		return (0);
}

int count_word(char *input)
{
    int i = 0;
    while(input[i] && (ft_isdigit(input[i]) || ft_isalpha(input[i]) || input[i] == '_') )
    {
        i++;
    }
    return (i);

}

int count_new_input(t_env	*env, char    *input)
{
    int count = 0;
    int count_name = 0;
    int single_q = 0;
    int double_q = 0;
    int i = 0;
    char    *name;
    char    *env_value;
    if (!input)
        return (0);
    
    while (*input)
    {
        i = 0;
        check_quots(*input, &single_q, &double_q);
        if (*input == '$' && *(input + 1) == '?' && single_q == 0)
        {
            input++;
            name = ft_strdup("?");
            env_value = envsearch3(env, name);
            if (env_value)
                count += strlen(env_value);
            free(name);
        }
        else if (*input == '$' && (ft_isalpha(*(input + 1)) || *(input + 1) == '_' ) && single_q == 0)
        {
            input++;
            name = safe_malloc(count_word(input) + 1, 'a');
            if (!name)
                return (0);
            i = 0;
            while(*input && (ft_isdigit(*input) || ft_isalpha(*input) || *input == '_') )
            {
                name[i++] = *input;
                input++;
            }
            name[i] = '\0';
            env_value = envsearch3(env, name);
            if (env_value)
                count += strlen(env_value);
            free(name);
        }
        else if (*input == '$' && (*(input + 1) == '*' || *(input + 1) == '@' || ft_isdigit(*input + 1)))
            input = input + 2;
        else if (*input == '$' && single_q == 0 && double_q ==0 &&  (*(input + 1) == '\'' || *(input + 1) == '\"'))
            input++;
        else 
        {
            count++;
            input++;
        }
    }
    return (count);
}

// int check_ambigous(char *input, char *env_value, int j, char    *name) 
// {
//     if (!env_value)
//     {
//         while(input[j] && input[j] != ' ' && input[j] != '\t')
//             j--;
//         if (input[j] == '<' || input[j] == '>')
//         {
//             ft_putstr_fd("minishell: ", 2);
//             ft_putstr_fd(name, 2);
//              ft_putstr_fd(": ambiguous redirect\n", 2);
//             setandget(NULL)->exs = 1;
//             return (1);
//         }
//     }
//     return (0);
// }

char *expand_variables(t_env	*env, char    *input)
{
    int count;
    int count_name;
    int single_q = 0;
    int double_q = 0;
    int i = 0;
    int j = 0;
    char    *name;
    char    *env_value;
    char    *new_input;
    char    *tmp;
    char    *tmp2;


    if (!input)
        return (0);
    tmp2 = ft_strdup(input);
    tmp = input; 
	count = 0;
    count = count_new_input(env, input);
    // printf("%d\n", count);
    new_input = safe_malloc(count + 1, 'a');
    while (*input)
    {
        i = 0;
        check_quots(*input, &single_q, &double_q);
        if (*input == '$' && *(input + 1) == '?' && single_q == 0)
        {
            input++;
            name = ft_strdup("?");
            env_value = envsearch3(env, name);
            if (env_value)
            {
                while (*env_value)
                {
                    new_input[j++] = *env_value;
                    env_value++;
                }
            }
            input++;
        }
        else if (*input == '$' && (ft_isalpha(*(input + 1)) || *(input + 1) == '_') && single_q == 0)
        {
            input++;
            name = safe_malloc(count_word(input) + 1, 'a');
            i = 0;
            while(*input && (ft_isdigit(*input) || ft_isalpha(*input) || *input == '_' ))
            {
                name[i++] = *input;
                input++;
            }
            name[i] = '\0';
            env_value = envsearch3(env, name);
            // int j = ft_strlen(ft_strnstr(tmp2, name, ft_strlen(name))) - ft_strlen(tmp2);
            // if (check_ambigous(input , env_value, j, name) == 1)
            //    return (NULL);
            // printf("%s\n", env_value);
            if (env_value)
            {
                env_value = add_quotes(env_value);
                while (*env_value)
                {
                    new_input[j++] = *env_value;
                    env_value++;
                }
            }
        }
        else if (*input == '$' && (*(input + 1) == '*' || *(input + 1) == '@' || ft_isdigit(*(input + 1)) ))
            input = input + 2;
        else if (*input == '$' && single_q == 0 && double_q ==0 &&  (*(input + 1) == '\'' || *(input + 1) == '\"'))
            input++;
        else 
        {
            new_input[j++] = *input;
            input++;
        }
    }
    new_input[j] = '\0';
    free(tmp);
    return (new_input);
}

#include "../minishell.h"

void ft_export(t_cmd *cmd) {
    if (!cmd->args) {
        return;
    }
    char *arg = cmd->args;
    char *equal_sign = strchr(arg, '=');
    if (!equal_sign) {
        return;
    }
    *equal_sign = '\0';
    char *var = arg;
    char *value = equal_sign + 1;
    setenv(var, value, 1);
}
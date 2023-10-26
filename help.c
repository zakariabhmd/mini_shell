#include "mini_shell.h"

char **strdup_env(char **env)
{
    char **tmp;
    int len;
    int i;

    len = 0;
    i = 0;
    while(env[len])
        len++;
    tmp = malloc(sizeof(char *) * len + 1);
    if (!tmp)
        return (NULL);
    while (*env && env[i])
    {
        tmp[i] = ft_strdup(env[i]);
        i++;
    }
    tmp[i] = NULL;
    return (tmp);
}
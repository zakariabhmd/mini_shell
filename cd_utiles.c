/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utiles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 19:37:13 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/04 19:41:31 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void    set_path(t_savage *savage ,char *path, char *key)
{
    int     i;
    int     size;
    char    *var;
    char    **backup;

    size = ft_strlen(key) + 1;
    i = 0;
    while (savage->env[i])
    {
        if(ft_strnstr(savage->env[i], key, size))
        {
            var = ft_strjoin(key, path);
            backup = renew_env(&var, savage->env, i);
            free(var);
            free_env(savage->env);
            savage->env = backup;
        }
        i++;
    }

}

void    dce(t_savage *savage, char *path, char *print_err)
{
    char    *err_msg;
    char    *backup;

    path = ft_strjoin(" ", path);
    backup = ft_strdup(path);
    free(path);
    err_msg = ft_strjoin(backup, print_err);
    free(backup);
    ft_error(err_msg, savage->first_arg);
    free(err_msg);
}

void    dir_changer_err(t_savage *savage, char *path)
{
    struct stat d;
    if(stat(path, &d) != -1)
    {
        if(d.st_mode & S_IFDIR)
            dce(savage, path, ": Permission denied");
        else
            ft_error(" not a directory:", savage->first_arg);
    }
    else
        dce(savage, path, ": No such file or directory");
}

void    get_olddir(t_savage *savage,  char *oldpwd)
{
    char    *backup;

    backup = ft_strjoin("OLDPWD=", oldpwd);
    export(savage, backup);
    free(backup);
}
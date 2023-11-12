/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:57:50 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/11 23:28:03 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	change_loc(t_savage *savage, char *path)
{
	char	*oldclw;
	char	*clw;
	char	*backup;

	oldclw = malloc(1024);
	clw = malloc(1024);
	if (!chdir(path))
	{
		getcwd(clw, 1024);
		backup = get_env(savage, "PWD");
		if (backup)
			get_olddir(savage, backup);
		else
			get_olddir(savage, "");
		free(backup);
		set_path(savage, "PWD=", clw);
	}
	else
		dir_changer_err(savage, path);
	free(oldclw);
	free(clw);
}

int	home_check(t_savage *savage, char *path)
{
	char	*backup;

	free(path);
	path = NULL;
	backup = ft_strdup(savage->first_arg);
	ft_error(" HOME not set", backup);
	return (1);
}

int	too_args(t_savage *savage)
{
	ft_error(" too many arguments", savage->first_arg);
	return (1);
}

int	cd(t_savage *savage)
{
	char	*path;
	char	*loc;

	loc = savage->agrs[1];
	if (!loc || !ft_strncmp(loc, "~", 2))
	{
		path = get_env(savage, "HOME");
		if (!(ft_strcmp(path, "")))
			return (home_check(savage, path));
	}
	else if (!ft_strncmp(loc, ".", 2) || !ft_strncmp(loc, "", 1))
		path = get_env(savage, "PWD");
	else if (!ft_strncmp(loc, "-", 2))
		path = get_env(savage, "OLDPWD");
	else if (savage->agrs[2])
	{
		path = ft_strdup(loc);
		if (savage->agrs[3])
			return (too_args(savage));
	}
	else
		path = ft_strdup(loc);
	change_loc(savage, path);
	return (1);
}

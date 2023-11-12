/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:51:54 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/09 07:35:43 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	to_lower(char *in)
{
	int	i;

	i = 0;
	while (in[i])
	{
		in[i] = ft_tolower(in[i]);
		i++;
	}
}

char	*search_n_pwd(t_savage *savage)
{
	struct stat		dir_stat;
	struct dirent	*dirinfo;
	DIR				*dir_str;

	if (stat(".", &dir_stat) != -1 && dir_stat.st_mode & S_IFDIR)
	{
		dir_str = opendir(".");
		if (!dir_str)
			return (NULL);
		dirinfo = readdir(dir_str);
		while (dirinfo)
		{
			if (!(ft_strcmp(dirinfo->d_name, savage->agrs[0])))
			{
				closedir(dir_str);
				return (generate_absolute_path(".", savage->first_arg));
			}
			dirinfo++;
			dirinfo = readdir(dir_str);
		}
		closedir(dir_str);
	}
	savage->exit_status = 127;
	ft_error(" No such file or directory", savage->first_arg);
	return (NULL);
}

int	binary_path_ex(t_savage *savage, char *path, char *b_name, struct stat *st)
{
	DIR				*dir_str;
	struct dirent	*dir_info;

	if (stat(path, st) != -1 && st->st_mode & S_IFDIR)
	{
		dir_str = opendir(path);
		if (!dir_str)
			return (0);
		dir_info = readdir(dir_str);
		while (dir_info)
		{
			if (!(ft_strcmp(dir_info->d_name, b_name)))
			{
				savage->binary = 1;
				closedir(dir_str);
				free(b_name);
				return (1);
			}
			dir_info++;
			dir_info = readdir(dir_str);
		}
		closedir(dir_str);
	}
	return (0);
}

char	*search_bin(t_savage *savage, char **path)
{
	int			i;
	struct stat	st;
	char		*b_name;

	i = 0;
	b_name = ft_strdup(savage->agrs[0]);
	to_lower(b_name);
	while (path[i])
	{
		if (binary_path_ex(savage, path[i], b_name, &st))
			return (generate_absolute_path(path[i], savage->agrs[0]));
		i++;
	}
	return (NULL);
}

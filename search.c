/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 06:21:14 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/02 06:32:03 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*search_in_pwd(t_savage *savage)
{
	struct stat		dir_stat;
	struct dirent	*dirinfo;
	DIR				*dir_str;

	if (stat(".", &dir_stat) != -1 && dir_stat.st_mode)
	{
		dir_str = opendir(".");
		if (!dir_str)
			return (NULL);
		dirinfo = readdir(dir_str);
		while (dirinfo)
		{
			if (ft_strcmp(dirinfo->d_name, savage->agrs[0]))
			{
				closedir(dir_str);
				return (generate_path(".", savage->first_arg));
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


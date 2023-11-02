/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 06:21:14 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/02 06:24:57 by zbabahmi         ###   ########.fr       */
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
		
	}
}
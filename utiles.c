/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 06:23:53 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/04 13:08:32 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	   free_2d(char **str)
{
	int	idx;

	idx = 0;
	while (str[idx ]){
		free(str[idx]);
		str[idx] = NULL;
		idx++;
	}
	free(str);
	str = NULL;
}

int	ft_strcmp(char *s1, char *s2)
{
	while(*s2)
	{
		if(*s1 != *s2)
			return(0);
		s1++;
		s2++;
	}
	if(*s1 != *s2)
		return(0);
	return(1);
}
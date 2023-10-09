/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 06:23:53 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/10/09 06:29:39 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void free_2d(char **str)
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
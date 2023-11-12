/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 01:56:45 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/12 01:57:23 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	count_bs(char *str, int c)
{
	int	bs;
	int	i;

	i = 0;
	bs = 0;
	while (str[i])
	{
		if ((c == ' ' && str[i] == ' ')
			|| (c == '$' && str[i] == '$'
				&& (!str[i + 1] || str[i + 1] == ' ')))
			bs++;
		i++;
	}
	return (bs);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 06:49:14 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/10 06:51:50 by zbabahmi         ###   ########.fr       */
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

char	*escape_bs(char *str, int c)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(str) + count_bs(str, c) + 1));
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && str[i - 1] != '\\')
		{
			if (!str[i + 1] || str[i + 1] == '\\' || str[i + 1] == ' ')
				res[j++] = '\\';
		}
		else if (c == '\\' && str[i] == c)
			res[j++] = '\\';
		res[j++] = str[i];
		i++;
	}
	res[j++] = '\0';
	return (res);
}

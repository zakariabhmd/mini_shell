/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 23:07:41 by zbabahmi          #+#    #+#             */
/*   Updated: 2022/10/12 03:28:22 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last;
	char	find;
	size_t	zed;

	last = (char *)s;
	find = (char)c;
	zed = ft_strlen(s);
	while (zed > 0)
	{
		if (last[zed] == find)
			return (last + zed);
		zed--;
	}
	if (last[zed] == find)
		return (last);
	return (0);
}

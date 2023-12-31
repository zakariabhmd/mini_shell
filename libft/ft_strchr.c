/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 22:37:02 by zbabahmi          #+#    #+#             */
/*   Updated: 2022/10/22 18:19:07 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*zed;

	zed = (char *)s;
	while (*zed != (char)c)
	{
		if (*zed == '\0')
		{
			return (0);
		}
		zed++;
	}
	return (zed);
}

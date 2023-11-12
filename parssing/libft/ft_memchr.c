/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoukmat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:10:39 by atoukmat          #+#    #+#             */
/*   Updated: 2022/10/26 16:10:47 by atoukmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int				i;
	unsigned char	*sv2;

	i = 0;
	sv2 = (unsigned char *)s;
	while (n > 0)
	{
		if (sv2[i] == (unsigned char)c)
		{
			return (&sv2[i]);
		}
		i++;
		n--;
	}
	return (0);
}

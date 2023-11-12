/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoukmat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:53:20 by atoukmat          #+#    #+#             */
/*   Updated: 2022/10/29 16:53:25 by atoukmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	slen;
	size_t	dlen;
	size_t	i;

	if (dstsize == 0 && dst == 0)
		return (ft_strlen(src));
	slen = ft_strlen(src);
	dlen = ft_strlen(dst);
	i = 0;
	if (dstsize <= dlen || dstsize == 0)
		return (slen + dstsize);
	while (src[i] && i < dstsize - dlen - 1)
	{
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + i] = '\0';
	return (slen + dlen);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoukmat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:17:02 by atoukmat          #+#    #+#             */
/*   Updated: 2022/10/26 16:17:04 by atoukmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	h;
	size_t	n;

	h = 0;
	if (needle[0] == '\0')
	{
		return ((char *)haystack);
	}
	while (haystack[h] != '\0')
	{
		n = 0;
		while (haystack[h + n] == needle[n] && (n + h) < len)
		{
			if (haystack[h + n] == '\0' && needle[n] == '\0')
			{
				return ((char *)&haystack[h]);
			}
			n++;
		}
		if (needle[n] == '\0')
			return ((char *)haystack + h);
		h++;
	}
	return (0);
}

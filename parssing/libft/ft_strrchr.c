/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoukmat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:34:22 by atoukmat          #+#    #+#             */
/*   Updated: 2022/10/26 16:34:32 by atoukmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	char			*p;

	i = 0;
	p = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			p = &((char *)s)[i];
		}
		i++;
	}
	if ((char)c == s[i])
		p = (char *)&s[i];
	return (p);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoukmat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:56:28 by atoukmat          #+#    #+#             */
/*   Updated: 2022/10/29 16:56:38 by atoukmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n)
	{
		if (ft_strlen(s1) == 0)
			return (s1[i] - s2[i]);
		while (s1[i] != '\0' && i < n)
		{
			if (s1[i] != s2[i])
				return ((unsigned char)s1[i] - (unsigned char)s2[i]);
			i++;
		}
		if (i != n)
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

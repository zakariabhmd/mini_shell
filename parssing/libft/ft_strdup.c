/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:07:11 by atoukmat          #+#    #+#             */
/*   Updated: 2023/11/11 23:20:36 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	len;
	char	*p;
	int		i;

	if (!str)
	{
		return (NULL);
	}
	len = ft_strlen(str);
	i = 0;
	p = ft_malloc(len + 1, NULL, ALLOC, NULL);
	if (!p)
		return (NULL);
	while (str[i] != '\0')
	{
		p[i] = str[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:16:42 by atoukmat          #+#    #+#             */
/*   Updated: 2023/11/11 23:15:22 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stddef.h>

size_t	ft_strlcpy(char *destination, const char *source, size_t size)
{
	size_t	i;
	size_t	source_len;

	source_len = 0;
	while (source[source_len] != '\0')
		source_len++;
	i = 0;
	while (i < size - 1 && source[i] != '\0')
	{
		destination[i] = source[i];
		i++;
	}
	while (i < size)
	{
		destination[i] = '\0';
		i++;
	}
	return (source_len);
}

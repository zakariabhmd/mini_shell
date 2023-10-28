/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 02:54:28 by zbabahmi          #+#    #+#             */
/*   Updated: 2022/10/12 03:49:36 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*zed;

	zed = malloc(count * size);
	if (zed)
	{
		ft_bzero(zed, count * size);
		return (zed);
	}
	return (0);
}

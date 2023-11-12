/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:15:47 by atoukmat          #+#    #+#             */
/*   Updated: 2023/11/11 23:18:14 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (s1 && s2)
	{
		str = (char *)ft_malloc((ft_strlen(s1) + ft_strlen(s2) + 1), \
				NULL, ALLOC, NULL);
		if (str == NULL)
			return (NULL);
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
		while (s2[j])
		{
			str[i] = s2[j++];
			i++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}

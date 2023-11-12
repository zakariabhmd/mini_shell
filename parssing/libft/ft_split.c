/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 22:40:50 by atoukmat          #+#    #+#             */
/*   Updated: 2023/11/11 23:24:35 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	words_counter(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	start;
	size_t	end;
	size_t	i;

	split = ft_malloc((words_counter(s, c) + 1) * (sizeof(char *)), \
			NULL, ALLOC, NULL);
	if (!split)
		return (NULL);
	start = 0;
	end = 0;
	i = 0;
	while (i < words_counter(s, c))
	{
		while (s[start] == c)
			start++;
		end = start;
		while (s[end] != c && s[end])
			end++;
		split[i] = ft_substr(s, start, (end - start));
		start = end;
		i++;
	}
	split[i] = 0;
	return (split);
}

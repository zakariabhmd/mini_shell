/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:11:18 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/04 17:15:51 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	counter_w(const char *tpm, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (*tpm)
	{
		if (*tpm != c && count == 0)
		{
			count = 1;
			i++;
		}
		else if (*tpm == c)
			count = 0;
		tpm++;
	}
	return (i);
}

int	size_word(char const *s, char c, int i)
{
	int	size;

	size = 0;
	while (s[i] != c && s[i])
	{
		size++;
		i++;
	}
	return (size);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		word;
	int		size;
	char	**sp;
	int		j;

	i = 0;
	j = -1;
	word = counter_w(s, c);
	sp = (char **)malloc((word + 1) * sizeof(char *));
	if (!sp)
		return (0);
	while (++j < word)
	{
		while (s[i] == c)
			i++;
		size = size_word(s, c, i);
		sp[j] = ft_substr(s, i, size);
		i += size;
	}
	sp[j] = 0;
	return (sp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 02:11:08 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/12 05:51:40 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	whitespaces(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	separ(char input, int c)
{
	if (c == ' ' && whitespaces(input))
		return (1);
	else if (input == c)
		return (1);
	return (0);
}

int	counter(char *input, int c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (input[i])
	{
		if (separ(input[i], c) && input[i - 1] != '\\')
		{
			word++;
			while (input[i] && !separ(input[i], c))
				i++;
		}
		i++;
	}
	return (word);
}

int	check_backslash(char *input, int i)
{
	int	bs;

	bs = 0;
	i--;
	while (i >= 0 && input[i] == '\\')
	{
		i--;
		bs++;
	}
	if (bs > 1 && input[i] == ' ')
		bs = 1;
	return ((bs + 1) % 2);
}

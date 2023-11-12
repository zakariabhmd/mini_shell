/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_help1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 21:06:00 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/12 07:26:56 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	count_length_two_arr(char **str)
{
	int	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

char	**join_tables(char **table1, char **table2)
{
	int		count;
	int		index;
	int		size;
	char	**dst;

	count = 0;
	index = 0;
	size = count_length_two_arr(table1) + count_length_two_arr(table2);
	dst = ft_malloc((sizeof(char *) * (size + 1)), NULL, ALLOC, NULL);
	while (table1[count])
		dst[index++] = table1[count++];
	count = 0;
	while (table2[count])
		dst[index++] = table2[count++];
	dst[index] = NULL;
	return (dst);
}

int	is_redirect(char *red)
{
	if (!(ft_strcmp(red, ">")) || !(ft_strcmp(red, ">>")) \
		|| !(ft_strcmp(red, "<")) || !(ft_strcmp(red, "<<")))
		return (1);
	return (0);
}

int	count_redirection_and_files(char **args)
{
	int	count;
	int	count_returend;

	count = 0;
	count_returend = 0;
	while (args[count])
	{
		if (is_redirect(args[count]))
		{
			if (args[count + 1])
				count_returend++;
			count_returend++;
		}
		count++;
	}
	if (count_returend == 0)
		return (1);
	return (count_returend);
}

int	count_argment_without_red(char **args)
{
	int	count;
	int	reterned_count;

	count = 0;
	reterned_count = 0;
	while (args[count])
	{
		if (count == 0 && !is_redirect(args[count]))
			reterned_count++;
		else
			if (count - 1 >= 0 && !is_redirect(args[count - 1]) \
				&& !is_redirect(args[count]))
				reterned_count++;
		count++;
	}
	return (reterned_count);
}

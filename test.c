/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoukmat <atoukmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:33:33 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/15 07:58:00 by atoukmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*rm_delimiter(char *input, int c)
{
	char	*tmp;
	int		i;

	tmp = ft_strdup(input);
	i = 0;
	while (tmp[i])
	{
		if (separ(tmp[i], c) && check_backslash(tmp, i))
			tmp[i] = '\0';
		i++;
	}
	return (tmp);
}

void	skip_spaces(char *str, int *i)
{
	while (str[*i] && str[*i] == ' ')
		(*i)++;
}

void	lex_help(char **res, int j, int i)
{
	free(res[j]);
	res[j] = ft_strdup("");
	i += 2;
}

void	lex_help1(char *input, char **res, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < len)
	{
		skip_spaces(input, &i);
		res[j] = ft_strdup(&input[i]);
		if (!ft_strncmp(res[j], "\"\"", 2))
		{
			lex_help(res, j, i);
		}
		else
			i += ft_strlen(res[j++]);
		while (i < len && !input[i])
			i++;
	}
	res[j] = NULL;
}

char	**lexical_analysis(char *input, int c)
{
	char	**res;
	int		len;
	int		i;
	int		j;

	if (!input)
		return (NULL);
	len = ft_strlen(input);
	input = rm_delimiter(input, c);
	res = ft_malloc((sizeof(char *) * (len + 1)), NULL, ALLOC, NULL);
	if (!res)
		return (NULL);
	lex_help1(input, res, len);
	return (res);
}

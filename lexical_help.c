/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 06:44:01 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/10 06:45:05 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	skip_spaces(char *str, int *i)
{
	while (str[*i] && str[*i] == ' ')
		(*i)++;
}

int	whitespaces(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

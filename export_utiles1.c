/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utiles1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 04:49:20 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/12 04:50:46 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	ft_strncmp_res(char *s1, char *s2, int len)
{
	while (*s1 && *s2 && len)
	{
		if (*s1 != *s2)
			return (1);
		s1++;
		s2++;
		len--;
	}
	if (*s1 == *s2)
		return (0);
	return (1);
}

int	invalid_char(char *var, int i)
{
	if (var[i] == '$' || var[i] == '&' || \
		var[i] == '@' || var[i] == '!' || \
		var[i] == ';' || var[i] == ' ' || \
		var[i] == '\"' || var[i] == '\\' || \
		var[i] == '-' || \
		(var[i] == '\\' && var[i + 1] != '_' && !ft_isdigit(var[i + 1])))
		return (1);
	return (0);
}

int	check_valid_name(char *var)
{
	int	i;

	i = 0;
	if (!*var || ft_isdigit(*var) || *var == '=')
		return (0);
	while (var[i] && var[i] != '=')
	{
		if (invalid_char(var, i))
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

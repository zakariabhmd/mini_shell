/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:49:20 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/07 21:16:12 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	echo_printer(char **arg)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while (arg[i])
	{
		if (!ft_strncmp(arg[i], "-n", 2))
		{
			sign = 0;
			i++;
		}
		else
			break ;
	}
	while (arg[i])
	{
		ft_putstr_fd(arg[i], 1);
		if (arg[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (sign)
		ft_putchar_fd('\n', 1);
	return (1);
}

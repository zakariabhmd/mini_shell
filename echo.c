/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:49:20 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/15 18:50:35 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	check_multiple_new_line(char *arg)
{
	int	idx;

	idx = 0;
	if (arg[idx] == '-')
		idx++;
	while (arg[idx])
	{
		if (arg[idx] != 'n')
			return (0);
		idx++;
	}
	if (idx == 1)
		return (0);
	return (1);
}

int	echo_printer(char **arg, t_savage *savage)
{
	int	sign;
	int	i;

	i = 0;
	sign = 0;
	while (arg[i])
	{
		if (!ft_strncmp(arg[i], "-n", 2))
		{
			sign = check_multiple_new_line(arg[i++]);
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
	if (sign == 0)
		ft_putchar_fd('\n', 1);
	savage->exit_status = 0;
	return (1);
}

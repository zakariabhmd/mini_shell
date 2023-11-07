/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:02:47 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/07 21:16:55 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	write_err_msg(t_savage *savage)
{
	char	*backup;

	backup = ft_strdup("exit: ");
	backup = ft_strjoin(backup, savage->agrs[1]);
	ft_error(" numeric argument required", backup);
	free(backup);
	exit(255);
}

int	toomany(char *arg)
{
	if (arg)
	{
		ft_error("exit: too many arguments", NULL);
		return (1);
	}
	else
		return (0);
}

void	all_exit(int handler, t_savage *savage)
{
	sh_cleaner(savage);
	exit(handler);
}

void	to_exit(t_savage *savage)
{
	int		handler;
	char	*box;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	if (savage->agrs[1])
	{
		box = savage->agrs[1];
		while (box[i])
		{
			if (box[i] == '-')
				i++;
			if (!ft_isdigit(box[i]))
				write_err_msg(savage);
			i++;
		}
		handler = ft_atoi(box);
		if (toomany(savage->agrs[2]))
			handler = 1;
	}
	else
		handler = savage->exit_status;
	all_exit(handler, savage);
}

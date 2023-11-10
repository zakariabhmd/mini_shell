/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 06:54:56 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/10 06:55:35 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	exev_args(t_savage *savage)
{
	char	*path;

	if (!bulttin_check(savage))
	{
		path = get_path(savage);
		if (path == NULL)
		{
			printf("minishell: %s: command not found\n", savage->agrs[0]);
			exit(127);
		}
		if (execve(path, savage->agrs, savage->env) == -1)
		{
			perror("minishell: execve");
			exit(126);
		}
	}
}

int	count_pipe(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i - 1);
}

void	waitsignal(int sig)
{
	(void)sig;
	signal(SIGINT, waitsignal);
}

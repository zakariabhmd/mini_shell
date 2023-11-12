/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 07:01:58 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/12 07:02:12 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_help1(t_savage *savage, int fd, char *input, int i)
{
	while (1)
	{
		free(input);
		signal(SIGINT, waitsignal);
		input = readline("heredoc-> ");
		if (!input)
			break ;
		if (!(ft_strcmp(input, savage->agrs[i + 1])))
		{
			free(input);
			break ;
		}
		ft_putendl_fd(input, fd);
	}
}

int	herdoc(t_savage *savage, int i)
{
	int		fd;
	char	*input;

	fd = -1;
	input = ft_calloc(1, 1);
	savage->exit_status = 1;
	unlink("/tmp/test");
	fd = open("/tmp/test", O_CREAT | O_WRONLY, 0777);
	ft_help1(savage, fd, input, i);
	close (fd);
	savage->exit_status = 0;
	fd = open("/tmp/test", O_RDONLY, 0777);
	return (fd);
}

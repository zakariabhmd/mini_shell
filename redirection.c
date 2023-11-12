/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:50:54 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/12 04:26:03 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	red_output(t_savage *savage, int i)
{
	int	fd;

	fd = -1;
	if (savage->agrs[i + 1])
	{
		fd = open(savage->agrs[i + 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fd == -1)
		{
			savage->exit_status = 1;
			ft_error(" No such file or directory", savage->agrs[i + 1]);
		}
		else
		{
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
	}
	else
	{
		savage->exit_status = 2;
		ft_error("syntax error near unexpected token `newline'", NULL);
	}
	return (fd);
}

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

void	check_help(t_savage *savage, int i, int fd)
{
	while (savage->agrs[i])
	{
		if (valide_redirection(savage, savage->agrs[i]))
		{
			if (!(ft_strcmp(savage->agrs[i], "<<")) && savage->agrs[i + 1])
			{
				if (fd != -1)
				{
					fd = herdoc(savage, i);
					if (fd != -1)
					{
						dup2(fd, 0);
					}
				}
			}
			else if (!(ft_strcmp(savage->agrs[i], "<")))
				fd = red_input(savage, i);
			else if (!(ft_strcmp(savage->agrs[i], ">")))
				fd = red_output(savage, i);
			else if (!(ft_strcmp(savage->agrs[i], ">>")))
				fd = red_append(savage, i);
		}
		else
		{
			fd = -1;
			break ;
		}
		i++;
	}

}

int	check_redirections(t_savage *savage)
{
	int		fd;
	int		i;
	int		count;
	char	**dst;

	savage->agrs = sort_args(savage->agrs);
	i = 0;
	check_help(savage, i, fd);
	count = 0;
	while (savage->agrs[count])
	{
		if (is_redirect(savage->agrs[count]))
			break ;
		count++;
	}
	dst = malloc(sizeof(char *) * (count + 1));
	count = 0;
	while (savage->agrs[count])
	{
		if (is_redirect(savage->agrs[count]))
			break ;
		dst[count] = savage->agrs[count];
		count++;
	}
	dst[count] = 0;
	savage->agrs = dst;
	return (fd);
}

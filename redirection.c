/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:50:54 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/12 07:09:22 by zbabahmi         ###   ########.fr       */
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

void	check_test(t_savage *savage, int i, int fd)
{
	if (!(ft_strcmp(savage->agrs[i], "<")))
		fd = red_input(savage, i);
	else if (!(ft_strcmp(savage->agrs[i], ">")))
		fd = red_output(savage, i);
	else if (!(ft_strcmp(savage->agrs[i], ">>")))
		fd = red_append(savage, i);
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
			check_test(savage, i, fd);
		}
		else
		{
			fd = -1;
			break ;
		}
		i++;
	}
}

void	check_help1(t_savage *savage, char **dst, int count)
{
	while (savage->agrs[count])
	{
		if (is_redirect(savage->agrs[count]))
			break ;
		dst[count] = savage->agrs[count];
		count++;
	}
	dst[count] = 0;
	savage->agrs = dst;
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
	dst = ft_malloc((sizeof(char *) * (count + 1)), NULL, ALLOC, NULL);
	count = 0;
	check_help1(savage, dst, count);
	return (fd);
}

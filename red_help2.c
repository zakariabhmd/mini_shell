/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_help2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 21:08:23 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/12 04:11:11 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	red_append(t_savage *savage, int i)
{
	int	fd;

	fd = -1;
	if (!savage->agrs[i + 1])
	{
		savage->exit_status = 2;
		ft_error("syntax error near unexpected token `newline'", NULL);
	}
	else
	{
		fd = open(savage->agrs[i + 1], O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (fd == -1)
		{
			savage->exit_status = 1;
			ft_error(" No such file or directory", savage->agrs[i + 1]);
		}
		else
			dup2(fd, 1);
	}
	return (fd);
}

int	init_data_structer_sort_args(t_data *data, char **oldargs)
{
	data->index = 0;
	data->count = 0;
	data->dst = malloc(sizeof(char *) * \
		(count_redirection_and_files(oldargs) + 1));
	if (!data->dst)
		return (1);
	data->dst_two = malloc(sizeof(char *) * \
		(count_argment_without_red(oldargs) + 1));
	return (0);
}

void	split_redirection_and_files(t_data *data, char **oldargs)
{
	while (oldargs[data->count])
	{
		if (is_redirect(oldargs[data->count]))
		{
			data->dst[data->index] = oldargs[data->count];
			data->index++;
			data->count++;
			if (!oldargs[data->count])
				break ;
			if (oldargs[data->count])
			{
				data->dst[data->index] = oldargs[data->count];
				data->index++;
			}
		}
		if (!*oldargs[data->count])
			break ;
		data->count++;
	}
	data->dst[data->index] = NULL;
}

void	split_args_are_not_redirections(t_data *data, char **oldargs)
{
	while (oldargs[data->count])
	{
		if (data->count == 0 && !is_redirect(oldargs[data->count]))
		{
			data->dst_two[data->index] = ft_strdup(oldargs[data->count]);
			data->index++;
		}
		else
		{
			if (data->count - 1 >= 0 && !is_redirect(oldargs[data->count - 1]) \
				&& !is_redirect(oldargs[data->count]))
			{
				data->dst_two[data->index] = ft_strdup(oldargs[data->count]);
				data->index++;
			}
		}
		data->count++;
	}
	data->dst_two[data->index] = NULL;
}

char	**sort_args(char **oldargs)
{
	t_data		data;
	char		**new_args;

	if (init_data_structer_sort_args(&data, oldargs))
		return (NULL);
	split_redirection_and_files(&data, oldargs);
	data.index = 0;
	data.count = 0;
	split_args_are_not_redirections(&data, oldargs);
	new_args = join_tables(data.dst_two, data.dst);
	return (new_args);
}

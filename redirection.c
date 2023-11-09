/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:50:54 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/09 08:03:50 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int count_length_two_arr(char **str) {
	int count = 0;
	while (str[count])
		count++;
	return count;
}

char	**join_tables(char **table1, char **table2)
{
	int		count;
	int		index;
	int		size;
	char	**dst;

	count = 0;
	index = 0;
	size = count_length_two_arr(table1) + count_length_two_arr(table2);
	dst = malloc(sizeof(char *) * (size + 1));
	while (table1[count])
		dst[index++] = table1[count++];
	count = 0;
	while (table2[count])
		dst[index++] = table2[count++];
	dst[index] = NULL;
	return (dst);
}

typedef struct t_data
{
	char	**dst;
	int		index;
	int		count;
	char	**dst_two;
}	t_data;

int	is_redirect(char *red)
{
	if (!(ft_strcmp(red, ">")) || !(ft_strcmp(red, ">>")) \
		|| !(ft_strcmp(red, "<")) || !(ft_strcmp(red, "<<")))
		return (1);
	return (0);
}

int	count_redirection_and_files(char **args)
{
	int	count;
	int	count_returend;

	count = 0;
	count_returend = 0;
	while (args[count])
	{
		if (is_redirect(args[count]))
		{
			if (args[count + 1])
				count_returend++;
			count_returend++;
		}
		count++;
	}
	if (count_returend == 0)
		return (1);
	return (count_returend);
}

int	count_argment_without_red(char **args)
{
	int	count;
	int	reterned_count;

	count = 0;
	reterned_count = 0;
	while (args[count])
	{
		if (count == 0 && !is_redirect(args[count]))
			reterned_count++;
		else
			if (count - 1 >= 0 && !is_redirect(args[count - 1]) \
				&& !is_redirect(args[count]))
				reterned_count++;
		count++;
	}
	return (reterned_count);
}


int	init_data_structer_sort_args(t_data *data, char **oldargs)
{
	data->index = 0;
	data->count = 0;
	data->dst = malloc(sizeof(char *) * (count_redirection_and_files(oldargs) + 1));
	if (!data->dst)
		return (1);
	data->dst_two = malloc(sizeof(char *) * (count_argment_without_red(oldargs) + 1));
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

// ------------------------------------------

int	red_error(t_savage *savage, int input, int output)
{
	char	*msg;

	msg = NULL;
	if (input > 2)
	{
		if (input < 4)
			msg = ft_strjoin("syntax error near unexpected token `", "<'");
		else
			msg = ft_strjoin("syntax error near unexpected token `", "<<'");
		ft_error(msg, NULL);
		free(msg);
		savage->exit_status = 2;
		return (1);
	}
	if (output > 2)
	{
		if (output < 4)
			msg = ft_strjoin("syntax error near unexpected token `", ">'");
		else
			msg = ft_strjoin("syntax error near unexpected token `", ">>'");
		ft_error(msg, NULL);
		free(msg);
		savage->exit_status = 2;
		return (1);
	}
	return (0);
}

int	valide_redirection(t_savage *savage, char *str)
{
	int	input;
	int	output;
	int	i;

	input = 0;
	output = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '<')
			input++;
		else if (str[i] == '>')
			output++;
		else if (str[i] != ' ')
		{
			input = 0;
			output = 0;
		}
		i++;
	}
	if (red_error(savage, input, output))
		return (0);
	return (1);
}

int	red_exists(t_savage *savage, int i)
{
	struct stat	st;
	int			fd;

	fd = -1;
	if ((fd = open (savage->agrs[i + 1], O_RDONLY, 0644)) == -1)
	{
		if (stat(savage->agrs[i + 1], &st) != -1)
		{
			if (!(st.st_mode & S_IRUSR) ||
				(st.st_mode & S_IRUSR && (!(st.st_mode & S_IXUSR))))
			{
				savage->exit_status = 1;
				ft_error(" Permission denied", savage->agrs[i + 1]);
			}
		}
		else
		{
			savage->exit_status = 1;
			ft_error(" No such file or directory", savage->agrs[i + 1]);
		}
	}
	return (fd);
}
int	red_input(t_savage *savage, int i)
{
	int	fd;

	fd = -1;
	if (savage->agrs[i + 1])
	{
		fd = red_exists(savage, i);
		if (fd != -1)
			dup2(fd, 0);
	}
	else
	{
		savage->exit_status = 2;
		ft_error("syntax error near unexpected token `newline'", NULL);
	}
	if (i == 0 && savage->agrs[0])
	{
		free(savage->first_arg);
		savage->first_arg = ft_strdup(savage->agrs[0]);
	}
	return (fd);
}

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
		if ((fd = open(savage->agrs[i + 1], O_CREAT | O_APPEND | O_WRONLY, 0644)) == -1)
		{
			savage->exit_status = 1;
			ft_error(" No such file or directory", savage->agrs[i + 1]);
		}
		else
			dup2(fd, 1);
	}
	return (fd);
}

// int old_fd = 1;

int	red_output(t_savage *savage, int i)
{
	int	fd;

	fd = -1;
	if (savage->agrs[i + 1])
	{
		if ((fd = open(savage->agrs[i + 1], O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
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

int	herdoc(t_savage *savage, int i)
{
	int		fd;
	char	*input;

	fd = -1;
	savage->exit_status = 1;
	unlink("/tmp/test");
	fd = open("/tmp/test", O_CREAT | O_WRONLY, 0777);
	while (1)
	{
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
	close (fd);
	savage->exit_status = 0;
	fd = open("/tmp/test", O_RDONLY, 0777);
	return (fd);
}

int	check_redirections(t_savage *savage)
{
	int	fd;
	int	i;
	int	count;

	savage->agrs = sort_args(savage->agrs);
	i = 0;
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
	count = 0;
	while (savage->agrs[count])
	{
		if (is_redirect(savage->agrs[count]))
			break ;
		count++;
	}
	char **dst = malloc(sizeof(char *) * (count + 1));
	count = 0;
	while (savage->agrs[count])
	{
		if (is_redirect(savage->agrs[count]))
			break;
		dst[count] = savage->agrs[count];
		count++;
	}
	dst[count] = 0;
	savage->agrs = dst;
	return (fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:50:54 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/07 21:24:16 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	is_redirect(char *red)
{
	if (ft_strcmp(red, ">") || ft_strcmp(red, ">>") \
		|| ft_strcmp(red, "<") || ft_strcmp(red, "<<"))
		return (1);
	return (0);
}

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
			dup2(fd, 1);
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
		input = readline("heredoc-> ");
		if (!input)
			break ;
		if (ft_strcmp(input, savage->agrs[i + 1]))
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

	i = 0;
	while (savage->agrs[i])
	{
		if (valide_redirection(savage, savage->agrs[i]))
		{
			if (ft_strcmp(savage->agrs[i], "<<") && savage->agrs[i + 1])
			{
				if (fd != -1)
				{
					fd = herdoc(savage, i);
					if (fd != -1)
						dup2(fd, 0);
				}
			}
			else if (ft_strcmp(savage->agrs[i], "<"))
				fd = red_input(savage, i);
			else if (ft_strcmp(savage->agrs[i], ">"))
				fd = red_output(savage, i);
			else if (ft_strcmp(savage->agrs[i], ">>"))
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

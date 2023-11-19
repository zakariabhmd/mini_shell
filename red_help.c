/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoukmat <atoukmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 21:09:40 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/15 07:58:00 by atoukmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	ft_help(t_savage *savage, int output, char *msg)
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
		ft_help(savage, output, msg);
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

	fd = open (savage->agrs[i + 1], O_RDONLY, 0644);
	if (fd == -1)
	{
		if (stat(savage->agrs[i + 1], &st) != -1)
		{
			if (!(st.st_mode & S_IRUSR) || \
				(st.st_mode & S_IRUSR && (!(st.st_mode & S_IXUSR))))
			{
				savage->exit_status = 1;
				ft_error(" Permission denied", savage->agrs[i + 1]);
			}
		}
		else
		{
			savage->exit_status = 1;
			ft_error("syntax error near unexpected token `newline'", \
					savage->agrs[i + 1]);
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

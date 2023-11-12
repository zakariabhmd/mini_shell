/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:19:10 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/12 04:50:07 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	invalid_export(t_savage *savage, char *var, char *cmd)
{
	char	*print_err;
	char	*backup;
	int		size;

	size = ft_strlen(var);
	print_err = malloc((sizeof(char) * (size + 28)));
	if (!print_err)
		return (0);
	backup = NULL;
	backup = ft_strjoin(" `", var);
	if (!backup)
		return (free(print_err), 0);
	ft_strcpy(print_err, backup);
	free(backup);
	backup = ft_strjoin(print_err, "': not a valid identifier");
	if (!backup)
		return (free(print_err), 0);
	ft_strcpy(print_err, backup);
	free(backup);
	savage->exit_status = 1;
	ft_error(print_err, cmd);
	free(print_err);
	return (1);
}

int	esc_char(char c)
{
	if (c == '$' || c == '\\' || c == '\"')
		return (1);
	return (0);
}

int	count_s_char(char *s)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	while (s[i])
	{
		if (esc_char(s[i]))
			counter++;
		i++;
	}
	return (counter);
}

char	*write_q_and_bslash(char *s)
{
	char	*box;
	int		i;
	int		j;
	int		size;

	i = 0;
	j = 0;
	size = ft_strlen(s);
	box = malloc((sizeof(char) * (size + count_s_char(s)) * 13));
	if (!box)
		return (NULL);
	while (s[i])
	{
		if (esc_char(s[i]))
			box[j] = '\\';
		box[j] = s[i];
		if (s[i] == '=')
			box[++j] = '\"';
		i++;
		j++;
	}
	if (ft_strchr(s, '='))
		box[j++] = '\"';
	box[j] = '\0';
	return (box);
}

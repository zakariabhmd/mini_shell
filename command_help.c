/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoukmat <atoukmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 01:49:49 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/15 07:58:00 by atoukmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*update_lastarg(char **arg)
{
	char	*res;
	char	*tmp;
	int		i;

	i = 0;
	while (arg[i])
		i++;
	tmp = ft_strchr(arg[i - 1], '=');
	if (tmp)
		*tmp = '\0';
	res = ft_strjoin("_=", arg[i - 1]);
	return (res);
}

char	**set_args(char *str)
{
	char	**args;
	char	*bs;
	int		i;

	if (!str)
		return (NULL);
	args = lexical_analysis(str, ' ');
	i = 0;
	while (args[i])
	{
		bs = bs_parse(args[i], 2);
		free(args[i]);
		args[i] = ft_strdup(bs);
		free(bs);
		i++;
	}
	if (!args)
		return (NULL);
	return (args);
}

char	*append_pwd(char *value)
{
	char	pwd[1024];
	char	*hold;
	int		size;
	int		i;

	size = ft_strlen(value);
	hold = value;
	i = 0;
	if (getcwd(pwd, 1024))
	{
		if (value[0] == ':')
			return (ft_strjoin(pwd, value));
		if (value[size - 1] == ':')
			return (ft_strjoin(value, pwd));
		while (hold[i])
		{
			hold = ft_strchr(hold, ':');
			if (!hold)
				break ;
			if (hold[i + 1] == ':')
				return (ft_strjoin(value, pwd));
			i++;
		}
	}
	return (ft_strdup(value));
}

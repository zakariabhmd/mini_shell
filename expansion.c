/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:25:52 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/12 05:58:57 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*escape_bs(char *str, int c)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = ft_malloc((sizeof(char) * (ft_strlen(str) + count_bs(str, c) + 1)), \
					NULL, ALLOC, NULL);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && str[i - 1] != '\\')
		{
			if (!str[i + 1] || str[i + 1] == '\\' || str[i + 1] == ' ')
				res[j++] = '\\';
		}
		else if (c == '\\' && str[i] == c)
			res[j++] = '\\';
		res[j++] = str[i];
		i++;
	}
	res[j++] = '\0';
	return (res);
}

char	*get_env_value(t_savage *savage, int i)
{
	char	*value;
	char	*tmp;

	if (savage->env[i])
		value = ft_strdup(ft_strchr(savage->env[i], '=') + 1);
	else
		value = ft_strdup("");
	tmp = ft_strdup(value);
	value = escape_bs(tmp, '\\');
	return (value);
}

char	*var_expand(char *var, t_savage *savage)
{
	int		len;
	int		i;
	char	*res;

	len = ft_strlen(var);
	i = 0;
	while (savage->env[i])
	{
		if (!ft_strncmp(savage->env[i], var, len) && savage->env[i][len] == '=')
			break ;
		else
			i++;
	}
	res = get_env_value(savage, i);
	return (res);
}

char	*expd(char *str, t_savage *savage)
{
	char	*tmp;

	if (str[1] == '?')
	{
		free(str);
		str = ft_itoa(savage->exit_prev);
	}
	else if (str[0] == '$')
	{
		str++;
		tmp = ft_strdup(str);
		str = var_expand(tmp, savage);
		free(tmp);
	}
	return (str);
}

char	*expansion(t_savage *savage, char *commands)
{
	char	**lex_env;
	int		i;
	char	*res;
	char	*hold;

	hold = ft_strdup("");
	commands = escape_bs(commands, '$');
	lex_env = ft_split(commands, ' ');
	i = 0;
	while (lex_env[i])
	{
		commands = expd(lex_env[i], savage);
		res = ft_strjoin(commands, " ");
		hold = ft_strjoin(hold, res);
		free(res);
		i++;
	}
	return (hold);
}

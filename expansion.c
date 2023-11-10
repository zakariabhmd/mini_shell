/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:25:52 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/10 06:50:37 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*get_env_value(t_savage *savage, int i)
{
	char	*value;
	char	*tmp;

	if (savage->env[i])
		value = ft_strdup(ft_strchr(savage->env[i], '=') + 1);
	else
		value = ft_strdup("");
	tmp = ft_strdup(value);
	free(value);
	value = escape_bs(tmp, '\\');
	free(tmp);
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

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	else
	{
		while (s1[i])
			str[j++] = s1[i++];
	}
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	free(s1);
	return (str);
}

char	*expansion(t_savage *savage, char *commands)
{
	char	**lex_env;
	int		i;
	char	*res;
	char	*hold;

	i = 0;
	hold = ft_strdup("");
	free(commands);
	commands = escape_bs(commands, '$');
	lex_env = ft_split(commands, ' ');
	while (lex_env[i])
	{
		commands = expd(lex_env[i], savage);
		res = ft_strjoin(commands, " ");
		hold = ft_strjoin_free(hold, res);
		free(res);
		i++;
	}
	free_env(lex_env);
	return (hold);
}

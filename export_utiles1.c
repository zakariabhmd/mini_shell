/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utiles1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoukmat <atoukmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 04:49:20 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/15 07:58:00 by atoukmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	ft_strncmp_res(char *s1, char *s2, int len)
{
	while (*s1 && *s2 && len)
	{
		if (*s1 != *s2)
			return (1);
		s1++;
		s2++;
		len--;
	}
	if (*s1 == *s2)
		return (0);
	return (1);
}

int	invalid_char(char *var, int i)
{
	if (var[i] == '$' || var[i] == '&' || var[i] == '@' || var[i] == '!'
		|| var[i] == ';' || var[i] == ' ' || var[i] == '\"' || var[i] == '\\'
		|| var[i] == '-' || (var[i] == '\\' && var[i + 1] != '_'
			&& !ft_isdigit(var[i + 1])))
		return (1);
	return (0);
}

int	check_valid_name(char *var)
{
	int	i;

	i = 0;
	if (!*var || ft_isdigit(*var) || *var == '=')
		return (0);
	while (var[i] && var[i] != '=')
	{
		if (invalid_char(var, i))
			return (0);
		i++;
	}
	return (1);
}

char	**check_env(char **env)
{
	char	**backup_env;
	char	*backup;
	char	*backup1;
	int		i;

	i = 0;
	backup_env = strdup_env(env);
	while (backup_env[i])
	{
		backup = ft_strjoin("declare -x ", backup_env[i]);
		backup1 = write_q_and_bslash(backup);
		free(backup_env[i]);
		free(backup);
		backup_env[i] = backup1;
		i++;
	}
	free(backup1);
	return (backup_env);
}

int	environment_0(t_savage *savage, char **var)
{
	int		i;
	char	**env_writer;

	if (savage->agrs[1])
	{
		ft_putendl_fd("env: too many arguments", 1);
		return (1);
	}
	i = 0;
	env_writer = var;
	path_search(env_writer);
	while (env_writer[i])
	{
		printf("%s\n", env_writer[i]);
		i++;
	}
	export(savage, "_=env");
	return (1);
}

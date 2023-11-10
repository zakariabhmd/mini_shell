/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:02:56 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/10 06:58:50 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

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

int	write_env(t_savage *savage)
{
	char	**backup_env;
	char	**backup_env1;

	backup_env = strdup_env(savage->env);
	backup_env1 = check_env(backup_env);
	environment(savage, backup_env1);
	return (1);
}

void	do_export(t_savage *savage, char *var, int j)
{
	int		i;
	int		var_len;
	char	*var_value;
	char	*backup;
	char	**backup_env;

	i = 0;
	if (var)
		var_value = ft_strdup(var);
	else
		var_value = ft_strdup(savage->agrs[j]);
	backup = ft_strchr(var_value, '=');
	if (!backup)
		var_len = ft_strlen(var_value);
	else
		var_len = ft_strlen(var_value) - ft_strlen(backup);
	while (savage->env[i] && ft_strncmp_res(savage->env[i], var_value, var_len))
		i++;
	backup = ft_strdup(var_value);
	free(var_value);
	var_value = bs_parse(backup, 3);
	free(backup);
	backup_env = renew_env(&var_value, savage->env, i);
	free_env(savage->env);
	free(var_value);
	savage->env = backup_env;
}

int	alpha(char *str)
{
	while (*str)
	{
		if (ft_isalpha(*str))
			return (1);
		str++;
	}
	return (0);
}

int	export(t_savage *savage, char *var)
{
	char	*backup;
	int		i;

	i = 1;
	if (var && check_valid_name(var))
		do_export(savage, var, 0);
	else if (var)
		invalid_export(savage, var, "export");
	else if (!savage->agrs[i])
		return (write_env(savage));
	else
	{
		while (savage->agrs[i])
		{
			if (!check_valid_name(savage->agrs[i]))
				invalid_export(savage, savage->agrs[i], "export");
			else if ((backup = ft_strchr(savage->agrs[i], '=')) && \
				backup != savage->agrs[i])
				do_export(savage, var, i);
			else if (alpha(savage->agrs[i]) && \
				!(ft_strchr(savage->agrs[i], '=')))
			{
				do_export(savage, savage->agrs[i], i);
			}
			i++;
		}
	}
	return (1);
}

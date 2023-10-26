/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:02:56 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/10/26 06:09:52 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

// int	ft_expt(t_savage *savage)
// {
// 	int	test;

// 	test = 0;
// 	cleane_env("_", savage->env);
// 	test = export(savage, NULL);
// 	return (test);
// }
char	**check_env(char **env)
{
	char	**backup_env;
	char	*backup1;
	char	*backup2;
	int		i;

	i = 0;
	backup_env = strdup_env(env);
	while(backup_env[i])
	{
		backup1 = ft_strjoin("declare -x ", backup_env[i]);
		backup2 = write_q_back(backup1);
		free(backup_env[i]);
		free(backup1);
		backup_env[i] = backup2;
		i++;
	}
	free(backup2);
	return (backup_env);
}


void	help_export(t_savage *savage, char *arg, int i)
{
	int	j;
	int	arg_len;
	char *arg_value;
	char *backup;
	char **backup_env;

	j = 0;
	if(arg)
		arg_value = ft_strdup(arg);
	else
		arg_value = ft_strdup(savage->agrs[i]);
	backup = ft_strchr(arg_value, '=');
	if (!backup)
		arg_len = ft_strlen(arg_value);
	else
		arg_len = ft_strlen(arg_value) - ft_strlen(backup);
	while (savage->env[j] && ft_strncmp_res(savage->env[j], arg_value, arg_len))
		j++;
	backup = ft_strdup(arg_value);
	// free(arg_value);
	// arg_value =
	// free (backup);
	// backup_env =
	// free (arg_value);
	// savage->env = backup_env;
}

int	write_env(t_savage *savage)
{
	char	**backup_env1;
	char	**backup_env2;

	backup_env1 = strdup_env(savage->env);
	backup_env2 = check_env(backup_env1);
	// envirment(savage, backup_env1);
	return (1);
}

int	ft_help(char *str)
{
	while (*str)
	{
		if (ft_isalpha(*str))
			return (1);
		str++;
	}
	return (0);
}

int	export(t_savage *savage, char *arg)
{
	char *backup;
	int	i;

	i = 1;
	if (arg && check_name(arg))
		help_export(savage, arg, 0);
	else if (arg)
		invalide_export(savage, arg, "export");
		else if(!savage->agrs[i])
			return(write_env(savage));
		else
		{
				while(savage->agrs[i])
				{
					if(!check_name(savage->agrs[i]))
						invalide_export(savage, savage->agrs[i], "export");
					else if((backup = ft_strchr(savage->agrs[i], '=')) && backup != savage->agrs[i])
						help_export(savage, arg, i);
					else if(ft_help(savage->agrs[i]) && !(ft_strchr(savage->agrs[i], '=')))
					{
						help_export(savage, savage->agrs[i], i);
					}
					i++;
				}
		}
		return(1);
}


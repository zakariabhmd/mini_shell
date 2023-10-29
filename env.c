/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:37:08 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/10/29 14:46:25 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*get_env(t_savage *savage, char *arg)
{
	int	i;
	int	sign;

	i = 0;
	sign = ft_strlen(arg);
	while(savage->env[i])
	{
		if(!ft_strncmp(savage->env[i], arg, sign))
			return (ft_strdup(ft_strchr(savage->env[i], '=') + 1));
		i++;
	}
	return (ft_strdup(" "));
}

void	claner_env(char *arg, char **env)
{
	int	i;
	int	size;

	size = ft_strlen(arg);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(arg, env[i], size))
			break ;
		i++;
	}
	if (env[i])
	{
		free(env[i]);
		env[i] = NULL;
		i++;
		while (env[i])
		{
			env[i - 1] = env[i];
			i++;
		}
		env[i - 1] = NULL;
	}
}

void	path_search(char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			tmp = env[i];
			env[i] = env[i + 1];
			env[i + 1] = tmp;
			i++;
		}
		i++;
	}
}


int	envirment(t_savage *savage, char **arg)
{
	int i;
	char **env_writer;

	if(savage->agrs[i])
	{
		ft_putendl_fd("env: too many arguments", 1);
		return (1);
	}
	i = 0;
	env_writer = arg;
	path_search(env_writer);
	while (env_writer[i])
		ft_putendl_fd(env_writer[i++], 1);
	export(savage, "_=env");
	return (1);
}
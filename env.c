/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:37:08 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/10/26 04:06:14 by marvin           ###   ########.fr       */
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



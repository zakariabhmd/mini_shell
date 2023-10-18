/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:37:08 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/10/18 14:48:10 by zbabahmi         ###   ########.fr       */
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


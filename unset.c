/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 07:15:19 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/10/26 07:15:19 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	valid_key_name(char *str)
{
	int	i;

	i = 0;
	if (!str || ft_isdigit(str[i]) || str[i] == '=')
		return (0);
	while (str[i])
	{
		if (invalid_char(str, i) || str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

int	unset(t_savage *savage)
{
    int i;

    i = 1;

    while(savage->args[i])
    {
        if(valid_key_name(savage->args[i]))
            env_cleaner(savage->args[i], savage->env);
        else
            invalid_export(savage, savage->args[i], "unset");
        i++;
    }
    return (1);
}
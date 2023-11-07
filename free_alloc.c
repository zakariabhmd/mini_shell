/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:58:18 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/07 22:07:06 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	free_env(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i++]);
	}
	free(str);
}

void	sh_cleaner(t_savage *savage)
{
	free(savage->command);
	savage->command = NULL;
	free_env(savage->agrs);
	savage->agrs = NULL;
	free_env(savage->env);
	savage->env = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 06:02:58 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/11 23:30:50 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	**reallocation(char **env, int added)
{
	char	**backup;
	int		i;

	i = 0;
	while (env[i])
		i++;
	backup = ft_malloc(((i + added + 1) * sizeof(char *)), NULL, ALLOC, NULL);
	if (!backup)
		return (NULL);
	return (backup);
}

char	**renew_env(char **var, char **env, int pos)
{
	char	**backup;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (env[pos])
		backup = reallocation(env, 0);
	else
		backup = reallocation(env, 1);
	backup[pos] = ft_strdup(*var);
	while (env[i])
	{
		if (j != pos)
			backup[j] = ft_strdup(env[i]);
		i++;
		j++;
	}
	if (j != pos)
		backup[j] = NULL;
	else
		backup[i + 1] = NULL;
	return (backup);
}

char	*generate_absolute_path(char *path, char *bin)
{
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	path = ft_strjoin(tmp, bin);
	free(tmp);
	return (path);
}

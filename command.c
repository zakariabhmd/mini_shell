/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:47:06 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/02 18:15:35 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*append_pwd(char *value)
{
	char	pwd[1024];
	char	*hold;
	int		size;
	int		i;

	size = ft_strlen(value);
	hold = value;
	i = 0;
	if (getcwd(pwd, 1024))
	{
		if (value[0] == ':')
			return (ft_strjoin(pwd, value));
		if (value[size - 1] == ':')
			return (ft_strjoin(value, pwd));
		while (hold[i])
		{
			hold = ft_strchr(hold, ':');
			if (!hold)
				break ;
			if (hold[i + 1] == ':')
				return (ft_strjoin(value, pwd));
			i++;
		}
	}
	return (ft_strdup(value));
}

char	*get_path(t_savage *savage)
{
	char	*value;
	char	*pwd;
	char	**paths;
	char	*backup;

	value = get_env(savage, "PATH");
	if (!value || !ft_strlen(value))
	{
		free(value);
		pwd = search_n_pwd(savage);
	}
	else
	{
		backup = append_pwd(value);
		paths = ft_split(backup, ':');
		pwd = search_bin(savage, paths);
		free(value);
		free(backup);
		free_env(paths);
	}
	if (!access(savage->agrs[0], X_OK))
		pwd = savage->agrs[0];
	return (pwd);
}

void exev_args(t_savage *savage)
{
	char	*path;

	if (!bulttin_check(savage))
	{
		path = get_path(savage);
		if (path == NULL)
		{
			printf("minishell: %s: command not found\n", savage->agrs[0]);
			exit(127);
		}
		if (execve(path, savage->agrs, savage->env) == -1)
		{
			perror("minishell: execve");
			exit(126);
		}
	}
}
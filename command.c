/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:47:06 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/12 01:54:49 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	waitsignal(int sig)
{
	(void)sig;
	signal(SIGINT, waitsignal);
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

void	exev_args(t_savage *savage)
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

int	count_pipe(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i - 1);
}

void	check_command(t_savage *savage)
{
	char	*exp;
	int		hold;
	int		holder;

	hold = dup(STDOUT_FILENO);
	if (!savage->agrs[0])
		return ;
	savage->first_arg = ft_strdup(savage->agrs[0]);
	holder = check_redirections(savage);
	if (holder != -1)
	{
		if (savage->agrs[0] && !(bulttin_check(savage)))
			check_one_command(savage);
	}
	if (holder != -1)
	{
		close(holder);
		dup2(hold, STDOUT_FILENO);
		close(hold);
	}
}

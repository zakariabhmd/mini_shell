/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:47:06 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/15 18:19:10 by zbabahmi         ###   ########.fr       */
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

	path = get_path(savage);
	if (path == NULL)
	{
		printf("minishell: %s: command not found\n", savage->agrs[0]);
		savage->exit_status = 127;
		exit(127);
	}
	if (execve(path, savage->agrs, savage->env) == -1)
	{
		savage->exit_status = 126;
		perror("minishell: execve");
		exit(126);
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

char	**check_command(t_savage *savage)
{
	int	hold;
	int	holder;

	hold = dup(STDOUT_FILENO);
	savage->agrs = savage->cmd[0].agrs;
	if (savage->cmd[0].first_arg && (savage->cmd[0].first_arg[0] != '\0'))
		savage->first_arg = savage->cmd[0].first_arg;
	else
		return (savage->env);
	if (!savage->agrs[0] || savage->agrs[0][0] == '\0')
		return (savage->env);
	holder = check_redirections(savage);
	if (holder != -1)
	{
		if (savage->agrs[0] && !(bulttin_check(savage)))
			check_one_command(savage);
	}
	close(hold);
	if (holder != -1)
	{
		close(holder);
		dup2(hold, STDOUT_FILENO);
		close(hold);
	}
	return (savage->env);
}

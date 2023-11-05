/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:47:06 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/05 22:42:05 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*update_lastarg(char **arg)
{
	char	*res;
	char	*tmp;
	int		i;

	i = 0;
	while (arg[i])
		i++;
	tmp = ft_strchr(arg[i - 1], '=');
	if (tmp)
		*tmp = '\0';
	res = ft_strjoin("_=", arg[i - 1]);
	return (res);
}

char	**set_args(char *str)
{
	char	**args;
	char	*bs;
	int		i;

	if (!str)
		return (NULL);
	args = lexical_analysis(str, ' ');
	i = 0;
	while (args[i])
	{
		bs = bs_parse(args[i], 2);
		free(args[i]);
		args[i] = ft_strdup(bs);
		free(bs);
		i++;
	}
	if (!args)
		return (NULL);
	return (args);
}

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

void	check_command(t_savage *savage)
{
	// char	*exp;

	// exp = expansion(savage, &savage->command[0]);
	// savage->agrs = set_args(exp);
	// savage->first_arg = ft_strdup(savage->agrs[0]);
	// if (check_redirections(savage) != -1)
	// {
		if(!bulttin_check(savage))
			check_one_command(savage);
	// }
}
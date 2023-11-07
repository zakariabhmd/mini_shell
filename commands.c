/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 03:57:43 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/07 21:13:55 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "mini_shell.h"



// char	*update_lastarg(char **arg)
// {
// 	char	*res;
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	while (arg[i])
// 		i++;
// 	tmp = ft_strchr(arg[i - 1], '=');
// 	if (tmp)
// 		*tmp = '\0';
// 	res = ft_strjoin("_=", arg[i - 1]);
// 	return (res);
// }

// char	*get_path(t_savage *savage)
// {
// 	char	*value;
// 	char	*pwd;

// 	value = get_env(savage, "PATH");
// 	if (!value || ft_strlen(value))
// 	{
// 		pwd = search_in_pwd(savage);
// 	}
// }

// int	count_pipe(char **arg)
// {
// 	int i;

// 	i = 0;
// 	while (arg[i])
// 		i++;
// 	return (i - 1);
// }

// void	cmd_test(t_savage *savage)
// {
// 	pid_t	pid;
// 	char	*path;
// 	char	*backup;

// 	savage->bin = 0;
// 	path = get_path(savage);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (path == NULL)
// 		{
// 			ft_error("command not found", savage->first_arg);
// 			exit(127);
// 		}
// 		if (execve(path, savage->agrs, savage->env) == -1)
// 		{
// 			perror("minishell: execve");
// 			exit(126);
// 		}
// 	}
// 	waitpid(pid, &savage->exit_status, 0);
// 	backup = update_lastarg(savage->agrs);
// 	export(savage, backup);
// 	free(backup);
// 	free(path);
// }

// void	check_command(t_savage *savage)
// {
// 	if (!savage->agrs[0])
// 		return ;
// 	savage->first_arg = ft_strdup(savage->agrs[0]);
// 	if (savage->agrs[0] && !(bulttin_check(savage)))
// 		cmd_test(savage);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 05:08:55 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/02 21:41:30 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"
#include <stdio.h>

int	ft_expt(t_savage *savage)
{
	int	test;

	test = 0;
	claner_env("_", savage->env);
	test = export(savage, NULL);
	return (test);
}

int	bulttin_check(t_savage *savage)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(savage->agrs[0], "exit"))
		to_exit(savage);
	else if (ft_strcmp(savage->agrs[0], "echo"))
		ret = echo_printer(savage->agrs + 1);
	else if (ft_strcmp(savage->agrs[0], "cd"))
		ret = chdir(*savage->agrs + 1);
	else if (ft_strcmp(savage->agrs[0], "pwd"))
		ret = pwd_com();
	// else if (ft_strcmp(savage->agrs[0], "export"))
	// 	ret = ft_expt(savage);
	// else if(ft_strcmp(savage->agrs[0], "unset"))
	// 	ret = unset(savage);
	return (ret);
}
int	child(t_savage *savage, int fd[2], int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		if (savage->command[i + 1])
			dup2(fd[1], 1);
		exev_args(savage);
		close(fd[1]);
		exit(savage->exit_status);
	}
	close(fd[1]);
	return (pid);
}

int count_pipe(char **arg)
{
	int i;

	i = 0;
	while (arg[i])
		i++;
	return (i - 1);
}

void multipale_cmds(t_savage *savage, int x)
{
	int stdi = dup(0);
	int stdo = dup(1);
	int i = 0;
	int fd[2];
	pid_t pid;

	while (i <= x)
	{
		pipe(fd);
		pid = child(savage, fd, i);
		dup2(fd[0], 0);
		if(savage->command[x])
			waitpid(pid, &savage->exit_status, WNOHANG);
		savage->exit_status = WEXITSTATUS(savage->exit_status);
		close(fd[0]);
		i++;
	}
	pid_t top = wait(&savage->exit_status);
	while (top > 0)
	{
		if (top < pid)
			savage->exit_status = WEXITSTATUS(savage->exit_status);
		top = wait(&savage->exit_status);
	}
	savage->exit_status = WEXITSTATUS(savage->exit_status);
	dup2(stdi, 0);
	dup2(stdo, 1);
}

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

void check_one_command(t_savage *savage)
{
	pid_t	pid;
	char	*path;
	char	*backup;

	path = get_path(savage);
	pid = fork();
	if (pid == 0)
	{
		if (path == NULL)
		{
			ft_error(" command not found", savage->first_arg);
			exit(127);
		}
		if (execve(path, savage->agrs, savage->env) == -1)
		{
			perror("minishell: execve");
			exit(126);
		}
	}
	waitpid(pid, &savage->exit_status, 0);
	if (WIFEXITED(savage->exit_status))
		savage->exit_status = WEXITSTATUS(savage->exit_status);
	if (savage->exit_status == -1)
		ft_putchar_fd('\n', 1);
	backup = update_lastarg(savage->agrs);
	export(savage, backup);
	free(backup);
	free(path);
	// waitpid(pid, &savage->exit_status, 0);
	// int status;
	// pid_t pid = fork();
	// if (pid == 0)
	// {
	// 		get_path(savage);
	// 	// char *command;
	// 	// idx = 0;
	// 	// while (path[idx])
	// 	// {
	// 	// 	// command = ft_strjoin(path[idx], "/");
	// 	// 	// command = ft_strjoin(command, savage->command);
	// 	// 	// if (access(command, R_OK) == 0){
	// 	// 	// 	execve(command, savage->agrs, env);
	// 	// 	// 	perror("exec");
	// 	// 	// }
	// 	// 	// idx++;
	// 	// }
	// 	// printf("command not found\n");
	// }
	// waitpid(pid, &status, 0);
}



int main (int ac, char **av, char **env)
{

	t_savage *savage = ft_calloc(1, sizeof(t_savage));
	char *line;
	savage->env = strdup_env(env);
	while (1)
	{
		line = readline("minishell-> ");
		add_history(line);
		 if (line)
		 {
			savage->command = ft_strdup(line);
			savage->agrs = ft_split(line, ' ');
		 }
		int x = 0;
		char **str = ft_split(line, '|');
		while (str[x])
			x++;
		// char **path = ft_split(holder2, ':');
		if (x == 1){
			if(!bulttin_check(savage))
				check_one_command(savage);
		}
		else if (x > 1){
			multipale_cmds(savage, x);
		}

	}
}
// }
// 	savage[0].command = ft_strdup("ls");
// 	// savage[0].agrs = ft_split("grep main main.c", ' ');

// 	return (0);
// }
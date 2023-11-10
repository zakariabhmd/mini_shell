/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:30:20 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/10 06:42:05 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	duplicate_fd(t_cmds *cmd)
{
	cmd->i = 0;
	cmd->stdi = dup(0);
	cmd->stdo = dup(1);
}

void	duplicate1_fd(t_cmds *cmd)
{
	dup2(cmd->stdi, 0);
	dup2(cmd->stdo, 1);
}

int	child_proc(t_savage *savage, int fd[2], int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		if (savage->command[i + 1])
			dup2(fd[1], 1);
		check_redirections(savage);
		exev_args(savage);
		close(fd[1]);
		exit(savage->exit_status);
	}
	close(fd[1]);
	return (pid);
}

void	pipe_help(t_savage *savage, t_cmds *cmd)
{
	while (cmd->i <= savage->count)
	{
		get_args(savage, cmd->i);
		pipe(cmd->fd);
		cmd->pid = child_proc(savage, cmd->fd, cmd->i);
		dup2(cmd->fd[0], 0);
		if (savage->command[cmd->i])
			waitpid(cmd->pid, &savage->exit_status, WNOHANG);
		savage->exit_status = WEXITSTATUS(savage->exit_status);
		close(cmd->fd[0]);
		free_env(savage->agrs);
		if (*savage->first_arg)
			free(savage->first_arg);
		cmd->i++;
	}
}

void	multipale_cmds(t_savage *savage, t_cmds *cmd)
{
	duplicate_fd(cmd);
	pipe_help(savage, cmd);
	close(cmd->fd[0]);
	close(cmd->fd[1]);
	cmd->top = wait(&savage->exit_status);
	while (cmd->top > 0)
	{
		if (cmd->top < cmd->pid)
			savage->exit_status = WEXITSTATUS(savage->exit_status);
		cmd->top = wait(&savage->exit_status);
	}
	savage->exit_status = WEXITSTATUS(savage->exit_status);
	duplicate1_fd(cmd);
	close(cmd->stdi);
	close(cmd->stdo);
}

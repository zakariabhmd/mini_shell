/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 04:11:15 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/15 21:08:05 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"
#include "minishell.h"

void	ft_get_args(t_savage *savage, int i)
{
	savage->agrs = savage->cmd[i].agrs;
	if (savage->cmd[i].first_arg)
		savage->first_arg = savage->cmd[i].first_arg;
}

void	check_one_command(t_savage *savage)
{
	pid_t	pid;
	char	*path;

	path = get_path(savage);
	pid = fork();
	if (pid == 0)
	{
		if (path == NULL)
		{
			ft_error(" command not found", savage->first_arg);
			savage->exit_status = 127;
			exit(127);
		}
		savage->exit_status = 0;
		execve(path, savage->agrs, savage->env);
	}
	signal(SIGINT, waitsignal);
	waitpid(pid, &savage->exit_status, 0);
	if (WIFEXITED(savage->exit_status))
		savage->exit_status = WEXITSTATUS(savage->exit_status);
	if (savage->exit_status == -1)
		ft_putchar_fd('\n', 1);
}

void	free_l_env(t_env *tokens)
{
	t_env	*current;
	t_env	*temp;

	current = tokens;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp->arg);
		free(temp);
	}
}

size_t	list_length(t_proc *cmds)
{
	size_t	counter;
	t_proc	*head;

	counter = 0;
	head = cmds;
	while (head)
	{
		counter++;
		head = head->next;
	}
	return (counter);
}

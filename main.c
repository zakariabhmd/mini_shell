/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 05:08:55 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/08 20:42:17 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"
#include <stdio.h>

void	get_args(t_savage *savage, int i)
{
	char	*exp;

	exp = expansion(savage, savage->command[i]);
	savage->agrs = set_args(exp);
	free(exp);
	if (savage->agrs[0])
		savage->first_arg = ft_strdup(savage->agrs[0]);
}

void	check_one_command(t_savage *savage)
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
}

void	check_test(char *input, t_savage *savage, t_cmds *cmd)
{
	savage->command = lexical_analysis(input, '|');
	savage->count = count_pipe(savage->command);
	if (savage->count == 0)
	{
		check_command(savage);
	}
	else if (savage->count)
	{
		multipale_cmds(savage, cmd);
	}
}

int	main(int ac, char **av, char **env)
{
	t_cmds		cmd;
	t_savage	savage;
	char		*line;

	(void)ac;
	(void)av;
	savage.exit_status = 0;
	savage.env = strdup_env(env);
	while (1)
	{
		line = readline("minishell-> ");
		if (!line)
		{
			free(line);
			free(savage.env);
			exit(savage.exit_status);
		}
		add_history(line);
		check_test(line, &savage, &cmd);
	}
}

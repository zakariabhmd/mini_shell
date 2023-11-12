/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 05:08:55 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/12 02:15:19 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"
#include <stdio.h>

void	ft_get_args(t_savage *savage, int i)
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
		execve(path, savage->agrs, savage->env);
	}
	signal(SIGINT, waitsignal);
	waitpid(pid, &savage->exit_status, 0);
	if (WIFEXITED(savage->exit_status))
		savage->exit_status = WEXITSTATUS(savage->exit_status);
	if (savage->exit_status == -1)
		ft_putchar_fd('\n', 1);
	backup = update_lastarg(savage->agrs);
	export(savage, backup);
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

void	signl(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int ac, char **argv, char **env)
{
	char				*input;
	t_token				*tokens;
	t_proc				*cmds;
	t_env				*l_env;
	struct sigaction	minisig;

	tokens = NULL;
	cmds = NULL;
	(void)ac;
	(void)argv;
	minisig.sa_handler = signl;
	sigemptyset(&minisig.sa_mask);
	sigaddset(&minisig.sa_mask, SIGQUIT);
	minisig.sa_flags = 0;
	sigaction(SIGINT, &minisig, NULL);
	sigaction(SIGQUIT, &minisig, NULL);
	l_env = local_env(env);
	while (1)
	{
		input = readline("Shell $ ");
		if (input == NULL)
			break ;
		if (ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		tokens = get_tokens(input);
		if (syntax_checker(tokens))
		{
			cmds = parsing(tokens, l_env);
			handle_merge(input, cmds, env);
			free_procs(cmds);
		}
		else
		{
			perror("Syntax error");
		}
		free_tokens(tokens);
		free(input);
	}
	free_l_env(l_env);
	return (0);
}

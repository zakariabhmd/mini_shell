/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 05:08:55 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/15 22:12:28 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"
#include "minishell.h"
#include "main.h"

void	segnal_dup(t_main *m)
{
	m->savage->minisig.sa_handler = signl;
	sigemptyset(&m->savage->minisig.sa_mask);
	sigaddset(&m->savage->minisig.sa_mask, SIGQUIT);
	m->savage->minisig.sa_flags = 0;
	sigaction(SIGINT, &m->savage->minisig, NULL);
	sigaction(SIGQUIT, &m->savage->minisig, NULL);
	dup2(m->savage->fd, 1);
	dup2(m->savage->fd0, 0);
}

void	pars_and_execute(t_main *m)
{
	m->cmds = parsing(m->tokens, m->l_env, m->savage->exit_status);
	m->my_env = handle_merge(m->input, m->cmds, lenv_2_env(m->l_env),
			m->savage);
	m->l_env = local_env(m->my_env);
	free_procs(m->cmds);
}

int	get_tokens_by_rl(t_main *m)
{
	m->input = readline("minishell->");
	if (m->input == NULL)
		return (0);
	add_history(m->input);
	return (1);
}

void	main_helper(t_main	*m)
{
	while (1)
	{
		segnal_dup(m);
		if (!get_tokens_by_rl(m))
			break ;
		if (ft_strlen(m->input) == 0)
		{
			free(m->input);
			continue ;
		}
		m->tokens = get_tokens(m->input, m->savage);
		if (syntax_checker(m->tokens))
			pars_and_execute(m);
		else
		{
			m->savage->exit_status = 258;
			perror("syntax error near unexpected token `|'");
		}
		free(m->input);
	}
}

int	main(int ac, char **argv, char **env)
{
	t_main	*m;

	m = ft_malloc(sizeof(t_main), NULL, ALLOC, NULL);
	set_main(m, env);
	main_helper(m);
	free_l_env(m->l_env);
	free(m);
	return (0);
}

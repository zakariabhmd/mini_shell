/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:52:00 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/15 20:06:59 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"
#include "minishell.h"
#include "main.h"

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

void	fill_zakaria_struct(t_merge_var *var, char **env, t_proc *cmds)
{
	t_proc	*head;

	var->savage->env = env;
	var->idx = 0;
	head = cmds;
	var->savage[var->idx].count = var->commands_count;
	while (head)
	{
		var->savage->cmd[var->idx].first_arg = head->program;
		var->i = 0;
		var->savage->cmd[var->idx].agrs = head->args;
		head = head->next;
		var->idx++;
	}
}

char	**handle_merge(char *input, t_proc *cmds, char **my_env,
		t_savage *savage)
{
	char		**env;
	t_merge_var	*var;

	var = ft_malloc(sizeof(t_merge_var), NULL, ALLOC, NULL);
	if (!cmds || !my_env)
		return (my_env);
	var->commands_count = list_length(cmds);
	if (var->commands_count == 0)
		return (my_env);
	savage->count = var->commands_count;
	savage->cmd = ft_malloc((sizeof(t_args) * var->commands_count), NULL,
			ALLOC, NULL);
	if (!savage)
		return (my_env);
	var->savage = savage;
	fill_zakaria_struct(var, my_env, cmds);
	if (savage->count == 1)
		env = check_command(savage);
	else
		env = multipale_cmds(input, savage, &var->cmd);
	return (env);
}

void	set_main(t_main *m, char **env)
{
	m->l_env = local_env(env);
	m->savage = ft_malloc(sizeof(t_savage), NULL, ALLOC, NULL);
	m->savage->fd = dup(1);
	m->savage->fd0 = dup(0);
}

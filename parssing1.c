/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 22:12:14 by atoukmat          #+#    #+#             */
/*   Updated: 2023/11/15 20:00:37 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "minishell.h"
#include <string.h>

t_proc	*new_command(t_token *tokens, t_env *env, int exit_status)
{
	t_proc	*new_proc;

	new_proc = (t_proc *)ft_malloc(sizeof(t_proc), NULL, ALLOC, NULL);
	if (new_proc == NULL)
	{
		perror("Memory allocation failed");
		exit(1);
	}
	new_proc->args = get_args(tokens, env, exit_status);
	if (new_proc->args == NULL)
		return (NULL);
	new_proc->program = ft_strdup(new_proc->args[0]);
	new_proc->next = NULL;
	return (new_proc);
}

void	handel_norm_1(t_var_pars *var, t_token *tokens, t_env *env,
		int exit_status)
{
	var->new_proc = new_command(tokens, env, exit_status);
	if (var->head == NULL)
	{
		var->head = var->new_proc;
		var->current = var->head;
	}
	else
	{
		var->current->next = var->new_proc;
		var->current = var->current->next;
	}
}

t_proc	*parsing(t_token *tokens, t_env *env, int exit_status)
{
	t_var_pars	*var;

	var = ft_malloc(sizeof(t_var_pars), NULL, ALLOC, NULL);
	var->head = NULL;
	var->current = NULL;
	var->prev_token = NULL;
	var->red = NULL;
	var->token = tokens;
	while (var->token != NULL)
	{
		if (var->token->token == PIPE_LINE)
		{
			handel_norm_1(var, tokens, env, exit_status);
			tokens = var->token->next;
		}
		var->prev_token = var->token;
		var->token = var->token->next;
	}
	var->new_proc = new_command(tokens, env, exit_status);
	if (var->head == NULL)
		var->head = var->new_proc;
	else
		var->current->next = var->new_proc;
	return (var->head);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:59:33 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/15 20:01:54 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "minishell.h"
#include <string.h>

void	counting_args(t_var_args *var, t_token *tokens)
{
	var->arg_count = 0;
	var->current = tokens;
	while (var->current != NULL && var->current->token != PIPE_LINE)
	{
		if (var->current->token != WHITE_SPACE)
		{
			var->arg_count++;
		}
		var->current = var->current->next;
	}
}

void	pre_set_args(t_var_args *var, t_token *tokens)
{
	var->args = ft_malloc(sizeof(char *) * (var->arg_count + 1), \
						NULL, ALLOC, NULL);
	if (var->args == NULL)
	{
		perror("Memory allocation failed");
		exit(1);
	}
	var->i = 0;
	var->current = tokens;
	var->c = 0;
	var->k = 0;
}

void	handel_norm(t_var_args *var)
{
	perror("Memory allocation failed");
	var->k = 0;
	while (var->k < var->i)
	{
		free(var->args[var->k]);
		var->k++;
	}
	free(var->args);
	free(var);
	exit(1);
}

void	double_quate(t_var_args *var, t_env *env, int exit_status)
{
	var->expanded = expand_inside_dq(var->arg, env, exit_status);
	var->args[var->i] = var->expanded;
	var->args[var->i] = ft_strjoin(var->args[var->i], " ");
}

void	dollar_sing(t_var_args *var, t_env *env, int exit_status)
{
	if (var->arg[1] == '\0')
		var->args[var->i] = ft_strdup("$");
	else
	{
		var->expanded = expand_1(var->arg + 1, env, exit_status);
		if (var->expanded)
			var->args[var->i] = var->expanded;
		else
			var->args[var->i] = ft_strdup("");
	}
}

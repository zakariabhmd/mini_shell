/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxerr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoukmat <atoukmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 22:15:39 by atoukmat          #+#    #+#             */
/*   Updated: 2023/11/15 10:46:19 by atoukmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipes(t_syntax_var *var)
{
	if ((var->current->next == NULL) || (var->current->arg[1]
			&& var->current->arg[1] == '|'))
		return (0);
	if (var->current->next->token == WHITE_SPACE
		&& ((var->current->next->next == NULL)
			|| (var->current->next->next->token == PIPE_LINE)))
		return (0);
	if (var->current->prev == NULL || (var->current->prev->token == WHITE_SPACE
			&& (var->current->prev->prev == NULL
				|| var->current->prev->prev->token == PIPE_LINE)))
		return (0);
	return (1);
}

int	syntax_checker(t_token *tokens)
{
	t_syntax_var	*var;

	var = ft_malloc(sizeof(t_syntax_var), NULL, ALLOC, NULL);
	var->current = tokens;
	var->prev = NULL;
	while (var->current != NULL)
	{
		if (var->current->token == PIPE_LINE && !check_pipes(var))
		{
			free(var);
			return (0);
		}
		var->prev = var->current;
		var->current = var->current->next;
		if (var->current != NULL)
			var->current->prev = var->prev;
	}
	free(var);
	return (1);
}

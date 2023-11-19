/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:00:09 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/15 20:01:49 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "minishell.h"
#include <string.h>

void	splitting_args(t_var_args *var, t_env *env, int exit_status)
{
	while (var->current && var->current->token != PIPE_LINE)
	{
		if (var->current->token != WHITE_SPACE)
		{
			var->c = 1;
			var->arg = ft_strdup(var->current->arg);
			if (var->arg == NULL)
				handel_norm(var);
			if (var->current->token == DOUBLE_QUOTE)
				double_quate(var, env, exit_status);
			else if (var->current->token == ENV)
				dollar_sing(var, env, exit_status);
			else
				var->args[var->i] = var->arg;
			var->i++;
		}
		var->current = var->current->next;
	}
}

void	ft_list_remove_if(t_token **head, char *arg_to_remove)
{
	t_token	*current;
	t_token	*next_node;

	if (*head == NULL)
		return ;
	current = *head;
	while (current != NULL)
	{
		next_node = current->next;
		if (ft_strcmp(current->arg, arg_to_remove) == 0)
		{
			if (current->prev != NULL)
				current->prev->next = current->next;
			else
				*head = current->next;
			if (current->next != NULL)
				current->next->prev = current->prev;
			free(current->arg);
			free(current);
		}
		current = next_node;
	}
}

void	handle_joined(t_token *tokens)
{
	t_token	*head;

	head = tokens;
	while (head)
	{
		if (((head->token == SINGLE_QUOTE || head->token == DOUBLE_QUOTE || \
			head->token == 10) && \
			(head->next && (head->next->token == SINGLE_QUOTE || \
			head->next->token == DOUBLE_QUOTE || head->next->token == 10))))
		{
			if (head->next && head->next->arg)
			{
				head->arg = ft_strjoin(head->arg, head->next->arg);
				ft_list_remove_if(&head, head->next->arg);
			}
			head = tokens;
		}
		else
			head = head->next;
	}
}

char	**get_args(t_token *tokens, t_env *env, int exit_status)
{
	char		**res;
	t_var_args	*var;

	handle_joined(tokens);
	var = ft_malloc(sizeof(t_var_args), NULL, ALLOC, NULL);
	counting_args(var, tokens);
	if (var->arg_count == 0)
	{
		return (NULL);
	}
	pre_set_args(var, tokens);
	splitting_args(var, env, exit_status);
	if (var->c == 0)
	{
		return (NULL);
	}
	var->args[var->arg_count] = NULL;
	res = var->args;
	return (res);
}

void	free_args(char **args)
{
	char	**current;

	current = args;
	while (*current != NULL)
	{
		current++;
	}
}

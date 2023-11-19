/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainn1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 04:09:43 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/15 18:26:53 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"
#include "minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*temp;

	current = tokens;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp->arg);
		free(temp);
	}
}

void	free_procs(t_proc *procs)
{
	t_proc	*current;
	t_proc	*temp;

	current = procs;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
}

void	print_token(t_token *token)
{
	printf("Token Type: %d\n", token->token);
	printf("Token Text: %s\n", token->arg);
	printf("Token Length: %d\n", token->i);
}

void	print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		print_token(current);
		current = current->next;
	}
}

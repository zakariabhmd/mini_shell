/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 22:13:12 by atoukmat          #+#    #+#             */
/*   Updated: 2023/11/15 18:17:15 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "main.h"

void	set_var(t_tokens_var *var, char *input)
{
	var->head = NULL;
	var->current = NULL;
	var->str_len = ft_strlen(input);
	var->i = 0;
}

void	continue_norm_1(t_tokens_var *var)
{
	if (var->word)
		var->word[var->word_len] = '\0';
	var->new_token = ft_malloc(sizeof(t_token), NULL, ALLOC, NULL);
	if (var->new_token == NULL)
	{
		perror("Memory allocation failed");
		exit(1);
	}
	if (var->word)
	{
		var->new_token->arg = var->word;
		var->new_token->i = var->word_len;
		var->new_token->token = var->token;
		var->new_token->next = NULL;
	}
}

int	tokens_parser(t_tokens_var *var, char *input, t_savage *savage)
{
	var->c = input[var->i];
	var->token = get_type(var->c);
	var->j = var->i;
	if (var->token == SINGLE_QUOTE || var->token == DOUBLE_QUOTE)
	{
		if (!quote_token(var, input, savage))
			return (0);
	}
	else if (var->token == ENV)
		env_token(var, input);
	else if (var->token == REDIR_IN || var->token == REDIR_OUT)
		dir_token(var, input);
	else
	{
		while (var->j < var->str_len && get_type(input[var->j]) == var->token)
			var->j++;
	}
	return (1);
}

void	continue_norm_0(t_tokens_var *var, char *input)
{
	var->word_len = var->j - var->i;
	var->word = (char *)ft_malloc(var->word_len + 1, NULL, ALLOC, NULL);
	if (var->word == NULL)
	{
		perror("Memory allocation failed");
		exit(1);
	}
	if (var->token == SINGLE_QUOTE || var->token == DOUBLE_QUOTE)
		ft_strlcpy(var->word, input + var->i + 1, var->word_len - 1);
	else
		ft_strlcpy(var->word, input + var->i, var->word_len + 1);
	continue_norm_1(var);
}

t_token	*get_tokens(char *input, t_savage *savage)
{
	t_tokens_var	*var;
	t_token			*res;

	var = ft_malloc(sizeof(t_tokens_var), NULL, ALLOC, NULL);
	set_var(var, input);
	while (var->i < var->str_len)
	{
		if (!tokens_parser(var, input, savage))
			return (NULL);
		continue_norm_0(var, input);
		if (var->head == NULL)
		{
			var->head = var->new_token;
			var->current = var->head;
		}
		else
		{
			var->current->next = var->new_token;
			var->current = var->current->next;
		}
		var->i = var->j;
	}
	res = var->head;
	free(var);
	return (res);
}

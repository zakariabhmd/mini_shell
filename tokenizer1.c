/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 04:19:24 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/15 18:16:32 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "main.h"

t_type_token	get_type(char c)
{
	if (c == 32 || c == '\t')
		return (WHITE_SPACE);
	else if (c == 10)
		return (NEW_LINE);
	else if (c == 39)
		return (SINGLE_QUOTE);
	else if (c == 34)
		return (DOUBLE_QUOTE);
	else if (c == '$')
		return (ENV);
	else if (c == 124)
		return (PIPE_LINE);
	else if (c == 60)
		return (REDIR_IN);
	else if (c == 62)
		return (REDIR_OUT);
	return (10);
}

int	quote_token(t_tokens_var *var, char *input, t_savage *savage)
{
	var->quote = var->c;
	var->j++;
	while (var->j < var->str_len && input[var->j] != var->quote)
		var->j++;
	if (input[var->j] != var->quote)
	{
		perror("syntax err : token needed ");
		savage->exit_status = 1;
		return (0);
	}
	if (var->j < var->str_len)
		var->j++;
	return (1);
}

void	env_token(t_tokens_var *var, char *input)
{
	var->j++;
	if (input[var->j] == '?')
		var->j++;
	else
	{
		while ((var->j < var->str_len && ft_isalnum(input[var->j])))
			var->j++;
	}
}

void	dir_token(t_tokens_var *var, char *input)
{
	while (get_type(input[var->j]) == REDIR_IN
		|| get_type(input[var->j]) == REDIR_OUT)
		var->j++;
}

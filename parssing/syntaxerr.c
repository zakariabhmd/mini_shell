/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxerr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoukmat <atoukmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 22:15:39 by atoukmat          #+#    #+#             */
/*   Updated: 2023/11/09 06:12:08 by atoukmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int syntax_checker(t_token *tokens)
{
    t_token *current = tokens;
    t_token *prev = NULL;

    while (current != NULL)
	{
        if (current->token == PIPE_LINE) 
		{	
            if ((current->next == NULL) || (current->arg[1] && current->arg[1] == '|')) 
                return 0;
            if (current->next->token == WHITE_SPACE &&
                ((current->next->next == NULL) || (current->next->next->token == PIPE_LINE)))
                return 0;
            
            if (current->prev == NULL || (current->prev->token == WHITE_SPACE && 
                (current->prev->prev == NULL || current->prev->prev->token == PIPE_LINE))) 
                return 0;
        }
		else if (current->token == REDIR_IN) 
		{
            if (current->arg[2] && current->arg[2] == '<') 
                return 0;
            if ((current->next == NULL) || (current->next->token == WHITE_SPACE &&
                ((current->next->next == NULL) || (current->next->next->token == PIPE_LINE))) )
                return 0;
            if (current->arg[1] && current->arg[1] == '<') 
                current->token = D_REDIR_IN;
        }
		else if (current->token == REDIR_OUT) 
		{
            if (current->arg[2] && current->arg[2] == '>') 
                return 0;
            if (current->arg[1] && current->arg[1] == '>')
                current->token = D_REDIR_OUT;
            if ((current->next == NULL) || (current->next->token == WHITE_SPACE &&
                ((current->next->next == NULL) || (current->next->next->token == PIPE_LINE))) )
                return 0;
        }
        prev = current;
        current = current->next;
        if (current != NULL) 
            current->prev = prev;
    }
    return 1;
}

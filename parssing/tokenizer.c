/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 22:13:12 by atoukmat          #+#    #+#             */
/*   Updated: 2023/11/11 06:41:43 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

type_token get_type(char c)
{
    if (c == 32 || c == '\t')
        return WHITE_SPACE;
    else if (c == 10)
        return NEW_LINE;
    else if (c == 39)
        return SINGLE_QUOTE;
    else if (c == 34)
        return DOUBLE_QUOTE;
    else if (c =='$')
        return ENV;
    else if (c == 124)
        return PIPE_LINE;
    else if (c == 60)
        return REDIR_IN;
    else if (c == 62)
        return REDIR_OUT;
    return 10;
}

t_token *get_tokens(char *input)
{
    t_token *head = NULL;
    t_token *current = NULL;
    int str_len = ft_strlen(input);
    int i = 0;

    while (i < str_len)
    {
        char c = input[i];
        type_token token = get_type(c);
        int j = i;
        if (token == SINGLE_QUOTE || token == DOUBLE_QUOTE)
        {
            char quote = c;
            j++;
            while (j < str_len && input[j] != quote)
                j++;
            if(input[j] != quote )
            {
                perror("syntax err ; err ");
                return(NULL);
            }
            if (j < str_len)
                j++;
        }
        else if(token == ENV)
        {
            j++;
            while (j < str_len && ft_isalnum(input[j]))
                j++;
        }
        else if(token == REDIR_IN || token == REDIR_OUT)
        {
            while(get_type(input[j]) == REDIR_IN || get_type(input[j]) == REDIR_OUT)
                j++;
        }
        else
        {
            while (j < str_len && get_type(input[j]) == token)
                j++;
        }
        int word_len = j - i;
        char *word = (char *)malloc(word_len + 1);
        if (word == NULL)
        {
            perror("Memory allocation failed");
            exit(1);
        }
        if (token == SINGLE_QUOTE || token == DOUBLE_QUOTE)
            ft_strlcpy(word, input + i + 1, word_len - 1);
        else
            ft_strlcpy(word, input + i , word_len + 1);
        if(word)
            word[word_len] = '\0';
        t_token *new_token = (t_token *)malloc(sizeof(t_token));
        if (new_token == NULL)
        {
            perror("Memory allocation failed");
            exit(1);
        }
        if(word)
        {
            new_token->arg = word;
            new_token->i = word_len;
            new_token->token = token;
            new_token->next = NULL;
        }
        if (head == NULL)
        {
            head = new_token;
            current = head;
        }
        else
        {
            current->next = new_token;
            current = current->next;
        }
        i = j;
    }
    return head;
}


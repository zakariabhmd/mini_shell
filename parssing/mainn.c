/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 21:56:37 by atoukmat          #+#    #+#             */
/*   Updated: 2023/11/12 05:21:45 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../mini_shell.h"

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
		free(current->program);
		free_args(current->args);
		temp = current;
		current = current->next;
		free(temp);
	}
}

void print_commands(t_proc *cmds)
{
    t_proc *current;
    char **args;
    int i = 0;
    current = cmds;
    while (current != NULL)
	{
        ft_putstr_fd("Command Program: ",1);
        ft_putstr_fd(cmds->program,1);
        write(1,"\n",1);
        ft_putstr_fd("Command Arguments:\n",1);
        args = current->args;
        i = 0;
        while (args && args[i])
		{
            printf("shish => %d\n",i);
            ft_putstr_fd(args[i],1);
            write(1,"\n",1);
            i++;
        }
        // t_red *redir = current->redir;
        // while (redir != NULL)
		// {
        //     printf("Redirection Type: ");
        //     if (redir->type == REDIR_IN)
        //         printf("<\n");
        //     else if (redir->type == REDIR_OUT)
        //         printf(">\n");
        //     else if (redir->type == D_REDIR_IN)
        //         printf("<<\n");
        //     else if (redir->type == D_REDIR_OUT)
        //         printf(">>\n");
        //     printf("Redirection File: %s\n", redir->file);

        //     redir = redir->next;
        // }
        printf("\n");
        current = current->next;
    }
    // exit(0);
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

void print_env(t_env *l_env)
{
    t_env *current = l_env;

    while (current != NULL)
	{
        printf("Position: %d, Length: %d, Argument: %s\n", current->pos, current->len, current->arg);
        current = current->next;
    }
}

t_env *local_env(char **env)
{
    t_env *head = NULL;
    t_env *tail = NULL;
    int i = 0;

    while (env[i] != NULL)
	{
        char *env_var = env[i];
        t_env *new_node = (t_env *)malloc(sizeof(t_env));
        if (new_node == NULL)
		{
            perror("malloc");
            exit(1);
        }
        new_node->arg = ft_strdup(env_var);
        new_node->pos = i;
        new_node->len = ft_strlen(env_var);
        new_node->next = NULL;
        new_node->prev = tail;
        if (tail != NULL)
            tail->next = new_node;
        else
            head = new_node;
        tail = new_node;
        i++;
    }
    return head;
}

size_t list_length(t_proc *cmds)
{
    size_t counter = 0;
    t_proc *head = cmds;
    while (head)
    {
        counter++;
        head = head->next;
    }
    return counter;
}

char **strdup_env(char **env)
{
    char **tmp;
    int len = 0;
    int i = 0;

    if (!env)
        return NULL;
    while (env[len])
        len++;
    tmp = ft_malloc((sizeof(char *) * len + 1),NULL,ALLOC,NULL);
    while (i < len)
    {
        tmp[i] = ft_strdup(env[i]);
        i++;
    }
    tmp[i] = NULL;
    return tmp;
}

void free_savage(t_savage *savage, int count)
{
    int i = 0;
    int j = 0;
    while ( i < count)
    {
        free(savage[i].first_arg);
        while ( savage[i].agrs && savage[i].agrs[j])
        {
            free(savage[i].agrs[j]);
            j++;
        }
        free(savage[i].agrs);
        j = 0;
        while(savage[i].env && savage[i].env[j])
        {
            free(savage[i].env[j]);
            j++;
        }
        free(savage[i].env);
        i++;
    }
    free(savage);
}

void handle_merge(char *input, t_proc *cmds, char **env)
{
	t_cmds cmd;
    if (!cmds || !env)
        return;
    int commands_count = list_length(cmds);
    if (commands_count == 0)
        return;
    t_savage *savage = ft_malloc((sizeof(t_savage) * commands_count),NULL,ALLOC,NULL);
    if (!savage)
        return;
    int idx = 0;
    t_proc *head = cmds;
    while (head)
     {
        savage[idx].count = commands_count;
        savage[idx].first_arg = ft_strdup(head->program);
        savage[idx].agrs = strdup_env(head->args);
        savage[idx].env = strdup_env(env);
        head = head->next;
        idx++;
    }
    if (savage->count == 1)
        check_command(savage);
     else
        multipale_cmds(input, savage, &cmd);
}
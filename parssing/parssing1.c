/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 22:12:14 by atoukmat          #+#    #+#             */
/*   Updated: 2023/11/12 05:22:18 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"
#include <string.h>

char *expand(char *str, t_env *env)
{
    t_env *cur = env;
    // print_env(l_env);
    while (cur)
    {
        char *env_arg = cur->arg;
        if (ft_strncmp(str, env_arg, ft_strlen(str) - 1) == 0)
            return ft_strdup(env_arg + ft_strlen(str) + 1);
        cur = cur->next;
    }
    return NULL;
}

char *expand_inside_dq(const char *str, t_env *env)
{
    int i = 0;
    char *expanded_str = ft_strdup(str);

    while (expanded_str[i] != '\0')
    {
        if (expanded_str[i] == '$')
        {
            int j = i + 1;
            while (ft_isalnum(expanded_str[j]))
                j++;

            if (j > i + 1)
            {
                char env_var[j - i];
                ft_strlcpy(env_var, &expanded_str[i + 1], j - i);
                env_var[j - i] = '\0';
                char *expanded = expand(env_var, env);

                if (expanded)
                {
                    char *new_str = (char *)malloc(ft_strlen(expanded_str) - ft_strlen(env_var) + ft_strlen(expanded) + 1);
                    if (new_str == NULL)
                    {
                        perror("Memory allocation failed");
                        exit(1);
                    }
                    ft_strlcpy(new_str, expanded_str, i + 1);
                    ft_strlcat(new_str, expanded, ft_strlen(new_str) + ft_strlen(expanded) + 1);
                    ft_strlcat(new_str, expanded_str + j, ft_strlen(new_str) + ft_strlen(expanded) + 1);
                    free(expanded_str);
                    expanded_str = new_str;
                    i += ft_strlen(expanded) - 1;
                    free(expanded);
                }
                else
                {
                    char *new_str = (char *)malloc(ft_strlen(expanded_str) - (j - i) + 1);
                    if (new_str == NULL)
                    {
                        perror("Memory allocation failed");
                        exit(1);
                    }
                    ft_strlcpy(new_str, expanded_str, i + 1);
                    ft_strlcat(new_str, expanded_str + j, ft_strlen(new_str) + ft_strlen(expanded_str + j) + 1);
                    free(expanded_str);
                    expanded_str = new_str;
                    i -= 1;
                }

            }
        }
        i++;
    }

    return expanded_str;
}
char **get_args(t_token *tokens, t_env *env)
{
    int arg_count = 0;
    t_token *current = tokens;
    while (current != NULL && current->token != PIPE_LINE)
    {
        if (current->token != WHITE_SPACE)
        {
            arg_count++;
        }
        current = current->next;
    }
    if (arg_count == 0)
        return NULL;
    char **args = (char **)malloc((arg_count + 1) * sizeof(char *));
    if (args == NULL)
    {
        perror("Memory allocation failed");
        exit(1);
    }
    int i = 0;
    current = tokens;
    int c = 0;
    int k = 0;
    while (current && current->token != PIPE_LINE)
    {
        if (current->token != WHITE_SPACE)
        {
            c = 1;
            char *arg = ft_strdup(current->arg);
            if (arg == NULL)
            {
                perror("Memory allocation failed");
                k = 0;
                while (k < i)
                {
                    free(args[k]);
                    k++;
                }
                free(args);
                exit(1);
            }
            if (current->token == DOUBLE_QUOTE)
            {
                char *expanded = expand_inside_dq(arg, env);
                args[i] = expanded;
                free(arg);
            }
            else if (current->token == ENV)
            {
                printf("KKK\n");
                if (arg[1] == '\0')
                    args[i] = ft_strdup("$");
                else
                {
                    char *expanded = expand(arg + 1, env);
                    args[i] = expanded;
                }
                free(arg);
            }
            else
                args[i] = arg;
            i++;
        }
        current = current->next;
    }
    if (c == 0)
    {
        free(args);
        return NULL;
    }
    args[arg_count] = NULL;
    return args;
}


void free_args(char **args)
{
    char **current = args;
    while (*current != NULL)
    {
        free(*current);
        current++;
    }
    free(args);
}

t_red	*ft_lstnew(char *file, type_token type)
{
	t_red	*node;

	node = malloc(sizeof(t_red));
	if (!node)
		return (0);
	node->file = file;
    node->type = type;
	node->next = NULL;
	return (node);
}

t_red	*ft_lstlast(t_red *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_red **lst, t_red *new)
{
	t_red	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}

t_red *get_red_linked_list(char **args)
{
    t_red *list_of_red = NULL;

    int i = 0;
    while (args[i])
    {
        if (!ft_strcmp(args[i], "<<"))
        {
            ft_lstadd_back(&list_of_red, ft_lstnew(args[i + 1], D_REDIR_IN));
            args[i] = ft_strdup("Z");
            args[i + 1] = ft_strdup("Z");
            i++;
        }
        else if (!ft_strcmp(args[i], ">>"))
        {
            ft_lstadd_back(&list_of_red, ft_lstnew(args[i + 1], D_REDIR_OUT));
            args[i] = ft_strdup("Z");
            args[i + 1] = ft_strdup("Z");
            i++;
        }
        else if (!ft_strcmp(args[i] , "<") )
        {
            ft_lstadd_back(&list_of_red, ft_lstnew(args[i + 1], REDIR_IN));
            args[i] = ft_strdup("Z");
            args[i + 1] = ft_strdup("Z");
            i++;
        }
        else if (!ft_strcmp(args[i], ">"))
        {
            ft_lstadd_back(&list_of_red, ft_lstnew(args[i + 1], REDIR_OUT));
            args[i] = ft_strdup("Z");
            args[i + 1] = ft_strdup("Z");
            i++;
        }

        i++;
    }
    return (list_of_red);
}

void    print_red_list(t_red *head)
{
    t_red *curr = head;
    while (curr)
    {
        printf("-----> %s %d\n", curr->file, curr->type);
        curr = curr->next;
    }
}

char **get_command_args(char **args)
{
    char **res = NULL;
    int count = 0;
    int i = 0;
    while (args[i])
    {
        if (ft_strcmp(args[i], "Z"))
            count++;
        i++;
    }
    res = malloc(sizeof(char *) * count + 1);
    i = 0;
    int j = 0;
    while (args[i])
    {
        if (ft_strcmp(args[i], "Z"))
        {
            res[j] = args[i];
            j++;
        }
        i++;
    }
    res[j] = NULL;
    // j = 0;
    // while (args[j])
    // {
    //     free(args[j]);
    //     j++;
    // }
    // free(args);
    return (res);
}

// t_proc *parsing(t_token *tokens,t_env *env)
// {
//     t_proc *head = NULL;
//     t_proc *current = NULL;
//     t_token *token = tokens;
//     t_token *prev_token = NULL;

//     t_red *red = NULL;///

//     head->program = NULL;
//     head->args = NULL;
//     head->redir =  NULL;
//     printf("Shite\n");
//     while (token != NULL )
//     {
//         if (token->token == PIPE_LINE)
//         {
//             t_proc *new_proc = (t_proc *)malloc(sizeof(t_proc));
//             if (new_proc == NULL)
//             {
//                 perror("Memory allocation failed");
//                 exit(1);
//             }
//             new_proc->args = get_args(tokens,env);
//             // red = get_red_linked_list(new_proc->args);
//             // new_proc->redir = red;
//             // new_proc->args = get_command_args(new_proc->args);
//             new_proc->program = ft_strdup(new_proc->args[0]);
//             new_proc->next = NULL;
//             if (head == NULL)
//             {
//                 head = new_proc;
//                 current = head;
//             }
//             else
//             {
//                 current->next = new_proc;
//                 current = current->next;
//             }
//             // if (prev_token != NULL)
//             // {
//             //     free_tokens(prev_token);
//             //     free_args(new_proc->args);
//             // }
//             tokens = token->next;;
//         }
//         prev_token = token;
//         token = token->next;
//     }
//     // printf("token (%s)\n", token->arg);
//     t_proc *new_proc = (t_proc *)malloc(sizeof(t_proc));
//     if (new_proc == NULL)
//     {
//         perror("Memory allocation failed");
//         exit(1);
//     }
//     printf("khobza\n");
//     new_proc->args = get_args(tokens,env);
//     int idx = 0;
//     while(new_proc->args[idx] != NULL)
//     {
//         printf("%s\n",new_proc->args[idx]);
//         idx++;

//     }

//     if(new_proc->args == NULL)
//         return( NULL);
//     // printf("hada arg %s\n", new_proc->args[0]);
//     // red = get_red_linked_list(new_proc->args);
//     // new_proc->redir = red;
//     // new_proc->args = get_command_args(new_proc->args);
//     new_proc->program = ft_strdup(new_proc->args[0]);
//     new_proc->next = NULL;
//     if (head == NULL)
//         head = new_proc;
//      else
//         current->next = new_proc;
//     return head;
// }

t_proc *parsing(t_token *tokens,t_env *env)
{
    t_proc *head = NULL;
    t_proc *current = NULL;
    t_token *token = tokens;
    t_token *prev_token = NULL;

    t_red *red = NULL;

    while (token != NULL)
    {
        if (token->token == PIPE_LINE)
        {
            t_proc *new_proc = (t_proc *)malloc(sizeof(t_proc));
            if (new_proc == NULL)
            {
                perror("Memory allocation failed");
                exit(1);
            }
            new_proc->args = get_args(tokens,env);
            if(new_proc->args == NULL)
                return(NULL);
            // red = get_red_linked_list(new_proc->args);
            // new_proc->redir = red;
            // new_proc->args = get_command_args(new_proc->args);
            new_proc->program = ft_strdup( new_proc->args[0]);
            new_proc->next = NULL;
            if (head == NULL)
            {
                head = new_proc;
                current = head;
            }
            else
            {
                current->next = new_proc;
                current = current->next;
            }
            // if (prev_token != NULL)
            // {
            //     free_tokens(prev_token);
            //     free_args(new_proc->args);
            // }
            tokens = token->next;;
        }
        prev_token = token;
        token = token->next;
    }
    t_proc *new_proc = (t_proc *)malloc(sizeof(t_proc));
    if (new_proc == NULL)
    {
        perror("Memory allocation failed");
        exit(1);
    }
    new_proc->args = get_args(tokens,env);
    if(new_proc->args == NULL)
        return(NULL);
    // red = get_red_linked_list(new_proc->args);
    // new_proc->redir = red;
    // new_proc->args = get_command_args(new_proc->args);
    new_proc->program = ft_strdup( new_proc->args[0]);
    new_proc->next = NULL;
    if (head == NULL)
        head = new_proc;
     else
        current->next = new_proc;
    return head;
}
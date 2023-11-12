/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 21:57:05 by atoukmat          #+#    #+#             */
/*   Updated: 2023/11/12 01:51:37 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL
# define MINI_SHELL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./libft/libft.h"
#include "../ft_mallocc/ft_malloc.h"


typedef enum {
    BREAK,
    WHITE_SPACE,
    NEW_LINE,
    SINGLE_QUOTE,
    DOUBLE_QUOTE,
    ESCAPE,
    ENV,
    PIPE_LINE,
    REDIR_IN,
    REDIR_OUT,
    D_REDIR_IN,
    D_REDIR_OUT,
} type_token;

typedef struct s_env {
    char *arg;
    int pos;
    int len;
    struct s_env *next;
    struct s_env *prev;
} t_env;

typedef struct s_token {
    int i;
    char *arg;
    type_token token;
    struct s_token *prev;
    struct s_token *next;
} t_token;

typedef struct s_red {
    int red;
    char *file;
    type_token type;
    struct s_red *next;
} t_red;

typedef struct s_proc {
    char *program;
    char **args;
    t_red *redir;
    struct s_proc *next;
} t_proc;

// typedef struct s_savage {
// 	char	**command;
// 	char	**agrs;
// 	char	**env;
// 	char	*first_arg;
// 	int		exit_status;
// 	int		count;
// 	int		binary;
// 	int		exit_prev;
// }t_savage;

void free_tokens(t_token *tokens);
void free_procs(t_proc *procs) ;
void print_commands(t_proc *cmds) ;
void print_token(t_token *token) ;
void print_tokens(t_token *tokens) ;
char **get_args(t_token *tokens,t_env *env) ;
void free_args(char **args) ;
t_proc *parsing(t_token *tokens,t_env *env) ;
int syntax_checker(t_token *tokens) ;
type_token get_type(char c) ;
t_token *get_tokens(char *input) ;
void	free_tokens(t_token *tokens);
void	free_procs(t_proc *procs);
void print_commands(t_proc *cmds);
void	print_token(t_token *token);
void	print_tokens(t_token *tokens);
void print_env(t_env *l_env);
t_env *local_env(char **env);
size_t list_length(t_proc *cmds);
char	**strdup_env(char **env);
void handle_merge(char *input, t_proc *cmds , char **env);

#endif
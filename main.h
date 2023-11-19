/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 05:14:00 by atoukmat          #+#    #+#             */
/*   Updated: 2023/11/15 20:07:17 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "mini_shell.h"
# include "minishell.h"

typedef struct s_exp_var
{
	char	*expanded_str;
	int		i;
	int		j;
	char	*exit_status_str;
	char	*new_str;
	char	*env_var;
	char	*expanded;

}t_exp_var;

typedef struct s_args
{
	char				**agrs;
	char				*first_arg;
}						t_args;

typedef struct s_savage
{
	t_args				*cmd;
	char				**command;
	char				**agrs;
	char				**env;
	char				*first_arg;
	char				*pars;
	int					exit_status;
	int					count;
	int					binary;
	int					exit_prev;
	int					fd;
	int					fd0;
	struct sigaction	minisig;
}						t_savage;

typedef struct s_cmds
{
	pid_t				pid;
	pid_t				top;
	int					fd[2];
	int					stdi;
	int					stdo;
	int					i;
}						t_cmds;

typedef struct t_data
{
	char				**dst;
	int					index;
	int					count;
	char				**dst_two;
}						t_data;

typedef struct s_merge_var
{
	t_cmds				cmd;
	int					commands_count;
	t_savage			*savage;
	int					idx;
	int					i;
}						t_merge_var;

typedef enum s_type_token
{
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
}					t_type_token;

typedef struct s_env
{
	char			*arg;
	int				pos;
	int				len;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

typedef struct s_token
{
	int				i;
	char			*arg;
	t_type_token	token;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_red
{
	int				red;
	char			*file;
	t_type_token	type;
	struct s_red	*next;
}					t_red;

typedef struct s_proc
{
	char			*program;
	char			**args;
	t_red			*redir;
	struct s_proc	*next;
}					t_proc;

typedef struct s_var_exapnd
{
	int				i;
	char			*expanded_str;
	char			*env_var;
	char			*expanded;
	char			*new_str;
	int				j;
}					t_var_expand;

typedef struct s_syntax_var
{
	t_token			*current;
	t_token			*prev;
}					t_syntax_var;

typedef struct s_tokens_var
{
	t_token			*head;
	t_token			*current;
	int				str_len;
	int				i;
	char			c;
	t_type_token	token;
	int				j;
	char			quote;
	int				word_len;
	char			*word;
	t_token			*new_token;
}					t_tokens_var;

typedef struct s_var_args
{
	int				arg_count;
	t_token			*current;
	char			**args;
	int				i;
	int				c;
	int				k;
	char			*arg;
	char			*expanded;

}					t_var_args;

typedef struct s_var_pars
{
	t_proc			*head;
	t_proc			*current;
	t_token			*token;
	t_token			*prev_token;
	t_red			*red;
	t_proc			*new_proc;
}					t_var_pars;

typedef struct s_env_var
{
	t_env			*head;
	t_env			*tail;
	int				i;
	char			*env_var;
	t_env			*new_node;

}					t_env_var;

typedef struct s_main
{
	char		*input;
	t_token		*tokens;
	t_proc		*cmds;
	t_env		*l_env;
	char		**my_env;
	t_savage	*savage;
}				t_main;

t_token				*get_tokens(char *input, t_savage *savage);
int					quote_token(t_tokens_var *var, char *input, \
								t_savage *savage);
char				**lenv_2_env(t_env *lenv);
void				free_l_env(t_env *tokens);
void				free_tokens(t_token *tokens);
void				free_procs(t_proc *procs);
void				print_commands(t_proc *cmds);
void				print_token(t_token *token);
void				print_tokens(t_token *tokens);
char				**get_args(t_token *tokens, t_env *env, int exit_status);
void				free_args(char **args);
t_proc				*parsing(t_token *tokens, t_env *env, int exit_status);
int					syntax_checker(t_token *tokens);
t_type_token		get_type(char c);
void				free_tokens(t_token *tokens);
void				free_procs(t_proc *procs);
void				print_commands(t_proc *cmds);
void				print_token(t_token *token);
void				print_tokens(t_token *tokens);
void				print_env(t_env *l_env);
t_env				*local_env(char **env);
size_t				list_length(t_proc *cmds);
char				**strdup_env(char **env);
void				env_token(t_tokens_var *var, char *input);
void				dir_token(t_tokens_var *var, char *input);
void				handel_norm(t_var_args *var);
void				double_quate(t_var_args *var, t_env *env, int exit_status);
void				dollar_sing(t_var_args *var, t_env *env, int exit_status);
void				counting_args(t_var_args *var, t_token *tokens);
void				pre_set_args(t_var_args *var, t_token *tokens);
char				*expand_1(char *str, t_env *env, int exit_status);
char				*expand_inside_dq(const char *str, t_env *env, \
									int exit_status);
char				*expand(char *str, t_env *env, int exit_status);
void				expand_dont_exist(t_exp_var *var);
int					count_pipe(char **arg);
int					echo_printer(char **arg, t_savage *savage);
int					pwd_com(void);
char				*get_env(t_savage *savage, char *arg);
void				env_cleaner(char *args, char **env);
int					ft_expt(t_savage *savage);
int					ft_strncmp_res(char *s1, char *s2, int len);
int					export(t_savage *savage, char *arg);
char				**strdup_env(char **env);
int					environment(t_savage *savage, char **var);
char				*bs_parse(char *str, int bs_check);
char				**renew_env(char **var, char **env, int pos);
int					ft_error(char *msg, char *bin);
void				free_env(char **str);
char				*search_bin(t_savage *savage, char **path);
char				*generate_absolute_path(char *path, char *bin);
int					bulttin_check(t_savage *savage);
char				*search_n_pwd(t_savage *savage);
char				*get_path(t_savage *savage);
void				to_exit(t_savage *savage);
void				sh_cleaner(t_savage *savage);
void				exev_args(t_savage *savage);
int					check_redirections(t_savage *savage);
char				*expansion(t_savage *savage, char *commands);
char				**lexical_analysis(char *input, int c);
char				**set_args(char *str);
char				**check_command(t_savage *savage);
void				check_one_command(t_savage *savage);
int					bulttin_check(t_savage *savage);
int					check_valid_name(char *var);
int					invalid_export(t_savage *savage, char *var, char *cmd);
char				*write_q_and_bslash(char *s);
void				get_olddir(t_savage *savage, char *oldpwd);
void				dir_changer_err(t_savage *savage, char *path);
int					cd(t_savage *savage);
void				set_path(t_savage *savage, char *path, char *key);
int					unset(t_savage *savage);
int					invalid_char(char *var, int i);
char				*update_lastarg(char **arg);
char				**multipale_cmds(char *input, t_savage *savage,
						t_cmds *cmd);
void				ft_get_args(t_savage *savage, int i);
void				signal_check(int sig);
void				waitsignal(int sig);
char				**multipale(t_savage *savage, t_cmds *cmd);
char				*append_pwd(char *value);
char				*ft_strcpy(char *dest, char *src);
int					count_bs(char *str, int c);
int					check_backslash(char *input, int i);
int					separ(char input, int c);
char				**check_env(char **env);
char				**join_tables(char **table1, char **table2);
int					is_redirect(char *red);
int					count_redirection_and_files(char **args);
int					count_argment_without_red(char **args);
int					red_input(t_savage *savage, int i);
int					red_append(t_savage *savage, int i);
char				**sort_args(char **oldargs);
int					herdoc(t_savage *savage, int i);
int					valide_redirection(t_savage *savage, char *str);
int					write_env(t_savage *savage);
void				path_search(char **env);
int					environment_0(t_savage *savage, char **var);
void				duplicate_fd(t_cmds *cmd);
void				duplicate1_fd(t_cmds *cmd);
void				signl(int signal);
void				fill_zakaria_struct(t_merge_var *var, char **env, \
										t_proc *cmds);
char				**handle_merge(char *input, t_proc *cmds, char **my_env, \
								t_savage *savage);
void				set_main(t_main *m, char **env);

#endif

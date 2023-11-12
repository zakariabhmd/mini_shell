/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 05:09:07 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/12 06:56:58 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "./parssing/libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <dirent.h>
# include <signal.h>
# include <fcntl.h>
# include "./ft_mallocc/ft_malloc.h"

# include "./parssing/minishell.h"

typedef struct s_savage {
	char	**command;
	char	**agrs;
	char	**env;
	char	*first_arg;
	char	*pars;
	int		exit_status;
	int		count;
	int		binary;
	int		exit_prev;
}t_savage;

typedef struct s_cmds{
	pid_t	pid;
	pid_t	top;
	int		fd[2];
	int		stdi;
	int		stdo;
	int		i;
}t_cmds;

typedef struct t_data
{
	char	**dst;
	int		index;
	int		count;
	char	**dst_two;
}	t_data;

int		count_pipe(char **arg);
int		echo_printer(char **arg);
int		pwd_com(void);
char	*get_env(t_savage *savage, char *arg);
void	env_cleaner(char *args, char **env);
int		ft_expt(t_savage *savage);
int		ft_strncmp_res(char *s1, char *s2, int len);
int		export(t_savage *savage, char *arg);
char	**strdup_env(char **env);
int		environment(t_savage *savage, char **var);
char	*bs_parse(char *str, int bs_check);
char	**renew_env(char **var, char **env, int pos);
int		ft_error(char *msg, char *bin);
void	free_env(char **str);
char	*search_bin(t_savage *savage, char **path);
char	*generate_absolute_path(char *path, char *bin);
int		bulttin_check(t_savage *savage);
char	*search_n_pwd(t_savage *savage);
char	*get_path(t_savage *savage);
void	to_exit(t_savage *savage);
void	sh_cleaner(t_savage *savage);
void	exev_args(t_savage *savage);
int		check_redirections(t_savage *savage);
char	*expansion(t_savage *savage, char *commands);
char	**lexical_analysis(char *input, int c);
char	**set_args(char *str);
void	check_command(t_savage *savage);
void	check_one_command(t_savage *savage);
int		bulttin_check(t_savage *savage);
int		check_valid_name(char *var);
int		invalid_export(t_savage *savage, char *var, char *cmd);
char	*write_q_and_bslash(char *s);
void	get_olddir(t_savage *savage, char *oldpwd);
void	dir_changer_err(t_savage *savage, char *path);
int		cd(t_savage *savage);
void	set_path(t_savage *savage, char *path, char *key);
int		unset(t_savage *savage);
int		invalid_char(char *var, int i);
char	*update_lastarg(char **arg);
void	multipale_cmds(char *input, t_savage *savage, t_cmds *cmd);
void	ft_get_args(t_savage *savage, int i);
void	waitsignal(int sig);
void	multipale(t_savage *savage, t_cmds *cmd);
char	**sort_args(char **oldargs);
int		valide_redirection(t_savage *savage, char *str);
int		red_input(t_savage *savage, int i);
int		red_append(t_savage *savage, int i);
int		is_redirect(char *red);
char	**join_tables(char **table1, char **table2);
int		count_redirection_and_files(char **args);
int		count_argment_without_red(char **args);
char	*append_pwd(char *value);
int		count_bs(char *str, int c);
int		counter(char *input, int c);
int		separ(char input, int c);
int		check_backslash(char *input, int i);
char	*ft_strcpy(char *dest, char *src);
int		herdoc(t_savage *savage, int i);

#endif

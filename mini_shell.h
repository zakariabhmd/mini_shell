/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 05:09:07 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/02 20:22:05 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

#include "./libft/libft.h"
#include <unistd.h>
#include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <dirent.h>

typedef struct s_savage {
	char *command;
	char **agrs;
	char **env;
	char	*first_arg;
	int	exit_status;
	int	count;
	int	binary;
}t_savage;

void free_2d(char **str);
int	ft_strcmp(char *s1, char *s2);
int	echo_printer(char **arg);
int	pwd_com(void);
int	ft_exit(t_savage *savage);
char	*get_env(t_savage *savage, char *arg);
void	claner_env(char *arg, char **env);
int	ft_expt(t_savage *savage);
int check_name(char *arg);
int ft_strncmp_res(char *s1, char *s2, int len);
int invalide_export(t_savage *savage, char *arg, char *cmd);
int	export(t_savage *savage, char *arg);
char **strdup_env(char **env);
char    *write_q_back(char *str);
int	envirment(t_savage *savage, char **arg);
char    *bs_parse(char *str, int bs_check);
char    **new_env(char **arg, char **env, int pos);
int	ft_error(char *msg, char *bin);
int	unset(t_savage *savage);
void	free_env(char **str);
char	*search_bin(t_savage *savage, char **path);
char	*generate_absolute_path(char *path, char *bin);
int	bulttin_check(t_savage *savage);
char	*search_n_pwd(t_savage *savage);
char	*get_path(t_savage *savage);
void	to_exit(t_savage *savage);
void	sh_cleaner(t_savage *savage);
void exev_args(t_savage *savage);

#endif
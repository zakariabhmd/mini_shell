/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 05:09:07 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/10/29 14:47:37 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

#include "./libft/libft.h"
#include <unistd.h>
#include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_savage {
	char *command;
	char **agrs;
	char **env;
	int	exit_status;
}t_savage;

void free_2d(char **str)ñ
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
void    free_env(char **str);
int invalid_char(char *arg, int i);

#endif
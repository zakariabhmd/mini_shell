/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 05:09:07 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/10/18 13:38:29 by zbabahmi         ###   ########.fr       */
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
}t_savage;

void free_2d(char **str);
int	ft_strcmp(char *s1, char *s2);
int	echo_printer(char **arg);
int	pwd_com(void);

#endif
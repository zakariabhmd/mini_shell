/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 21:13:14 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/15 18:47:51 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	duplicate_fd(t_cmds *cmd)
{
	cmd->i = 0;
	cmd->stdi = dup(0);
	cmd->stdo = dup(1);
}

void	duplicate1_fd(t_cmds *cmd)
{
	dup2(cmd->stdi, 0);
	dup2(cmd->stdo, 1);
}

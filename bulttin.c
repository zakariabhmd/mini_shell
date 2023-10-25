/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulttin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 10:13:29 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/10/20 13:24:11 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

// int	bulttin_check(t_savage *savage)
// {
// 	int	ret;

// 	ret = 0;
// 	if (ft_strcmp(savage->command, "exit"))
// 		ret = ft_exit(savage->command);
// 	else if (ft_strcmp(savage->command, "echo"))
// 		ret = echo_printer(savage->command + 1);
// 	else if (ft_strcmp(savage->command, "cd"))
// 		ret = chdir(savage->command + 1);
// 	else if (ft_strcmp(savage->command, "pwd"))
// 		ret = pwd_com();
// 	// else if (ft_strcmp(savage->command, "export"))
// 	// 	ret = export(savage->command);
// 	return (ret);
// }
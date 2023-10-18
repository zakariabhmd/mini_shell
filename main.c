/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 05:08:55 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/10/18 10:58:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"
#include <stdio.h>

int main (int ac, char **av, char **env)
{
	
	t_savage *savage = ft_calloc(1, sizeof(t_savage));
	char *line;
	while (1){
		line = readline("minishell-> ");
		if (line){
			savage->command = ft_strdup(line);
			int idx = 0;
			char **holder;
			char *holder2;
			while (env[idx])
			{
				holder = ft_split(env[idx], '=');
				if (ft_strncmp(holder[0], "PATH", ft_strlen(holder[0])) == 0) {
					holder2 = ft_strdup(holder[1]);
					free_2d(holder);
					break;
				}
				free_2d(holder);
				idx++;
			}
			char **path = ft_split(holder2, ':');
			char *command;
			idx = 0;
			while (path[idx]) {
				command = ft_strjoin(path[idx], "/");
				command = ft_strjoin(command, savage->command);
				// printf("%s\n"/, command);
				if (access(command, R_OK) == 0){
					execve(command, savage->agrs, env);
					perror("exec");
				}
				idx++;
			}
		}
	}
}
// 	savage[0].command = ft_strdup("ls");
// 	// savage[0].agrs = ft_split("grep main main.c", ' ');

// 	return (0);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 05:08:55 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/10/09 06:25:53 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"
#include <stdio.h>

int main (int ac, char **av, char **env) {

	t_savage *savage = ft_calloc(1, sizeof(t_savage));
	savage[0].command = ft_strdup("grep");
	savage[0].agrs = ft_split("grep main main.c", ' ');

	int idx = 0;
	char **holder;
	char *holder2;
	while (env[idx]) {
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
		command = ft_strjoin(command, savage[0].command);
		// printf("%s\n"/, command);
		if (access(command, R_OK) == 0){
			execve(command, savage[0].agrs, env);
			perror("fdas");
		}
		idx++;
	}
	// execv("/bin");
	return (0);
}
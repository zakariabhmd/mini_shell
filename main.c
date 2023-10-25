/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 05:08:55 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/10/25 04:46:58 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"
#include <stdio.h>

int	bulttin_check(t_savage *savage)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(savage->agrs[0], "exit"))
		exit(1);
	else if (ft_strcmp(savage->agrs[0], "echo"))
		ret = echo_printer(savage->agrs + 1);
	else if (ft_strcmp(savage->agrs[0], "cd"))
		ret = chdir(*savage->agrs + 1);
	else if (ft_strcmp(savage->agrs[0], "pwd"))
		ret = pwd_com();
	// else if (ft_strcmp(savage->command, "export"))
	// 	ret = export(savage->command);
	// else if(ft_strcmp(savage->agrs[0], "unsset"))
	return (ret);
}

int main (int ac, char **av, char **env)
{

	t_savage *savage = ft_calloc(1, sizeof(t_savage));
	char *line;
	while (1)
	{
		line = readline("minishell-> ");
		add_history(line);
		if (line){
			savage->command = ft_strdup(line);
			savage->agrs = ft_split(line, ' ');
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
			bulttin_check(savage);
			char **path = ft_split(holder2, ':');
			int status;
			pid_t pid = fork();
			if (pid == 0)
			{
				char *command;
				idx = 0;
				while (path[idx])
				{
					command = ft_strjoin(path[idx], "/");
					command = ft_strjoin(command, savage->command);
					if (access(command, R_OK) == 0){

						execve(command, savage->agrs, env);
						perror("exec");
					}
					idx++;
				}
			}
			waitpid(pid, &status, 0);
		}
	}
}
// 	savage[0].command = ft_strdup("ls");
// 	// savage[0].agrs = ft_split("grep main main.c", ' ');

// 	return (0);
// }
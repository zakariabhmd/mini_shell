/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 05:08:55 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/02 05:16:06 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"
#include <stdio.h>

int	ft_expt(t_savage *savage)
{
	int	test;

	test = 0;
	claner_env("_", savage->env);
	test = export(savage, NULL);
	return (test);
}

char	*lower(char *input)
{
	int		i;
	char	*output;
	char	*tmp;

	tmp = ft_strdup(input);
	output = ft_calloc(1, ft_strlen(tmp) + 1);
	i = 0;
	while (tmp[i])
	{
		output[i] = ft_tolower(tmp[i]);
		i++;
	}
	free(tmp);
	output[i] = '\0';
	return (output);
}

// int	env_exec(t_savage *savage)
// {
// 	char	*low;
// 	char	*backup;
// 	char	*path;

// 	low = lower(savage->agrs[0]);
// 	if (ft_strcmp(low, "env"))
// 	{
// 		path = get_path(savage);
// 		backup = ft_strjoin("_=", path);
// 		free(path);
// 		export(savage, backup);
// 		free(backup);
// 		free(low);
// 		return (envirment(savage, savage->env));
// 	}
// 	free(low);
// 	return(0);
// }

int	bulttin_check(t_savage *savage)
{
	int	ret;
	char	*backup;

	ret = 0;
	if (ft_strcmp(savage->agrs[0], "exit"))
		exit(1);
	else if (ft_strcmp(savage->agrs[0], "echo"))
		ret = echo_printer(savage->agrs + 1);
	else if (ft_strcmp(savage->agrs[0], "cd"))
		ret = chdir(*savage->agrs + 1);
	else if (ft_strcmp(savage->agrs[0], "pwd"))
		ret = pwd_com();
	else if (ft_strcmp(savage->agrs[0], "export"))
		ret = ft_expt(savage);
	else if(ft_strcmp(savage->agrs[0], "unset"))
		ret = unset(savage);
	// else
	// 	return (env_exec(savage));
	backup = update_lastarg(savage->agrs);
	export(savage, backup);
	free(backup);
	return (ret);
}

// int main (int ac, char **av, char **env)
// {

// 	t_savage *savage = ft_calloc(1, sizeof(t_savage));
// 	char *line;

// 	while (1)
// 	{
// 		line = readline("minishell-> ");
// 		add_history(line);
// 		if (line){
// 			savage->command = ft_strdup(line);
// 			savage->agrs = ft_split(line, ' ');
// 			int idx = 0;
// 			char **holder;
// 			char *holder2;
// 			while (env[idx])
// 			{
// 				holder = ft_split(env[idx], '=');
// 				if (ft_strncmp(holder[0], "PATH", ft_strlen(holder[0])) == 0) {
// 					holder2 = ft_strdup(holder[1]);
// 					free_2d(holder);
// 					break;
// 				}
// 				free_2d(holder);
// 				idx++;
// 			}
// 			// ft_pipe(savage);
// 			bulttin_check(savage);
// 			char **path = ft_split(holder2, ':');
// 			int status;
// 			pid_t pid = fork();
// 			if (pid == 0)
// 			{
// 				char *command;
// 				idx = 0;
// 				while (path[idx])
// 				{
// 					command = ft_strjoin(path[idx], "/");
// 					command = ft_strjoin(command, savage->command);
// 					if (access(command, R_OK) == 0){

// 						execve(command, savage->agrs, env);
// 						perror("exec");
// 					}
// 					idx++;
// 				}
// 			}
// 			waitpid(pid, &status, 0);
// 		}
// 	}
// }
// 	savage[0].command = ft_strdup("ls");
// 	// savage[0].agrs = ft_split("grep main main.c", ' ');

// 	return (0);
// }


int	main(int ac, char **av, char **env)
{
	t_savage savage;
	char	*store;
	int		fd;
	int		fd1;

	(void)av;
	if (ac == 2)
	{
		savage.input = NULL;
		savage.inst = NULL;
		savage.exit_status = 0;
		savage.test = 0;
		savage.env =strdup_env(env);
		// get
		store = ft_strdup("_=/bin/bash");
		export(&savage, store);
		free(store);
		fd = dup(1);
		fd1 = dup(0);
		while(1)
		{
			dup2(fd, 1);
			dup2(fd1, 0);
			savage.input = readline("minishell-> ");
			if (!savage.input)
			{
				free(savage.input);
				free_env(savage.env);
				exit(savage.exit_status);
			}
			else
			{
				savage.input = savage.parse;
				mini(savage.input, &savage);
			}
		}

	}
	else
		return (0);
}
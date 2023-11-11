/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 05:08:55 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/11 04:35:10 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"
#include <stdio.h>

int token_priority(char *line, int i, int token)
{
	int hold;

    hold = i;
    while (hold > 0 && line[hold] == ' ')
        hold--;
    if (token == '>' || token == '<')
    {
        if (hold > 0 && hold != i && (line[hold] == '>' || line[hold] == '<'))
            return (1);
        else
            return (0);
    }
    else
    {
        if (hold < 1 || line[hold] == ';' || line[hold] == '>' ||
            line[hold] == '<' || line[hold] == '|')
            return (1);
        else
            return (0);
    }
	return (0);
}

int invalid_err(t_savage *savage, char *input, int sep, int i)
{
	if (sep == ';')
		ft_error("syntax error near unexpected token `;'", NULL);
	else if (sep == '|')
		ft_error("syntax error near unexpected token `|'", NULL);
	else if (sep == '>' && input[i + 1] == '>')
		ft_error("syntax error near unexpected token `>>'", NULL);
	else if (sep == '<' && input[i + 1] == '<')
		ft_error("syntax error near unexpected token `<<'", NULL);
	else if (sep == '>')
		ft_error("syntax error near unexpected token `>'", NULL);
	else if (sep == '<')
		ft_error("syntax error near unexpected token `<<'", NULL);
	savage->exit_status = 2;
	return (1);
}

int check_after_pipe(char *input, int i)
{
	if (i - 2 >= 0 && *(input - 2) == '\\')
		return (0);
	while (*input && *input == ' ')
		input++;
	if (!*input)
		return (1);
	return (0);
}

int monitor_valide(t_savage *savage, char *input, int sep, int i)
{
	if (token_priority(input, i - 1, input[i]))
	{
		if (invalid_err(savage, input, sep, i))
			return (1);
		return (0);
	}
	else if (sep == '|' && check_after_pipe(&input[i + 1], i))
	{
		ft_error("syntax error: unexpected end of file", NULL);
		savage->exit_status = 2;
		return (1);
	}
	return (0);
}

int validate_input(char *input, t_savage *savage)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|' ||
			input[i] == '<' ||
			input[i] == '>' ||
			input[i] == ';')
		{
			if (monitor_valide(savage, input, input[i], i))
				return (0);
		}
		i++;
	}
	return (1);
}

void print_arr(char **arr)
{
	for(int i = 0; arr[i]; i++)
		printf("arr[%d]: %s\n", i, arr[i]);
}

void	get_args(t_savage *savage, int i)
{
	char	*exp;

	exp = expansion(savage, savage->command[i]);
	savage->agrs = set_args(exp);
	free(exp);
	if (savage->agrs[0])
		savage->first_arg = ft_strdup(savage->agrs[0]);
}

void	check_one_command(t_savage *savage)
{
	pid_t	pid;
	char	*path;
	char	*backup;

	path = get_path(savage);
	// printf("%s\n", path);
	pid = fork();
	if (pid == 0)
	{
		if (path == NULL)
		{
			ft_error(" command not found", savage->first_arg);
			exit(127);
		}
		if (execve(path, savage->agrs, savage->env) == -1)
		{
			perror("minishell: execve");
			exit(126);
		}
		// free(path);
	}
	signal(SIGINT, waitsignal);
	waitpid(pid, &savage->exit_status, 0);
	if (WIFEXITED(savage->exit_status))
		savage->exit_status = WEXITSTATUS(savage->exit_status);
	if (savage->exit_status == -1)
		ft_putchar_fd('\n', 1);
	backup = update_lastarg(savage->agrs);
	export(savage, backup);
	free(backup);
}

void	check_test(char *input, t_savage *savage, t_cmds *cmd)
{
	if (validate_input(input, savage))
	{
		savage->command = lexical_analysis(input, '|');
		savage->count = count_pipe(savage->command);
		if (savage->count == 0)
		{
			check_command(savage);
		}
		else if (savage->count)
		{
			multipale_cmds(savage, cmd);
		}
	}
	free(input);
}

int	main(int ac, char **av, char **env)
{
	t_cmds		cmd;
	t_savage	savage;
	char		*line;
	char		*str;
	int			fd;
	int			fd0;

	(void)ac;
	(void)av;
	if (ac == 1)
	{
		savage.exit_status = 0;
		savage.env = strdup_env(env);
		str = ft_strdup("_=/bin/bash");
		export(&savage, str);
		free(str);
		fd = dup(1);
		fd0 = dup(0);
		signal(SIGQUIT, signal_check);
		while (1)
		{
			dup2(fd, 1);
			dup2(fd0, 0);
			signal(SIGQUIT, signal_check);
			line = readline("minishell-> ");
			if (!line)
			{
				free(line);
				free(savage.env);
				exit(savage.exit_status);
			}
			add_history(line);
			savage.pars = parsing(line, &cmd);
			free(line);
			if(!savage.pars)
				savage.exit_status = 2;
			else
			{
				line = savage.pars;
				check_test(line, &savage, &cmd);
			}
		}
	}
	else
		return (0);
}

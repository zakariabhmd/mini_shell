/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulttin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 10:13:29 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/15 19:25:17 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"
#include "main.h"

int	ft_expt(t_savage *savage)
{
	int		test;

	test = 0;
	env_cleaner("_", savage->env);
	test = export(savage, NULL);
	return (test);
}

char	*lower(char *input)
{
	int		i;
	char	*output;
	char	*tmp;

	tmp = ft_strdup(input);
	output = ft_malloc(ft_strlen(tmp) + 1, NULL, ALLOC, NULL);
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

int	env_exec(t_savage *savage)
{
	char	*low;
	char	*path;
	char	*backup;

	low = lower(savage->agrs[0]);
	if (!(ft_strcmp(low, "env")))
	{
		return (environment(savage, savage->env));
	}
	return (0);
}

int	bulttin_check(t_savage *savage)
{
	int	ret;

	ret = 0;
	if (!(ft_strcmp(savage->agrs[0], "exit")))
		to_exit(savage);
	else if (!(ft_strcmp(savage->agrs[0], "echo")))
		ret = echo_printer(savage->agrs + 1, savage);
	else if (!(ft_strcmp(savage->agrs[0], "cd")))
		ret = cd(savage);
	else if (!(ft_strcmp(savage->agrs[0], "pwd")))
		ret = pwd_com();
	else if (!(ft_strcmp(savage->agrs[0], "export")))
		ret = ft_expt(savage);
	else if (!(ft_strcmp(savage->agrs[0], "unset")))
		ret = unset(savage);
	else
		return (env_exec(savage));
	return (ret);
}

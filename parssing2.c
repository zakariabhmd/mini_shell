/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:58:11 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/15 19:58:43 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "minishell.h"
#include <string.h>

size_t	env_size(t_env *cmds)
{
	size_t	counter;
	t_env	*head;

	counter = 0;
	head = cmds;
	while (head)
	{
		counter++;
		head = head->next;
	}
	return (counter);
}

char	**lenv_2_env(t_env *lenv)
{
	char	**env;
	t_env	*head;
	int		i;

	head = lenv;
	i = 0;
	env = ft_malloc(sizeof(char *) * env_size(lenv), NULL, ALLOC, NULL);
	while (head)
	{
		env[i] = ft_strdup(head->arg);
		head = head->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

char	*expand_1(char *str, t_env *env, int exit_status)
{
	t_env	*cur;
	char	*env_arg;

	cur = env;
	if (str[0] == '?')
		return (ft_itoa(exit_status));
	while (cur)
	{
		env_arg = cur->arg;
		if (ft_strncmp(str, env_arg, ft_strlen(str)) == 0
			&& env_arg[ft_strlen(str)] == '=')
			return (ft_strdup(env_arg + ft_strlen(str) + 1));
		cur = cur->next;
	}
	return (NULL);
}

char	*expand(char *str, t_env *env, int exit_status)
{
	t_env	*cur;
	char	*env_arg;

	cur = env;
	if (str[0] == '?')
		return (ft_itoa(exit_status));
	while (cur)
	{
		env_arg = cur->arg;
		if (ft_strncmp(str, env_arg, ft_strlen(str) - 1) == 0)
			return (ft_strdup(env_arg + ft_strlen(str)));
		cur = cur->next;
	}
	return (NULL);
}

void	expand_dont_exist(t_exp_var *var)
{
	var->new_str = (char *)ft_malloc((ft_strlen(var->expanded_str) - \
					(var->j - var->i) + 1), NULL, ALLOC, NULL);
	if (var->new_str == NULL)
	{
		perror("Memory allocation failed");
		exit(1);
	}
	ft_strlcpy(var->new_str, var->expanded_str, var->i + 1);
	ft_strlcat(var->new_str, var->expanded_str + var->j, ft_strlen(var->new_str)
		+ ft_strlen(var->expanded_str + var->j) + 1);
	free(var->expanded_str);
	var->expanded_str = var->new_str;
	var->i -= 1;
}

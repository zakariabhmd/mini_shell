/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:58:54 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/15 19:59:18 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "minishell.h"
#include <string.h>

void	expand_exist(t_exp_var *var)
{
	var->new_str = (char *)ft_malloc((ft_strlen(var->expanded_str) - \
					ft_strlen(var->env_var) + ft_strlen(var->expanded) + 1), \
					NULL, ALLOC, NULL);
	if (var->new_str == NULL)
	{
		perror("Memory allocation failed");
		exit(1);
	}
	ft_strlcpy(var->new_str, var->expanded_str, var->i + 1);
	ft_strlcat(var->new_str, var->expanded, ft_strlen(var->new_str)
		+ ft_strlen(var->expanded) + 1);
	ft_strlcat(var->new_str, var->expanded_str + var->j, ft_strlen(var->new_str)
		+ ft_strlen(var->expanded_str + var->j) + 1);
	free(var->expanded_str);
	var->expanded_str = var->new_str;
	var->i += ft_strlen(var->expanded) - 1;
}

void	exit_status_expand(t_exp_var *var, int exit_status)
{
	var->exit_status_str = ft_itoa(exit_status);
	var->new_str = (char *)ft_malloc((ft_strlen(var->expanded_str) - \
					(var->j - var->i) + ft_strlen(var->exit_status_str) + 1), \
					NULL, ALLOC, NULL);
	if (var->new_str == NULL)
	{
		perror("Memory allocation failed");
		exit(1);
	}
	ft_strlcpy(var->new_str, var->expanded_str, var->i + 1);
	ft_strlcat(var->new_str, var->exit_status_str, ft_strlen(var->new_str)
		+ ft_strlen(var->exit_status_str) + 1);
	ft_strlcat(var->new_str, var->expanded_str + var->j + 1,
		ft_strlen(var->new_str) + ft_strlen(var->expanded_str + var->j + 1)
		+ 1);
	var->expanded_str = var->new_str;
	var->i += ft_strlen(var->exit_status_str) - 1;
}

void	just_norm(t_exp_var *var, t_env *env, int exit_status)
{
	var->env_var = ft_malloc(sizeof(char) * (var->j - var->i), \
							NULL, ALLOC, NULL);
	ft_strlcpy(var->env_var, &var->expanded_str[var->i + 1], var->j - var->i);
	var->env_var[var->j - var->i] = '\0';
	var->expanded = expand(var->env_var, env, exit_status);
}

void	norm_lala(t_exp_var *var, t_env *env, int exit_status)
{
	var->j = var->i + 1;
	while (ft_isalnum(var->expanded_str[var->j]))
		var->j++;
	if (var->expanded_str[var->j] == '?' && (var->j == var->i + 1
			|| !ft_isalnum(var->expanded_str[var->j + 1])))
		exit_status_expand(var, exit_status);
	else if (var->j > var->i + 1)
	{
		just_norm(var, env, exit_status);
		if (var->expanded)
			expand_exist(var);
		else
			expand_dont_exist(var);
	}
}

char	*expand_inside_dq(const char *str, t_env *env, int exit_status)
{
	t_exp_var	*var;

	var = ft_malloc(sizeof(t_exp_var), NULL, ALLOC, NULL);
	var->i = 0;
	var->expanded_str = ft_strdup(str);
	while (var->expanded_str[var->i] != '\0')
	{
		if (var->expanded_str[var->i] == '$')
			norm_lala(var, env, exit_status);
		var->i++;
	}
	return (var->expanded_str);
}

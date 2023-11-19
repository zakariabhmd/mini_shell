/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 21:56:37 by atoukmat          #+#    #+#             */
/*   Updated: 2023/11/15 18:26:42 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"
#include "minishell.h"

void	print_env(t_env *l_env)
{
	t_env	*current;

	current = l_env;
	while (current != NULL)
	{
		printf("Position: %d, Length: %d, Argument: %s\n", current->pos,
			current->len, current->arg);
		current = current->next;
	}
}

void	fill_the_env(t_env_var *var)
{
	var->new_node = (t_env *)malloc(sizeof(t_env));
	if (var->new_node == NULL)
	{
		perror("malloc");
		exit(1);
	}
	var->new_node->arg = ft_strdup(var->env_var);
	var->new_node->pos = var->i;
	var->new_node->len = ft_strlen(var->env_var);
	var->new_node->next = NULL;
	var->new_node->prev = var->tail;
	if (var->tail != NULL)
		var->tail->next = var->new_node;
	else
		var->head = var->new_node;
}

t_env	*local_env(char **env)
{
	t_env_var	*var;

	var = ft_malloc(sizeof(t_env_var), NULL, ALLOC, NULL);
	var->head = NULL;
	var->tail = NULL;
	var->i = 0;
	while (env[var->i] != NULL)
	{
		var->env_var = env[var->i];
		fill_the_env(var);
		var->tail = var->new_node;
		var->i++;
	}
	return (var->head);
}

char	**strdup_env(char **env)
{
	char	**tmp;
	int		len;
	int		i;
	t_env	*head;

	len = 0;
	i = 0;
	if (!env)
		return (NULL);
	while (env[len])
		len++;
	tmp = ft_malloc((sizeof(char *) * len + 1), NULL, ALLOC, NULL);
	while (i < len)
	{
		tmp[i] = ft_strdup(env[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

void	free_savage(t_savage *savage, int count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < count)
	{
		free(savage[i].first_arg);
		while (savage[i].agrs && savage[i].agrs[j])
		{
			free(savage[i].agrs[j]);
			j++;
		}
		free(savage[i].agrs);
		j = 0;
		while (savage[i].env && savage[i].env[j])
		{
			free(savage[i].env[j]);
			j++;
		}
		free(savage[i].env);
		i++;
	}
	free(savage);
}

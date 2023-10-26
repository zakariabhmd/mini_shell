/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 06:02:47 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/10/26 06:02:47 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int ft_strncmp_res(char *s1, char *s2, int len)
{
	while(*s1 && *s2 && len)
	{
		if(*s1 != *s2)
			return(1);
		s1++;
		s2++;
		len--;
	}
	if(*s1 == *s2)
		return(0);
	return(1);
}

int invalid_char(char *arg, int i)
{
    if(arg[i] == '$' || arg[i] == '&' ||
                arg[i] == '@' || arg[i] == '!' ||
                arg[i] == ';' || arg[i] == ' ' ||
                arg[i] == '\"' || arg[i] == '\\' ||
                arg[i] == '-' ||
                (arg[i] == '\\' && arg[i + 1] != '_' && !ft_isdigit(arg[i])))
                return (1);
        return (0);
}

int check_name(char *arg)
{
    int i;

    i = 0;
    if (!*arg || ft_isdigit(*arg) || *arg == '=')
        return (0);
    while (arg[i] && arg[i] != '=')
    {
        if (invalid_char(arg, i))
            return (0);
        i++;
    }
    return (1);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;
	i = 0;

	while(src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	return(dest);
}

int invalide_export(t_savage *savage, char *arg, char *cmd)
{
    char *print_error;
    char *backup;
    int size;

    size = ft_strlen(arg);
    print_error = malloc(sizeof(char) * (size + 28));
    if (!print_error)
        return (0);
    backup = NULL;
    backup = ft_strjoin(" `", arg);
    if (!backup)
        return (free(print_error), 0);
    ft_strcpy(print_error, backup);
    free(backup);
    backup = ft_strjoin(print_error, "': not a valid identifier");
    if (!backup)
        return (free(print_error), 0);
    ft_strcpy(print_error, backup);
    free(backup);
    savage->exit_status = 1;
    // ft_error(print_error, cmd);
    free(print_error);
    return (1);
}

int     esc_char(char c)
{
	if (c == '$' || c == '\\' || c == '\"')
		return (1);
	return (0);
}

int count_char(char *str)
{
    int counter;
    int i;

    counter = 0;
    i = 0;
    while (str[i])
    {
        if(esc_char(str[i]))
            counter++;
        i++;
    }
    return (counter);
}

char    *write_q_back(char *str)
{
    char    *tmp;
    int     i;
    int     j;
    int     size;

    i = 0;
    j = 0;
    size = ft_strlen(str);
    tmp = malloc((sizeof(char) * (size + count_char(str)) * 13));
    if (!tmp)
        return (NULL);
    while (str[i])
    {
        if(esc_char(str[i]))
            tmp[j] = '\\';
        tmp[j] = str[i];
        if(str[i] == '=')
            tmp[++j] = '\"';
        i++;
            j++;
    }
    if(ft_strchr(str, '='))
        tmp[j++] = '\"';
    tmp[j] = '\0';
    return (tmp);
}
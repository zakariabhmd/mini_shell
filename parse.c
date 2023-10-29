/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:47:42 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/10/29 14:47:42 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	specialchar_check(char c, int check)
{
	if (check == 1 && (c == '\'' || c == '\"'))
		return (1);
	else if (check == 2 && (ft_isalpha(c)
			|| c == ' ' || c == '\t'
			|| c == '|' || c == ';'
			|| c == '$' || c == '\\'))
		return (1);
	else if (check == 3 && c == '\\')
		return (1);
	return (0);
}

char	*rm_safe(char *str, char *bs)
{
	char	*tmp;
	char	*res;
	int		str_len;
	int		bs_len;

	str_len = ft_strlen(str);
	bs_len = ft_strlen(bs);
	tmp = malloc((str_len - bs_len + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	ft_strlcpy(tmp, str, str_len - bs_len + 1);
	res = ft_strjoin(tmp, ++bs);
	free(tmp);
	return (res);
}

void    rm_bs(char **str, char *bs)
{
    char *res;

    res = rm_safe(*str, bs);
    free(*str);
    *str = ft_strdup(res);
    free(res);
}

char    *bs_parse(char *str, int bs_check)
{
    char    *bs;
    char    *res;

    res = ft_strdup(str);
    if(*str == '\\' && !*(str + 1))
    {
        *res = '\0';
        str++;
    }
    while(*str)
    {
        bs = ft_strchr(str, '\\');
        if (!bs)
            break;
        if(specialchar_check(*(bs + 1), bs_check))
            rm_bs(&res, bs);
        str = (bs + 1);
        if (*str == '\\')
            str++;
    }
    return (res);
}
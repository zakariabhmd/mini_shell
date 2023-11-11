/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabahmi <zbabahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 21:25:06 by zbabahmi          #+#    #+#             */
/*   Updated: 2023/11/07 22:10:23 by zbabahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	bs_previous(char *input, int start)
{
	int	i;

	i = 0;
	while (start && input[start - 1] == '\\')
		i++;
	return ((i + 1) % 2);
}

int	special_char(char c)
{
	if (c == '$' || c == '\\' || c == ';' || c == '|' || c == '\'')
		return (1);
	return (0);
}

int	special_chars_count(char *input, int start, int end, char quote)
{
	int	i;
	int	len;

	i = start + 1;
	len = 0;
	while (i < end)
	{
		if (quote != '\'' && special_char(input[i]))
			len++;
		else if (input[i] == ' ' || input[i] == '\t')
			len++;
		i++;
	}
	return (len);
}

char	*qalloc(char *input, int start, int end, char quote)
{
	char	*all;

	all = malloc(sizeof(char) * ((end - start)
				+ special_chars_count(input, start, end, quote) + 1));
	if (!all)
		return (NULL);
	return (all);
}

char	*between_quotes(char *input, int start, int end, char quote)
{
	char	*res;
	int		i;
	int		j;

	i = start + 1;
	j = 0;
	res = qalloc(input, start, end, quote);
	while (i < end)
	{
		if (quote == '\''
			&& (special_char(input[i])
				|| (input[i - 1] == '\\' && ft_isalpha(input[i]))))
			res[j++] = '\\';
		else
		{
			if (input[i] == ' ' || input[i] == '\t'
				|| input[i] == '|' || input[i] == ';' || input[i] == '\'')
				res[j++] = '\\';
			if (input[i - 1] == '\\'
				&& (input[i] == '|' || ft_isalpha(input[i])))
				res[j++] = '\\';
		}
		res[j++] = input[i++];
	}
	res[j] = '\0';
	return (res);
}

void quote_error(char quote)
{
	if (quote == '\'')
		ft_error("unexpected EOF while looking for matching `''", NULL);
	else
		ft_error("unexpected EOF while looking for matching `\"'", NULL);
}

char *endof_quote(char *input, char quote, int start, int *end)
{
	int		i;
	char	*res;

	i = start + 1;
	*end = 0;
	if (input[i] == quote && i > 1 && input[i - 2] == ' ')
	{
		*end += i + 1;
		return (ft_strdup("\"\""));
	}
	while (input[i])
	{
		if (input[i] == quote && (quote == '\'' || bs_previous(input, i)))
		{
			*end += (start + 1);
			res = between_quotes(input, start, *end, quote);
			return (res);
		}
		(*end)++;
		i++;
	}
	quote_error(quote);
	return (NULL);
}


char *rm_quotes(char *input, int *start, int *end)
{
	char 	*res;
	char	quote;

	*start = 0;
	while (input[*start])
	{
		if ((input[*start] == '\'' || input[*start] == '\"')
			&& bs_previous(input, *start))
		{
			quote = input[*start];
			res = endof_quote(input, quote, *start, end);
			return (res);
		}
		(*start)++;
	}
	*start = -1;
	return (input);
}

char	*quote_join(char *input, char *in_quote, char *buff, int start)
{
	char	*prev_quote;
	char	*str;
	char	*str1;

	prev_quote = malloc(sizeof(char) * (start + 1));
	if (!prev_quote)
		return (NULL);
	ft_strlcpy(prev_quote, input, start + 1);
	str = ft_strjoin(buff, prev_quote);
	free(prev_quote);
	str1 = ft_strjoin(str, in_quote);
	free(str);
	free(in_quote);
	return (str1);
}

char	*parse_join(char *input, char *in_quote, char *buff, int start)
{
	char	*res;

	if (start != -1)
		res = quote_join(input, in_quote, buff, start);
	else
	{
		if (ft_strcmp(buff, ""))
			res = ft_strdup(in_quote);
		else
			res = ft_strjoin(buff, in_quote);
	}
	return (res);
}

char	*quotes_parse(char *input, t_cmds *cmd)
{
	int	i;

	cmd->start = 0;
	cmd->end = 0;
	cmd->buff = ft_strdup("");
	i = 0;
	while (input[i])
	{
		cmd->in_quote = rm_quotes(&input[i], &cmd->start, &cmd->end);
		if (!cmd->in_quote)
		{
			free(cmd->buff);
			return (NULL);
		}
		cmd->tmp = parse_join(&input[i], cmd->in_quote,
				cmd->buff, cmd->start);
		free(cmd->buff);
		cmd->buff = cmd->tmp;
		if (cmd->start == -1)
			break ;
		else
			i += cmd->end + 1;
	}
	return (cmd->buff);
}

//==============================backslash parse=========================
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

void	rm_bs(char **str, char *bs)
{
	char	*res;

	res = rm_safe(*str, bs);
	free(*str);
	*str = ft_strdup(res);
	free(res);
}

char *bs_parse(char *str, int bs_check)
{
	char	*bs;
	char	*res;

	res = ft_strdup(str);
	if (*str == '\\' && !*(str + 1))
	{
		*res = '\0';
		str++;
	}
	while (*str)
	{
		bs = ft_strchr(str, '\\');
		if (!bs)
			break ;
		if (specialchar_check(*(bs + 1), bs_check))
			rm_bs(&res, bs);
		str = (bs + 1);
		if (*str == '\\')
			str++;
	}
	return (res);
}
//==============================parse=========================

char	*parsing(char *input, t_cmds *cmd)
{
	char	*res;
	char	*buff;

	buff = quotes_parse(input, cmd);
	res = NULL;
	if (buff)
	{
		res = bs_parse(buff, 1);
		free(buff);
	}
	return (res);
}

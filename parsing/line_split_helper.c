/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_split_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:19:54 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/14 10:14:44 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	single_loop(int *count, char *line, char c)
{
	while (line[*count] != c && line[*count])
		(*count)++;
	return (line[*count] != 0);
}

int	loop_until(int *count, char *line, char c)
{
	int	backcount;
	int	i;

	if (c == '\'')
		return (single_loop(count, line, c));
	while (line[*count])
	{
		if (line[*count] == c)
		{
			backcount = 0;
			i = *count - 1;
			while (i >= 0 && line[i] == '\\')
			{
				backcount++;
				i--;
			}
			if (backcount % 2 == 0)
				break ;
		}
		(*count)++;
	}
	if (!line[*count])
		return (0);
	return (1);
}

t_token	*copy_prev(int i, t_token *res)
{
	t_token	*ret;
	int		j;

	j = 0;
	ret = ft_calloc(i + 2, sizeof(t_token));
	if (!ret)
		return (return_free(res));
	while (j < i)
	{
		ret[j].word = ft_strdup(res[j].word);
		if (!ret[j].word)
		{
			free_token(res);
			return (return_free(ret));
		}
		ret[j].quote = res[j].quote;
		j++;
	}
	if (res)
		free_token(res);
	return (ret);
}

t_token	*add_word(t_slice slice, char *line, t_token *res)
{
	t_token	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (res)
		while (res[i].word)
			i++;
	ret = copy_prev(i, res);
	if (!ret)
		return (return_free(res));
	ret[i].word = malloc(sizeof(char) * (slice.end - slice.start + 1));
	if (!ret[i].word)
		return (return_free(res), return_free(ret));
	while ((slice.start + j) < slice.end)
	{
		ret[i].word[j] = line[slice.start + j];
		j++;
	}
	ret[i].word[j] = 0;
	ret[i].quote = slice.quote;
	ret[i + 1].word = NULL;
	return (ret);
}

int	is_operator(t_token tok)
{
	return (
		eqstr(tok.word, "<")
		|| eqstr(tok.word, ">")
		|| eqstr(tok.word, ">>")
		|| eqstr(tok.word, "<<")
		|| eqstr(tok.word, "|")
		|| eqstr(tok.word, ";")
	);
}

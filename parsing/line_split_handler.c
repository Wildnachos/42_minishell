/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_split_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:55:33 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/13 14:55:33 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_slice	ret_slice(int start, int end, t_quote quote)
{
	t_slice	slice;

	slice.start = start;
	slice.end = end;
	slice.quote = quote;
	return (slice);
}

int	single_char(int *start, int *count, char **line, t_token **res)
{
	if (*start < *count)
	{
		*res = add_word(ret_slice(*start, *count, NO_QUOTE), *line, *res);
		if (!(*res))
			return (0);
	}
	*res = add_word(ret_slice(*count, (*count) + 1, NO_QUOTE), *line, *res);
	if (!(*res))
		return (0);
	(*count)++;
	*start = *count;
	return (1);
}

int	double_char(int *start, int *count, char **line, t_token **res)
{
	if (*start < *count)
	{
		*res = add_word(ret_slice(*start, *count, NO_QUOTE), *line, *res);
		if (!(*res))
			return (0);
	}
	*res = add_word(ret_slice(*count, (*count) + 2, NO_QUOTE), *line, *res);
	if (!(*res))
		return (0);
	(*count) += 2;
	*start = *count;
	return (1);
}

t_token	*handle_quote(int *start, int *count, char **line, t_token **res)
{
	char	quote;
	t_slice	slice;

	if (*start < *count)
	{
		*res = add_word(ret_slice(*start, *count, NO_QUOTE), *line, *res);
		if (!(*res))
			return (0);
	}
	*start = *count + 1;
	quote = (*line)[(*count)++];
	if (!loop_until(count, *line, quote))
		return (return_free(*res));
	slice = ret_slice(*start, *count, which_quote((*line)[*start - 1]));
	*res = add_word(slice, *line, *res);
	if (!(*res))
		return (0);
	*start = *count + 1;
	return (*res);
}

int	handle_space(int *start, int *count, char **line, t_token **res)
{
	if (*start < *count)
	{
		*res = add_word(ret_slice(*start, *count, NO_QUOTE), *line, *res);
		if (!(*res))
			return (0);
	}
	*res = add_word(ret_slice(*count, *count + 1, NO_QUOTE), *line, *res);
	if (!(*res))
		return (0);
	while ((*line)[*count] == ' ')
		(*count)++;
	*start = *count;
	return (1);
}

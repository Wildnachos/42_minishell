/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:25:50 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/14 10:37:03 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_quote	which_quote(char quote)
{
	if (quote == '\"')
		return (DOUBLE_QUOTE);
	return (SINGLE_QUOTE);
}

int	handle_operator(t_token *tokens, t_token **res, int *i, int *j)
{
	t_token	*tmp;

	tmp = copy_prev(*j, *res);
	if (!tmp)
		return (0);
	*res = tmp;
	(*res)[*j].word = ft_strdup(tokens[*i].word);
	if (!(*res)[*j].word)
	{
		free_token(tmp);
		return (0);
	}
	(*res)[*j].quote = tokens[*i].quote;
	(*res)[*j + 1].word = NULL;
	(*j)++;
	(*i)++;
	return (1);
}

int	handle_merge(t_token *tokens, t_token **res, int *i, int *j)
{
	char	*word;
	t_quote	quote;
	char	*tmp;

	word = ft_strdup(tokens[*i].word);
	if (!word)
		return (0);
	quote = tokens[*i].quote;
	while (tokens[*i + 1].word && !eqstr(tokens[*i + 1].word, " ")
		&& !is_operator(tokens[*i + 1]))
	{
		tmp = ft_strjoin(word, tokens[(*i)++ + 1].word);
		free(word);
		if (!tmp)
			return (0);
		word = tmp;
	}
	*res = copy_prev(*j, *res);
	if (!*res)
		return (free_word(word, 0));
	(*res)[*j].word = word;
	(*res)[(*j)++].quote = quote;
	(*res)[*j].word = NULL;
	(*i)++;
	return (1);
}

t_token	*merge_tokens(t_token *tokens, int i, int j)
{
	t_token	*res;

	res = 0;
	while (tokens[i].word)
	{
		if (eqstr(tokens[i].word, " "))
		{
			i++;
			continue ;
		}
		if (is_operator(tokens[i]))
		{
			if (!handle_operator(tokens, &res, &i, &j))
				return (return_free(res));
		}
		else
		{
			if (!handle_merge(tokens, &res, &i, &j))
				return (return_free(res));
		}
	}
	free_token(tokens);
	return (res);
}

t_token	*split_line(char *lin, int count, int start, t_token *res)
{
	while (lin[count])
	{
		if (in(lin[count], "<>|;"))
		{
			if (lin[count + 1] == lin[count] && in(lin[count], "<>"))
			{
				if (!double_char(&start, &count, &lin, &res))
					return (return_free(res));
			}
			else
				if (!single_char(&start, &count, &lin, &res))
					return (return_free(res));
			continue ;
		}
		if (in(lin[count], "\"'") && !handle_quote(&start, &count, &lin, &res))
			return (0);
		else if (lin[count] == ' ')
		{
			if (!handle_space(&start, &count, &lin, &res))
				return (return_free(res));
			continue ;
		}
		count++;
	}
	return (finalize_tokens(start, count, lin, res));
}

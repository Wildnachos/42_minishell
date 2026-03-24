/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:48:24 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/14 09:57:56 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	handle_i(char **res, char **str, int i)
{
	*str = ins_str(*str, &((*res)[i]), 1);
	if (!(*str))
		return (-1);
	i++;
	return (i);
}

int	handle_continue(char **res, char **str, int i, t_data *data)
{
	if ((*res)[i + 1] != '?' && check_arg_char((*res)[i + 1]))
	{
		i = handle_i(res, str, i);
		return (i);
	}
	i = handle_dollar(res, str, i, data);
	return (i);
}

int	special_chars(char **res, char **newstr, int i, int *in_double_quotes)
{
	if ((*res)[i] == '\'' && !*in_double_quotes)
		return (handle_single_quotes(res, newstr, i));
	else if ((*res)[i] == '\"')
		return (handle_double_quotes(res, newstr, i, in_double_quotes));
	else if ((*res)[i] == '\\')
		return (handle_escape(res, newstr, i, *in_double_quotes));
	return (-2);
}

void	expand(char **res, t_data *data, int i, char *newstr)
{
	int		in_double_quotes;
	int		ret;

	in_double_quotes = 0;
	while ((*res)[i])
	{
		ret = special_chars(res, &newstr, i, &in_double_quotes);
		if (ret != -2)
			i = ret;
		else if ((*res)[i] == '$')
		{
			i = handle_continue(res, &newstr, i, data);
			if (i == -1)
				break ;
			continue ;
		}
		else
			i = handle_i(res, &newstr, i);
		if (i == -1)
			break ;
	}
	if (i == -1)
		newstr = 0;
	free (*res);
	*res = newstr;
}

void	expand_args(char **res, t_data *data, int i, int done)
{
	int	in_double_quotes;

	in_double_quotes = 0;
	while (!done)
	{
		while ((*res)[i])
		{
			if ((*res)[i] == '\'' && !in_double_quotes)
			{
				while (((*res)[i] != '\'' && (*res)[i]))
					i++;
			}
			if ((*res)[i] == '\"')
				in_double_quotes = !in_double_quotes;
			else if ((*res)[i] == '$')
			{
				expand(res, data, 0, 0);
				break ;
			}
			i++;
		}
		done = 1;
	}
}

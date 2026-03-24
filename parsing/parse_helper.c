/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:25:34 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/14 10:37:14 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_arg_char(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (0);
	return (1);
}

char	**free_strarr_char(char **tofree)
{
	int	i;

	i = 0;
	if (!tofree)
		return (0);
	while (tofree[i])
	{
		if (tofree[i])
			free(tofree[i]);
		i++;
	}
	free(tofree);
	return (0);
}

t_token	*finalize_tokens(int start, int count, char *lin, t_token *res)
{
	if (start < count)
	{
		res = add_word(ret_slice(start, count, NO_QUOTE), lin, res);
		if (!res)
			return (return_free(res));
	}
	res = merge_tokens(res, 0, 0);
	if (!res)
		return (return_free(res));
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:22:12 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/13 15:22:12 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	handle_single_quotes(char **res, char **str, int i)
{
	*str = ins_str(*str, &((*res)[i]), 1);
	if (!(*str))
		return (-1);
	i++;
	while ((*res)[i] && ((*res)[i] != '\''))
	{
		*str = ins_str(*str, &((*res)[i]), 1);
		if (!(*str))
			return (-1);
		i++;
	}
	if ((*res)[i] == '\'')
	{
		*str = ins_str(*str, &((*res)[i]), 1);
		if (!(*str))
			return (-1);
		i++;
	}
	return (i);
}

int	handle_double_quotes(char **res, char **str, int i, int *in_quotes)
{
	*in_quotes = !(*in_quotes);
	*str = ins_str(*str, &((*res)[i]), 1);
	if (!(*str))
		return (-1);
	i++;
	return (i);
}

int	handle_escape(char **res, char **str, int i, int in_quotes)
{
	if (in_quotes && ((*res)[i + 1] == '$' || (*res)[i + 1] == '\"'
		|| (*res)[i + 1] == '\\'))
		i++;
	else if (!in_quotes)
		i++;
	if ((*res)[i])
	{
		*str = ins_str(*str, &((*res)[i]), 1);
		if (!(*str))
			return (-1);
		i++;
	}
	return (i);
}

char	*dollar_helper(t_data *data, char **res, char *search, int i)
{
	char	*var;

	if ((*res)[i + 1] == '_' && check_arg_char((*res)[i + 2]))
	{
		if (!data->last_arg)
			var = ft_strdup("");
		else
			var = ft_strdup(data->last_arg);
	}
	else
		var = find(search, data->env);
	return (var);
}

int	handle_dollar(char **res, char **str, int i, t_data *data)
{
	char	*var;
	char	*search;
	int		len;

	if ((*res)[i + 1] == '?')
		len = 1;
	else
		len = var_len((*res) + i + 1);
	search = ft_substr(*res, i + 1, len);
	if (!search)
		return (-1);
	if ((*res)[i + 1] == '?')
		var = ft_itoa(data->exit_code);
	else
		var = dollar_helper(data, res, search, i);
	free(search);
	if (!var)
		var = ft_strdup("");
	if (!var)
		return (-1);
	*str = ins_str(*str, var, ft_strlen(var));
	if (!(*str))
		return (-1);
	free(var);
	return (i + len + 1);
}

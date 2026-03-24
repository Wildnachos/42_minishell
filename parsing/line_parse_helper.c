/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parse_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:17:42 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/14 10:22:53 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_command	*init_node(int pipein)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (0);
	cmd->com = NULL;
	cmd->args = NULL;
	cmd->pipein = pipein;
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

int	get_redir_type(char *token, t_quote quote)
{
	if (quote != NO_QUOTE)
		return (-1);
	if (eqstr(token, "<"))
		return (IN);
	if (eqstr(token, "<<"))
		return (HERE);
	if (eqstr(token, ">"))
		return (OUT);
	if (eqstr(token, ">>"))
		return (APP);
	return (-1);
}

char	**append(char **args, char *arg, int i, char **res)
{
	if (args)
		while (args[i])
			i++;
	res = malloc(sizeof(char *) * (i + 2));
	if (!res)
		return (0);
	i = 0;
	if (args)
	{
		while (args[i])
		{
			res[i] = ft_strdup(args[i]);
			if (!res[i++])
				return (free_strarr_char(res));
		}
	}
	res[i] = ft_strdup(arg);
	if (!res[i])
		return (free_strarr_char(res));
	res[i + 1] = 0;
	free_strarr(args);
	return (res);
}

int	insert_arg(char ***args, t_token token, int i)
{
	char	**arg;
	char	**res;

	arg = *args;
	if (arg)
		while (arg[i])
			i++;
	res = malloc(sizeof(char *) * (i + 2));
	if (!res)
		return (0);
	i = 0;
	res[i++] = ft_strdup(token.word);
	if (!res[i - 1])
		return (free_strarr(res));
	while (arg && arg[i - 1])
	{
		res[i] = ft_strdup(arg[i - 1]);
		if (!res[i++])
			return (free_strarr(res));
	}
	res[i] = 0;
	free_strarr(arg);
	*args = res;
	return (1);
}

int	add_arg(char ***args, t_token token)
{
	char	**arg;

	arg = *args;
	if (token.quote == SINGLE_QUOTE)
		arg = append(arg, token.word, 0, 0);
	else if (token.quote == NO_QUOTE)
		arg = append(arg, token.word, 0, 0);
	else if (token.quote == DOUBLE_QUOTE)
		arg = append(arg, token.word, 0, 0);
	if (!arg)
		return (0);
	*args = arg;
	return (1);
}

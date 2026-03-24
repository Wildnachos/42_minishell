/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:08:38 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/16 10:08:38 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "initialization.h"
#include "parsing/parsing.h"
#include "execution/execution.h"

int	is_redir(t_token *token)
{
	if (get_redir_type(token->word, token->quote) > -1)
		return (1);
	return (0);
}

int	is_op(t_token *token)
{
	if ((eqstr(token->word, "|") || eqstr(token->word, ";"))
		&& token->quote == NO_QUOTE)
		return (1);
	return (0);
}

int	check_middle_errors(t_token *token, int i)
{
	if (i > 0)
	{
		if (is_redir(&token[i - 1]) && is_redir(&token[i]))
			return (i);
		if (is_redir(&token[i - 1]) && is_op(&token[i]))
			return (i);
	}
	if (i > 1 && eqstr(token[i - 1].word, "|") && eqstr(token[i].word, "|")
		&& token[i - 1].quote == NO_QUOTE && token[i].quote == NO_QUOTE)
		return (i);
	return (0);
}

int	check_edge_errors(t_token *token, int last)
{
	if (is_op(&token[0]))
		return (-1);
	if (is_op(&token[last]) || is_redir(&token[last]))
		return (-2);
	return (0);
}

int	valid_tok(t_token *token)
{
	int	i;
	int	ret;

	i = 0;
	while (token[i].word)
	{
		ret = check_middle_errors(token, i);
		if (ret)
			return (ret);
		i++;
	}
	return (check_edge_errors(token, i - 1));
}

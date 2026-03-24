/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:10:45 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/14 10:10:51 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	append_redir(t_redir **redirs, t_redir *curr)
{
	t_redir	*end;

	if (!*redirs)
		*redirs = curr;
	else
	{
		end = *redirs;
		while (end->next)
			end = end->next;
		end->next = curr;
	}
}

int	init_redirs(t_token *tok, int i, t_redir **redirs)
{
	t_redir	*curr;

	while (tok[i].word && !eqstr(tok[i].word, "|") && !eqstr(tok[i].word, ";"))
	{
		if (get_redir_type(tok[i].word, tok[i].quote) > -1)
		{
			curr = malloc(sizeof(t_redir));
			if (!curr || !tok[i + 1].word)
				return (free_redir_ret(curr, 0));
			curr->next = NULL;
			curr->type = get_redir_type(tok[i].word, NO_QUOTE);
			curr->delim = ft_strdup(tok[i++ + 1].word);
			if (!curr->delim)
				return (free_redir_ret(curr, 0));
			append_redir(redirs, curr);
		}
		i++;
	}
	return (1);
}

int	parse_help(t_token *tokens, t_command *cmd, int *i)
{
	while (tokens[*i].word && !(eqstr(tokens[*i].word, "|")
			&& tokens[*i].quote == NO_QUOTE)
		&& !(eqstr(tokens[*i].word, ";") && tokens[*i].quote == NO_QUOTE))
	{
		if (get_redir_type(tokens[*i].word, tokens[*i].quote) > -1)
		{
			*i += 2;
			continue ;
		}
		if (cmd->com == 0)
		{
			cmd->com = ft_strdup(tokens[*i].word);
			if (!cmd->com || !insert_arg(&(cmd->args), tokens[(*i)++], 0))
				return (0);
		}
		else
		{
			if (!add_arg(&(cmd->args), tokens[(*i)++]))
				return (0);
		}
	}
	return (1);
}

int	pipe_skip(t_command *cmd, int i, int j)
{
	cmd->next = init_node(j);
	if (!(cmd->next))
		return (-1);
	i++;
	return (i);
}

t_command	*parse_line(t_token *tok, t_command *head, t_command *cmd, int i)
{
	while (tok[i].word)
	{
		cmd->com = 0;
		cmd->args = 0;
		if (!init_redirs(tok, i, &(cmd->redir)))
			return (0);
		if (!parse_help(tok, cmd, &i))
			return (0);
		if (tok[i].word && eqstr(tok[i].word, "|") && tok[i].quote == NO_QUOTE)
			i = pipe_skip(cmd, i, 1);
		else if (tok[i].word && eqstr(tok[i].word, ";")
			&& tok[i].quote == NO_QUOTE)
			i = pipe_skip(cmd, i, 0);
		else
		{
			cmd->next = 0;
			if (tok[i].word)
				i++;
		}
		if (i == -1)
			return (0);
		if (cmd->next)
			cmd = cmd->next;
	}
	return (head);
}

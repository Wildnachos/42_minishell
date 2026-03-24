/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:25:31 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/15 14:42:02 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	free_strarr(char **tofree)
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

int	free_redir_ret(t_redir *redir, int ret)
{
	t_redir	*tmp;

	if (!redir)
		return (ret);
	while (redir)
	{
		if (redir->delim)
			free(redir->delim);
		tmp = redir;
		redir = redir->next;
		free(tmp);
	}
	return (ret);
}

void	free_line(t_command *cmd)
{
	t_command	*tmp;

	if (!cmd)
		return ;
	while (cmd)
	{
		if (cmd->com)
			free(cmd->com);
		free_strarr(cmd->args);
		free_redir_ret(cmd->redir, 0);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

void	free_token(t_token *res)
{
	int	i;

	i = 0;
	if (!res)
		return ;
	while (res[i].word)
	{
		if (res[i].word)
			free(res[i].word);
		i++;
	}
	free(res);
}

t_token	*return_free(t_token *res)
{
	free_token(res);
	return (0);
}

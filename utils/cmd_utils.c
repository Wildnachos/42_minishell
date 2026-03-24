/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:51:26 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/15 14:51:26 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	cmd_redir_in(t_command *cmd)
{
	t_redir	*r;

	r = cmd->redir;
	while (r)
	{
		if (r->type == IN)
			return (true);
		r = r->next;
	}
	return (false);
}

bool	cmd_redir_out(t_command *cmd)
{
	t_redir	*r;

	r = cmd->redir;
	while (r)
	{
		if (r->type == OUT)
			return (true);
		r = r->next;
	}
	return (false);
}

bool	cmd_redir_app(t_command *cmd)
{
	t_redir	*r;

	r = cmd->redir;
	while (r)
	{
		if (r->type == APP)
			return (true);
		r = r->next;
	}
	return (false);
}

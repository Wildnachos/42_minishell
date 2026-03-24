/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:07:21 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/16 11:07:21 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

bool	heredoc_after(t_redir	*r)
{
	t_redir	*redir;

	redir = r->next;
	while (redir)
	{
		if (redir->type == HERE)
			return (true);
		redir = redir->next;
	}
	return (false);
}

void	error(int exit_code, char *message)
{
	if (message)
		ft_putstr_fd(message, STDERR);
	if (exit_code)
		exit(exit_code);
}

bool	failure(t_data *data)
{
	reset_stds(data);
	return (false);
}

int	init_redir_fds(t_data *data, int count)
{
	int	j;

	data->redir_fds = malloc(sizeof(int) * (count + 1));
	if (!data->redir_fds)
		return (0);
	j = 0;
	while (j <= count)
		data->redir_fds[j++] = -111;
	return (1);
}

int	open_redir_fd(t_redir *r, t_data *data)
{
	if (r->type == HERE)
		return (get_heredoc(r, data));
	if (r->type == IN)
		return (open(r->delim, O_RDONLY));
	if (r->type == OUT)
		return (open(r->delim, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU));
	if (r->type == APP)
		return (open(r->delim, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU));
	return (-1);
}

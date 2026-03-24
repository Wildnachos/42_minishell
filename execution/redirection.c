/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:21:42 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/16 11:22:34 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	close_redir_fds(int *fd)
{
	int	i;

	if (!fd)
		return ;
	i = 0;
	while (1)
	{
		if (fd[i] == -111)
			break ;
		if (fd[i] >= 0)
			close(fd[i]);
		i++;
	}
	free(fd);
}

static int	close_fds_print_error(t_data *data, t_redir *redir)
{
	close_redir_fds(data->redir_fds);
	data->redir_fds = 0;
	if (redir->type != HERE)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(redir->delim, STDERR);
		if (access (redir->delim, F_OK) != 0)
			if (errno == ENOENT)
				ft_putstr_fd(": No such file or directory\n", STDERR);
		if (access ((redir->delim), X_OK))
			if (errno == EACCES)
				ft_putstr_fd(": Permission denied\n", STDERR);
	}
	return (EXIT_FAILURE);
}

static int	count_redirs(t_redir *redir)
{
	int		i;

	i = 0;
	while (redir)
	{
		redir = redir->next;
		i++;
	}
	return (i);
}

static void	dups(t_command *cmd, t_redir *redir, int fd)
{
	if (redir->type == HERE)
	{
		if (!heredoc_after(redir))
			cmd->input = fd;
	}
	else if (redir->type == IN)
		cmd->input = fd;
	else if (redir->type == OUT || redir->type == APP)
	{
		if (!heredoc_after(redir))
			cmd->output = fd;
	}
}

int	redirect_in_out(t_command *cmd, t_redir	*r, int i, t_data *data)
{
	int	redir_count;

	r = cmd->redir;
	redir_count = count_redirs(r);
	if (!init_redir_fds(data, redir_count))
		return (EXIT_FAILURE);
	while (r)
	{
		data->redir_fds[i] = open_redir_fd(r, data);
		if (data->redir_fds[i] == -1)
		{
			data->redir_fds[i] = -111;
			close_fds_print_error(data, r);
			return (EXIT_FAILURE);
		}
		dups(cmd, r, data->redir_fds[i++]);
		r = r->next;
	}
	data->redir_fds[i] = -111;
	return (EXIT_SUCCESS);
}

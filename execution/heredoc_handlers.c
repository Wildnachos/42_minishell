/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:18:22 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/16 11:18:45 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	handle_heredoc_eof(char *delim, int *fd)
{
	print_err_here(delim);
	close(fd[0]);
	close(fd[1]);
	g_sig = 0;
}

void	write_heredoc_line(char *str, int fd, t_data *data)
{
	expand_args(&str, data, 0, 0);
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\n", fd);
	free(str);
}

void	handle_heredoc_interrupt(int *fd)
{
	close(fd[0]);
	close(fd[1]);
	handle_signals();
}

int	finish_heredoc(char *str, char *delim, int *fd)
{
	if (!str)
	{
		if (g_sig != -1)
			handle_heredoc_eof(delim, fd);
		else
			handle_heredoc_interrupt(fd);
		return (-1);
	}
	free(str);
	if (fd[1] >= 0)
		close(fd[1]);
	if (g_sig == -1)
		return (handle_heredoc_interrupt(fd), -1);
	handle_signals();
	return (fd[0]);
}

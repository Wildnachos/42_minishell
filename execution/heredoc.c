/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:18:51 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/16 11:20:25 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	handle_sig_heredoc(int sig)
{
	(void)sig;
	g_sig = -1;
	write(1, "\n", 1);
	close(STDIN);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;
	unsigned char	*str;

	i = 0;
	str = s;
	while (i < n)
		str[i++] = '\0';
	return ;
}

void	signals_heredoc(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = handle_sig_heredoc;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

void	print_err_here(char *limit)
{
	ft_putstr_fd("warning: here-document delimited by end-of-file", STDERR);
	ft_putstr_fd(" (wanted '", STDERR);
	ft_putstr_fd(limit, STDERR);
	ft_putstr_fd("')\n", STDERR);
}

int	get_heredoc(t_redir	*r, t_data *data)
{
	char	*str;
	int		fd[2];

	if (pipe(fd) == -1)
		perror("pipe");
	signals_heredoc();
	str = readline("> ");
	while (str && g_sig != -1)
	{
		if (eqstr(str, r->delim))
			break ;
		write_heredoc_line(str, fd[1], data);
		if (g_sig == -1)
			str = 0;
		else
			str = readline("> ");
	}
	return (finish_heredoc(str, r->delim, fd));
}

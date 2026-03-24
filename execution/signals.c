/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:02:32 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/15 22:02:32 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_int_sig(int sig)
{
	if (sig == SIGINT)
		g_sig = 1;
	else if (sig == SIGQUIT)
		g_sig = 2;
}

void	handle_signals(void)
{
	if (g_sig == 1)
		write(1, "\n", 1);
	else if (g_sig == 2)
		write(1, "Quit (core dumped)\n", 20);
	g_sig = 0;
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, SIG_IGN);
	rl_reset_line_state ();
}

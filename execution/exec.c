/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:35:59 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/16 09:44:31 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	close_all_fd(t_command *cmd)
{
	t_command	*tmp;

	tmp = cmd;
	while (tmp->next)
	{
		if (tmp->input > 0)
			close(tmp->input);
		if (tmp->output > 0)
			close(tmp->output);
		tmp = tmp->next;
	}
}

static void	create_pipe(t_command *cmd)
{
	int			fd[2];

	if (!cmd->pipein)
		cmd->input = -1;
	if (!cmd->next)
		cmd->output = -1;
	if (cmd->next)
	{
		if (cmd_redir_app(cmd) || cmd_redir_out(cmd))
		{
			cmd->output = -1;
			cmd->next->input = -1;
		}
		else if (cmd->next->pipein)
		{
			if (pipe(fd) == -1)
				error(0, "Error pipe\n");
			cmd->output = fd[1];
			cmd->next->input = fd[0];
		}			
	}	
	if (cmd->input > 0 && cmd_redir_in(cmd))
		close(cmd->input);
}

void	closing(t_command *cmd)
{
	if (cmd->input > 0)
		close(cmd->input);
	if (cmd->output > 0)
		close (cmd->output);
}

t_command	*exc_cmd(t_command *cmd, t_data *data)
{
	data->redir_fds = NULL;
	data->exit_code = EXIT_SUCCESS;
	create_pipe(cmd);
	if (cmd->redir)
		data->exit_code = redirect_in_out(cmd, cmd->redir, 0, data);
	if (data->exit_code == EXIT_SUCCESS && cmd->com)
	{
		if (!cmd->next &&!cmd->pipein && is_builtin(cmd->com))
			data->exit_code = exec_builtin(cmd, data->env, data);
		else
			create_child_process(cmd, data, 0, 0);
	}
	closing(cmd);
	if (data->redir_fds)
		close_redir_fds(data->redir_fds);
	data->redir_fds = 0;
	return (cmd->next);
}

int	exec(t_command *cmd, t_data *data)
{
	t_command	*tmp;
	int			status;
	pid_t		pid;

	status = 0;
	tmp = cmd;
	data->exit_code = 0;
	while (tmp)
		tmp = exc_cmd(tmp, data);
	close_all_fd(cmd);
	tmp = cmd;
	signal(SIGINT, handle_int_sig);
	signal(SIGQUIT, handle_int_sig);
	while (tmp)
	{
		pid = waitpid(0, &status, 0);
		if (pid == data->pid)
			if (WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status);
		tmp = tmp->next;
	}
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	return (data->exit_code);
}

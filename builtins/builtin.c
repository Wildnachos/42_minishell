/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:57:07 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/15 15:57:07 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_builtin(char *command)
{
	if (eqstr(command, "echo"))
		return (1);
	if (eqstr(command, "cd"))
		return (1);
	if (eqstr(command, "pwd"))
		return (1);
	if (eqstr(command, "env"))
		return (1);
	if (eqstr(command, "export"))
		return (1);
	if (eqstr(command, "unset"))
		return (1);
	if (eqstr(command, "exit"))
		return (1);
	return (0);
}

static void	dup_in_out(t_command *cmd)
{
	if (cmd->output > 0)
	{
		if (dup2(cmd->output, STDOUT_FILENO) < 0)
			ft_putstr_fd("Error dup2 builtin output\n", STDERR);
		if (cmd->output >= 0)
			close(cmd->output);
	}
	if (cmd->input > 0)
	{
		if (dup2(cmd->input, STDIN_FILENO) < 0)
			ft_putstr_fd("Error dup2 builtin input\n", STDERR);
		if (cmd->input >= 0)
			close(cmd->input);
	}
}

int	exec_builtin(t_command *cmd, t_env *env, t_data *data)
{
	int		result;

	result = 0;
	if (!cmd->next &&!cmd->pipein)
		dup_in_out(cmd);
	if (eqstr(cmd->args[0], "echo"))
		result = ft_echo(cmd->args);
	else if (eqstr(cmd->args[0], "cd"))
		result = ft_cd(cmd->args, env);
	else if (eqstr(cmd->args[0], "pwd"))
		result = ft_pwd();
	else if (eqstr(cmd->args[0], "env"))
		result = ft_env(env);
	else if (eqstr(cmd->args[0], "export"))
		result = ft_export(cmd->args, env);
	else if (eqstr(cmd->args[0], "unset"))
		result = ft_unset(cmd->args, env);
	else if (eqstr(cmd->args[0], "exit"))
		result = ft_exit(cmd->args);
	reset_stds(data);
	return (result);
}

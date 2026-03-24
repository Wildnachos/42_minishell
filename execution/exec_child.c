/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:51:31 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/16 09:51:31 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	absolute_path(char **path, char *cmd)
{
	*path = ft_strdup(cmd);
	if (!(*path))
		return (EXIT_FAILURE);
	if (access((*path), F_OK))
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd((*path), STDERR);
		ft_putstr_fd(" : No such file or directory\n", STDERR);
		free(*path);
		*path = NULL;
		return (CMD_NOT_FOUND);
	}
	return (EXIT_SUCCESS);
}

static bool	is_dir(char **path, char *cmd, t_data *data)
{
	struct stat	path_stat;

	stat(*path, &path_stat);
	if (!S_ISREG(path_stat.st_mode))
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(cmd, STDERR);
		ft_putstr_fd(" : Is a directory\n", STDERR);
		data->exit_code = CMD_NOT_EXEC;
		return (false);
	}
	return (true);
}

static bool	crtl_cmd_exist(char **path, t_data *data, char *cmd)
{
	if (!ft_strchr(cmd, '/'))
		*path = find_cmd_in_env(path, data, cmd);
	else
		data->exit_code = absolute_path(path, cmd);
	if (!(*path))
		return (failure(data));
	if (access ((*path), X_OK))
	{
		perror(*path);
		free(*path);
		*path = NULL;
		if (errno == EACCES)
		{
			ft_putstr_fd("minishell: ", STDERR);
			ft_putstr_fd((*path), STDERR);
			ft_putstr_fd(": Permission denied\n", STDERR);
		}
		data->exit_code = CMD_NOT_EXEC;
		return (failure(data));
	}
	if (!is_dir(path, cmd, data))
		return (failure(data));
	return (true);
}

static void	dup_in_out(t_command *cmd)
{
	if (cmd->output > 0)
	{
		if (cmd->next && cmd->next->input > 0)
			close(cmd->next->input);
		if (dup2(cmd->output, STDOUT_FILENO) < 0)
			error(0, "Error dup2 output\n");
		if (cmd->output > 2)
			close(cmd->output);
	}
	if (cmd->input > 0)
	{
		if (dup2(cmd->input, STDIN_FILENO) < 0)
			error(0, "Error dup2 input\n");
		if (cmd->input > 2)
			close(cmd->input);
	}
}

void	create_child_process(t_command *cmd, t_data *data, char *path,
			char **env_ch)
{
	env_ch = env_to_arr(data->env);
	if (!env_ch)
		return ;
	data->pid = fork();
	if (data->pid < 0)
		close_all_fd(cmd);
	else if (data->pid == 0)
	{
		rl_clear_history();
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup_in_out(cmd);
		if (is_builtin(cmd->com))
			data->exit_code = (exec_builtin(cmd, data->env, data));
		else if (crtl_cmd_exist(&path, data, cmd->args[0]))
			execve(path, cmd->args, env_ch);
		else if (!path && data->exit_code == EXIT_SUCCESS)
			error_message(cmd->com);
		free(env_ch);
		free_all_exit(cmd, data->input, data, data->exit_code);
	}
	free(env_ch);
	if (path)
		free(path);
}

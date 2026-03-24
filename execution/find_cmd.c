/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:46:28 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/15 22:46:28 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	error_message(char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(path, STDERR);
	if (fd == -1 && folder == NULL)
		ft_putstr_fd(": No such file or directory\n", STDERR);
	else if (fd == -1 && folder != NULL)
		ft_putstr_fd(": Is a directory\n", STDERR);
	else if (fd != -1 && folder == NULL)
		ft_putstr_fd(": Permission denied\n", STDERR);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		ret = CMD_NOT_FOUND;
	else
		ret = CMD_NOT_EXEC;
	if (folder)
		closedir(folder);
	if (fd > 0)
		close(fd);
	return (ret);
}

char	*path_join(const char *s1, const char *s2)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(s1, "/");
	if (!tmp)
		return (0);
	path = ft_strjoin(tmp, s2);
	free(tmp);
	if (!path)
		return (0);
	return (path);
}

char	*check_dir(char *bin, char *command)
{
	DIR				*folder;
	struct dirent	*item;
	char			*path;

	path = NULL;
	folder = opendir(bin);
	if (!folder)
		return (NULL);
	item = readdir(folder);
	while (item)
	{
		if (ft_strncmp(item->d_name, command, INT_MAX) == 0)
			path = path_join(bin, item->d_name);
		item = readdir(folder);
	}
	closedir(folder);
	return (path);
}

char	*find_cmd_in_env(char **path, t_data *data, char *cmd)
{
	int		i;
	char	**bins;
	t_env	*env_path;

	env_path = get_elem(data->env, "PATH");
	if (!env_path)
		return (NULL);
	bins = ft_split(env_path->value + 5, ":");
	if (!bins || !bins[0])
		return (NULL);
	i = 0;
	while (cmd && bins[i] && *path == NULL)
		*path = check_dir(bins[i++], cmd);
	free_strarr(bins);
	if (!(*path))
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(cmd, STDERR);
		ft_putstr_fd(": command not found\n", STDERR);
		data->exit_code = CMD_NOT_FOUND;
	}
	return (*path);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *) s + i);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

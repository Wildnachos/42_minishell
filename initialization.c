/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 23:23:43 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/15 23:24:44 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "initialization.h"

static t_env	*copy_env_vars(char **env, int i)
{
	t_env	*first;
	char	*tmp;

	tmp = ft_strdup(env[i]);
	if (!tmp)
		return (NULL);
	first = append_node(NULL, tmp);
	while (env[++i])
	{
		if (env[i][0] == '_')
			continue ;
		tmp = ft_strdup(env[i]);
		if (!tmp)
			return (NULL);
		append_node(first, tmp);
	}
	return (first);
}

t_data	*init_env(int ac, char **av, char **env, int i)
{
	t_env	*first;
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->pid = 0;
	data->last_arg = 0;
	data->redir_fds = 0;
	data->fd[0] = -1;
	data->fd[1] = -1;
	if (!*env)
		create_basic_env(ac, av, data);
	else
	{
		first = copy_env_vars(env, i);
		if (!first)
			return (NULL);
		data->env = first;
	}
	ft_shlvl_plus(data->env);
	return (data);
}

void	redir_stds(t_data *data)
{
	data->fd[0] = dup(STDIN);
	data->fd[1] = dup(STDOUT);
}

void	reset_stds(t_data *data)
{
	dup2(data->fd[0], STDIN);
	dup2(data->fd[1], STDOUT);
	if (data->fd[0] != -1)
		close(data->fd[0]);
	if (data->fd[1] != -1)
		close(data->fd[1]);
	data->fd[0] = -1;
	data->fd[1] = -1;
}

int	empty_line(char *line)
{
	int	i;

	i = 0;
	while ((line[i] && line[i] == ' ') || line[i] == '\n' || line[i] == '\r'
		|| line[i] == '\f' || line[i] == '\t' || line[i] == '\v')
		i++;
	if (i == ft_strlen(line))
		return (1);
	return (0);
}

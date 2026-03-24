/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:30:28 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/13 15:30:28 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	update_oldpwd(t_env *env, char *old_pwd, int failure)
{
	t_env	*cur;

	if (failure)
	{
		free(old_pwd);
		return (EXIT_FAILURE);
	}
	if (old_pwd)
	{
		cur = env;
		while (cur)
		{
			if (ft_strncmp(cur->value, "OLDPWD=", 7) == 0)
			{
				free(cur->value);
				cur->value = old_pwd;
				return (EXIT_SUCCESS);
			}
			cur = cur->next;
		}
		append_node(env, old_pwd);
		if (!env)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	update_pwd(char *arg, t_env *env)
{
	char	*old_pwd;
	char	*new_pwd;
	t_env	*cur;

	old_pwd = 0;
	cur = env;
	while (cur)
	{
		if (ft_strncmp(cur->value, "PWD=", 4) == 0)
		{
			old_pwd = ft_strjoin("OLD", cur->value);
			if (!old_pwd)
				return (EXIT_FAILURE);
			new_pwd = ft_strjoin("PWD=", arg);
			if (!new_pwd)
				return (update_oldpwd(env, old_pwd, 1));
			free(cur->value);
			cur->value = new_pwd;
			break ;
		}
		cur = cur->next;
	}
	return (update_oldpwd(env, old_pwd, 0));
}

static int	go_to_path(char *path, t_env *env)
{
	int		ret;
	char	cwd[PATH_MAX];

	ret = chdir(path);
	if (ret == 0)
	{
		if (getcwd(cwd, PATH_MAX) == NULL)
			return (EXIT_FAILURE);
		ret = update_pwd(cwd, env);
	}
	else
	{
		ft_putstr_fd("minishell: ", STDERR);
		perror(path);
		ret = EXIT_FAILURE;
	}
	return (ret);
}

int	ft_cd(char **args, t_env *env)
{
	t_env	*tmp;

	if (args && args[1] && args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR);
		return (EXIT_FAILURE);
	}
	if (!args[1] || eqstr(args[1], "~") || eqstr(args[1], "--"))
	{
		tmp = get_elem(env, "HOME");
		if (!tmp)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (EXIT_FAILURE);
		}
		else
			return (go_to_path(tmp->value + 1
					+ size_until_eq(tmp->value), env));
	}
	return (go_to_path(args[1], env));
}

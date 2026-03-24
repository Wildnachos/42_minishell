/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:09:11 by akabbaj           #+#    #+#             */
/*   Updated: 2025/04/21 14:09:11 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static bool	print_err(char *str)
{
	ft_putstr_fd("export: `", STDERR);
	ft_putstr_fd(str, STDERR);
	ft_putstr_fd("': not a valid identifier\n", STDERR);
	return (false);
}

static bool	valid_id(char *str)
{
	int	i;

	i = 0;
	if (!str[0] || (str[0] != '_' && !ft_isalpha(str[0])))
		return (print_err(str));
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (print_err(str));
		i++;
	}
	return (true);
}

static int	update_env(char **args, t_env *env)
{
	char	*tmp;
	t_env	*new;
	int		i;

	i = 0;
	while (args[++i])
	{
		if (!valid_id(args[i]))
			return (EXIT_FAILURE);
		tmp = ft_strdup(args[i]);
		if (!tmp)
			return (EXIT_FAILURE);
		new = get_elem(env, args[i]);
		if (new)
		{
			free(new->value);
			new->value = tmp;
		}
		else
			append_node(env, tmp);
	}
	return (EXIT_SUCCESS);
}

static void	print_env(char *arr)
{
	int	i;

	i = 0;
	ft_putstr_fd("declare -x ", STDOUT);
	while (arr[i] && arr[i] != '=')
		write(STDOUT, &arr[i++], 1);
	if (arr[i] && arr[i] == '=')
	{
		ft_putstr_fd("=\"", STDOUT);
		ft_putstr_fd(&arr[i + 1], STDOUT);
		ft_putstr_fd("\"\n", STDOUT);
	}
	else
		ft_putstr_fd("\n", STDOUT);
}

int	ft_export(char **args, t_env *env)
{
	char	**arr;
	int		i;

	if (nb_args(args) >= 2)
		return (update_env(args, env));
	else
	{
		arr = env_to_arr(env);
		if (!arr)
			return (EXIT_FAILURE);
		sort_arr(arr);
		i = 0;
		while (arr[i])
			print_env(arr[i++]);
		free (arr);
	}
	return (EXIT_SUCCESS);
}

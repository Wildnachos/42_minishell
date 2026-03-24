/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:48:32 by akabbaj           #+#    #+#             */
/*   Updated: 2025/04/21 14:09:00 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	delete_env(t_env *first, t_env *env_to_del)
{
	t_env	*tmp;

	while (first)
	{
		tmp = first->next;
		if (tmp == env_to_del)
		{
			first->next = tmp->next;
			free (tmp->value);
			free (tmp);
			break ;
		}
		first = tmp;
	}
}

size_t	size_until_eq(char *env)
{
	size_t	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

int	ft_unset(char **args, t_env *env)
{
	t_env	*first;
	int		i;

	i = 0;
	first = env;
	while (args[++i])
	{
		env = first;
		while (env)
		{
			if (ft_strncmp(args[i], env->value, size_until_eq(env->value)) == 0)
			{
				delete_env(first, env);
				break ;
			}
			env = env->next;
		}
	}
	return (EXIT_SUCCESS);
}

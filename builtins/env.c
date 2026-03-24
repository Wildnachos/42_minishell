/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:22:53 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/13 15:22:53 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	create_basic_env(int ac, char **av, t_data *data)
{
	t_env	*first;
	char	cwd[PATH_MAX];

	(void)ac;
	(void)av;
	if (getcwd(cwd, PATH_MAX))
	{
		first = append_node(NULL, ft_strjoin("PWD=", cwd));
		append_node(first, ft_strdup("SHLVL=0"));
	}
	data->env = first;
	return ;
}

int	ft_atoi(const char *nptr)
{
	long long	nmbr;
	long		is_neg;
	int			i;

	i = 0;
	is_neg = 1;
	nmbr = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		is_neg *= -1;
		i++;
	}
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		if ((nmbr == 922337203685477580 && nptr[i] > '7')
			|| nmbr > 922337203685477580)
			return (-1 * (is_neg != -1));
		nmbr = (nmbr * 10) + (nptr[i] - '0');
		i++;
	}
	return (nmbr * is_neg);
}

int	ft_env(t_env *env)
{
	while (env)
	{
		if (in('=', env->value))
		{
			ft_putstr_fd(env->value, STDOUT);
			ft_putstr_fd("\n", STDOUT);
		}
		env = env->next;
	}
	return (EXIT_SUCCESS);
}

int	ft_shlvl_plus(t_env *env)
{
	t_env	*tmp;
	int		i;
	char	*i_char;

	tmp = get_elem(env, "SHLVL");
	i = ft_atoi(tmp->value + 6);
	i_char = ft_itoa(++i);
	if (!i_char)
		return (EXIT_FAILURE);
	free(tmp->value);
	tmp->value = ft_strjoin("SHLVL=", i_char);
	free(i_char);
	if (!tmp->value)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

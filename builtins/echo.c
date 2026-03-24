/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:26:36 by akabbaj           #+#    #+#             */
/*   Updated: 2025/04/17 11:26:36 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_echo(char **args)
{
	int	i;
	int	n_op;

	i = 1;
	n_op = 0;
	if (nb_args(args) > 1)
	{
		while (args[i] && eqstr(args[i], "-n"))
		{
			n_op = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], STDOUT);
			if (args[i + 1] && args[i][0] != '\0')
				ft_putstr_fd(" ", STDOUT);
			i++;
		}
	}
	if (n_op == 0)
		ft_putstr_fd("\n", STDOUT);
	return (EXIT_SUCCESS);
}

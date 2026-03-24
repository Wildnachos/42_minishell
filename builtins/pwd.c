/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javera-m <javera-m@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:32:19 by javera-m          #+#    #+#             */
/*   Updated: 2025/03/31 13:26:00 by javera-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		ft_putstr_fd(cwd, STDOUT);
		ft_putstr_fd("\n", STDOUT);
		return (EXIT_SUCCESS);
	}
	else
	{
		perror("pwd");
		return (EXIT_FAILURE);
	}
}

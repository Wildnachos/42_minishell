/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:09:09 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/09 14:09:09 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	almost_atoi(char *str, int *err)
{
	unsigned long long	ret;
	int					i;
	int					j;
	int					pn;

	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	pn = 1;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			pn = -1;
	j = i;
	ret = 0;
	while ('0' <= str[i] && str[i] <= '9')
		ret = ret * 10 + (str[i++] - 48);
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] || i - j > 20 || ((pn == -1 && (ret - 1) > LONG_MAX) || \
		(pn == 1 && (ret > LONG_MAX))))
		*err = 1;
	return ((int)((ret * pn) % 256));
}

static int	print_exit(char *message, int ret)
{
	ft_putstr_fd(message, STDOUT);
	return (ret);
}

int	ft_exit(char **args)
{
	int	err;
	int	ret;

	ret = 0;
	err = 0;
	if (!args[1])
		return (print_exit("exit\n", ret));
	if (args[1])
	{
		ret = almost_atoi(args[1], &err);
		if (err)
		{
			ft_putstr_fd("exit\nminishell: exit: ", STDERR);
			ft_putstr_fd(args[1], STDERR);
			ft_putstr_fd(": numeric argument required\n", STDERR);
			return (2);
		}
		if (args[2])
		{
			ft_putstr_fd("exit\nminishell: exit:", STDOUT);
			ft_putstr_fd(" too many arguments\n", STDERR);
			return (1);
		}
	}
	return (print_exit("exit\n", ret));
}

int	syntax_error(t_token *res, t_data *data)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR);
	if (valid_tok(res) > 0)
		ft_putstr_fd(res[valid_tok(res)].word, STDERR);
	else if (valid_tok(res) == -2)
		ft_putstr_fd("newline", STDERR);
	else
		ft_putstr_fd(res[0].word, STDERR);
	ft_putstr_fd("'\n", STDERR);
	free_token(res);
	data->exit_code = 2;
	return (2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:03:50 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/14 10:47:15 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INITIALIZATION_H
# define INITIALIZATION_H
# include "minishell.h"
# include "parsing/parsing.h"
# include "execution/execution.h"

t_data	*init_env(int ac, char **av, char **env, int i);
void	redir_stds(t_data *data);
void	reset_stds(t_data *data);
int		empty_line(char *line);
int		valid_tok(t_token *token);

#endif
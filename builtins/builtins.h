/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:19:55 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/14 11:19:55 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "../minishell.h"
# include "../headers.h"
# include "../initialization.h"
# include "../utils/utils.h"

/*builtin*/
int			ft_exit(char **args);
int			ft_echo(char **args);
int			ft_cd(char **args, t_env *env);
int			ft_pwd(void);
int			ft_export(char **args, t_env *env);
int			ft_env(t_env *env);
int			ft_unset(char **args, t_env *env);
size_t		size_until_eq(char *env);
int			ft_shlvl_plus(t_env *env);
void		create_basic_env(int ac, char **av, t_data *data);

//builtin.c
int			is_builtin(char *command);
int			exec_builtin(t_command *cmd, t_env *env, t_data *data);

int			syntax_error(t_token *res, t_data *data);

#endif
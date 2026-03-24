/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:08:51 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/16 11:08:51 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "../minishell.h"
# include "../headers.h"
# include "../utils/utils.h"
# include "../builtins/builtins.h"
# include "../parsing/parsing.h"
# define CMD_NOT_EXEC 126
# define CMD_NOT_FOUND 127

//signals.c
void		handle_int_sig(int sig);
void		handle_signals(void);

//exec.c
int			exec(t_command *cmd, t_data *data);
void		close_all_fd(t_command *cmd);
void		error(int exit_code, char *message);

//exec_child.c
void		create_child_process(t_command *cmd, t_data *data, char *path,
				char **env_ch);

//find_cmd.c
char		*check_dir(char *bin, char *command);
int			error_message(char *path);
char		*path_join(const char *s1, const char *s2);
char		*find_cmd_in_env(char **path, t_data *data, char *cmd);
char		*ft_strchr(const char *s, int c);

//redirection.c
int			redirect_in_out(t_command *cmd, t_redir	*r, int i, t_data *data);
void		close_redir_fds(int *fd);
int			open_redir_fd(t_redir *r, t_data *data);
int			init_redir_fds(t_data *data, int count);

//heredoc.c
int			get_heredoc(t_redir	*r, t_data *data);
void		error(int exit_code, char *message);
bool		heredoc_after(t_redir	*r);
int			check_sigint_hook(void);
bool		failure(t_data *data);
int			finish_heredoc(char *str, char *delim, int *fd);
void		write_heredoc_line(char *str, int fd, t_data *data);
void		print_err_here(char *limit);

#endif
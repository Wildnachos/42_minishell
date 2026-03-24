/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:39:44 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/14 10:44:05 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../minishell.h"
# include "../headers.h"
# include "../utils/utils.h"

t_quote		which_quote(char quote);
t_token		*return_free(t_token *res);
int			loop_until(int *count, char *line, char c);
t_token		*add_word(t_slice slice, char *line, t_token *res);
t_token		*split_line(char *line, int count, int start, t_token *res);
t_command	*init_node(int pipein);
int			get_redir_type(char *token, t_quote quote);
char		**append(char **args, char *arg, int i, char **res);
int			insert_arg(char ***args, t_token token, int i);
int			add_arg(char ***args, t_token token);
t_command	*parse_line(t_token *tok, t_command *head, t_command *cmd, int i);
int			init_redirs(t_token *tok, int i, t_redir **redirs);
int			free_strarr(char **tofree);
int			single_char(int *start, int *count, char **line, t_token **res);
int			double_char(int *start, int *count, char **line, t_token **res);
t_token		*handle_quote(int *start, int *count, char **line, t_token **res);
int			handle_space(int *start, int *count, char **line, t_token **res);
t_slice		ret_slice(int start, int end, t_quote quote);
void		free_line(t_command *cmd);
int			free_redir_ret(t_redir *redir, int ret);
void		free_token(t_token *res);
void		expand_args(char **res, t_data *data, int i, int done);
void		handle_signal(int sig);
int			check_var(char *var, char *word);
int			handle_single_quotes(char **res, char **str, int i);
int			handle_double_quotes(char **res, char **str, int i, int *in_quotes);
int			handle_escape(char **res, char **str, int i, int in_quotes);
int			handle_dollar(char **res, char **str, int i, t_data *data);
int			check_arg_char(char c);
int			var_len(char *word);
int			check_var(char *var, char *word);
char		*find(char *word, t_env *env);
char		*ins_str_helper(int len, char *s);
char		*ins_str(char *newstr, char *s, int len);
int			single_loop(int *count, char *line, char c);
int			loop_until(int *count, char *line, char c);
t_token		*copy_prev(int i, t_token *res);
t_token		*add_word(t_slice slice, char *line, t_token *res);
int			is_operator(t_token tok);
int			check_arg_char(char c);
char		**free_strarr_char(char **tofree);
t_token		*finalize_tokens(int start, int count, char *lin, t_token *res);
t_token		*merge_tokens(t_token *tokens, int i, int j);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:40:04 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/14 09:45:48 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "../minishell.h"
# include "../headers.h"
# include "parsing/parsing.h"

//cmd_utils.c
bool		cmd_redir_out(t_command *cmd);
bool		cmd_redir_in(t_command *cmd);
bool		cmd_redir_app(t_command *cmd);

//utils_libft.c
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_isalpha(int c);
void		ft_putstr_fd(char *s, int fd);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			nb_args(char **args);

//utils_lst.c
t_env		*append_node(t_env *env, char *content);
void		free_data(t_data *data);
t_env		*get_elem(t_env *first, char *arg);

//utils_array.c
char		**env_to_arr(t_env *env);
void		sort_arr(char **arr);

int			ft_strlen(const char *s);
void		*ft_calloc(unsigned int nmemb, size_t size);
char		*ft_strdup(const char *s);
int			eqstr(char *s1, char *s2);
int			in(char c, char *char_set);
char		**ft_split(char *s, char *set);
char		*ft_substr(const char *s, unsigned int start, size_t len);
char		*ft_itoa(int n);
int			ft_isalnum(int c);
void		*ft_memcpy(void *dest, const void *src, size_t n);

int			free_word(char *word, int ret);
void		free_all_exit(t_command *line, char *input, t_data *data, int ret);
int			free_data_exit(t_data *data);
void		free_tokdata_exit(t_token *token, t_data *data, int ret);

#endif
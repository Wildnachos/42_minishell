/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:44:36 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/15 14:53:09 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define IN 0 // <
# define OUT 1 // >
# define APP 2 // >>
# define HERE 3 // <<
# define STDIN 0
# define STDOUT 1
# define STDERR 2

extern int	g_sig;

typedef struct s_redir
{
	int				type;
	char			*delim;
	struct s_redir	*next;
}	t_redir;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_command
{
	char				*com;
	char				**args;
	int					pipein;
	int					input;
	int					output;
	t_redir				*redir;
	struct s_command	*next;
}	t_command;

typedef struct s_data
{
	t_env		*env;
	char		*last_arg;
	int			exit_code;
	int			fd[2];
	int			*redir_fds;
	int			pid;
	char		*input;
	t_command	*head;
}	t_data;	

typedef enum e_quote
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_quote;

typedef struct s_token
{
	char	*word;
	t_quote	quote;
}	t_token;

typedef struct s_slice
{
	int		start;
	int		end;
	t_quote	quote;
}	t_slice;

#endif
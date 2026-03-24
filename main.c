/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:02:57 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/16 12:05:13 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "initialization.h"
#include "parsing/parsing.h"
#include "execution/execution.h"
#include "builtins/builtins.h"

int	g_sig = 0;

char	*last_arg(t_command *line)
{
	t_command	*next;
	int			i;

	i = 0;
	next = line->next;
	if (next || !line->args)
		return (0);
	while (line->args[i])
	{
		if (line->args[i] && !(line->args[i + 1]))
			break ;
		i++;
	}
	return (ft_strdup(line->args[i]));
}

int	run_command(t_command *line, char *input, t_data *data)
{
	int		ret;
	char	*tmp;

	data->input = input;
	data->head = line;
	redir_stds(data);
	ret = exec(line, data);
	reset_stds(data);
	tmp = last_arg(line);
	if (tmp)
	{
		free(data->last_arg);
		data->last_arg = tmp;
	}
	if (line->com && eqstr(line->com, "exit") && (ret != 1 || (line->args
				&& eqstr(line->args[1], "1"))))
		free_all_exit(line, input, data, ret);
	free_line(line);
	free(input);
	return (ret);
}

int	iswhitespace(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\n'
			&& *str != '\v' && *str != '\f' && *str != '\r')
			return (0);
		str++;
	}
	return (1);
}

int	handle_command(char *input, t_data *data)
{
	t_token		*res;
	int			ret;
	t_command	*line;
	t_command	*head;

	add_history(input);
	expand_args(&input, data, 0, 0);
	if (iswhitespace(input))
		return (0);
	res = split_line(input, 0, 0, 0);
	if (!res)
		return (free_word(input, 1));
	if (valid_tok(res))
		return (syntax_error(res, data));
	head = init_node(0);
	if (!head)
		free_tokdata_exit(res, data, 1);
	line = parse_line(res, head, head, 0);
	free_token(res);
	if (!line)
		free_all_exit(0, input, data, 1);
	ret = run_command(line, input, data);
	return (ret);
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_data		*data;
	int			ret;

	data = NULL;
	while (1)
	{
		signal(SIGPIPE, SIG_IGN);
		handle_signals();
		if (!data)
			data = init_env(ac, av, env, 0);
		if (!data)
			return (1);
		input = readline("minishell> ");
		if (!input)
			return (free_data_exit(data));
		if (empty_line(input))
		{
			free(input);
			continue ;
		}
		ret = handle_command(input, data);
	}
	free_data(data);
	return (ret);
}

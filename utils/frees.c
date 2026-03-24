/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:55:38 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/15 14:55:57 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	free_word(char *word, int ret)
{
	if (word)
		free(word);
	return (ret);
}

void	free_all_exit(t_command *line, char *input, t_data *data, int ret)
{
	line = line;
	free_line(data->head);
	if (input)
		free(input);
	free_data(data);
	exit(ret);
}

void	free_tokdata_exit(t_token *token, t_data *data, int ret)
{
	free_token(token);
	free_data(data);
	exit(ret);
}

int	free_data_exit(t_data *data)
{
	printf("exit\n");
	free_data(data);
	return (0);
}

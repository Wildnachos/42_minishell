/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 23:29:58 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/16 08:51:09 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "../builtins/builtins.h"

t_env	*get_elem(t_env *first, char *arg)
{
	t_env	*tmp;

	tmp = first;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, arg, size_until_eq(tmp->value)) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

void	free_data(t_data *data)
{
	t_env	*tmp;

	if (data)
	{
		while (data->env)
		{
			tmp = data->env;
			data->env = data->env->next;
			if (tmp->value)
				free (tmp->value);
			free (tmp);
		}
		if (data->last_arg)
			free(data->last_arg);
		if (data->redir_fds)
		{
			close_redir_fds(data->redir_fds);
			data->redir_fds = 0;
		}
		free(data);
	}
}

t_env	*ft_lstlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_env	*append_node(t_env *env, char *content)
{
	t_env	*new;
	t_env	*temp;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	if (!content)
		new->value = 0;
	else
		new->value = content;
	new->next = NULL;
	if (!env)
		env = new;
	else
	{
		temp = ft_lstlast(env);
		temp->next = new;
	}
	return (env);
}

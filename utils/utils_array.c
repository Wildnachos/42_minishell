/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:12:33 by akabbaj           #+#    #+#             */
/*   Updated: 2025/04/21 14:12:33 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	env_len(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

char	**env_to_arr(t_env *env)
{
	char	**arr;
	int		i;
	int		len;

	len = env_len(env);
	i = 0;
	arr = (char **)malloc(sizeof(char *) * (len + 1));
	if (!arr)
		return (NULL);
	while (env)
	{
		arr[i] = env->value;
		env = env->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

static int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	sort_arr(char **arr)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	len = arr_len(arr);
	i = -1;
	while (++i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strncmp(arr[i], arr[j], INT_MAX) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
	}
}

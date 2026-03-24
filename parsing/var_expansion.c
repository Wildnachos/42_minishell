/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:08:01 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/13 15:08:01 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	var_len(char *word)
{
	int	i;

	i = 0;
	if (!word || (!((word[i] >= 'A' && word[i] <= 'Z')
				|| (word[i] >= 'a' && word[i] <= 'z')
				|| (word[i] == '_'))))
		return (0);
	while (word[i] && ((word[i] >= 'A' && word[i] <= 'Z')
			|| (word[i] >= 'a' && word[i] <= 'z')
			|| (word[i] >= '0' && word[i] <= '9')
			|| (word[i] == '_')))
		i++;
	return (i);
}

int	check_var(char *var, char *word)
{
	int	i;

	i = 0;
	while (word[i] && var[i] != '=')
	{
		if (word[i] != var[i])
			return (0);
		i++;
	}
	if (!word[i] && var[i] == '=')
		return (1);
	return (0);
}

char	*find(char *word, t_env *env)
{
	char	**res_arr;
	char	*res;

	while (env)
	{
		if (check_var(env->value, word))
		{
			res_arr = ft_split(env->value, "=");
			if (!res_arr)
				return (0);
			res = ft_strdup(res_arr[1]);
			free(res_arr[0]);
			free(res_arr[1]);
			free(res_arr);
			if (!res)
				return (0);
			return (res);
		}
		env = env->next;
	}
	return (0);
}

char	*ins_str_helper(int len, char *s)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (NULL);
	ft_memcpy(tmp, s, len);
	tmp[len] = 0;
	return (tmp);
}

char	*ins_str(char *newstr, char *s, int len)
{
	char	*tmp;
	char	mini[2];
	int		old_len;

	if (len == 1)
	{
		mini[0] = s[0];
		mini[1] = '\0';
		s = mini;
	}
	if (!newstr)
		return (ins_str_helper(len, s));
	old_len = ft_strlen(newstr);
	tmp = malloc(sizeof(char) * (old_len + len + 1));
	if (!tmp)
		return (NULL);
	ft_memcpy(tmp, newstr, old_len);
	ft_memcpy(tmp + old_len, s, len);
	tmp[old_len + len] = 0;
	free(newstr);
	return (tmp);
}

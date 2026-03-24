/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:21:21 by akabbaj           #+#    #+#             */
/*   Updated: 2025/05/13 14:22:35 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_calloc(unsigned int nmemb, size_t size)
{
	char	*result;
	size_t	i;

	i = 0;
	if (!nmemb || !size)
		result = malloc(1);
	else
		result = malloc(size * nmemb);
	if (!result)
		return (0);
	result[0] = 0;
	while (i < (size * nmemb))
		result[i++] = 0;
	return (result);
}

char	*ft_strdup(const char *s)
{
	int			size;
	int			i;
	char		*result;

	i = 0;
	size = ft_strlen(s);
	if (size == 0)
		return (ft_calloc(1, 1));
	result = malloc(size + 1);
	if (!result)
		return (0);
	while (i < size)
	{
		result[i] = s[i];
		i++;
	}
	result[i] = 0;
	return (result);
}

int	eqstr(char *s1, char *s2)
{
	int	count;

	count = 0;
	while (s1[count] && s2[count])
	{
		if (s1[count] != s2[count])
			return (0);
		count++;
	}
	if (s1[count] == s2[count])
		return (1);
	return (0);
}

int	in(char c, char *char_set)
{
	int	count;

	count = 0;
	while (char_set[count])
	{
		if (char_set[count] == c)
			return (1);
		count++;
	}
	return (0);
}

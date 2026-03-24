/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_helper2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akabbaj <akabbaj@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:12:21 by akabbaj           #+#    #+#             */
/*   Updated: 2025/04/21 14:12:27 by akabbaj          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t			i;
	unsigned int	x;
	char			*substr;

	i = 0;
	x = ft_strlen(s);
	if (start >= x)
		return (ft_strdup(""));
	while (s[start + i] && i < len)
		i++;
	substr = (char *)malloc(sizeof(char) * (i + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

int	digs(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		dig;
	long	x;

	x = n;
	dig = digs(x);
	res = malloc(sizeof(char) * (dig + 1));
	if (!res)
		return (0);
	res[dig--] = 0;
	if (n == 0)
		res[0] = '0';
	if (x < 0)
	{
		res[0] = '-';
		x *= -1;
	}
	while (x > 0)
	{
		res[dig--] = (x % 10) + 48;
		x = x / 10;
	}
	return (res);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int		i;
	unsigned char		*str;
	const unsigned char	*str1;

	i = 0;
	if (!dest && !src)
		return (dest);
	str = dest;
	str1 = src;
	while (i < n)
	{
		str[i] = str1[i];
		i++;
	}
	return (dest);
}

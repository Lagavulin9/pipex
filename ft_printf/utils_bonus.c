/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 12:19:39 by jinholee          #+#    #+#             */
/*   Updated: 2022/08/23 12:55:42 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"
#include <stdlib.h>

void	ft_memcpy(char *dst, char *src, size_t n)
{
	size_t	i;

	if (!dst || !src)
		return ;
	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strcat(char *dst, char *src)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(dst);
	while (src[i])
	{
		dst[len + i] = src[i];
		i++;
	}
	dst[len + i] = '\0';
	return (dst);
}

char	*ft_chrdup(char c)
{
	char	*dup;

	if (c)
	{
		dup = malloc(2);
		if (dup)
		{
			dup[0] = c;
			dup[1] = '\0';
		}
	}
	else
	{
		dup = malloc(1);
		*dup = '\0';
	}
	return (dup);
}

char	*ft_strdup(char *str)
{
	size_t	i;
	char	*dup;

	if (!str)
		return (ft_strdup("(null)"));
	dup = malloc(ft_strlen(str) + 1);
	if (dup)
	{
		i = 0;
		while (str[i])
		{
			dup[i] = str[i];
			i++;
		}
		dup[i] = '\0';
	}
	return (dup);
}

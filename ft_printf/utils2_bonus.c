/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 12:20:44 by jinholee          #+#    #+#             */
/*   Updated: 2022/08/23 12:55:44 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"
#include <stdlib.h>

size_t	num_in_base_len(unsigned long num, int base_len)
{
	size_t	len;

	len = 0;
	while (1)
	{
		len++;
		num /= base_len;
		if (!num)
			break ;
	}
	return (len);
}

char	*ft_ltoa(long num, t_info *info)
{
	size_t		num_len;
	char		*result;

	if (num < 0)
	{
		num = -num;
		info->pos_sign = "-";
	}
	num_len = num_in_base_len(num, 10);
	result = malloc(num_len + 1);
	if (result)
	{
		result[num_len] = '\0';
		while (num_len > 0)
		{
			result[--num_len] = "0123456789"[num % 10];
			num /= 10;
		}
	}
	return (result);
}

char	*ft_hex_convert(unsigned long num, t_info *info)
{
	char	*result;
	size_t	num_len;

	if (info->format == 'x' || info->format == 'X')
		num = (unsigned int)num;
	num_len = num_in_base_len(num, 16);
	result = malloc(num_len + 1);
	if (result)
	{
		result[num_len] = '\0';
		while (num_len > 0)
		{
			result[--num_len] = "0123456789abcdef"[num % 16];
			num /= 16;
		}
	}
	return (result);
}

char	*to_uppercase(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if ('a' <= str[i] && str[i] <= 'z')
			str[i] -= 32;
		i++;
	}
	return (str);
}

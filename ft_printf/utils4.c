/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 12:23:56 by jinholee          #+#    #+#             */
/*   Updated: 2022/08/23 12:54:17 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>

size_t	get_len(t_info *info)
{
	const long	sign_len = ft_strlen(info->pos_sign);
	const long	radix_len = ft_strlen(info->radix);
	const long	str_len = ft_strlen(info->ret);
	long		total;

	total = sign_len + radix_len + str_len;
	if (info->width > total)
		total = info->width;
	info->width = info->width - sign_len - radix_len - str_len;
	return (total);
}

char	*str_slice(char *result, t_info *info, long len)
{
	if (*(info->ret) == '0' && len == 0)
	{
		result = malloc(1);
		if (result)
		{
			*result = '\0';
			free(info->ret);
			info->ret = result;
		}
	}
	else if (info->precision < len)
	{
		result = malloc(info->precision + 1);
		if (result)
		{
			info->ret[info->precision] = '\0';
			*result = '\0';
			ft_strcat(result, info->ret);
			free(info->ret);
			info->ret = result;
		}
	}
	return (result);
}

char	*precision_fill(t_info *info)
{
	long	len;
	char	*result;

	len = (long)ft_strlen(info->ret);
	result = info->ret;
	if (info->format == 's' && info->precision >= 0)
		result = str_slice(result, info, len);
	else if (info->precision > len)
	{
		result = malloc(info->precision + 1);
		if (result)
		{
			*result = '\0';
			while (info->precision-- > len)
				ft_strcat(result, "0");
			ft_strcat(result, info->ret);
			free(info->ret);
			info->ret = result;
		}
	}
	else if (is_num_format(info->format) && info->precision == 0)
		result = str_slice(result, info, 0);
	return (result);
}

char	*width_fill(char *result, t_info *info)
{
	if (info->precision >= 0)
		info->fill = " ";
	if (info->zfill && info->precision < 0)
	{
		ft_strcat(result, info->pos_sign);
		while (info->width-- > 0)
			ft_strcat(result, info->fill);
	}
	else
	{
		while (info->width-- > 0)
			ft_strcat(result, info->fill);
		ft_strcat(result, info->pos_sign);
	}
	return (result);
}

int	null_print(t_info *info)
{
	int		len;

	len = 0;
	if (info->ljust)
	{
		len += write(1, "\0", 1);
		while (info->width-- > 1)
			len += write(1, " ", 1);
	}
	else
	{
		while (info->width-- > 1)
			len += write(1, " ", 1);
		len += write(1, "\0", 1);
	}
	free(info->ret);
	return (len);
}

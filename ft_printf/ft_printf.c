/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:55:08 by jinholee          #+#    #+#             */
/*   Updated: 2022/08/23 12:55:35 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

void	init(t_info *info)
{
	info->ljust = 0;
	info->precision = -1;
	info->width = 0;
	info->zfill = 0;
	info->fill = " ";
	info->pos_sign = "";
	info->radix = "";
	info->ret = "";
	info->total = 0;
}

void	set_flags(t_info *info, char *str, size_t *i)
{
	while (!is_format(str[*i]))
	{
		if (str[*i] == '-')
			info->ljust = 1;
		if (str[*i] == '0' && !is_digit(str[*i - 1]))
		{
			info->zfill = 1;
			info->fill = "0";
		}
		if (str[*i] == '.')
			info->precision = get_precision(str, i);
		else if (is_digit(str[*i]))
			info->width = info->width * 10 + str[*i] - '0';
		if (str[*i] == ' ' && *(info->pos_sign) != '+')
			info->pos_sign = " ";
		if (str[*i] == '+')
			info->pos_sign = "+";
		if (str[*i] == '#')
			info->radix = "0x";
		(*i)++;
	}
}

void	set_ret(t_info *info, char format, va_list ap)
{
	info->format = format;
	if (format == 'c')
		info->ret = ft_chrdup(va_arg(ap, int));
	else if (format == 's')
		info->ret = ft_strdup(va_arg(ap, char *));
	else if (format == 'p')
	{
		info->ret = ft_hex_convert((size_t)va_arg(ap, void *), info);
		info->radix = "0x";
	}
	else if (format == 'd' || format == 'i')
		info->ret = ft_ltoa(va_arg(ap, int), info);
	else if (format == 'u')
		info->ret = ft_ltoa((unsigned int)va_arg(ap, int), info);
	else if (format == 'x' || format == 'X')
	{
		info->ret = ft_hex_convert(va_arg(ap, int), info);
		if (*(info->ret) == '0')
			info->radix = "";
	}
	else if (format == '%')
		info->ret = ft_chrdup('%');
	precision_fill(info);
}

int	format_write(char *str, size_t *i, va_list ap)
{
	t_info	info;
	int		len;
	char	*result;

	init(&info);
	set_flags(&info, str, i);
	set_ret(&info, str[(*i)++], ap);
	if (info.format == 'c' && ft_strlen(info.ret) == 0)
		len = null_print(&info);
	else
	{
		if (info.ljust)
			result = ljust(&info);
		else
			result = join(&info);
		if (info.format == 'X')
			to_uppercase(result);
		len = write(1, result, ft_strlen(result));
		free(info.ret);
		free(result);
	}
	return (len);
}

int	ft_printf(const char *str, ...)
{
	size_t	i;
	int		len;
	int		temp;
	va_list	ap;

	va_start(ap, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			temp = format_write((char *)str, &i, ap);
			if (temp == -1)
				return (-1);
			len += temp;
		}
		else
			len += write(1, str + i++, 1);
	}
	va_end(ap);
	return (len);
}

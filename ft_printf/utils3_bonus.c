/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 12:21:42 by jinholee          #+#    #+#             */
/*   Updated: 2022/08/23 12:56:30 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	is_digit(char c)
{
	return ('0' <= c && c <= '9');
}

int	is_flag(char c)
{
	return (c == '-' || c == '0' || c == '.'
		|| c == '#' || c == ' ' || c == '+');
}

int	is_format(char c)
{
	return (c == 'c' || c == 's' || c == 'p'
		|| c == 'd' || c == 'i' || c == 'u'
		|| c == 'x' || c == 'X' || c == '%');
}

int	is_num_format(char c)
{
	return (c == 'd' || c == 'i' || c == 'u'
		|| c == 'x' || c == 'X');
}

long	get_precision(char *str, size_t *i)
{
	long	num;

	num = 0;
	(*i)++;
	while (is_digit(str[*i]))
	{
		num = num * 10 + (str[*i] - '0');
		(*i)++;
	}
	(*i)--;
	return (num);
}

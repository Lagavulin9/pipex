/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 12:22:49 by jinholee          #+#    #+#             */
/*   Updated: 2022/08/23 12:24:55 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

char	*join(t_info *info)
{
	char	*result;

	result = malloc(get_len(info) + 1);
	if (result)
	{
		*result = '\0';
		if (is_num_format(info->format) && info->zfill \
			&& info->precision < 0)
		{
			ft_strcat(result, info->radix);
			result = width_fill(result, info);
		}
		else
		{
			result = width_fill(result, info);
			ft_strcat(result, info->radix);
		}
		ft_strcat(result, info->ret);
	}
	return (result);
}

char	*ljust(t_info *info)
{
	char	*result;

	result = malloc(get_len(info) + 1);
	if (result)
	{
		*result = '\0';
		ft_strcat(result, info->pos_sign);
		ft_strcat(result, info->radix);
		ft_strcat(result, info->ret);
		while (info->width-- > 0)
			ft_strcat(result, " ");
	}
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:00:45 by jinholee          #+#    #+#             */
/*   Updated: 2022/11/10 12:29:53 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

int	init(int fd, char **line, t_gnl *gnl)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	else
	{
		*line = 0;
		gnl->total = 0;
		gnl->len = 0;
		return (1);
	}
}

void	*gnl_memcpy(char *dst, char *src, size_t n)
{
	size_t	i;

	if (!dst || !src)
		return (0);
	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

int	buf_end(char **line, t_gnl *gnl)
{
	if (gnl->rbyte == -1 || (!gnl->rbyte && !gnl->total))
	{
		free(*line);
		*line = 0;
		gnl->index = BUFFER_SIZE;
		gnl->rbyte = BUFFER_SIZE;
		return (1);
	}
	if (!gnl->rbyte && gnl->total)
	{
		gnl->index = BUFFER_SIZE;
		gnl->rbyte = BUFFER_SIZE;
		return (1);
	}
	return (0);
}

char	*join(char *line, t_gnl *gnl)
{
	char	*buffer;
	char	*new_line;

	buffer = gnl->buffer + gnl->index - gnl->len;
	new_line = malloc(gnl->total + gnl->len + 1);
	if (!new_line)
		return (0);
	if (line)
	{
		gnl_memcpy(new_line, line, gnl->total);
		free(line);
	}
	gnl_memcpy(new_line + gnl->total, (char *)buffer, gnl->len);
	gnl->total += gnl->len;
	gnl->len = 0;
	new_line[gnl->total] = 0;
	return (new_line);
}

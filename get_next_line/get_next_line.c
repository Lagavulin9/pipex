/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:41:28 by jinholee          #+#    #+#             */
/*   Updated: 2022/11/10 12:30:15 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd)
{
	static t_gnl	gnl = {"", BUFFER_SIZE, 0, 0, BUFFER_SIZE};
	char			*line;

	if (!init(fd, &line, &gnl))
		return (0);
	while (1)
	{
		if ((size_t)gnl.rbyte == gnl.index)
		{
			line = join(line, &gnl);
			gnl.rbyte = read(fd, gnl.buffer, BUFFER_SIZE);
			if (buf_end(&line, &gnl))
				return (line);
			gnl.index = 0;
		}
		if (gnl.buffer[gnl.index] == '\n')
		{
			gnl.index++;
			gnl.len++;
			return (join(line, &gnl));
		}
		gnl.index++;
		gnl.len++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:00:20 by jinholee          #+#    #+#             */
/*   Updated: 2022/11/10 12:29:28 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_gnl
{
	char	buffer[BUFFER_SIZE];
	size_t	index;
	size_t	len;
	size_t	total;
	ssize_t	rbyte;
}				t_gnl;

int		init(int fd, char **line, t_gnl *gnl);
void	*gnl_memcpy(char	*dst, char *src, size_t n);
int		buf_end(char **line, t_gnl *gnl_memcpy);
char	*join(char *line, t_gnl *gnl);
char	*get_next_line(int fd);

#endif

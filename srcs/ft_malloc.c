/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:31:24 by jinholee          #+#    #+#             */
/*   Updated: 2022/11/16 20:27:16 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

void	free_split(char **splitted)
{
	int	i;

	i = 0;
	while (splitted[i])
		free(splitted[i++]);
	free(splitted);
}

void	ft_exit(char *msg, int exit_status)
{
	if (msg)
		write(2, msg, ft_strlen(msg));
	exit(exit_status);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		ft_exit("malloc error\n", 1);
	return (ptr);
}
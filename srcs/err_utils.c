/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 21:35:12 by jinholee          #+#    #+#             */
/*   Updated: 2022/11/17 14:27:40 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	free_split(char **splitted)
{
	int	i;

	i = 0;
	while (splitted[i])
		free(splitted[i++]);
	free(splitted);
}

void	perror_exit(char *msg, int exit_status)
{
	perror(msg);
	exit(exit_status);
}

void	usage_msg(void)
{
	ft_putendl_fd(USAGE_MSG, 2);
	exit(1);
}

void	command_not_found(char *cmd)
{
	ft_putstr_fd(NOT_FOUND_MSG, 2);
	ft_putendl_fd(cmd, 2);
	exit(127);
}

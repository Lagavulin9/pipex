/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:19:27 by jinholee          #+#    #+#             */
/*   Updated: 2022/11/10 17:42:57 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc == 5)
	{
		printf("%s\n", argv[--argc]);
	}
	else
		write(1, usage_msg, ft_strlen(usage_msg));
	return (0);
}
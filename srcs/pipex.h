/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:19:32 by jinholee          #+#    #+#             */
/*   Updated: 2022/11/10 17:48:03 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# define usage_msg "usage : pipex <file1> <cmd1> <cmd2> <file2>\n"


typedef struct s_info
{
	int	i;
}			t_info;

void	ft_exit(char *msg, int exit_status);
void	*ft_malloc(size_t size);

#endif
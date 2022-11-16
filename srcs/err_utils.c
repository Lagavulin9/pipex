/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 21:35:12 by jinholee          #+#    #+#             */
/*   Updated: 2022/11/16 21:35:32 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	perror_exit(char *str)
{
	perror(str);
	exit(errno);
}

void	usage_msg(void)
{
	write(1, USAGE_MSG, ft_strlen(USAGE_MSG));
	exit(1);
}

void	command_not_found(char *cmd)
{
	//127로 수정
	write(2, NOT_FOUND_MSG, ft_strlen(NOT_FOUND_MSG));
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	exit(1);
}
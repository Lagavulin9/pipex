/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:19:27 by jinholee          #+#    #+#             */
/*   Updated: 2022/11/17 16:34:25 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void	set_fd(t_info *info, int arg_idx)
{
	int	to_stdin;
	int	to_stdout;

	if (arg_idx == 2)
	{
		to_stdin = open_file(info->infile, O_RDONLY);
		to_stdout = info->pipe_fd[WRITE];
	}
	else if (arg_idx == info->argc - 2)
	{
		to_stdin = info->prev;
		to_stdout = open_file(info->outfile, O_CREAT | O_TRUNC | O_RDWR);
	}
	else
	{
		to_stdin = info->prev;
		to_stdout = info->pipe_fd[WRITE];
	}
	if (dup2(to_stdin, STDIN_FILENO) == -1 || \
			dup2(to_stdout, STDOUT_FILENO) == -1)
		perror_exit("dup2", 1);
	close(to_stdin);
	close(to_stdout);
	close(info->pipe_fd[READ]);
}

void	set_info(t_info *info, int argc, char *argv[])
{
	info->argc = argc;
	info->infile = argv[1];
	info->outfile = argv[argc - 1];
	info->prev = -1;
}

int main(int argc, char *argv[], char *envp[])
{
	t_info	info;
	pid_t	pid;
	int		arg_idx;

	if (argc < 5)
		usage_msg();
	info.argc = argc;
	info.infile = argv[1];
	info.outfile = argv[argc - 1];
	info.prev = -1;
	arg_idx = 2;
	while (arg_idx < argc - 1)
	{
		if (pipe(info.pipe_fd) == -1)
			perror_exit("pipe", 1);
		pid = fork();
		if (pid == -1)
			perror_exit("fork", 1);
		if (pid == 0)
		{
			set_fd(&info, arg_idx);
			execute(argv, envp, arg_idx);
		}
		else
		{
			close(info.pipe_fd[WRITE]);
			close(info.prev);
			info.prev = info.pipe_fd[READ];
			arg_idx++;
		}
	}
	close(info.pipe_fd[READ]);
	while (arg_idx-- > 2)
		waitpid(-1, 0, 0);
	return (0);
}
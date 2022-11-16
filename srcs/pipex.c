/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:19:27 by jinholee          #+#    #+#             */
/*   Updated: 2022/11/16 21:35:30 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include "ft_printf.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

void	child_process(int argc, char *argv[], char *envp[], int arg_idx)
{
	pid_t	pid;
	static int		prev = 0;
	int		pipe_fd[2];
	int		file_fd;

	if (pipe(pipe_fd) == -1)
		perror_exit("pipe");
	pid = fork();
	if (pid == -1)
		perror_exit("fork");
	if (pid == 0)
	{
		close(pipe_fd[READ]);
		if (arg_idx == 2)
		{
			file_fd = open_file(argv[1], O_RDONLY);
			dup2(file_fd, 0);
			dup2(pipe_fd[WRITE], 1);
			close(file_fd);
			close(pipe_fd[WRITE]);
			close(prev);
		}
		else if (arg_idx == argc - 2)
		{
			file_fd = open_file(argv[argc - 1], O_CREAT | O_TRUNC | O_RDWR);
			dup2(file_fd, 1);
			dup2(prev, 0);
			close(file_fd);
			close(prev);
		}
		else
		{
			dup2(prev, 0);
			dup2(pipe_fd[WRITE], 1);
			close(pipe_fd[WRITE]);
			close(prev);
		}
		execute(argv, envp, arg_idx);
		exit(0);
	}
	else
	{
		close(pipe_fd[WRITE]);
		prev = pipe_fd[READ];
		if (arg_idx < argc - 2)
			child_process(argc, argv, envp, arg_idx + 1);
		waitpid(pid, 0, 0);
	}
}

int main(int argc, char *argv[], char *envp[])
{
	pid_t	pid;
	int		pipe_fd[2];
	int		file_fd;
	int		arg_idx;
	int		prev;

	if (argc < 5)
		usage_msg();
	arg_idx = 2;
	prev = -1;
	while (arg_idx < argc - 1)
	{
		if (pipe(pipe_fd) == -1)
			perror_exit("pipe");
		pid = fork();
		if (pid == -1)
			perror_exit("fork");
		if (pid == 0)
		{
			//fprintf(stderr, "%s, read : %d, write : %d prev : %d\n", argv[arg_idx], pipe_fd[READ], pipe_fd[WRITE], prev);
			if (arg_idx == 2)
			{
				file_fd = open_file(argv[1], O_RDONLY);
				dup2(file_fd, 0);
				dup2(pipe_fd[WRITE], 1);
				close(file_fd);
				close(pipe_fd[WRITE]);
			}
			else if (arg_idx == argc - 2)
			{
				file_fd = open_file(argv[argc - 1], O_CREAT | O_TRUNC | O_RDWR);
				dup2(file_fd, 1);
				dup2(prev, 0);
				close(file_fd);
				close(prev);
			}
			else
			{
				dup2(prev, 0);
				dup2(pipe_fd[WRITE], 1);
				close(pipe_fd[WRITE]);
				close(prev);
			}
			close(pipe_fd[READ]);
			execute(argv, envp, arg_idx);
			//exit(0);
		}
		else
		{
			close(pipe_fd[WRITE]);
			close(prev);
			prev = pipe_fd[READ];
			arg_idx++;
		}
	}
	close(pipe_fd[READ]);
	while (arg_idx-- > 2)
		waitpid(-1, 0, 0);
	return (0);
}
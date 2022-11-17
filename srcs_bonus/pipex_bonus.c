/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:19:27 by jinholee          #+#    #+#             */
/*   Updated: 2022/11/17 20:39:38 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft.h"
#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void	set_info(t_info *info, int argc, char *argv[], char *envp[])
{
	info->argc = argc;
	info->infile = argv[1];
	info->outfile = argv[argc - 1];
	info->delimiter = ft_strjoin(argv[2], "\n");
	info->prev = -1;
	info->argv = argv;
	info->envp = envp;
}

void	set_fd(t_info *info, int arg_idx)
{
	int	to_stdin;
	int	to_stdout;

	to_stdin = info->prev;
	to_stdout = info->pipe_fd[WRITE];
	if (arg_idx == 2)
		to_stdin = open_file(info->infile, O_RDONLY);
	else if (ft_strncmp(info->infile, "here_doc", 9) == 0 && arg_idx == 3)
		to_stdin = open_file(TMP_FILE, O_CREAT | O_RDWR);
	if (arg_idx == info->argc - 2)
	{
		if (ft_strncmp(info->infile, "here_doc", 9) == 0)
			to_stdout = open_file(info->outfile, O_CREAT | O_RDWR | O_APPEND);
		else
			to_stdout = open_file(info->outfile, O_CREAT | O_RDWR | O_TRUNC);
	}
	if (dup2(to_stdin, STDIN_FILENO) == -1 || \
			dup2(to_stdout, STDOUT_FILENO) == -1)
		perror_exit("dup2", 1);
	close(to_stdin);
	close(to_stdout);
	close(info->pipe_fd[READ]);
}

void	child_process(t_info *info, int arg_idx)
{
	pid_t	pid;

	if (pipe(info->pipe_fd) == -1)
		perror_exit("pipe", 1);
	pid = fork();
	if (pid == -1)
		perror_exit("fork", 1);
	if (pid == 0)
	{
		set_fd(info, arg_idx);
		execute(info->argv, info->envp, arg_idx);
		exit(0);
	}
	close(info->pipe_fd[WRITE]);
	close(info->prev);
	info->prev = info->pipe_fd[READ];
}

void	here_doc(t_info *info)
{
	char	*line;
	int		tmp_file;

	tmp_file = open_file(TMP_FILE, O_CREAT | O_RDWR);
	while (1)
	{
		write(STDOUT_FILENO, "pipe heredoc> ", 14);
		line = get_next_line(0);
		if (line)
		{
			if (ft_strncmp(line, info->delimiter, \
				ft_strlen(info->delimiter)) == 0)
			{
				free(line);
				break ;
			}
			write(tmp_file, line, ft_strlen(line));
			free(line);
		}
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_info	info;
	int		arg_idx;

	if (argc < 5)
		usage_msg();
	set_info(&info, argc, argv, envp);
	arg_idx = 1;
	if (ft_strncmp(info.infile, "here_doc", 9) == 0)
	{
		if (argc != 6)
			usage_msg();
		here_doc(&info);
		arg_idx++;
	}
	while (++arg_idx < argc - 1)
		child_process(&info, arg_idx);
	close(info.pipe_fd[READ]);
	while (arg_idx-- > 2)
		waitpid(-1, 0, 0);
	unlink(TMP_FILE);
	return (0);
}

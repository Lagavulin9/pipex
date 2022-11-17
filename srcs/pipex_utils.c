/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 21:33:45 by jinholee          #+#    #+#             */
/*   Updated: 2022/11/17 20:24:03 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

int	open_file(char *file_path, int options)
{
	int	fd;

	fd = open(file_path, options, 0644);
	if (fd == -1)
		perror_exit(file_path, 1);
	return (fd);
}

char	**get_path(char **envp)
{
	char	**path;
	char	*temp;
	int		i;

	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH=", 5))
		{
			path = ft_split(*envp + 5, ':');
			if (path)
			{
				i = 0;
				while (path[i])
				{
					temp = path[i];
					path[i] = ft_strjoin(path[i], "/");
					i++;
					free(temp);
				}
			}
			return (path);
		}
		envp++;
	}
	return (0);
}

char	*get_executable_path(char **argv, char **envp, int idx)
{
	char	**path;
	char	**cmd;
	char	*file_path;
	int		i;

	path = get_path(envp);
	if (!path)
		perror_exit(0, 1);
	cmd = ft_split(argv[idx], ' ');
	if (!*cmd)
		command_not_found("");
	i = 0;
	while (path[i])
	{
		file_path = ft_strjoin(path[i++], *cmd);
		if (access(file_path, F_OK) == 0)
			break ;
		free(file_path);
		file_path = 0;
	}
	free_split(path);
	free_split(cmd);
	return (file_path);
}

void	execute(char **argv, char **envp, int arg_idx)
{
	char	*exec_path;
	char	**cmd;

	cmd = ft_split(argv[arg_idx], ' ');
	exec_path = get_executable_path(argv, envp, arg_idx);
	if (!exec_path)
		command_not_found(*cmd);
	if (access(exec_path, X_OK) == -1)
		perror_exit(*cmd, 1);
	execve(exec_path, cmd, envp);
}

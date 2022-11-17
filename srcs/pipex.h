/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:19:32 by jinholee          #+#    #+#             */
/*   Updated: 2022/11/17 16:27:19 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# define USAGE_MSG "usage: pipex <file1> <cmd1> <cmd2> <file2>"
# define NOT_FOUND_MSG "zsh: command not found: "
# define READ 0
# define WRITE 1

typedef struct s_info
{
	int		argc;
	int		prev;
	int		pipe_fd[2];
	char	*infile;
	char	*outfile;
	char	**argv;
	char	**envp;
}				t_info;

void	perror_exit(char *msg, int exit_status);
void	usage_msg(void);
void	command_not_found(char *cmd);

void	free_split(char **splitted);
void	*ft_malloc(size_t size);

int		open_file(char *file_path, int options);
char	**get_path(char **envp);
char	*get_executable_path(char **argv, char **envp, int idx);
void	execute(char **argv, char **envp, int arg_idx);

#endif
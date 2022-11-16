/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:19:32 by jinholee          #+#    #+#             */
/*   Updated: 2022/11/15 13:10:51 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# define USAGE_MSG "usage : pipex <file1> <cmd1> <cmd2> <file2>\n"
# define NOT_FOUND_MSG "zsh : command not found: "
# define READ 0
# define WRITE 1

typedef struct s_info
{
	char	**path;
	char	*infile;
	char	*outfile;
	char	**cmd;
	int		infile_fd;
	int		outfile_fd;
	char	*exec_path;
	int		cmd_idx;
	int		argc;
	char	**argv;
	char	**envp;
}			t_info;

void	free_split(char **splitted);
void	ft_exit(char *msg, int exit_status);
void	*ft_malloc(size_t size);

#endif
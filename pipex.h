/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:36:36 by lonulli           #+#    #+#             */
/*   Updated: 2025/01/22 16:36:37 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/*Cmd handlers*/

void	first_child(int infile, char *av, int *i, char **environ);
void	middle_childs(char *av);
void	parent(int outfile, char *av);
void	heredoc(char *limiter, int ac, int *i);

/*Utils*/

int		ft_strcmp(char *s1, char *s2);
char	**get_args(char *av);
char	*pathfinder(const char *cmd, char **env);
void	free_paths(char **path, char error);
void	free_args(char **args);
int		ft_strlen_pipex(char *str);
char	*gnl_pipex(char **line);
void	check_ac(int ac, int *infile, int *outfile);

/*Error handlers*/

int		check_file_existence(char *infile, char *outfile);
void	custom_dup2(int fd, char *flag);
void	custom_pipe(int fds[2]);
void	custom_unlink(char *filepath);
void	check_fork(pid_t pid, int wefd, int refd);
void	close_fds(int wefd, int refd);
void	free_and_close(char **args, char *cmd_path, int fds[2], char error);
void	close_remaining_fds(int outfile, int infile);

#endif

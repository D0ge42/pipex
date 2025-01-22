/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:35:51 by lonulli           #+#    #+#             */
/*   Updated: 2025/01/22 16:35:52 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>

void	custom_dup2(int fd, char *flag)
{
	if (!ft_strcmp(flag, "STDIN"))
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			exit(EXIT_FAILURE);
		}
	}
	else if (!ft_strcmp(flag, "STDOUT"))
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			exit(EXIT_FAILURE);
		}
	}
}

void	custom_pipe(int fds[2])
{
	if (pipe(fds) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(EXIT_FAILURE);
	}
}

void	check_fork(pid_t pid, int wefd, int refd)
{
	if (pid < 0)
	{
		close(wefd);
		close(refd);
		ft_putstr_fd(strerror(errno), 2);
		exit(EXIT_FAILURE);
	}
}

void	close_fds(int wefd, int refd)
{
	close(wefd);
	close(refd);
}

void	custom_unlink(char *filepath)
{
	if (unlink(filepath) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(EXIT_FAILURE);
	}
}

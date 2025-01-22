/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:35:37 by lonulli           #+#    #+#             */
/*   Updated: 2025/01/22 16:35:38 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

/*Function that will execute the first command.
It will get data from infile rather than from STDIN thanks to dup2
After that it will set fd[1] to be the new stdout.
This way whatever will be written in the write end of the pipe
can be read from the write end of the pipe by middle childs*/

void	first_child(int infile, char *av, int *i, char **environ)
{
	pid_t		pid;
	int			fds[2];
	char		**args;
	char		*cmd_path;

	cmd_path = NULL;
	pid = 0;
	args = NULL;
	custom_pipe(fds);
	pid = fork();
	check_fork(pid, fds[1], fds[0]);
	args = get_args(av);
	if (pid == 0)
	{
		custom_dup2(infile, "STDIN");
		custom_dup2(fds[1], "STDOUT");
		cmd_path = pathfinder(args[0], environ);
		if (access(cmd_path, F_OK) == -1)
			free_and_close(args, cmd_path, fds, 'Y');
		if (execve(cmd_path, args, environ) == -1)
			free_and_close(args, cmd_path, fds, 'Y');
	}
	custom_dup2(fds[0], "STDIN");
	*i += 3;
	free_and_close(args, cmd_path, fds, 'N');
}

/*Middle childs are handled in a different way. They read from the
previous read end of the pipe and write on the current write end of the pipe.
We'll set fd[0] to be the new stdin.
We'll also set fd[1] to be the new stdout,
	to make it so data can be read after.*/

void	middle_childs(char *av)
{
	int			fds[2];
	pid_t		pid;
	extern char	**environ;
	char		**args;
	char		*cmd_path;

	cmd_path = NULL;
	args = NULL;
	custom_pipe(fds);
	pid = fork();
	check_fork(pid, fds[1], fds[0]);
	args = get_args(av);
	if (pid == 0)
	{
		if (!args)
			return ;
		custom_dup2(fds[1], "STDOUT");
		cmd_path = pathfinder(args[0], environ);
		if (access(cmd_path, F_OK) == -1)
			free_and_close(args, cmd_path, fds, 'Y');
		if (execve(cmd_path, args, environ) == -1)
			free_and_close(args, cmd_path, fds, 'Y');
	}
	custom_dup2(fds[0], "STDIN");
	free_and_close(args, cmd_path, fds, 'N');
}

/*Parent will execute the last command and set output file descriptor
to be the new stdout. This way the data will be stored inside outfile rather
than going on STDOUT.*/

void	parent(int outfile, char *av)
{
	pid_t		pid;
	int			fds[2];
	extern char	**environ;
	char		**args;
	char		*cmd_path;

	cmd_path = NULL;
	custom_pipe(fds);
	pid = fork();
	check_fork(pid, fds[1], fds[0]);
	args = get_args(av);
	if (pid == 0)
	{
		custom_dup2(outfile, "STDOUT");
		cmd_path = pathfinder(args[0], environ);
		if (access(cmd_path, F_OK) == -1)
			free_and_close(args, cmd_path, fds, 'Y');
		if (execve(cmd_path, args, environ) == -1)
			free_and_close(args, cmd_path, fds, 'Y');
	}
	free_and_close(args, cmd_path, fds, 'N');
}

/*Heredoc is short for "heredocument".
In our case it's used to pass multi-line input to a command or program.
A prompt will open and we can type stuff that will be passed to cmds as if it
was being read from a file.
Whatever will be wrote in the terminal, will be redirected to a temporary file
from which we'll read data from next child.*/

void	heredoc(char *limiter, int ac, int *i)
{
	char	*line;
	int		tmp_file;

	if (ac < 6)
		exit(EXIT_FAILURE);
	tmp_file = open("tmp_file.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	limiter = ft_strjoin(limiter, "\n");
	while (1)
	{
		line = gnl_pipex(&line);
		if (!ft_strcmp(line, limiter))
			break ;
		if (!line)
			continue ;
		ft_putstr_fd(line, tmp_file);
		free(line);
	}
	free(line);
	free(limiter);
	tmp_file = open("tmp_file.txt", O_RDONLY);
	custom_dup2(tmp_file, "STDIN");
	close(tmp_file);
	custom_unlink("tmp_file.txt");
	*i += 3;
}

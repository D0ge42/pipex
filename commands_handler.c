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

void	first_child(int infile, char *av, int *i)
{
	pid_t		pid;
	extern char	**environ;
	int			fd[2];
	char		**args;

	pid = 0;
	args = NULL;
	custom_pipe(fd);
	pid = fork();
	check_fork(pid, fd[1], fd[0]);
	if (pid == 0)
	{
		args = get_args(av);
		custom_dup2(infile, "STDIN");
		custom_dup2(fd[1], "STDOUT");
		if (access(pathfinder(args[0], environ), F_OK) == -1)
		{
			perror("Command not found");
			close_fds(fd[1], fd[0]);
			exit(1);
		}
		if (execve(pathfinder(args[0], environ), args, environ) == -1)
		{
			close_fds(fd[1], fd[0]);
			ft_putstr_fd(strerror(errno), 2);
		}
	}
	custom_dup2(fd[0], "STDIN");
	close_fds(fd[1], fd[0]);
	*i += 3;
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

	pid = 0;
	args = NULL;
	custom_pipe(fds);
	pid = fork();
	check_fork(pid, fds[1], fds[0]);
	if (pid == 0)
	{
		args = get_args(av);
		if (!args)
			return ;
		custom_dup2(fds[1], "STDOUT");
		if (access(pathfinder(args[0], environ), F_OK) == -1)
		{
			perror("Command not found");
			close_fds(fds[1], fds[0]);
			exit(1);
		}
		if (execve(pathfinder(args[0], environ), args, environ) == -1)
		{
			close_fds(fds[1], fds[0]);
			ft_putstr_fd(strerror(errno), 2);
		}
	}
	custom_dup2(fds[0], STDIN_FILENO);
	close_fds(fds[1], fds[0]);
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
	int			i;

	i = 0;
	custom_pipe(fds);
	pid = fork();
	check_fork(pid, fds[1], fds[0]);
	args = get_args(av);
	if (pid == 0)
	{
		custom_dup2(outfile, "STDOUT");
		if (access(pathfinder(args[0], environ), F_OK) == -1)
		{
			perror("Command not found");
			close_fds(fds[1], fds[0]);
			exit(1);
		}
		if (execve(pathfinder(args[0], environ), args, environ) == -1)
		{
			close_fds(fds[1], fds[0]);
			ft_putstr_fd(strerror(errno), 2);
		}
	}
	while (args[i])
		free(args[i++]);
	free(args);
	close_fds(fds[1], fds[0]);
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

	line = NULL;
	tmp_file = open("tmp_file.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (ac < 6)
		exit(EXIT_FAILURE);
	limiter = ft_strjoin(limiter, "\n");
	if (!limiter)
		exit(EXIT_FAILURE);
	while (1)
	{
		ft_putstr_fd("here_doc >", 1);
		line = get_next_line(0);
		if (!line)
		{
			free(limiter);
			exit(EXIT_FAILURE);
		}
		if (!ft_strcmp(line, limiter))
		{
			free(limiter);
			free(line);
			break ;
		}
		ft_putstr_fd(line, tmp_file);
		free(line);
	}
	tmp_file = open("tmp_file.txt", O_RDONLY);
	custom_dup2(tmp_file, "STDIN");
	close(tmp_file);
	custom_unlink("tmp_file.txt");
	*i += 3;
}

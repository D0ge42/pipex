#include "libft/libft.h"
#include "pipex.h"
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

/*Function to checks wheter selected files exists
and they're accessible in read/write mode */

int	check_file_existence(char *infile, char *outfile)
{
	if (access(infile, F_OK) != 0)
	{
		perror("Input file does not exists");
		return (0);
	}
	if (access(outfile, F_OK) != 0)
	{
		perror("Output file does not exists");
		return (-2);
	}
	if (!access(infile, F_OK) && !access(infile, F_OK))
	{
		if (access(infile, R_OK) != 0)
		{
			perror("Can't read from input file");
			return (0);
		}
		if (access(outfile, W_OK) != 0)
		{
			perror("Can't write in output file");
			return (0);
		}
	}
	return (1);
}

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
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		args = get_args(av);
		dup2(infile, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		execve(pathfinder(args[0], environ), args, environ);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	*i += 3;
}
/*Function used to get command and relative flags.
Space will be the separator. This way we'll be able to separate
every command by the flags and use them.*/

char	**get_args(char *av)
{
	char	**args;

	if (!av)
		return (NULL);
	args = ft_split(av, ' ');
	if (!args)
		return (NULL);
	return (args);
}

/*Middle childs are handled in a different way. They read from the
previous read end of the pipe and write on the current write end of the pipe.
We'll set fd[0] to be the new stdin.
We'll also set fd[1] to be the new stdout, to make it so data can be read after.*/

void	middle_childs(char *av)
{
	int			fds[2];
	pid_t		pid;
	extern char	**environ;
	char		**args;

	pid = 0;
	args = NULL;
	pipe(fds);
	pid = fork();
	if (pid == 0)
	{
		args = get_args(av);
		dup2(fds[1], STDOUT_FILENO);
		if (access(pathfinder(args[0], environ), F_OK) == -1)
		{
			close(fds[1]);
			exit(1);
		}
		execve(pathfinder(args[0], environ), args, environ);
	}
	dup2(fds[0], STDIN_FILENO);
	close(fds[1]);
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
	pipe(fds);
	pid = fork();
	args = get_args(av);
	if (pid == 0)
	{
		dup2(outfile, STDOUT_FILENO);
		execve(pathfinder(args[0], environ), args, environ);
	}
	while (args[i])
		free(args[i++]);
	free(args);
	close(fds[0]);
	close(fds[1]);
}
int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	heredoc(char *limiter, int ac, int *i)
{
	char	*line;
	int		tmp_file;

	tmp_file = 0;
	line = NULL;
	if (ac < 6)
		return ;
	tmp_file = open("tmp_file.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	limiter = ft_strjoin(limiter, "\n");
	while (1)
	{
		write(1, "here_doc >", 10);
		line = get_next_line(0);
		if (!line)
			return ;
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, tmp_file);
		free(line);
	}
	tmp_file = open("tmp_file.txt", O_RDONLY | O_APPEND);
	free(limiter);
	dup2(tmp_file, STDIN_FILENO);
	close(tmp_file);
	unlink("tmp_file.txt");
	*i += 3;
}
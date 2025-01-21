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
void	first_child(int infile, char *av)
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
	dup2(infile,STDIN_FILENO);
}

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
	dup2(fds[0],STDIN_FILENO);
	close(fds[1]);
}

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
		execve(pathfinder(args[0],environ), args, environ);
	}
	while (args[i])
		free(args[i++]);
	free(args);
	close(fds[0]);
	close(fds[1]);
}

void	heredoc(char *limiter, int ac)
{
	char	*line;
	int		tmp_file;
	size_t	line_len;

	tmp_file = 0;
	line = NULL;
	if (ac < 6)
		return ;
	tmp_file = open("tmp_file.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(tmp_file, STDOUT_FILENO);
	while (1)
	{
		line = get_next_line(0);
		line_len = ft_strlen(line);
		if (line_len > 0 && line[line_len - 1] == '\n')
			line[line_len - 1] = '\0';
		if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
		{
			free(line);
			break ;
		}
		if (line == NULL)
			break;
		write(tmp_file, line, ft_strlen(line));
	}
	tmp_file = open("tmp_file.txt", O_WRONLY);
	dup2(tmp_file,STDIN_FILENO);
	close(tmp_file);
	unlink("tmp_file.txt");
}

// void pipe_creator(int pipefd[2])
// {
//     pid_t pid;
//     pid = fork();
//     char write_msg[] = "Hello from writer";
//     char read_msg[50];
//     if (pid == 0) //Processo figlio
//     {
//         close(pipefd[1]);
//         read(pipefd[0],read_msg,sizeof(read_msg));
//         ft_printf("Child read: %s\n", read_msg);
//     }
//     else
//     {
//         close(pipefd[0]);
//         write(pipefd[1],write_msg,ft_strlen(write_msg)+ 1);
//         close(pipefd[1]);
//     }
//     return (0);
// }
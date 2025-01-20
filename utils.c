#include "libft/libft.h"
#include "pipex.h"

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
int	first_child(int infile, char *av)
{
	pid_t		pid;
	extern char	**environ;
	int			fd[2];
	char		**args;

	// Handle Error
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(infile, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		args = get_args(av);
        
		execve(pathfinder(args[0], environ), args, environ);
	}
    close(fd[1]);
    return fd[0];
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

int	middle_childs(int fd, char *av)
{
	int			fds[2];
	pid_t		pid;
	extern char	**environ;
	char		**args;

	// Leggo dalla fd[0] della pipe precedente.
	// Scrivo nella fd[1] della pipe corrente.
	// Repeat
	pipe(fds);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd, STDIN_FILENO);
		dup2(fds[1], STDOUT_FILENO);
		args = get_args(av);
        if (access(pathfinder(args[0],environ),F_OK) == -1)
        {
            close(fds[1]);
            exit(1);
        }
		execve(pathfinder(args[0], environ), args, environ);
	}
    close(fds[1]);
	return fds[0];
}

// int	last_child(int outfile)
// {
// 	pid_t	pid;
// 	int		fd[2];

// 	pipe(fd);
// 	// Handle Error
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		dup2(fd[1], STDOUT_FILENO);
// 		dup2(outfile, STDOUT_FILENO);
// 		// Exec command
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		dup2(fd[0], STDIN_FILENO);
// 		waitpid(pid, NULL, 0);
// 	}
// }

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
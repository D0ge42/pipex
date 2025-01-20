#include "libft/libft.h"
#include "pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

/*Function to checks wheter selected files exists
and they're accessible in read/write mode */

int	check_file_existence(char *infile, char *outfile)
{

	if (access(infile, F_OK) == -1)
		perror("Input file does not exists");
	if (access(infile, R_OK) == -1)
	{
		perror("Can't read from input file");
		return (0);
	}
	if (access(outfile, W_OK) == -1)
	{
        perror("Can't write to output file");
        return 0;
	}
	return (1);
}

void first_child(int infile)
{
	pid_t pid;
	int fd[2];
	
	//Handle Error

	pipe(fd);

	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(infile,STDIN_FILENO);
		dup2(fd[1],STDOUT_FILENO);
		//Exec command
	}
	else
	{
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

char **get_args(char *av)
{
	if(!av)
		return NULL;
	char **args = ft_split(av,' ');
	if(!args)
		return NULL;
	return args;
}

void middle_childs()
{
	pid_t pid;
	int fd[2];

	pipe(fd);

	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1],STDOUT_FILENO);
		//exec
	}
	else
	{
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
	}
}

void last_child(int outfile)
{
	pid_t pid;
	int fd[2];

	pipe(fd);
	
	//Handle Error

	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1],STDOUT_FILENO);
		dup2(outfile,STDOUT_FILENO);
		//Exec command
	}
	else
	{
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

// void execute(char **av, char **env)
// {
//     char **cmd = ft_split(av,' ');

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
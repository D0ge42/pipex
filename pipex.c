#include "libft/libft.h"
#include "pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>

/*Function to check wheter the command exists or not
We'll check for the word PATH= which means env variables are set.
Once we find it, we can skip 5 chars and do split to get every path as word
If access return 0,
	it means the current command is present in given path and we can return and free
else we go to the next iteration*/

void	free_paths(char **path)
{
	int	i;

	i = -1;
	while (path[++i] != NULL && path)
		free(path[i]);
	if (path)
		free(path);
}

char	*pathfinder(const char *cmd, char **env)
{
	char		**path;
	int			i;
	char		*return_path;
	size_t		len;

	i = 0;
	while (!ft_strnstr((*env), "PATH=", 5))
		env++;
	path = ft_split(*env + 5, ':');
	while (path[i] && path)
	{
		len = ft_strlen((char *)cmd) + ft_strlen(path[i]) + 2;
		return_path = malloc(sizeof(char) * (len));
		ft_memset(return_path, '\0', len);
		ft_strlcat(return_path, path[i], len);
		return_path[ft_strlen(path[i++])] = '/';
		ft_strlcat(return_path, cmd, len);
		if (access(return_path, F_OK) == 0)
			break ;
		free(return_path);
	}
	if (!path[i])
		return_path = ft_strdup("");
	free_paths(path);
	return (return_path);
}

int	main(int ac, char **av,char **env)
{
	(void)ac;
	int fd[2];
	int infile = open(av[1],O_RDONLY);
	int outfile = open(av[ac - 1],O_WRONLY | O_CREAT | O_TRUNC, 0644);
	int result = check_file_existence(av[1], av[ac - 1]);
	
	//int command_count = ac - 2;
	if(result == 1)
	{

		pipe(fd);
		pid_t pid = fork();

		if (pid == 0)
		{
			// grep hello
			close(fd[0]);
			dup2(infile,STDIN_FILENO);
			dup2(fd[1],STDOUT_FILENO);
			char **args_0 = get_args(av[2]);
			execve(pathfinder(args_0[0],env),args_0,env);
			close(fd[1]);
		}
		else 
		{
			// wc -w
			close(fd[1]);
			dup2(fd[0],STDIN_FILENO);
			dup2(outfile,STDOUT_FILENO);
			char **args_1 = get_args(av[3]);
			execve(pathfinder(args_1[0],env), args_1,env);
			close(fd[0]);
		}
	}
}

	// Creo pipe per poter scrivere alla read e write end of the pipe.
	// La pipe 0 legge da infile, e scrive in pipe0
	// pipe 1 reads from  pipe0 and writes  in outfile
	// We'll need 1 pipe each 2 commands

	// At this point we're ready to fork the main process and create childs.
	// Each child will handle a different command.

	// We'll have to configure each file descriptor inside each child with dup2();
	// Basically if there's only one command it will be something like
	// dup2(fd[0],stdin) --> to redirect stdin to infile.
	// This mean that will be reading from file rather than from stdin.
	// dup2(fd[1],stdout) --> to redirect stdout to outfile.
	// This mean that we won't be redirecting our output to stdout,but instead to outfile.

	// Once fds are set we can start executing commands on the respective file descriptors.
	// Commands will be executed on specified fd rather than on the stdout

	//Handle heredoc
	//If we find here_doc string as first argument we must handle it with gnl.
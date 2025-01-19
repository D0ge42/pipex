#include "libft/libft.h"
#include "pipex.h"

/*Function to check wheter the command exists or not
We'll check for the word PATH= which means env variables are set.
Once we find it, we can skip 5 chars and do split to get every path as word
If access return 0, it means the current command is present in given path and we can return and free
else we go to the next iteration*/

void free_paths(char **path)
{
    int i;
    i = -1;

    while(path[++i] != NULL && path)
        free(path[i]);
    if(path)
        free(path);
}

char	*pathfinder(const char *cmd, char **env)
{
	char	**path;
	int		i;
	char	*return_path;
	size_t	len;

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

/*Waitpid works like that. If WNOHANG Flags is present
it means that parent won-t wait for children to end its process. 
It will return 0 if when the process reach waitpid call the children process is not dead yet.

By using sleep 1 we'll be able to give enough time to children process to die. This way pid
won't be 0, but it will be > 0 and it will enter a different if statement.*/

int	main()
{
    pid_t pid;
    int pipefd[2];
    pipe(pipefd);

    pid = fork();
    int status;

    char write_msg[] = "Hello from writer";
    char read_msg[300];
    if (pid == 0) //Child
    {
        close(pipefd[0]);
        write(pipefd[1],write_msg,ft_strlen(write_msg) + 1);
        close(pipefd[1]);
    }
    else
    {
        close(pipefd[1]);
        sleep(1); 
        pid_t result = waitpid(pid,&status,WNOHANG);
        ft_printf("RESULT OF WAITPID = %i\n",result);
        if (result == 0)
            printf("Il figlio non è ancora terminato, continuo a fare altro");
        else
        {
            read(pipefd[0],read_msg,sizeof(read_msg));
            ft_printf("Parent read: %s\n", read_msg);
        }
        close(pipefd[0]);

    }
    return 0;
}
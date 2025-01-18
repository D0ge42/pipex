#include "libft/libft.h"
#include "pipex.h"
#include <unistd.h>

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

int	main(int ac, const char **av, char **env)
{
	(void)ac;
	// check_existence(av[1],av[2]);
	char *str = pathfinder(av[1], env);
	ft_printf("%s\n", str);
    free(str);
}
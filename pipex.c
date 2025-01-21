#include "libft/libft.h"
#include "pipex.h"

/*Function to check wheter the command exists or not
We'll check for the word PATH= which means env variables are set.
Once we find it, we can skip 5 chars and do split to get every path as word
If access return 0,it means the current command is present in given path 
and we can return and free, else we go to the next iteration*/

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
		if (!return_path)
		{
			free_paths(path);
			exit(EXIT_FAILURE);
		}
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

/*Need to add comments.*/

int	main(int ac, char **av)
{
	int	infile;
	int	outfile;
	int	i;

	infile = 0;
	outfile = 0;
	if ((av[1] && av[ac - 1]))
	{
		infile = open(av[1], O_RDONLY);
		if (ft_strcmp(av[1], "here_doc"))
			outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	i = 0;
	if (!ft_strcmp(av[1], "here_doc"))
		heredoc(av[2], ac, &i);
	else
		first_child(infile, av[2], &i);
	while (i < ac - 2)
		middle_childs(av[i++]);
	parent(outfile, av[i]);
}

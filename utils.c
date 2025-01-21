#include "pipex.h"

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
/* good old strcmp :) */

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	free_paths(char **path)
{
	int	i;

	i = -1;
	while (path[++i] != NULL && path)
		free(path[i]);
	if (path)
		free(path);
}

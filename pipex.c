#include "pipex.h"
#include "libft/libft.h"
#include <cstring>
#include <unistd.h>


/*Check the existence of infile and outfile using F_OK*/

int check_existence(const char *in, const char *out)
{
    if (access(in, F_OK) == 0 && access(out, F_OK) == 0)
    {
        ft_printf("File exists");
        return 1;
    }
    return 0;
}
/*Function to return path of the given command*/
char *pathfinder(char *cmd)
{
    char **path;
    int i = 0;
}

int	main(int ac, char **av)//char **env)
{
    (void)ac;
    check_existence(av[1],av[2]);
}
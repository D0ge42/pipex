# ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>
#include "libft/libft.h"


int check_file_existence(char *infile, char *outfile);
char	*pathfinder(const char *cmd, char **env);
void first_child(int infile, char *av, int *fd);
int *middle_childs(int *fd);
char **get_args(char *av);
#endif
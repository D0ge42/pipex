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
char **get_args(char *av);
void first_child(int infile, char *av);
void middle_childs(char *av);
void parent(int outfile, char *av);
void heredoc(char *limiter, int ac);

#endif
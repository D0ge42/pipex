# ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include "libft/libft.h"



/*Cmd handlers*/

void first_child(int infile, char *av, int *i);
void middle_childs(char *av);
void parent(int outfile, char *av);
void heredoc(char *limiter, int ac, int *i);

/*Utils*/

int ft_strcmp(char *s1, char *s2);
char **get_args(char *av);
char	*pathfinder(const char *cmd, char **env);
void	free_paths(char **path);

/*Error handlers*/

int check_file_existence(char *infile, char *outfile);
void custom_dup2(int fd, char *flag);
void custom_pipe(int fds[2]);
void custom_unlink(char *filepath);
void check_fork(pid_t pid, int wefd, int refd);
void close_fds(int wefd, int refd);

#endif
#include "libft/libft.h"
#include "pipex.h"

/*Function to checks wheter selected files exists
and they're accessible in read/write mode */

int check_file_existence(char *infile,char *outfile)
{
    if(access(infile,F_OK) != 0)
    {
        perror("Input file does not exists");
        return 0;
    }
    if(access(outfile,F_OK) != 0)
    {
        perror("Output file does not exists");
        return 0;
    }
    if (!access(infile,F_OK) && !access(infile,F_OK))
    {
        if(access(infile,R_OK) != 0)
        {
            perror("Can't read from input file");
            return 0;
        }
        if(access(outfile,W_OK) != 0)
        {
            perror("Can't write in output file");
            return 0;
        }
    }
    return 1;
}

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
//     return 0;
// }
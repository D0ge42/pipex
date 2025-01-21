#include "pipex.h"

/*Function to checks wheter selected files exists
and they're accessible in read/write mode */

int	check_file_existence(char *infile, char *outfile)
{
	if (access(infile, F_OK) != 0)
	{
		perror("Input file does not exists");
		exit(EXIT_FAILURE);
	}
	if (access(outfile, F_OK) != 0)
	{
		perror("Output file does not exists");
		exit(EXIT_FAILURE);
	}
	if (!access(infile, F_OK) && !access(infile, F_OK))
	{
		if (access(infile, R_OK) != 0)
		{
			perror("Can't read from input file");
			exit(EXIT_FAILURE);
		}
		if (access(outfile, W_OK) != 0)
		{
			perror("Can't write in output file");
			exit(EXIT_FAILURE);
		}
	}
	return (1);
}

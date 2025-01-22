/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:17:30 by lonulli           #+#    #+#             */
/*   Updated: 2024/12/23 09:17:31 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Function to update stash to the next new line.
It also handle the case where the end of file is reached.
Paramaters: Takes stash and make a new one out of it.
Return value: New stash. */

static char	*update_stash(char *stash)
{
	int		i;
	char	*new_stash;
	int		j;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	if (stash[i] == '\n')
		i += 1;
	j = i;
	while (stash[j])
		j++;
	new_stash = malloc(sizeof(char) * (j - i) + 1);
	if (((j - i) == 0 && !ft_strchr('\n', stash)) || !new_stash)
	{
		free(new_stash);
		return (NULL);
	}
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	return (new_stash);
}

/*Function to calculate lenght of a string until a "\n" is met.
Takes a string as parameter. Return the start of the next line we've to print.
Done by adding +1 to the index where we find the new line.*/

static int	linelen(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i + 1);
}

/*Extract line we'll get the string out of the current stash.
Will also free the old_line
Parameters: String stash, from where we'll extract the line to print.
Old line, which is the old line we've to free.(The buffer where we've used read.
Return values: Line we've to print.*/

char	*extract_line(char *stash, char *old_line)
{
	int		i;
	int		linelenght;
	char	*line;

	free(old_line);
	if (!stash || ft_strlen(stash) == 0)
		return (NULL);
	i = 0;
	if (stash)
		linelenght = linelen(stash);
	else
		linelenght = ft_strlen(stash);
	line = malloc(sizeof(char) * linelenght + 1);
	while (stash[i] != '\n' && stash[i] != '\0')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i] = '\n';
	else
		line[i] = '\0';
	line[i + 1] = '\0';
	return (line);
}

/*Function that will join stash with buffer and also free previous buffer.
Parameters: Old stash, and the buffer to join with the string.
Return values: New stash.*/

static char	*join_and_free(char *stash, char *buf)
{
	char	*temp;

	temp = stash;
	stash = ft_strjoin_gnl(stash, buf);
	free(temp);
	return (stash);
}

/* Workflow of main function:
1) Check for errors before making any read call.
2) Allocate enough space for the line we'll join to the stash at FD index.
3) Initial read call to enter loop.
4) Null terminate current buffer("line") and join it to stash at FD index.
5) When a new line is met we break, else we keep reading.
6) We now have an unique stash from where to extract the line.
7) We updated the new stash by removing until "\n"
8) Free (temp) which is the old stash[fd]. <-- Only made to free last stash call
9) Almost all frees happens inside sub-functions.
10) Return the new line. */

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash[1024];
	int			bytes_read;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = safe_malloc();
	if (!line)
		return (NULL);
	bytes_read = read(fd, line, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		line[bytes_read] = '\0';
		stash[fd] = join_and_free(stash[fd], line);
		if (ft_strchr('\n', line))
			break ;
		bytes_read = read(fd, line, BUFFER_SIZE);
	}
	line = extract_line(stash[fd], line);
	temp = stash[fd];
	stash[fd] = update_stash(stash[fd]);
	free(temp);
	return (line);
}

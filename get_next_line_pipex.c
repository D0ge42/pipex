/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_pipex.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:35:58 by lonulli           #+#    #+#             */
/*   Updated: 2025/01/22 16:35:59 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <time.h>

/*Custom gnl made for pipex. It takes 1 as BUFFER_SIZE
and a pointer to string.
By passing the address of the line (making it a pointer to string)
we can easily  assign it's address to the buffer address.
We'll then free line and job is done.*/

char	*gnl_pipex(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = (char *)malloc(1000000);
	if (!buffer)
		return (NULL);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	return (*line);
}

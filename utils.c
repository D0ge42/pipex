/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:37:06 by lonulli           #+#    #+#             */
/*   Updated: 2025/01/22 16:37:07 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

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
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	free_paths(char **path, char error)
{
	int	i;

	i = -1;
	while (path[++i] != NULL && path)
		free(path[i]);
	if (path)
		free(path);
	if (error == 'Y')
		exit(1);
}

void	free_args(char **args)
{
	int	i;

	i = -1;
	while (args[++i] && args)
		free(args[i]);
	free(args);
}

void	free_and_close(char **args, char *cmd_path, int fds[2], char error)
{
	int	i;

	i = -1;
	if (error == 'Y')
	{
		free(cmd_path);
		free_args(args);
		close_fds(fds[1], fds[0]);
		perror(NULL);
		exit(1);
	}
	else
	{
		while (args[++i])
			free(args[i]);
		free(args);
		close_fds(fds[1], fds[0]);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:17:53 by lonulli           #+#    #+#             */
/*   Updated: 2024/12/23 09:17:54 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Duplicate a given string using malloc.*/

char	*ft_strdup_gnl(const char *str)
{
	int		i;
	char	*new;
	int		len;

	i = 0;
	if (!str)
	{
		new = malloc(sizeof(char));
		*new = '\0';
		return (new);
	}
	len = ft_strlen((char *)str);
	new = malloc(sizeof(char) * len + 1);
	if (!new)
		return (NULL);
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

/*Join 2 strings togheter in a new one, using malloc*/

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*result;
	size_t	s1len;
	size_t	s2len;
	char	*ret;

	if (!s1)
		return (ft_strdup_gnl(s2));
	s1len = ft_strlen((char *)s1);
	s2len = ft_strlen((char *)s2);
	result = (char *)malloc(sizeof(char) * (s1len + s2len + 1));
	if (!result)
		return (NULL);
	ret = result;
	while (*s1)
		*result++ = *s1++;
	while (*s2)
		*result++ = *s2++;
	*result = '\0';
	return (ret);
}

char	*safe_malloc(void)
{
	char	*line;

	line = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	return (line);
}

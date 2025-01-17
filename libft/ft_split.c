/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:16:51 by lorenzo           #+#    #+#             */
/*   Updated: 2024/12/10 16:42:22 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static size_t	count_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			count++;
			while (*s != c && *s != '\0')
				s++;
		}
		else
			s++;
	}
	return (count);
}

static char	*char_skipper(char *s, char c, char x)
{
	if (x == '=')
	{
		while (*s == c && *s)
			s++;
	}
	else if (x == '!')
	{
		while (*s != c && *s)
			s++;
	}
	return (s);
}

char	**ft_split(char const *s, char c)
{
	char	*start;
	int		i;
	int		k;
	char	**phrase;
	size_t	words;

	words = count_words(s, c);
	i = 0;
	phrase = (char **)malloc(sizeof(char *) * (words + 1));
	if (!phrase)
		return (0);
	while (words-- > 0)
	{
		k = 0;
		s = char_skipper((char *)s, c, '=');
		start = (char *)s;
		s = char_skipper((char *)s, c, '!');
		phrase[i] = (char *)malloc(sizeof(char) * ((s - start) + 1));
		while (start < s)
			phrase[i][k++] = *start++;
		phrase[i++][k] = '\0';
	}
	phrase[i] = NULL;
	return (phrase);
}

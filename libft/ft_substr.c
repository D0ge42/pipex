/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:28:18 by lorenzo           #+#    #+#             */
/*   Updated: 2024/12/11 12:13:52 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*rstring;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen((char *)s) || len == 0)
		return (ft_strdup(""));
	if (start + len > ft_strlen((char *)s))
		len = ft_strlen((char *)s) - start;
	i = 0;
	rstring = (char *)malloc(sizeof(char) * (len + 1));
	if (!rstring)
		return (NULL);
	while (len)
	{
		rstring[i] = s[start];
		i++;
		start++;
		len--;
	}
	rstring[i] = '\0';
	return (rstring);
}

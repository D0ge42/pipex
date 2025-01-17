/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:24:08 by lorenzo           #+#    #+#             */
/*   Updated: 2024/08/13 18:44:33 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*calloc(size_t nmemb, size_t size)
{
	void	*array;

	if (nmemb && size && (4294967295U / size <= nmemb))
		return (0);
	array = malloc(sizeof(nmemb * size));
	if (!array)
		return (NULL);
	ft_bzero(array, (nmemb * size));
	return (array);
}

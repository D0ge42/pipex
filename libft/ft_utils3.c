/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:17:22 by lonulli           #+#    #+#             */
/*   Updated: 2025/01/07 09:17:23 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	zero_writer(int zeros, int *count)
{
	if (zeros < 0)
		return ;
	while (zeros)
	{
		ft_putchar_count('0', count);
		zeros--;
	}
}

void	space_writer(int spaces, int *count)
{
	while (spaces)
	{
		ft_putchar_count(' ', count);
		spaces--;
	}
}

void	free_structs(t_format **struct_array, const char *format)
{
	int	i;
	int	struct_count;

	if (!struct_array)
		return ;
	i = 0;
	struct_count = perc_counter('%', format);
	while (i < struct_count)
	{
		free(struct_array[i]);
		i++;
	}
	free(struct_array);
}

void	initialize_struct(t_format *new_s)
{
	new_s->plus = 0;
	new_s->hashtag = 0;
	new_s->minus = 0;
	new_s->space = 0;
	new_s->zero = 0;
	new_s->precision = 0;
	new_s->width = 0;
	new_s->conversion = 0;
}

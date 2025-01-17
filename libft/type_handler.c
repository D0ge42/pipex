/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:18:50 by lonulli           #+#    #+#             */
/*   Updated: 2025/01/07 09:18:51 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Struct to string takes a va_list, the current structure and count
Here the current struct is passed to its respect conversion handler
along with va_list and count.
Everything will then be handled in its respective "container"*/

void	struct_to_string(t_format *new, va_list args, int *count)
{
	if (new->conversion == 's')
		string_handler(new, args, count);
	if (new->conversion == 'c')
		char_handler(new, args, count);
	if (new->conversion == 'i' || new->conversion == 'd')
		int_handler(new, args, count);
	if (new->conversion == 'u')
		uint_handler(new, args, count);
	if (new->conversion == 'X' || new->conversion == 'x')
		hexa_handler(new, args, count);
	if (new->conversion == 'p')
		p_handler(new, args, count);
	if (new->conversion == '%')
		ft_putchar_count('%', count);
}

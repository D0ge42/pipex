/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:16:06 by lonulli           #+#    #+#             */
/*   Updated: 2025/01/07 09:16:08 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*ft_printf workflow
1) Create a struct array. Number of struct depends on number of %
2) Each struct will be filled with specific info of current %.
3) From each struct we'll print the resulting string,
made of different,flags,width,precision and conversion*/

int	ft_printf(const char *format, ...)
{
	int			j;
	int			i;
	int			count;
	va_list		args;
	t_format	**struct_array;

	j = 0;
	i = 0;
	count = 0;
	struct_array = create_struct_array(format);
	va_start(args, format);
	while (format[i] && struct_array)
	{
		if (format[i] == '%')
		{
			struct_to_string(struct_array[j++], args, &count);
			jump_index(format, &i);
		}
		else if (format[i])
			ft_putchar_count(format[i++], &count);
	}
	free_structs(struct_array, format);
	va_end(args);
	return (count);
}

// int main()
// {
// 	ft_printf("HELLO WORLD");
// }
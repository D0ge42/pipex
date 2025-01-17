/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:18:40 by lonulli           #+#    #+#             */
/*   Updated: 2025/01/07 09:18:41 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Takes format string and makes a structure out of it,
	with all the relative info.*/

t_format	*create_struct(const char *format)
{
	t_format	*new;

	new = (t_format *)malloc(sizeof(t_format));
	initialize_struct(new);
	new->width = get_width(format);
	new->precision = get_precision(format);
	get_flags(new, format);
	get_conversion(format, new);
	return (new);
}

/*Creates a struct array out of a format string. Each % is a structure.*/

t_format	**create_struct_array(const char *format)
{
	int			struct_count;
	int			n_struct;
	int			i;
	t_format	**struct_array;

	i = 0;
	n_struct = 0;
	struct_count = 0;
	struct_count = perc_counter('%', format);
	struct_array = (t_format **)malloc(sizeof(t_format *) * struct_count);
	while (format[i])
	{
		if (format[i] == '%')
		{
			struct_array[n_struct] = create_struct(&(format[i]));
			jump_index(format, &i);
			n_struct++;
		}
		else
			i++;
	}
	return (struct_array);
}

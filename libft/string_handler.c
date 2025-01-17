/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:18:34 by lonulli           #+#    #+#             */
/*   Updated: 2025/01/07 09:18:35 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Handle every combination of width/precision for strings. */

void	string_handler(t_format *new, va_list args, int *count)
{
	int		len;
	int		spaces;
	char	*str;

	str = va_arg(args, char *);
	if (str)
		len = ft_strlen(str);
	else
		len = 6;
	if (new->precision == -1 || new->precision == 0)
		spaces = new->width - (len);
	else
		spaces = new->width - new->precision;
	if (new->minus == 0 && spaces > 0)
		space_writer(spaces, count);
	ft_putstr_count(str, count, new, len);
	if (new->minus == 1 && spaces > 0)
		space_writer(spaces, count);
}

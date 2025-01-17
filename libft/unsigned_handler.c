/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:18:58 by lonulli           #+#    #+#             */
/*   Updated: 2025/01/07 09:19:00 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	u_left_padding(t_format *new, unsigned int num, int *count, int spaces)
{
	int	precision;

	precision = new->precision - count_udigits(num);
	if (spaces > 0 && new->minus == 1)
	{
		if (precision > 0)
		{
			while (precision--)
				ft_putchar_count('0', count);
		}
		ft_printunb_count(num, count);
		if (new->zero == 1 && new->precision == 0)
			zero_writer(spaces, count);
		else
			space_writer(spaces, count);
	}
}

void	u_right_padding(t_format *new, unsigned int num, int *count, int spaces)
{
	int	precision;

	precision = new->precision - count_udigits(num);
	if (new->zero == 1 && precision <= 0)
		zero_writer(spaces, count);
	else
		space_writer(spaces, count);
	if (precision > 0)
	{
		while (precision--)
			ft_putchar_count('0', count);
	}
	ft_printunb_count(num, count);
}

void	u_no_padding(t_format *new, unsigned int num, int *count)
{
	int	precision;

	precision = new->precision - count_udigits(num);
	if (precision > 0)
	{
		while (precision--)
			ft_putchar_count('0', count);
	}
	ft_printunb_count(num, count);
}

void	uint_handler(t_format *new, va_list args, int *count)
{
	int	num;
	int	spaces;

	num = va_arg(args, unsigned);
	spaces = new->width - max(count_udigits(num), new->precision);
	if (new->conversion == 'u')
	{
		if (spaces > 0 && new->minus == 0)
			u_right_padding(new, num, count, spaces);
		else if (spaces > 0 && new->minus == 1)
			u_left_padding(new, num, count, spaces);
		else if (spaces <= 0)
			u_no_padding(new, num, count);
	}
}

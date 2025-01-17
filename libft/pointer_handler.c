/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:18:28 by lonulli           #+#    #+#             */
/*   Updated: 2025/01/07 09:18:29 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Handle padding when there's no minus flag and padding*/

void	p_left_padding(t_format *new, unsigned long long num, int *count,
		int spaces)
{
	int	precision;

	precision = new->precision - count_memory_address_length(num);
	precision = 0;
	if (spaces > 0 && new->minus == 1 && num != 0)
	{
		if (precision > 0)
		{
			while (precision--)
				ft_putchar_count('0', count);
		}
		ft_putchar_count('0', count);
		ft_putchar_count('x', count);
		ft_print_pointer(num, count);
		if (new->zero == 1 && new->precision == 0)
			zero_writer(spaces, count);
		else
			space_writer(spaces, count);
	}
}

/*Handle padding when there's minus flag and padding*/

void	p_right_padding(t_format *new, unsigned long long num, int *count,
		int spaces)
{
	int	precision;

	precision = new->precision - count_memory_address_length(num);
	if (new->zero == 1 && precision <= 0)
		zero_writer(spaces, count);
	else
		space_writer(spaces, count);
	if (precision > 0 && num != 0)
	{
		while (precision--)
			ft_putchar_count('0', count);
	}
	if (num != 0)
	{
		ft_putchar_count('0', count);
		ft_putchar_count('x', count);
	}
	ft_print_pointer(num, count);
}

/*Handle conversion when no padding is provided*/

void	p_no_padding(t_format *new, unsigned long long num, int *count)
{
	int	precision;

	precision = new->precision - count_memory_address_length(num);
	if (num != 0)
	{
		ft_putchar_count('0', count);
		ft_putchar_count('x', count);
	}
	if (precision > 0 && num != 0)
	{
		while (precision--)
			ft_putchar_count('0', count);
	}
	ft_print_pointer(num, count);
}

void	p_handler(t_format *new, va_list args, int *count)
{
	unsigned long long	num;
	int					spaces;

	num = va_arg(args, unsigned long long);
	spaces = new->width - max(new->precision, count_memory_address_length(num));
	if (num != 0)
		spaces -= 2;
	if (new->conversion == 'p')
	{
		if (spaces > 0 && new->minus == 0)
			p_right_padding(new, num, count, spaces);
		else if (spaces > 0 && new->minus == 1)
			p_left_padding(new, num, count, spaces);
		else if (spaces <= 0)
			p_no_padding(new, num, count);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:17:51 by lonulli           #+#    #+#             */
/*   Updated: 2025/01/07 09:17:52 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	hashflag(int hastag, char c, int *count, unsigned int num)
{
	if (hastag == 1 && c == 'x' && num != 0)
	{
		ft_putchar_count('0', count);
		ft_putchar_count('x', count);
	}
	if (hastag == 1 && c == 'X' && num != 0)
	{
		ft_putchar_count('0', count);
		ft_putchar_count('X', count);
	}
}

void	hexa_left_padding(t_format *new, unsigned int num, int *count,
		int spaces)
{
	int	precision;

	precision = new->precision - count_hex_digits(num);
	if (spaces > 0 && new->minus == 1)
	{
		if (precision > 0)
		{
			while (precision--)
				ft_putchar_count('0', count);
		}
		hashflag(new->hashtag, new->conversion, count, num);
		if (new->conversion == 'X')
			ft_print_hexa(num, count, 'X');
		else
			ft_print_hexa(num, count, 'x');
		if (new->zero == 1 && new->precision == 0)
			zero_writer(spaces, count);
		else
			space_writer(spaces, count);
	}
}

void	hexa_right_padding(t_format *new, unsigned int num, int *count,
		int spaces)
{
	int	precision;

	precision = new->precision - count_hex_digits(num);
	if (new->zero == 1 && precision <= 0)
		zero_writer(spaces, count);
	else
		space_writer(spaces, count);
	if (precision > 0)
	{
		while (precision--)
			ft_putchar_count('0', count);
	}
	hashflag(new->hashtag, new->conversion, count, num);
	if (new->conversion == 'X')
		ft_print_hexa(num, count, 'X');
	else
		ft_print_hexa(num, count, 'x');
}

void	hexa_no_padding(t_format *new, unsigned int num, int *count)
{
	int	precision;

	precision = new->precision - count_hex_digits(num);
	if (precision > 0)
	{
		while (precision--)
			ft_putchar_count('0', count);
	}
	if (new->conversion == 'X' && new->hashtag == 1 && num != 0)
	{
		ft_putchar_count('0', count);
		ft_putchar_count('X', count);
	}
	if (new->conversion == 'x' && new->hashtag == 1 && num != 0)
	{
		ft_putchar_count('0', count);
		ft_putchar_count('x', count);
	}
	if (new->conversion == 'X')
		ft_print_hexa(num, count, 'X');
	else
		ft_print_hexa(num, count, 'x');
}

void	hexa_handler(t_format *new, va_list args, int *count)
{
	unsigned int	num;
	int				spaces;

	num = va_arg(args, unsigned int);
	spaces = new->width - max(new->precision, count_hex_digits(num));
	if (new->hashtag == 1)
		spaces -= 2;
	if (new->conversion == 'x' || new->conversion == 'X')
	{
		if (spaces > 0 && new->minus == 0)
			hexa_right_padding(new, num, count, spaces);
		else if (spaces > 0 && new->minus == 1)
			hexa_left_padding(new, num, count, spaces);
		else if (spaces <= 0)
			hexa_no_padding(new, num, count);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integers_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:18:13 by lonulli           #+#    #+#             */
/*   Updated: 2025/01/07 09:18:14 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	id_left_padding(t_format *new, long long num, int *count, int spaces)
{
	int	precision;

	precision = new->precision - count_digits(num);
	if (new->space == 1 && !new->plus && num >= 0)
		ft_putchar_count(' ', count);
	if (new->plus == 1 && num >= 0 && new->zero == 1)
		ft_putchar_count('+', count);
	if (num < 0)
	{
		ft_putchar_count('-', count);
		num *= -1;
	}
	if (new->plus == 1 && num >= 0 && new->zero == 0)
		spaces--;
	if (new->zero == 1 && spaces && new->precision == 0)
		zero_writer(spaces, count);
	else
		space_writer(spaces, count);
	if (new->plus == 1 && num >= 0 && new->zero == 0)
		ft_putchar_count('+', count);
	zero_writer(precision, count);
	ft_printnb_count(num, count, new);
}

void	id_right_padding(t_format *new, long long num, int *count, int spaces)
{
	int	precision;

	if (new->space == 1 && !new->plus && num >= 0)
	{
		ft_putchar_count(' ', count);
		spaces--;
	}
	precision = new->precision - count_digits(num);
	if (new->plus == 1 && num >= 0)
	{
		ft_putchar_count('+', count);
		spaces--;
	}
	if (num < 0)
	{
		ft_putchar_count('-', count);
		num *= -1;
	}
	zero_writer(precision, count);
	ft_printnb_count(num, count, new);
	space_writer(spaces, count);
}

void	id_no_padding(t_format *new, long long num, int *count)
{
	int	precision;

	precision = 0;
	if (new->space == 1 && !new->plus && num >= 0)
		ft_putchar_count(' ', count);
	if (new->precision > count_digits(num))
		precision = new->precision - count_digits(num);
	if (new->plus == 1)
	{
		if (num >= 0)
			ft_putchar_count('+', count);
		else
		{
			ft_putchar_count('-', count);
			num *= -1;
		}
	}
	if (num < 0)
	{
		ft_putchar_count('-', count);
		num *= -1;
	}
	zero_writer(precision, count);
	ft_printnb_count(num, count, new);
}

void	int_handler(t_format *new, va_list args, int *count)
{
	int	spaces;
	int	num;

	num = va_arg(args, int);
	spaces = new->width - max(new->precision, count_digits(num));
	if ((new->plus == 1 && num >= 0 && new->zero == 1) || (new->space == 1
			&& !new->plus && num >= 0))
		spaces--;
	if (num < 0)
		spaces--;
	if (new->precision == -1 && num == 0)
		spaces += 1;
	if (spaces > 0 && new->minus == 1)
		id_right_padding(new, num, count, spaces);
	else if (spaces > 0 && new->minus == 0)
		id_left_padding(new, num, count, spaces);
	else
		id_no_padding(new, num, count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:16:33 by lonulli           #+#    #+#             */
/*   Updated: 2025/01/07 09:16:36 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printnb_count(long long int nb, int *count, t_format *new)
{
	if (nb == 0 && new->precision == -1)
		return ;
	if (nb < 0)
	{
		ft_putchar_count('-', count);
		nb *= -1;
	}
	if (nb > 9)
		ft_printnb_count(nb / 10, count, new);
	ft_putchar_count(nb % 10 + '0', count);
}

void	ft_printunb_count(unsigned int nb, int *count)
{
	if (nb > 9)
		ft_printunb_count(nb / 10, count);
	ft_putchar_count(nb % 10 + '0', count);
}

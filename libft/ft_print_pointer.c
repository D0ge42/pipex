/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:16:48 by lonulli           #+#    #+#             */
/*   Updated: 2025/01/07 09:16:49 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ptr_is_null(void *nb, int *count)
{
	if (!nb)
	{
		ft_putstr("(nil)");
		*count += 5;
		return (1);
	}
	return (0);
}

void	ft_print_pointer(uintptr_t nb, int *count)
{
	char	*lc_hexa_base;

	if (ptr_is_null((void *)nb, count) == 1)
		return ;
	lc_hexa_base = "0123456789abcdef";
	if (nb >= 16)
		ft_print_pointer(nb / 16, count);
	ft_putchar_count(lc_hexa_base[nb % 16], count);
}

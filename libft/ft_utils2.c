/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:17:13 by lonulli           #+#    #+#             */
/*   Updated: 2025/01/07 09:17:14 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_digits(long long num)
{
	int	count;

	count = 0;
	if (num == -2147483648)
		return (10);
	if (num == 0)
		return (1);
	if (num < 0)
		num *= -1;
	while (num > 0)
	{
		count++;
		num /= 10;
	}
	return (count);
}

int	count_udigits(unsigned int num)
{
	int	count;

	count = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		count++;
		num /= 10;
	}
	return (count);
}

int	count_hex_digits(unsigned int num)
{
	int	count;

	count = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		count++;
		num /= 16;
	}
	return (count);
}

int	count_memory_address_length(unsigned long long address)
{
	int	count;

	count = 0;
	if (address == 0)
		return (5);
	while (address > 0)
	{
		count++;
		address /= 16;
	}
	return (count);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:17:45 by lonulli           #+#    #+#             */
/*   Updated: 2025/01/07 09:17:46 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_flag(char c)
{
	if (c == '-' || c == '+' || c == ' ' || c == '#' || c == '0')
		return (1);
	return (0);
}

int	is_conversion(char c)
{
	if (c == '%' || c == 'c' || c == 's' || c == 'd' || c == 'i' || c == 'u'
		|| c == 'x' || c == 'X' || c == 'p')
		return (1);
	return (0);
}

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	perc_counter(char c, const char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (c == str[i] && is_conversion(str[i + 1]))
		{
			count++;
			i += 2;
		}
		else if (c == str[i])
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}

void	jump_index(const char *format, int *i)
{
	if (format[*i] == '%')
		(*i)++;
	while (!is_conversion(format[*i]) && format[*i])
		(*i)++;
	if (is_conversion(format[*i]))
		(*i)++;
}

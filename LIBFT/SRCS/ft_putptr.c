/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:40:09 by abdeel-o          #+#    #+#             */
/*   Updated: 2022/10/19 19:21:02 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putvalue(unsigned long number, char *base, int counter)
{
	if (number >= 16)
	{
		counter += ft_putvalue(number / 16, base, counter);
		counter += ft_putvalue(number % 16, base, counter);
	}
	else
		counter = ft_putchar(base[number]);
	return (counter);
}

int	ft_putptr(void *ptr, char *base, int counter)
{
	long	number;

	number = (unsigned long)ptr;
	ft_putstr("0x");
	counter += ft_putvalue(number, base, counter);
	return (counter + 2);
}

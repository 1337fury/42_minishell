/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pformat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:18:26 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/02/06 09:32:49 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pformat(va_list arg, const char c)
{
	int	counter;

	counter = 0;
	if (c == 'c')
		counter += ft_putchar(va_arg(arg, int));
	else if (c == 's')
		counter += ft_putstr(va_arg(arg, char *));
	else if (c == 'p')
		counter += ft_putptr(va_arg(arg, void *), "0123456789abcdef", counter);
	else if (c == 'd')
		counter += ft_putnbr(va_arg(arg, int), counter);
	else if (c == 'i')
		counter += ft_putnbr(va_arg(arg, int), counter);
	else if (c == 'u')
		counter += ft_putunsigned(va_arg(arg, unsigned int), counter);
	else if (c == 'x')
		counter += ft_put_hexa(va_arg(arg, unsigned int),
				"0123456789abcdef", counter);
	else if (c == 'X')
		counter += ft_put_hexa(va_arg(arg, unsigned int),
				"0123456789ABCDEF", counter);
	else if (c == '%')
		counter += ft_putsign();
	return (counter);
}

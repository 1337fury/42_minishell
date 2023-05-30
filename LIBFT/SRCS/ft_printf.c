/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:35:11 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/02/13 11:24:38 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		counter;

	counter = 0;
	va_start(arg, format);
	while (*format)
	{
		if (*format == '%')
			counter += ft_pformat(arg, *(++format));
		else
			counter += ft_putchar(*format);
		format++;
	}
	va_end(arg);
	return (counter);
}

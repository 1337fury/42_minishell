/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 21:47:38 by abdeel-o          #+#    #+#             */
/*   Updated: 2022/10/18 23:31:53 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n, int counter)
{
	int	number;

	number = n;
	if (number == -2147483648)
	{
		write(1, "-2147483648", 11);
		counter += 11;
		return (counter);
	}
	if (number < 0)
	{
		write(1, "-", 1);
		number = -number;
	}
	if (number <= 9)
		counter = ft_putchar((number + 48));
	else if (number > 9)
	{
		counter += ft_putnbr(number / 10, counter);
		counter += ft_putnbr(number % 10, counter);
	}
	if (n < 0)
		return (counter + 1);
	return (counter);
}

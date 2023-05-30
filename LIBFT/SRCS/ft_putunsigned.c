/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 23:03:05 by abdeel-o          #+#    #+#             */
/*   Updated: 2022/10/19 15:56:52 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunsigned(unsigned int n, int counter)
{
	if (n <= 9)
		counter = ft_putchar((n + 48));
	else if (n > 9)
	{
		counter += ft_putunsigned(n / 10, counter);
		counter += ft_putunsigned(n % 10, counter);
	}
	return (counter);
}
